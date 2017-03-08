#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化标题栏
    titleBar = new TitleBar(this, TITLE_HEIGHT);
    titleBar->setTitle(TITLE);
    titleBar->setBackColor("rgb(0,100,180)");
    titleBar->setIcon(QPixmap(":icon/icon.ico"));

    //初始化图片与姓名条
    labelPic = new QLabel[MAX_COUNT]();
    labelName = new QLabel[MAX_COUNT]();
    for(int i = 0; i < MAX_COUNT; ++i){
        labelPic[i].setParent(this);
        labelPic[i].setGeometry((i+1)*H_SPACE+i*PIC_WIDTH,
                                V_SPACE + TITLE_HEIGHT,
                                PIC_WIDTH,
                                PIC_HEIGHT);
        labelPic[i].setAlignment(Qt::AlignCenter);
        labelPic[i].setScaledContents(false);
        labelPic[i].show();
        labelPic[i].setVisible(false);

        labelName[i].setParent(this);
        labelName[i].setGeometry(labelPic[i].x(),
                                 labelPic[i].y()+V_SPACE+PIC_HEIGHT,
                                 NAME_WIDTH,
                                 NAME_HEIGHT);
        labelName[i].setAlignment(Qt::AlignCenter);
        labelName[i].setStyleSheet("font:28px \"楷体\"");
        labelName[i].setVisible(false);
    }

    //初始化开始按钮
    ui->pushBtnStart->setGeometry(H_SPACE, V_SPACE,
                                  BTN_WIDTH, BTN_HEIGHT);
    ui->pushBtnStart->setEnabled(false);

    //初始化模式切换按钮
    ui->pushBtnSwitch->setGeometry(H_SPACE,
                                   BTN_HEIGHT + 2 * V_SPACE,
                                   SWITCH_WIDTH,
                                   SWITCH_HEIGHT);
    ui->pushBtnSwitch->setEnabled(false);

    //初始化文件名文本框

    ui->lineFile->setGeometry(H_SPACE, V_SPACE,
                              FILE_WIDTH, FILE_HEIGHT);

    //初始化浏览按钮
    ui->pushBtnBrowse->setGeometry(H_SPACE,
                                   FILE_HEIGHT + V_SPACE * 2,
                                   BROWSE_WIDTH, BROWSE_HEIGHT);

    //初始化计时器
    timerShow = new QTimer;
    timerShow->setInterval(100);
    connect(timerShow, SIGNAL(timeout()),
            this, SLOT(dispWinner()));

    //初始化窗体
    this->resize(2 * H_SPACE + GROUP_BOX_WIDTH,
                 2 * V_SPACE + GROUP_2_HEIGHT + TITLE_HEIGHT);

    this->setMinimumSize(this->width(), this->height());
    this->setMaximumWidth((MAX_COUNT + 1) * H_SPACE + \
                          MAX_COUNT * PIC_WIDTH);
    this->setMaximumHeight(5 * V_SPACE + \
                           TITLE_HEIGHT + \
                           PIC_HEIGHT + \
                           NAME_HEIGHT + \
                           GROUP_1_HEIGHT + \
                           GROUP_2_HEIGHT);

    this->setWindowFlags(Qt::FramelessWindowHint);

    //初始化动画效果
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(500);

    //初始化名单
    nameList = new QVector<QString>;
    imageList = new QVector<QString>;

    //绑定随机数种子
    qsrand(QTime::currentTime().msec());
}

MainWindow::~MainWindow(){
    delete ui;
    delete titleBar;
    delete[] labelPic;
    delete[] labelName;
    delete timerShow;
    delete nameList;
    delete imageList;
    delete animation;
}

void MainWindow::getRands(int array[], const int range, const int count){
    int t, i, j;
    for(i = 0; i < count; ++i){
        t = qrand()%range;
        for(j = 0; j < i; ++j){
            if(array[j] == t){
                break;
            }
        }
        if(j < i){
            --i;
            continue;
        }
        array[i] = t;
    }
}

