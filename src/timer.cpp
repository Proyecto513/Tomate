#include "timer.h"

Timer::Timer(QObject *parent) : QObject(parent) {
  this->timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &Timer::sendTimeout);
}

void Timer::resetTimer() {
  this->stopTimer();
  this->timer->start(1000);
}

bool Timer::isRunning() { return this->timer->isActive(); }

void Timer::stopTimer() {
  if (this->timer->isActive()) {
    this->timer->stop();
  }
}

void Timer::togglePauseTimer(bool pause) {
  if (pause) {
    this->stopTimer();
  } else {
    this->resetTimer();
  }
}
