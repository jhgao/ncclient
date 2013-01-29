#ifndef VIDEOBUFFER_H
#define VIDEOBUFFER_H

#include <QBuffer>
#include <QReadWriteLock>
#include <QReadLocker>
#include <QWriteLocker>

class VideoBuffer : public QBuffer
{
    Q_OBJECT
public:
    explicit VideoBuffer(QObject *parent = 0);
    void appendBlock(const QByteArray&);
signals:
    void sig_readyPlay();
    
public slots:
private:
    QReadWriteLock i_lock;
    bool i_triggered;
};

#endif // VIDEOBUFFER_H
