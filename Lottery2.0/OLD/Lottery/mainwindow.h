#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//窗体移动
#include <QPoint>
#include <QMouseEvent>
//图片姓名
#include <QLabel>
//文件
#include <QFile>
#include <QTextStream>
//文件选择对话框
#include <QFileDialog>
//自定义标题栏
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

    //图片数量
    static const int PIC_COUNT = 1;

    //图片QLabel
    QLabel labelPic[PIC_COUNT];

    //姓名QLabel
    QLabel labelName[PIC_COUNT];

    //水平垂直间距
    static const int H_SPACE = 20;
    static const int V_SPACE = 20;

    //标题栏高度
    static const int TITLE_HEIGHT = 130;

    //图片大小
    static const int PIC_HEIGHT = 240;
    static const int PIC_WIDTH = 180;

    //姓名大小
    static const int NAME_HEIGHT = 50;
    static const int NAME_WIDTH = PIC_WIDTH;

    //按钮大小
    static const int BTN_HEIGHT = 50;
    static const int BTN_WIDTH = PIC_WIDTH;

    //TitleBar
    TitleBar *titleBar;
};

#endif // MAINWINDOW_H
