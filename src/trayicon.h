#ifndef TRAYICON_H
#define TRAYICON_H

#include "timer.h"
#include <QAction>
#include <QMap>
#include <QMenu>
#include <QSettings>
#include <QSound>
#include <QSystemTrayIcon>
#include <QWidget>

class TrayIcon : public QSystemTrayIcon {
  Q_OBJECT
  Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
public:
  TrayIcon(QWidget *parent = 0);

  enum State { ShortBreak, LongBreak, WorkTime };
  Q_ENUM(State)
  State state() const;

  ~TrayIcon();

signals:
  void stateChanged(State state);

private:
  // Methods
  /**
   * @brief setupTrayIcon
   *      Setup icon for the tray icon and sets the menu
   *
   * Method that is called on the constructor of the class to setup the icon of
   * the trayicon and set the context menu with the property
   */
  void setupTrayIcon();

  /**
   * @brief setupMenu Setup menu with options
   *
   * Method that is called on the constructor of the class thats setups the
   * connections of the menu with the actions: ~Work time ~Short break ~Long
   * break ~Settings ~Quit
   */
  void setupMenu(QWidget *parent);

  /**
   * @brief setupTimer Setup the main timer
   *
   * Instantiate the main timer, depending on the autostart settings, it starts
   * it based on the current cycle
   */
  void setupTimer();

  /**
   * @brief restoreSettings Loads the user settings into the program or set the
   * default values
   */
  void restoreSettings();

  /**
   * @brief setState Set the current state of the timer
   * @param state New state of the timer
   *
   * Sets the property state of the the class which indicates the time to reset
   * the timer to
   */
  void setState(State state);

  /**
   * @brief setupStates Setup the values of the timer statuses
   */
  void setupStates();

  /**
   * @brief tick Runs every time the timer timeouts
   *
   * Updates the visualization of the time, ticks (increments) the ticks
   * property
   */
  void tick();

  /**
   * @brief startWorkTime starts the timer for a work time
   */
  void startWorkTime();

  /**
   * @brief startShortBreak starts the timer for a short break time
   */
  void startShortBreak();

  /**
   * @brief startLongBreak starts the timer for a long time
   */
  void startLongBreak();

  /**
   * @brief openSettings Creates and shows a new instance of the settings dialog
   * window
   */
  void openSettings();

  /**
   * @brief early
   * @return if value of earlySeconds is greater than zero
   */
  bool early();

  /**
   * @brief resetTimerProperties Resets to default values all timer related
   * properties
   * @param resetTicks True by default, send a False value to avoid resetting
   * the ticks
   *
   * Reset to 0 the ticks and the secondElapsed variables and send the signal to
   * reset the timer itself
   */
  void resetTimerProperties(bool resetTicks = true);

  /**
   * @brief checkCurrentTimerItem Checks the current timer state and puts a
   * check mark in the appropriate menu item
   */
  void checkCurrentTimerItem();

  /**
   * @brief switchTimers When a timer ends setup the next appropriate timer
   */
  void switchTimers();

  /**
   * @brief controlsEnabledCheck Check if pause and stop controls should be
   * enabled and enables or disables them
   */
  void controlsEnabledCheck(bool running);

  /**
   * @brief resetCounterView Resets the counter widget text to "00:00"
   */
  void resetCounterView();

  // Properties
  QMenu *trayIconMenu;
  QAction *workTimeMenuItem, *shortBreakMenuItem, *longBreakMenuItem,
      *pauseMenuItem, *stopMenuItem, *settingsMenuItem, *quitMenuItem,
      *showTime;
  Timer *timer;
  QSettings settings;
  State m_state;
  QMap<State, int *> states;
  int work, sbreak, lbreak, sbreakCycles, sbreakCyclesCompleted, earlySeconds,
      ticks, secondsRemaining;
  bool autostart;
};

#endif // TRAYICON_H
