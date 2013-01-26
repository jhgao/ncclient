#include "ncclientwindow.h"
#include "ui_ncclientwindow.h"

NCClientWindow::NCClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCClientWindow)
{
    ui->setupUi(this);
}

NCClientWindow::~NCClientWindow()
{
    delete ui;
}
