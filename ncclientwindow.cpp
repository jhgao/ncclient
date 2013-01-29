#include "ncclientwindow.h"
#include "ui_ncclientwindow.h"

NCClientWindow::NCClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCClientWindow),
    i_con(0),i_conThread(0),m_isConnected(false),
    i_con2(0),i_conThread2(0),m_isConnected2(false)
{
    ui->setupUi(this);
    connect(ui->pushButton_all_connect, SIGNAL(clicked()),
            ui->pushButton_linkServer, SLOT(click()));
    connect(ui->pushButton_all_connect, SIGNAL(clicked()),
            ui->pushButton_linkServer_2, SLOT(click()));

    initCon();
    initCon2();
    initVideo();

    //find a local ip
    QList<QHostAddress> ipAddressesList;
    QString ipAddress;

    ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    ui->lineEdit_serverAddr_all->setText(ipAddress);
    ui->lineEdit_serverPort_all->setText(QString::number(SERVER_DEFAULT_PORT));
}

NCClientWindow::~NCClientWindow()
{
    if(i_conThread){
        i_conThread->quit();
        i_conThread->wait(20);
    }

    if(i_conThread2){
        i_conThread2->quit();
        i_conThread2->wait(20);
    }

    delete ui;
}

void NCClientWindow::on_pushButton_linkServer_clicked()
{
    if(m_isConnected){
        emit sig_onConAbortCmd();
    }else{
        //new connection

        if(ui->radioButton_protocol_TCP->isChecked()){
            i_con = new Connection(PROTOC_TCP,i_videoBuf);
        }else if(ui->radioButton_protocol_UDP->isChecked()){
            i_con = new Connection(PROTOC_UDP,i_videoBuf);
        }else{
            return;
        }

        connect(i_con, SIGNAL(sig_progressPercent(uint)),
                this, SLOT(updateProgress(uint)));
        connect(i_con, SIGNAL(sig_gotBlockSN(quint32)),
                this, SLOT(onGotBlock(quint32)));
        connect(i_con, SIGNAL(connected()),
                this, SLOT(onConnected()));
        connect(i_con, SIGNAL(disconnected()),
                this, SLOT(onDisconnected()));

        connect(this, SIGNAL(sig_onConAbortCmd()),
                i_con, SLOT(slot_abortWorks()));
        connect(this, SIGNAL(sig_onConConnectToHostCmd(QString,quint16)),
                i_con, SLOT(slot_connectToHost(QString,quint16)));

        //handle connection in another thread
        if( i_conThread){
            i_conThread->quit();
            i_conThread->deleteLater();
        }
        i_conThread = new ExecThread(this);
        i_con->moveToThread(i_conThread);
        i_conThread->start();

        emit sig_onConConnectToHostCmd(
                    ui->lineEdit_serverAddr->text(),
                    (quint16)ui->lineEdit_serverPort->text().toInt());
    }
}

void NCClientWindow::on_pushButton_linkServer_2_clicked()
{

    if(m_isConnected2){
        emit sig_onConAbortCmd2();
    }else{
        //new connection

        if(ui->radioButton_protocol_TCP_2->isChecked()){
            i_con2 = new Connection(PROTOC_TCP,i_videoBuf2);
        }else if(ui->radioButton_protocol_UDP_2->isChecked()){
            i_con2 = new Connection(PROTOC_UDP,i_videoBuf2);
        }else{
            return;
        }

        connect(i_con2, SIGNAL(sig_progressPercent(uint)),
                this, SLOT(updateProgress2(uint)));
        connect(i_con2, SIGNAL(sig_gotBlockSN(quint32)),
                this, SLOT(onGotBlock2(quint32)));
        connect(i_con2, SIGNAL(connected()),
                this, SLOT(onConnected2()));
        connect(i_con2, SIGNAL(disconnected()),
                this, SLOT(onDisconnected2()));

        connect(this, SIGNAL(sig_onConAbortCmd2()),
                i_con2, SLOT(slot_abortWorks()));
        connect(this, SIGNAL(sig_onConConnectToHostCmd2(QString,quint16)),
                i_con2, SLOT(slot_connectToHost(QString,quint16)));
        //handle connection in another thread
        if( i_conThread2){
            i_conThread2->quit();
            i_conThread2->deleteLater();
        }
        i_conThread2 = new ExecThread(this);
        i_con2->moveToThread(i_conThread2);
        i_conThread2->start();

        emit sig_onConConnectToHostCmd2(
                    ui->lineEdit_serverAddr_2->text(),
                    (quint16)ui->lineEdit_serverPort_2->text().toInt());
    }
}

