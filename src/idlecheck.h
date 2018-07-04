#ifndef IDLECHECK_H
#define IDLECHECK_H

#include <QDebug>
#include <QObject>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <X11/extensions/scrnsaver.h>
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted

class IdleCheck : public QObject {
  Q_OBJECT
public:
  explicit IdleCheck(QObject *parent = nullptr);
  bool isIdle();
  void check();

private:
  Display *dpy;
  XScreenSaverInfo *ssi;
  int event_basep, error_basep;
  bool _idle;
  void setIdle(bool status);

  ~IdleCheck();
signals:
  void idleChanged(bool);

public slots:
};

#endif // IDLECHECK_H
