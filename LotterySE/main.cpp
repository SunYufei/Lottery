#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":image/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    QTime t;
    t.start();
    while(t.elapsed() <= 3000);

    MainWindow w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
