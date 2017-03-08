#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //主窗体设置
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //图片姓名QLabel初始化
    for(int i = 0; i < PIC_COUNT; ++i){
        labelPic[i].setParent(ui->frame);
        labelPic[i].setGeometry(H_SPACE * (i+1) + PIC_WIDTH * i,
                                V_SPACE,
                                PIC_WIDTH,
                                PIC_HEIGHT);
        labelPic[i].setStyleSheet("border-width:1px;border-style:solid");
        labelPic[i].setText("picture");
        labelPic[i].show();

        labelName[i].setParent(ui->frame);
        labelName[i].setGeometry(H_SPACE * (i+1) + PIC_WIDTH * i,
                                 V_SPACE*2+PIC_HEIGHT,
                                 NAME_WIDTH,
                                 NAME_HEIGHT);
        labelName[i].setStyleSheet("border-width:1px;border-style:solid");
        labelName[i].setText("name");
        labelName[i].show();
    }

    //frame初始化
    ui->frame->setGeometry(0,
                           TITLE_HEIGHT,
                           (H_SPACE+PIC_WIDTH)*PIC_COUNT+H_SPACE,
                           4*V_SPACE+PIC_HEIGHT+NAME_HEIGHT+BTN_HEIGHT);

    //按钮初始化
    ui->pushBtnStart->resize(BTN_WIDTH,
                             BTN_HEIGHT);

    //主窗体大小调整
    this->resize(ui->frame->width(),
                 TITLE_HEIGHT+ui->frame->height());

    //标题栏
    titleBar = new TitleBar(this, TITLE_HEIGHT);
    titleBar->setStyleSheet("QLabel{font:18px \"黑体\";color:rgb(255,255,255)}");
    titleBar->setTitle(tr("摇号&点名"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
