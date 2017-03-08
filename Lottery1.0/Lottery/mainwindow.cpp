#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nameList = new QVector<QString>;
    //禁用开始按钮
    ui->pushBtnStart->setEnabled(false);
    //禁用图片在QLabel伸展
    ui->labelPixmap->setScaledContents(false);
    //设置计时器参数
    timer = new QTimer();
    timer->setInterval(100);
    //随机数种子
    qsrand(QTime::currentTime().msec());
}

MainWindow::~MainWindow(){
    delete ui;
    delete nameList;
    delete timer;
}

void MainWindow::on_pushBtnExit_clicked(){
    this->close();
}

void MainWindow::on_pushBtnStart_clicked()
{
    //绑定Interval事件
    if(ui->radioBtnLottery->isChecked() == true){
        connect(timer, SIGNAL(timeout()), this, SLOT(dispLottery()));
    }
    else{
        connect(timer, SIGNAL(timeout()), this, SLOT(dispCallName()));
    }
    //按钮文本转换及计时器开关
    if (ui->pushBtnStart->text() == tr("开始")) {
        ui->pushBtnStart->setText(tr("停止"));
        timer->start();
    }
    else if (ui->pushBtnStart->text() == tr("停止")) {
        ui->pushBtnStart->setText(tr("开始"));
        timer->stop();
    }
}

void MainWindow::on_pushBtnBrowse_clicked(){
    //打开文件对话框
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("打开文件"),
                                                "",
                                                tr("文本文档(*.txt)"));
    //窗口控件显示文件目录
    ui->lineEdit->setText(path);
    nameList->clear();
    //打开文件
    QFile *file = new QFile(path);
    if(file->open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(file);
        while(!stream.atEnd()){
            nameList->append(stream.readLine());
        }
        file->close();
        //文件为空判断
        if(!nameList->empty()){
            ui->pushBtnStart->setEnabled(true);
        }
        else{
            QMessageBox::information(this,
                                     tr("提示信息"),
                                     tr("名单文件为空"),
                                     QMessageBox::Ok);
            ui->pushBtnStart->setEnabled(false);
        }
    }
    //设置图片路径
    int n = 0;
    for(int i = 0; i < path.length(); ++i){
        if(path[i]=='/'){
            n = i;
        }
    }
    imagePath = path.left(n + 1);
}

void MainWindow::dispLottery(){
    bool isImage = true;
    QString image;
    //获胜者代号
    int winner = (qrand()%(nameList->size()));
    //获胜者姓名
    ui->labelWinner->setText((*nameList)[winner]);
    //获胜者图片路径
    image = imagePath + (*nameList)[winner];
    //判断是否有匹配图片
    if(!QFile(image + ".jpg").open(QIODevice::ReadOnly)){
        if(!QFile(image + ".png").open(QIODevice::ReadOnly)){
            isImage = false;
        }
        else{
            image += ".png";
        }
    }
    else{
        image += ".jpg";
    }
    //找到图片，进行显示
    if(isImage == true){
        QPixmap pic = QPixmap(image);
        //图片太大，进行缩放
        if(pic.width() > ui->labelPixmap->width() || pic.width() > ui->labelPixmap->height()) {
            pic = pic.scaled(ui->labelPixmap->size(),
                             Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
        }
        //显示图片
        ui->labelPixmap->setPixmap(pic);
    }
    //未找到图片，提示信息
    else{
        ui->labelPixmap->setText(tr("未找到图片"));
    }
}

void MainWindow::dispCallName(){
    ui->labelWinner->setText("");
    if(nameList->size() >= 5){
        //产生5个不同随机数
        int a[5], t, i, j;
        for(i = 0; i < 5; ++i){
            t = qrand()%(nameList->size());
            for(j = 0; j < i; ++j){
                if(a[j] == t)
                    break;
            }
            if(j < i){
                --i;
                continue;
            }
            a[i] = t;
        }
        //显示姓名
        QString name;
        for(i = 0; i < 5; ++i){
            name += (*nameList)[a[i]];
            if(i % 2 != 0) name += "\n";
            else if( i != 4) name += "  ";
        }
        ui->labelPixmap->setText(name);
    }
    else{
        ui->labelPixmap->setText(tr("列表人数 < 5"));
    }
}
