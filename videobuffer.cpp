#include "videobuffer.h"
#include <QDebug>
VideoBuffer::VideoBuffer(QObject *parent) :
    QBuffer(parent),i_triggered(false)
{
}

void VideoBuffer::waitForAppendBlock(const QByteArray &a)
{
//    qDebug() << "VideoBuffer::waitForAppendBlock()";
    QWriteLocker locker(&i_lock);
    this->buffer().append(a);
}

qint64 VideoBuffer::waitForSize()
{
    QReadLocker locker(&i_lock);
    return this->size();
}

bool VideoBuffer::isSequential()
{
    return true;
}

bool VideoBuffer::atEnd() const
{
    QReadLocker locket(const_cast<QReadWriteLock*>(&i_lock));
    return QBuffer::atEnd();
}

bool VideoBuffer::canReadLine() const
{
    QReadLocker locket(const_cast<QReadWriteLock*>(&i_lock));
    return QBuffer::canReadLine();
}

void VideoBuffer::close()
{
    QWriteLocker locket(&i_lock);
    return QBuffer::close();
}

bool VideoBuffer::open(QIODevice::OpenMode flags)
{
    QWriteLocker locket(&i_lock);
    return QBuffer::open(flags);
}

qint64 VideoBuffer::pos() const
{
    QReadLocker locket(const_cast<QReadWriteLock*>(&i_lock));
    return QBuffer::pos();
}

bool VideoBuffer::seek(qint64 pos)
{
    QWriteLocker locket(&i_lock);
    return QBuffer::seek(pos);
}

qint64 VideoBuffer::size() const
{
    QReadLocker locket(const_cast<QReadWriteLock*>(&i_lock));
    return QBuffer::size();
}


void VideoBuffer::onDecodDone()
{
    emit sig_readyPlay();
}
