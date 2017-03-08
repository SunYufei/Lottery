#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /****** 初始化窗体组件 ******/

    // 标题栏
    this->setWindowTitle(TITLE);

    // 控制面板
    ui->lineEdit->setGeometry(H_SPACE, 2 * V_SPACE,
                              LINE_WIDTH, LINE_HEIGHT);
    ui->pushBtnBrowse->setGeometry(2 * H_SPACE + LINE_WIDTH,
                                   2 * V_SPACE,
                                   BTN_WIDTH, BTN_HEIGHT);
    ui->groupBox->setGeometry(H_SPACE, V_SPACE,
                              GROUP_WIDTH, GROUP_HEIGHT);
    ui->pushBtnStart->setGeometry((ui->groupBox->width() - BTN_WIDTH) / 2,
                                  3 * V_SPACE + BTN_HEIGHT,
                                  BTN_WIDTH,
                                  BTN_HEIGHT);
    ui->pushBtnStart->setEnabled(false);

    // 计时器
    timerShow.setInterval(100);
    connect(&timerShow, SIGNAL(timeout()),
            this, SLOT(dispWinner()));

    // 动画效果
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(600);

    // 初始化窗体
    this->setWindowFlags(this->windowFlags() & (~Qt::WindowMaximizeButtonHint));
    this->setFixedSize(MIN_WIDTH, MIN_HEIGHT);

    // 绑定随机数种子
    qsrand(QTime::currentTime().msec());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete animation;
}

void MainWindow::dispWinner()
{
    // 获得随机数
    int winner = getRands(columns);

    // 图片
    QPixmap pic;
    QString image;

    for(int i = 0; i < rows; i++)
    {
        if(winner < nameList[i].size())
        {
            // 显示名字
            vn[i]->setText(nameList[i].at(winner));

            image.clear();
            image = imageFloder + nameList[i].at(winner);

            if(QFile::exists(image + ".jpg"))
                image += ".jpg";
            else if(QFile::exists(image + ".jpeg"))
                image += ".jpeg";
            else if(QFile::exists(image + ".png"))
                image += ".png";
            else
                image = ":image/404.png";

            pic = QPixmap(image);

            // 图片过大，缩放
            if(pic.width() > PIC_WIDTH || pic.height() > PIC_HEIGHT)
            {
                pic = pic.scaled(vp[i]->size(),
                                 Qt::KeepAspectRatio,
                                 Qt::SmoothTransformation);
            }
            // 显示图片
            vp[i]->setPixmap(pic);
        }
        else
        {
            vp[i]->setPixmap(QPixmap());
            vn[i]->setText(tr(""));
        }
    }
}

int MainWindow::getRands(const int range)
{
    return qrand() % range;
}

void MainWindow::readFile(const QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        rows = 0;
        columns = 0;
        nameList.clear();
        QTextStream stream(&file);
        QString t;
        while(!stream.atEnd())
        {
            t = stream.readLine();
            nameList.append(t.split(' '));
        }
        rows = nameList.size();
        if (rows == 0)
        {
            QMessageBox::information(this,
                                     tr("提示信息"),
                                     tr("名单文件为空"),
                                     QMessageBox::Ok);
            ui->pushBtnStart->setEnabled(false);
            changeSize(MIN_WIDTH, MIN_HEIGHT);
            clearImage();
        }
        else
        {
            QVector<QStringList>::iterator it;
            for(it = nameList.begin(); it < nameList.end(); it++)
                if(it->size() > columns)
                    columns = it->size();
            ui->pushBtnStart->setEnabled(true);

            // 改变窗口大小
            int width = (rows + 1) * H_SPACE + \
                        rows * PIC_WIDTH;
            MAX_WIDTH = (width > MIN_WIDTH) ? width : MIN_WIDTH;
            changeSize(MAX_WIDTH, MAX_HEIGHT);

            // 图像显示模块初始化
            initImage();
        }
    }
    else
    {
        QMessageBox::information(this,
                                 tr("提示信息"),
                                 tr("文件打开失败"),
                                 QMessageBox::Ok);
    }
}

void MainWindow::on_pushBtnBrowse_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("打开文件"),
                                                "",
                                                tr("文本文档(*.txt)"));
    if(!path.isEmpty())
    {
        int n = 0;
        for(int i = 0; i < path.length(); i++)
            if(path[i] == '/')
                n = i;
        imageFloder = path.left(n + 1);
        ui->lineEdit->setText(path.right(path.length() - n - 1));
        readFile(path);
    }
}

void MainWindow::on_pushBtnStart_clicked()
{
    if (ui->pushBtnStart->text() == tr("开始"))
    {
        ui->pushBtnStart->setText(tr("停止"));
        ui->pushBtnBrowse->setEnabled(false);
        timerShow.start();
    }
    else if (ui->pushBtnStart->text() == tr("停止"))
    {
        ui->pushBtnStart->setText(tr("开始"));
        ui->pushBtnBrowse->setEnabled(true);
        timerShow.stop();
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->groupBox->setGeometry((this->width() - GROUP_WIDTH) / 2,
                              this->height() - V_SPACE - GROUP_HEIGHT,
                              GROUP_WIDTH,
                              GROUP_HEIGHT);
}

void MainWindow::changeSize(const int w, const int h)
{
    int x = this->x() - (w - this->width()) / 2;
    int y = this->y() - (h - this->height()) / 2;

    animation->setStartValue(QPoint(this->x(), this->y()));
    animation->setEndValue(QPoint(x, y));
    animation->start();
    this->setFixedSize(w, h);
}

void MainWindow::initImage()
{
    clearImage();

    // Allocate new
    vp.resize(rows);
    vn.resize(rows);
    for(int i = 0; i < rows; i++)
    {
        vp[i] = new QLabel();
        vp[i]->setParent(this);
        vp[i]->setGeometry(i * PIC_WIDTH + (i + 1) * H_SPACE,
                                V_SPACE,
                                PIC_WIDTH,
                                PIC_HEIGHT);
        vp[i]->setAlignment(Qt::AlignCenter);
        vp[i]->setScaledContents(false);
        vp[i]->show();

        vn[i] = new QLabel();
        vn[i]->setParent(this);
        vn[i]->setGeometry(i * NAME_WIDTH + (i + 1) * H_SPACE,
                                2 * V_SPACE + PIC_HEIGHT,
                                NAME_WIDTH,
                                NAME_HEIGHT);
        vn[i]->setAlignment(Qt::AlignCenter);
        vn[i]->setStyleSheet("font:28px \"楷体\"");
        vn[i]->show();
    }
}

void MainWindow::clearImage()
{
    for(int i = 0; i < vp.size(); i++)
    {
        vp[i]->destroyed();
        vn[i]->destroyed();
        delete vp[i];
        delete vn[i];
    }
    vp.clear();
    vn.clear();
}
