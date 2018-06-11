#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings) {
  ui->setupUi(this);
}

void Settings::setupSettings() {
  this->ui->workSpinBox->setValue(settings.value("worktime", 25).toInt());
  this->ui->sbreakSpinBox->setValue(settings.value("shortbreak", 5).toInt());
  this->ui->lbreakSpinBox->setValue(settings.value("longbreak", 15).toInt());
  this->ui->earlynotifySpinBox->setValue(
      settings.value("earlyseconds", 60).toInt());
  this->ui->sbreaknumberSpinBox->setValue(
      settings.value("breakcycles", 4).toInt());
  this->ui->autostartCheckBox->setChecked(
      settings.value("autostart", false).toBool());
}

void Settings::closeEvent(QCloseEvent *event) {
  event->ignore();
  this->hide();
}

void Settings::accept() {}

void Settings::done(int r) {}

int Settings::exec() {}

void Settings::open() {}

void Settings::reject() {}

Settings::~Settings() { delete ui; }
