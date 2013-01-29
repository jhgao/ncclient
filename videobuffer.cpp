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
