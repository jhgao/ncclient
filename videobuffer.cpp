#include "videobuffer.h"
#include <QDebug>
VideoBuffer::VideoBuffer(QObject *parent) :
    QBuffer(parent),i_triggered(false)
{
}

void VideoBuffer::appendBlock(const QByteArray &a)
{
    QReadLocker locker(&i_lock);
    this->buffer().append(a);
//    qDebug() << "VideoBuffer::appendBlock()" << this->buffer().size();
    if(this->buffer().size() > 15000
            && !i_triggered ){
        i_triggered = true;
        emit sig_readyPlay();
    }
}
