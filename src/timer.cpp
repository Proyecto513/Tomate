#include "timer.h"

Timer::Timer(QObject *parent) : QObject(parent) {
  this->timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &Timer::sendTimeout);
}

void Timer::resetTimer() {
  if (this->timer->isActive()) {
    this->timer->stop();
  }
  timer->start(1000);
}

bool Timer::isRunning() { return this->timer->isActive(); }
