#ifndef SETTINGS_H
#define SETTINGS_H

#include <QCloseEvent>
#include <QDialog>
#include <QSettings>

namespace Ui {
class Settings;
}

class Settings : public QDialog {
  Q_OBJECT

signals:
  void terminated();

public:
  explicit Settings(QWidget *parent = 0);
  void accept();
  void done(int r);
  int exec();
  void open();
  void reject();
  ~Settings();

private:
  void closeEvent(QCloseEvent *event);

  QSettings usersettings;
  void setupSettings();
  Ui::Settings *ui;
};

#endif // SETTINGS_H
