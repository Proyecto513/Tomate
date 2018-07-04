#include "idlecheck.h"

IdleCheck::IdleCheck(QObject *parent) : QObject(parent) {
  this->setIdle(false);
  dpy = QX11Info::display();
  if (!XScreenSaverQueryExtension(dpy, &event_basep, &error_basep)) {
    dpy = NULL;
    free(dpy);
    throw "screen saver extension not supported";
  }

  ssi = XScreenSaverAllocInfo();
  if (ssi == NULL) {
    dpy = NULL;
    free(dpy);
    XFree(ssi);
    throw "couldn't allocate screen saver info";
  }
}

void IdleCheck::check() {
  if (!XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), ssi)) {
    qDebug() << "couldn't query screen saver info";
  }

  qDebug() << ssi->idle;
  if (ssi->idle > 15 * 60000) {
    setIdle(true);
  } else {
    setIdle(false);
  }
}

void IdleCheck::setIdle(bool status) {
  if (this->_idle != status) {
    this->_idle = status;
    emit idleChanged(this->_idle);
  }
}

long IdleCheck::getIdle() { return ssi->idle; }

bool IdleCheck::isIdle() { return this->_idle; }

IdleCheck::~IdleCheck() {
  XFree(ssi);
  dpy = NULL;
  free(dpy);
}
