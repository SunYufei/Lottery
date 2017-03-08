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
#include "titlebar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /***** 常量 *****/

    //软件名称
    const QString TITLE = "摇号点名大师 2.0";

    //标题栏高度
    const int TITLE_HEIGHT = 40;

    //图片总数与显示数量
    const int MAX_COUNT = 5;
    int _count;

    //横向、纵向间隔
    const int H_SPACE = 20;
    const int V_SPACE = 20;

    //图片大小
    const int PIC_WIDTH = 198;
    const int PIC_HEIGHT = 275;

    //姓名条大小
    const int NAME_WIDTH = PIC_WIDTH;
    const int NAME_HEIGHT = 50;

    //GroupBox Width
    const int GROUP_BOX_WIDTH = NAME_WIDTH;

    //开始停止按钮大小
    const int BTN_WIDTH = GROUP_BOX_WIDTH - 2 * H_SPACE;
    const int BTN_HEIGHT = NAME_HEIGHT;

    //模式切换按钮大小
    const int SWITCH_WIDTH = BTN_WIDTH;
    const int SWITCH_HEIGHT = BTN_HEIGHT / 5 * 3;

    //GroupBox1 Height
    const int GROUP_1_HEIGHT = BTN_HEIGHT + \
                               SWITCH_HEIGHT + \
                               3 * V_SPACE;

    //文件名大小
    const int FILE_WIDTH = BTN_WIDTH;
    const int FILE_HEIGHT = 30;

    //浏览按钮大小
    const int BROWSE_WIDTH = BTN_WIDTH;
    const int BROWSE_HEIGHT = SWITCH_HEIGHT;

    //GroupBox2 Height
    const int GROUP_2_HEIGHT = FILE_HEIGHT + \
                               BROWSE_HEIGHT + \
                               3 * V_SPACE;

    /***** 所需控件 *****/

    //标题栏
    TitleBar *titleBar;

    //图片控件
    QLabel *labelPic;

    //姓名控件
    QLabel *labelName;

    //计时器
    QTimer *timerShow;

    //动画效果
    QPropertyAnimation *animation;

    /***** 其他存储 *****/

    //图片所在文件夹
    QString imageFolder;

    //名单
    QVector<QString> *nameList;
    QVector<QString> *imageList;

    /***** 私有函数 *****/

    //指定数量随机数
    void getRands(int array[], const int range, const int count);
private slots:

    //显示图片姓名，与timerShow绑定
    void dispWinner();

    //改变窗体大小位置
    void changeSize(int w, int h);

    void on_pushBtnStart_clicked();

    void on_pushBtnSwitch_clicked();

    void on_pushBtnBrowse_clicked();

protected:
    //窗体大小改变事件
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
