#ifndef SYSTEMNOTIFICATION_H
#define SYSTEMNOTIFICATION_H

#include <QObject>

class QDBusInterface;

class Notification : public QObject {
  Q_OBJECT
public:
  explicit Notification(QObject *parent = nullptr);
  void sendMessage(const QString &text);

  void sendMessage(const QString &text, const QString &title,
                   const int timeout = 5000);
signals:

public slots:

private:
  QDBusInterface *interface;
};

#endif // SYSTEMNOTIFICATION_H
