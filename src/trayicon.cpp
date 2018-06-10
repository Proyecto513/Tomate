#include "trayicon.h"
#include <QCoreApplication>
#include <QIcon>
#include <QPixmap>

TrayIcon::TrayIcon(QWidget *parent) : QSystemTrayIcon(parent) {
  this->autostart = false;
  restoreSettings();
  setupTimer();
  setupMenu(parent);
  setupTrayIcon();
}

void TrayIcon::restoreSettings() {
  this->work = settings.value("worktime", 25).toInt();
  this->sbreak = settings.value("shortbreak", 5).toInt();
  this->lbreak = settings.value("longbreak", 15).toInt();
  this->earlySeconds = settings.value("earlyseconds", 60).toInt();
  this->sbreakCycles = settings.value("breakcycles", 4).toInt();
  this->early = settings.value("early", true).toBool();
  this->autostart = settings.value("autostart", false).toBool();
}

void TrayIcon::setupTimer() { timer = new QTimer(this); }

void TrayIcon::setupMenu(QWidget *parent) {
  trayIconMenu = new QMenu(parent);
  QIcon::fromTheme("media-playback-pause"),
      workTimeMenuItem = new QAction(tr("Work time"), this);
  trayIconMenu->addAction(workTimeMenuItem);

  shortBreakMenuItem = new QAction(tr("Short break"), this);
  trayIconMenu->addAction(shortBreakMenuItem);

  longBreakMenuItem = new QAction(tr("Long break"), this);
  trayIconMenu->addAction(longBreakMenuItem);

  trayIconMenu->addSeparator();

  pauseMenuItem =
      new QAction(QIcon::fromTheme("media-playback-pause"), tr("Pause"), this);
  pauseMenuItem->setEnabled(this->autostart);
  trayIconMenu->addAction(pauseMenuItem);

  stopMenuItem =
      new QAction(QIcon::fromTheme("media-playback-stop"), tr("Stop"), this);
  stopMenuItem->setEnabled(this->autostart);
  trayIconMenu->addAction(stopMenuItem);

  trayIconMenu->addSeparator();

  settingsMenuItem =
      new QAction(QIcon::fromTheme("preferences-other"), tr("Settings"), this);
  trayIconMenu->addAction(settingsMenuItem);

  quitMenuItem =
      new QAction(QIcon::fromTheme("application-exit"), tr("Quit"), this);
  connect(quitMenuItem, &QAction::triggered, this, &QCoreApplication::quit);
  trayIconMenu->addAction(quitMenuItem);
}

void TrayIcon::setupTrayIcon() {
  this->setIcon(
      QIcon::fromTheme("tomate", QPixmap(":/icons/src/assets/tomate.svg")));
  this->setContextMenu(trayIconMenu);
}

TrayIcon::~TrayIcon() {}
