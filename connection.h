#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QTime>
#include "protocol/packet.h"
#include "protocol/protocoltypes.h"
#include "datahandler.h"

//datahandler & encoders
#include "dhudp/dhudp.h"
#include "dhtcp/dhtcp.h"

class Connection : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Connection(int protocType,
                        QObject *parent = 0);

    VideoBuffer* videoBuffer();
signals:
    void sig_ConnectionFinished(Connection*);
    void sig_progressPercent(uint);
    void sig_gotBlockSN(quint32 sn);
    void sig_bufReadyPlay();

public slots:
    void slot_abortWorks();
    void slot_connectToHost(QString, quint16);

private slots:
    void onControlSktReadyRead();
    void processCMD(const Packet& p);

    void writeOutCMD(quint16 cmd,
                     const QByteArray arg = QByteArray());
    void onConnected();

private:
    QString psCmdDbg(QString cmd, QString arg = QString());
    void processProtocolAck(eProtocTypes type, const QByteArray protocArg);
    quint16 packetSize; //for reading packet
    int i_cmd_counter;

    //protocol ack
    quint16     i_ackProtoc;
    QByteArray     i_ackProtocArg;

    //dh
    DataHandler *i_dh;

    //prtocol type of this connection
    int i_protocType;

    //video buffer ( implemented in DataHandler)
    VideoBuffer* i_videoBuffer;
};

#endif // CONNECTION_H
