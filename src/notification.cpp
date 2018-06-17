#include "notification.h"
#include <QApplication>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>

Notification::Notification(QObject *parent) : QObject(parent) {
  interface =
      new QDBusInterface(QStringLiteral("org.freedesktop.Notifications"),
                         QStringLiteral("/org/freedesktop/Notifications"),
                         QStringLiteral("org.freedesktop.Notifications"),
                         QDBusConnection::sessionBus(), this);
}

void Notification::sendMessage(const QString &text) {
  sendMessage(text, tr("Tomate info"));
}

void Notification::sendMessage(const QString &text, const QString &title,
                               const int timeout) {
  QList<QVariant> args;
  args << (qAppName()) << static_cast<unsigned int>(0) << "tomate" << title
       << text << QStringList() << QVariantMap() << timeout;
  interface->callWithArgumentList(QDBus::AutoDetect, "Notify", args);
}
