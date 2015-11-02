#ifndef WORKAREA_H
#define WORKAREA_H

#include <QObject>
#include <QThread>


class WorkArea : public QObject
{
    Q_OBJECT
public:
    explicit WorkArea(QObject *parent = 0);
    void doSetup(QThread* cThread);
    bool i;
    int j;
    QString name;
    QString text;

private:
    QThread* thread;

signals:
    bool done();
    void plainText(const QString &);

public slots:
    void startReading();
};

#endif // WORKAREA_H