void MainWindow::dispWinner(){
    //存放随机数
    int winner[MAX_COUNT];
    //获得随机数
    getRands(winner, nameList->size(), _count);
    //图片
    QPixmap pic;
    for(int i = 0; i < _count; ++i){
        pic = QPixmap(imageList->at(winner[i]));
        //图片太大，进行缩放
        if(pic.width() > labelPic[i].width() || pic.height() > labelPic[i].height()) {
            pic = pic.scaled(labelPic[i].size(),
                             Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
        }
        labelPic[i].setPixmap(pic);
        labelName[i].setText(nameList->at(winner[i]));
    }
}

void MainWindow::changeSize(int w, int h){
    int x = this->x() - (w - this->width())/2;
    int y = this->y() - (h - this->height())/2;

    animation->setStartValue(QPoint(this->x(), this->y()));
    animation->setEndValue(QPoint(x, y));
    animation->start();
    this->resize(w, h);
}

void MainWindow::resizeEvent(QResizeEvent *){
    titleBar->resize();

    ui->groupBox2->setGeometry((this->width() - GROUP_BOX_WIDTH) / 2,
                               this->height() - V_SPACE - GROUP_2_HEIGHT,
                               GROUP_BOX_WIDTH,
                               GROUP_2_HEIGHT);

    ui->groupBox1->setGeometry(ui->groupBox2->x(),
                               ui->groupBox2->y() - V_SPACE - GROUP_1_HEIGHT,
                               GROUP_BOX_WIDTH,
                               GROUP_1_HEIGHT);
}

void MainWindow::on_pushBtnStart_clicked(){
    if(ui->pushBtnStart->text() == "开始"){
        ui->pushBtnStart->setText("停止");
        ui->pushBtnBrowse->setEnabled(false);
        timerShow->start();
    }
    else{
        ui->pushBtnStart->setText("开始");
        ui->pushBtnBrowse->setEnabled(true);
        timerShow->stop();
    }
}

void MainWindow::on_pushBtnSwitch_clicked(){
    if(ui->pushBtnSwitch->text() == "切换到点名模式"){
        ui->pushBtnSwitch->setText("切换到摇号模式");
        changeSize(this->maximumWidth(),
                   this->maximumHeight());
    }else{
        ui->pushBtnSwitch->setText("切换到点名模式");
        changeSize(this->minimumWidth(),
                   this->maximumHeight());
    }
}

void MainWindow::on_pushBtnBrowse_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "打开文件",
                                                "", "文本文档(*.txt)");

    if(!path.isEmpty()) {
        //获得图片所在文件夹
        int n = 0;
        for(int i = 0; i < path.length(); ++i){
            if('/' == path[i]){
                n = i;
            }
        }
        imageFolder = path.left(n + 1);
        ui->lineFile->setText(path.right(path.length() - n - 1));

        //打开并读取名单文件
        QFile *file = new QFile(path);
        if(file->open(QIODevice::ReadOnly|QIODevice::Text)){
            nameList->clear();
            imageList->clear();
            QTextStream stream(file);
            while(!stream.atEnd()){
                nameList->append(stream.readLine());
                if(QFile::exists(imageFolder+nameList->at(nameList->size()-1)+".jpg")){
                    imageList->append(imageFolder+*(nameList->end())+".jpg");
                }
                else if(QFile::exists(imageFolder+*(nameList->end())+".jpeg")){
                    imageList->append(imageFolder+*(nameList->end())+".jpeg");
                }
                else if(QFile::exists(imageFolder+*(nameList->end())+".png")){
                    imageList->append(imageFolder+*(nameList->end())+".png");
                }
                else{
                    imageList->append(":/image/404.png");
                }
            }
            file->close();

            _count = nameList->size() < MAX_COUNT ? \
                     nameList->size() :\
                     MAX_COUNT;

            //文件为空判断
            if(0 != _count){
                ui->pushBtnStart->setEnabled(true);

                //show all pic & name
                for(int i = 0; i < MAX_COUNT; ++i){
                    labelPic[i].setVisible(true);
                    labelName[i].setVisible(true);
                }
                //change size minwidth, maxheight
                changeSize(this->minimumWidth(),
                           this->maximumHeight());

                this->setMaximumWidth((_count + 1) * H_SPACE + \
                                      PIC_WIDTH * _count);

                //只有一人，禁止打开点名模式
                if(_count > 1){
                    ui->pushBtnSwitch->setEnabled(true);
                }
                else{
                    ui->pushBtnSwitch->setEnabled(false);
                }

                //清空显示项目
                for(int i = 0; i < MAX_COUNT; ++i){
                    labelPic[i].setPixmap(QPixmap());
                    labelName[i].setText("");
                }
                //重设按钮
                ui->pushBtnSwitch->setText("切换到点名模式");
            }else{
                ui->pushBtnStart->setEnabled(false);
                ui->pushBtnSwitch->setEnabled(false);
                ui->pushBtnSwitch->setText("切换到点名模式");
                //hide all pic & name
                for(int i = 0; i < MAX_COUNT; ++i){
                    labelPic[i].setPixmap(QPixmap());
                    labelPic[i].setVisible(false);
                    labelName[i].setVisible(false);
                    labelName[i].setText("");
                }

                QMessageBox::information(this,
                                         "提示信息",
                                         "名单文件为空",
                                         QMessageBox::Ok);

                //change size minwidth & minheight
                changeSize(this->minimumWidth(),
                           this->minimumHeight());
            }
        }else{
            ui->pushBtnStart->setEnabled(false);
            ui->pushBtnSwitch->setEnabled(false);
            ui->pushBtnSwitch->setText("切换到点名模式");
            //hide all pic & name
            for(int i = 0; i < MAX_COUNT; ++i){
                labelPic[i].setPixmap(QPixmap());
                labelPic[i].setVisible(false);
                labelName[i].setVisible(false);
                labelName[i].setText("");
            }

            QMessageBox::information(this,
                                     "提示信息",
                                     "文件打开失败",
                                     QMessageBox::Ok);

            //change size minwidth & minheight
            changeSize(this->minimumWidth(),
                       this->minimumHeight());
        }
    }
}
