#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer : public QObject {
  Q_OBJECT
public:
  Timer(QObject *parent);
  /**
   * @brief Checks if the timer is running, if it is it resets with new values
   */
  void resetTimer();

  /**
   * @brief isRunning Indicates if the underlying timer is running
   * @return timer->isActive()
   */
  bool isRunning();

signals:
  void timeout();

private:
  QTimer *timer;
  void sendTimeout() { emit timeout(); }
};

#endif // TIMER_H