void NCClientWindow::initCon()
{
    /* connection 1 */
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);
    ui->graphicsView->setScene(&i_conScene);

    connect(ui->graphicsView, SIGNAL(sig_resized(QSize)),
            &i_conScene, SLOT(arragneToView(QSize)));
    qDebug() << "initCon() GUI thread " << this->thread();

}

void NCClientWindow::initCon2()
{
    /* connection 2 */
    ui->progressBar_2->setValue(0);
    ui->progressBar_2->setMaximum(100);
    ui->graphicsView_2->setScene(&i_conScene2);

    connect(ui->graphicsView_2, SIGNAL(sig_resized(QSize)),
            &i_conScene2, SLOT(arragneToView(QSize)));

    qDebug() << "initCon2 ()GUI thread " << this->thread();

}


void NCClientWindow::updateProgress(const unsigned int p)
{
    ui->progressBar->setValue(p);

    if( p == 100){
        this->onBufReadyPlay();
    }
}

void NCClientWindow::onGotBlock(const quint32 bsn)
{
    i_conScene.gotBlock(bsn);
}

void NCClientWindow::onConnected()
{
    m_isConnected = true;
    ui->groupBox_server->setDisabled(true);
    ui->groupBox_protocol->setDisabled(true);
    ui->pushButton_linkServer->setText("Disconnect");
}

void NCClientWindow::onDisconnected()
{
    m_isConnected = false;
    ui->groupBox_server->setEnabled(true);
    ui->groupBox_protocol->setEnabled(true);
    ui->pushButton_linkServer->setText("Connect");
}

void NCClientWindow::updateProgress2(const unsigned int p)
{
    ui->progressBar_2->setValue(p);
}

void NCClientWindow::onGotBlock2(const quint32 bsn)
{
    i_conScene2.gotBlock(bsn);
}

void NCClientWindow::onConnected2()
{
    m_isConnected2 = true;
    ui->groupBox_server_2->setDisabled(true);
    ui->groupBox_protocol_2->setDisabled(true);
    ui->pushButton_linkServer_2->setText("Disconnect");
}

void NCClientWindow::onDisconnected2()
{
    m_isConnected2 = false;
    ui->groupBox_server_2->setEnabled(true);
    ui->groupBox_protocol_2->setEnabled(true);
    ui->pushButton_linkServer_2->setText("Connect");
}

void NCClientWindow::onBufReadyPlay()
{
    qDebug() << "NCClientWindow::onConReadyPlay() in";
    ui->videoPlayer->play(Phonon::MediaSource(i_videoBuf));
    qDebug() << "NCClientWindow::onConReadyPlay() out";
}

void NCClientWindow::onBufReadyPlay2()
{
    qDebug() << "NCClientWindow::onConReadyPlay2() in";
    ui->videoPlayer_2->play(Phonon::MediaSource(i_videoBuf));
    qDebug() << "NCClientWindow::onConReadyPlay2() out";
}

void NCClientWindow::on_lineEdit_serverAddr_all_textChanged(const QString &arg1)
{
    ui->lineEdit_serverAddr->setText(arg1);
    ui->lineEdit_serverAddr_2->setText(arg1);
}

void NCClientWindow::on_lineEdit_serverPort_all_textChanged(const QString &arg1)
{
    ui->lineEdit_serverPort->setText(arg1);
    ui->lineEdit_serverPort_2->setText(arg1);
}

void NCClientWindow::initVideo()
{
    qDebug() << "NCClientWindow::initVideo()";
    i_videoBuf = new VideoBuffer(this);
    connect(i_videoBuf, SIGNAL(sig_readyPlay()),
            this, SLOT(onBufReadyPlay()));
    i_videoBuf2 = new VideoBuffer(this);
    connect(i_videoBuf2, SIGNAL(sig_readyPlay()),
            this, SLOT(onBufReadyPlay2()));
}

