#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent, const int height) : QWidget(parent)
{
    mParent = parent;
    this->setGeometry(0, 0, parent->width(), height);

    //图标
    labelIcon = new QLabel(this);

    //标题栏
    labelTitle = new QLabel(this);
    labelTitle->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);

    labelTitle->resize(this->width(), this->height());

    this->setStyleSheet("border-width:1px;border-style:solid");
}

TitleBar::~TitleBar(){
    delete labelIcon;
    delete labelTitle;
}

void TitleBar::setTitle(const QString title){
    labelTitle->setText(title);
    mParent->setWindowTitle(title);
}

void TitleBar::setStyleSheet(const QString &styleSheet){
    labelTitle->setStyleSheet(styleSheet);
}
