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

  /**
   * @brief stopTimer Stops the timer if its running
   */
  void stopTimer();

  /**
   * @brief togglePauseTimer Starts or stops the timer for a pseudo pause effect
   * @param pause indicates whether the timer is stopped or not
   */
  void togglePauseTimer(bool pause);

signals:
  void timeout();
  void stateChanged(bool running);

private:
  QTimer *timer;
  void sendTimeout() { emit timeout(); }
};

#endif // TIMER_H
