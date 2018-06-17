#include "trayicon.h"
#include "settings.h"
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QIcon>
#include <QPixmap>

TrayIcon::TrayIcon(QWidget *parent) : QSystemTrayIcon(parent) {
  this->autostart = false;
  this->ticks = 0;
  this->secondsRemaining = 0;
  this->sbreakCyclesCompleted = 0;
  this->m_state = State::WorkTime;
  this->notificationService = new Notification;
  restoreSettings();
  setupStates();
  setupTimer();
  setupMenu(parent);
  checkCurrentTimerItem();
  setupTrayIcon();
}

void TrayIcon::restoreSettings() {
  this->work = settings.value("worktime", 25).toInt();
  this->sbreak = settings.value("shortbreak", 5).toInt();
  this->lbreak = settings.value("longbreak", 15).toInt();
  this->earlySeconds = settings.value("earlyseconds", 60).toInt();
  this->sbreakCycles = settings.value("breakcycles", 4).toInt();
  this->autostart = settings.value("autostart", false).toBool();
}

void TrayIcon::setupStates() {
  states[State::ShortBreak] = &this->sbreak;
  states[State::LongBreak] = &this->lbreak;
  states[State::WorkTime] = &this->work;
}

void TrayIcon::setupTimer() {
  timer = new Timer(this);
  connect(timer, &Timer::timeout, this, &TrayIcon::tick);
  if (this->autostart) {
    timer->resetTimer();
  }
}

void TrayIcon::setupMenu(QWidget *parent) {
  trayIconMenu = new QMenu(parent);

  showTime = new QAction("00:00", this);
  showTime->setEnabled(false);
  if (this->autostart) {
    trayIconMenu->addAction(showTime);
  }

  workTimeMenuItem = new QAction(tr("Work time"), this);
  connect(workTimeMenuItem, &QAction::triggered, this,
          &TrayIcon::startWorkTime);
  workTimeMenuItem->setCheckable(true);
  trayIconMenu->addAction(workTimeMenuItem);

  shortBreakMenuItem = new QAction(tr("Short break"), this);
  connect(shortBreakMenuItem, &QAction::triggered, this,
          &TrayIcon::startShortBreak);
  shortBreakMenuItem->setCheckable(true);
  trayIconMenu->addAction(shortBreakMenuItem);

  longBreakMenuItem = new QAction(tr("Long break"), this);
  connect(longBreakMenuItem, &QAction::triggered, this,
          &TrayIcon::startLongBreak);
  longBreakMenuItem->setCheckable(true);
  trayIconMenu->addAction(longBreakMenuItem);

  trayIconMenu->addSeparator();

  pauseMenuItem =
      new QAction(QIcon::fromTheme("media-playback-pause"), tr("Pause"), this);
  pauseMenuItem->setCheckable(true);
  connect(pauseMenuItem, &QAction::toggled, this->timer,
          &Timer::togglePauseTimer);
  pauseMenuItem->setEnabled(this->autostart);
  trayIconMenu->addAction(pauseMenuItem);

  stopMenuItem =
      new QAction(QIcon::fromTheme("media-playback-stop"), tr("Stop"), this);
  connect(stopMenuItem, &QAction::triggered, this->timer, &Timer::stopTimer);
  connect(stopMenuItem, &QAction::triggered, this, &TrayIcon::resetCounterView);
  stopMenuItem->setEnabled(this->autostart);
  trayIconMenu->addAction(stopMenuItem);

  trayIconMenu->addSeparator();

  settingsMenuItem =
      new QAction(QIcon::fromTheme("preferences-other"), tr("Settings"), this);
  connect(settingsMenuItem, &QAction::triggered, this, &TrayIcon::openSettings);
  trayIconMenu->addAction(settingsMenuItem);

  quitMenuItem =
      new QAction(QIcon::fromTheme("application-exit"), tr("Quit"), this);
  connect(quitMenuItem, &QAction::triggered, this, &QCoreApplication::quit);
  trayIconMenu->addAction(quitMenuItem);

  connect(this->timer, &Timer::stateChanged, this,
          &TrayIcon::controlsEnabledCheck);
}

void TrayIcon::tick() {
  secondsRemaining = (*(states[m_state]) * 60) - ticks++;
  if (secondsRemaining == 0) {
    QSound::play(":/sounds/assets/alarm.wav");
    switchTimers();
  }
  showTime->setText(
      QDateTime::fromTime_t(secondsRemaining).toUTC().toString("mm:ss"));
  timer->resetTimer();
}

void TrayIcon::setupTrayIcon() {
  this->setIcon(
      QIcon::fromTheme("tomate", QPixmap(":/icons/assets/tomate-color.svg")));
  this->setContextMenu(trayIconMenu);
}

void TrayIcon::startWorkTime() {
  this->setState(State::WorkTime);
  this->checkCurrentTimerItem();
  this->ticks = 0;
  timer->resetTimer();
}

void TrayIcon::startShortBreak() {
  this->setState(State::ShortBreak);
  this->checkCurrentTimerItem();
  this->ticks = 0;
  timer->resetTimer();
}

void TrayIcon::startLongBreak() {
  this->setState(State::LongBreak);
  this->checkCurrentTimerItem();
  this->ticks = 0;
  timer->resetTimer();
}

void TrayIcon::openSettings() {
  Settings *sw = new Settings();
  sw->show();
}

void TrayIcon::resetTimerProperties(bool resetTicks) {
  if (resetTicks) {
    this->ticks = 0;
  }
}

bool TrayIcon::early() { return this->earlySeconds > 0; }

TrayIcon::State TrayIcon::state() const { return this->m_state; }

void TrayIcon::setState(State state) { this->m_state = state; }

void TrayIcon::checkCurrentTimerItem() {
  workTimeMenuItem->setChecked(false);
  shortBreakMenuItem->setChecked(false);
  longBreakMenuItem->setChecked(false);

  if (!timer->isRunning()) {
    return;
  }

  switch (this->m_state) {
  case TrayIcon::WorkTime:
    workTimeMenuItem->setChecked(true);
    break;
  case TrayIcon::ShortBreak:
    shortBreakMenuItem->setChecked(true);
    break;
  case TrayIcon::LongBreak:
    longBreakMenuItem->setChecked(true);
    break;
  default:
    break;
  }
}

void TrayIcon::switchTimers() {
  if (this->state() == TrayIcon::WorkTime) {
    if (sbreakCyclesCompleted++ == sbreakCycles) {
      sbreakCyclesCompleted = 0;
      notificationService->sendMessage(tr("It's time for a longer break"),
                                       tr("Time is up!"));
      startLongBreak();
    } else {
      notificationService->sendMessage(tr("It's time for a little break"),
                                       tr("Time is up!"));
      startShortBreak();
    }
  } else {
    notificationService->sendMessage(tr("It's time to go back to work!"),
                                     tr("Break is over"));
    startWorkTime();
  }
}

void TrayIcon::controlsEnabledCheck(bool running) {
  this->pauseMenuItem->setEnabled(running);
  this->pauseMenuItem->setEnabled(running);
}

void TrayIcon::resetCounterView() {
  showTime->setText("00:00");
  checkCurrentTimerItem();
}

TrayIcon::~TrayIcon() {
  delete timer;
  delete notificationService;
}
