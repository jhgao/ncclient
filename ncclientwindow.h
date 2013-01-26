#ifndef NCCLIENTWINDOW_H
#define NCCLIENTWINDOW_H

#include <QMainWindow>
#include "gui/rcvprogressview.h"

namespace Ui {
class NCClientWindow;
}

class NCClientWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit NCClientWindow(QWidget *parent = 0);
    ~NCClientWindow();
    
private slots:

private:
    Ui::NCClientWindow *ui;
};

#endif // NCCLIENTWINDOW_H
