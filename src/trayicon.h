#ifndef TRAYICON_H
#define TRAYICON_H

#include <QAction>
#include <QMenu>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QWidget>

class TrayIcon : public QSystemTrayIcon {
  Q_OBJECT

public:
  TrayIcon(QWidget *parent = 0);
  ~TrayIcon();

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
   * @brief setupMenu
   *    Setup menu with options
   *
   * Method that is called on the constructor of the class thats setups the
   * connections of the menu with the actions: ~Work time ~Short break ~Long
   * break ~Settings ~Quit
   */
  void setupMenu(QWidget *parent);

  /**
   * @brief setupTimer
   *    Setup the main timer
   *
   * Instantiate the main timer, depending on the autostart settings, it starts
   * it based on the current cycle
   */
  void setupTimer();

  /**
   * @brief restoreSettings
   *    Loads the user settings into the program or set the default values
   */
  void restoreSettings();

  // Properties
  QMenu *trayIconMenu;
  QAction *workTimeMenuItem, *shortBreakMenuItem, *longBreakMenuItem,
      *pauseMenuItem, *stopMenuItem, *settingsMenuItem, *quitMenuItem;
  QTimer *timer;
  QSettings settings;
  int work, sbreak, lbreak, sbreakCycles, earlySeconds;
  bool early, autostart;
};

#endif // TRAYICON_H
