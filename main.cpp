#include "mainwindow.h"
#include "app.h"
int main(int argc, char *argv[])
{
    App a(argc, argv,"","BH");
    MainWindow w;
    w.setWindowIcon(QIcon(":/images/logo.png"));
    w.show();

    return a.exec();
}
