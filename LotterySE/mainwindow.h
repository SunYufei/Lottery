#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QTextStream>
#include <QTime>
#include <QTimer>

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

    void on_pushBtnBrowse_clicked();

    void on_pushBtnStart_clicked();

    void dispWinner();

    void changeSize(const int w, const int h);

private:
    Ui::MainWindow *ui;

    /****** 常量 ******/

    const QString TITLE = "摇号大师 特别版";

    const int TITLE_HEIGHT = 40;

    const int H_SPACE      = 20;
    const int V_SPACE      = 20;

    const int PIC_WIDTH    = 198;
    const int PIC_HEIGHT   = 275;

    const int NAME_WIDTH   = PIC_WIDTH;
    const int NAME_HEIGHT  = 50;

    const int LINE_WIDTH   = PIC_WIDTH;
    const int LINE_HEIGHT  = 30;

    const int BTN_WIDTH    = LINE_WIDTH / 2;
    const int BTN_HEIGHT   = LINE_HEIGHT;

    const int GROUP_WIDTH  = LINE_WIDTH + \
                             BTN_WIDTH + \
                             3 * H_SPACE;
    const int GROUP_HEIGHT = LINE_HEIGHT + \
                             BTN_HEIGHT + \
                             4 * V_SPACE;

    const int MIN_WIDTH    = GROUP_WIDTH + \
                             2 * H_SPACE;
    const int MIN_HEIGHT   = GROUP_HEIGHT + \
                             2 * V_SPACE;

    int MAX_WIDTH = 0;
    const int MAX_HEIGHT   = MIN_HEIGHT + \
                             PIC_HEIGHT + \
                             NAME_HEIGHT + \
                             2 * V_SPACE;

    /****** 变量 ******/

    QString imageFloder;

    QTimer timerShow;

    QPropertyAnimation *animation;

    // 列表
    QVector<QLabel*> vp;
    QVector<QLabel*> vn;
    QVector<QStringList> nameList;

    int rows = 0;
    int columns = 0;

    /****** 成员函数 ******/

    void readFile(const QString path);

    int getRands(const int range);

    void initImage();
    void clearImage();

protected:

    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
