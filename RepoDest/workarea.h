#ifndef WORKAREA_H
#define WORKAREA_H

#include <QObject>
#include <QThread>

class WorkArea : public QObject
{
    Q_OBJECT
public:
    explicit WorkArea(QObject *parent = 0);
    void doSetup(QThread &cThread);
    bool i;

private:
    QThread* thread;

signals:

public slots:
    void startReading();
};

#endif // WORKAREA_H
