#include "ncclientwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NCClientWindow w;
    w.show();
    
    return a.exec();
}
