#include "ncclientwindow.h"
#include "ui_ncclientwindow.h"

NCClientWindow::NCClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCClientWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_all_connect, SIGNAL(clicked()),
            ui->pushButton_linkServer, SLOT(click()));
    connect(ui->pushButton_all_connect, SIGNAL(clicked()),
            ui->pushButton_linkServer_2, SLOT(click()));
}

NCClientWindow::~NCClientWindow()
{
    delete ui;
}
