#ifndef NCCLIENTWINDOW_H
#define NCCLIENTWINDOW_H

#include <QMainWindow>
#include <phonon>
#include "gui/rcvprogressscene.h"
#include "protocol/protocoltypes.h"
#include "connection.h"
#include "execthread.h"
#include "protocol/ports_define.h"
#include "videobuffer.h"

namespace Ui {
class NCClientWindow;
}

class NCClientWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit NCClientWindow(QWidget *parent = 0);
    ~NCClientWindow();
signals:
    void sig_onConAbortCmd();
    void sig_onConConnectToHostCmd(QString,quint16);

    void sig_onConAbortCmd2();
    void sig_onConConnectToHostCmd2(QString,quint16);
    
private slots:
    void updateProgress(const unsigned int);  // percent
    void onGotBlock(const quint32 bsn); //got block i

    void onConnected();
    void onDisconnected();

    void updateProgress2(const unsigned int);  // percent
    void onGotBlock2(const quint32 bsn); //got block i

    void onConnected2();
    void onDisconnected2();

    void onBufReadyPlay();
    void onBufReadyPlay2();


    void on_pushButton_linkServer_clicked();

    void on_pushButton_linkServer_2_clicked();

    void on_lineEdit_serverAddr_all_textChanged(const QString &arg1);

    void on_lineEdit_serverPort_all_textChanged(const QString &arg1);

private:

    void inline initVideo();
    void inline initCon();
    void inline initCon2();

    Ui::NCClientWindow *ui;
    RcvProgressScene i_conScene;
    RcvProgressScene i_conScene2;
    bool m_isConnected;
    bool m_isConnected2;

    Connection *i_con;
    ExecThread *i_conThread;

    Connection *i_con2;
    ExecThread *i_conThread2;

    VideoBuffer* i_videoBuf;
    VideoBuffer* i_videoBuf2;

    bool triggered;
    bool triggered2;
};

#endif // NCCLIENTWINDOW_H
