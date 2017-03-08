#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QVector>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushBtnExit_clicked();

    void on_pushBtnStart_clicked();

    void on_pushBtnBrowse_clicked();

    void dispLottery();

    void dispCallName();

private:
    Ui::MainWindow *ui;

    QVector<QString> *nameList;

    QString imagePath;

    QTimer *timer;

};

#endif // MAINWINDOW_H
