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
    void waitForAppendBlock(const QByteArray&);
    qint64 waitForSize();
    bool isSequential();


     bool	atEnd () const;
     bool	canReadLine () const;
     void	close ();
     bool	open ( OpenMode flags );
     qint64	pos () const;
     bool	seek ( qint64 pos );
     qint64	size () const;

signals:
    void sig_readyPlay();
    
public slots:
    void onDecodDone();
private:
    QReadWriteLock i_lock;
    bool i_triggered;
};

#endif // VIDEOBUFFER_H
