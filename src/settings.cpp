#include "settings.h"
#include "ui_settings.h"
Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings) {
  ui->setupUi(this);
  setupSettings();
}

void Settings::setupSettings() {
  this->ui->workSpinBox->setValue(usersettings.value("worktime", 25).toInt());
  this->ui->sbreakSpinBox->setValue(
      usersettings.value("shortbreak", 5).toInt());
  this->ui->lbreakSpinBox->setValue(
      usersettings.value("longbreak", 15).toInt());
  this->ui->earlynotifySpinBox->setValue(
      usersettings.value("earlyseconds", 60).toInt());
  this->ui->sbreaknumberSpinBox->setValue(
      usersettings.value("breakcycles", 4).toInt());
  this->ui->autostartCheckBox->setChecked(
      usersettings.value("autostart", false).toBool());
}

void Settings::closeEvent(QCloseEvent *event) {
  event->ignore();
  this->hide();
}

void Settings::accept() {
  usersettings.setValue("worktime", this->ui->workSpinBox->value());
  usersettings.setValue("shortbreak", this->ui->sbreakSpinBox->value());
  usersettings.setValue("longbreak", this->ui->lbreakSpinBox->value());
  usersettings.setValue("earlyseconds", this->ui->earlynotifySpinBox->value());
  usersettings.setValue("breakcycles", this->ui->sbreaknumberSpinBox->value());
  usersettings.setValue("autostart", this->ui->autostartCheckBox->isChecked());
  this->hide();
}

void Settings::done(int r) {}

int Settings::exec() { return 0; }

void Settings::open() {}

void Settings::reject() {}

Settings::~Settings() { delete ui; }
