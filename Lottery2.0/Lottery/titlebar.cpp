#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent, int height) :
    QWidget(parent),
    _parent(parent),
    _height(height){

    _layout = new QHBoxLayout(this);

    _icon = new QLabel(this);
    _icon->setGeometry(0, 0, _height, _height);
    _icon->setScaledContents(true);

    _title = new QLabel(this);
    _title->setGeometry(_height, 0, _height, _height);
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font:16px \"黑体\";color: rgb(255,255,255)");

    _close = new QPushButton(this);
    _close->resize(_height, _height);
    _close->setText("×");
    _close->setStyleSheet("background-color:red;font: 18px \"黑体\"");
    connect(_close, SIGNAL(clicked()), this, SLOT(closeClicked()));

    resize();
}

TitleBar::~TitleBar(){
    delete _icon;
    delete _title;
    delete _close;
    delete _layout;
}

void TitleBar::setIcon(QPixmap icon){
    icon.scaled(_icon->size(),
               Qt::KeepAspectRatio,
               Qt::SmoothTransformation);
    _icon->setPixmap(icon);
    _parent->setWindowIcon(QIcon(icon));
}

void TitleBar::setTitle(QString title){
    _title->setText(title);
    _parent->setWindowTitle(title);
}

void TitleBar::setBackColor(QString color){
    this->setStyleSheet("background-color:" + color);
}

void TitleBar::resize(){
    this->setGeometry(0, 0,
                      _parent->width(),
                      _height);
}

void TitleBar::resizeEvent(QResizeEvent *){

    _title->resize(this->width() - 2 * this->height(),
                   this->height());

    _close->setGeometry(this->width() - this->height(),
                        0,
                        this->height(),
                        this->height());

}

void TitleBar::closeClicked(){
    _parent->close();
}

void TitleBar::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        m_drag = true;
        dragPos = e->pos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *e){
    if(m_drag && (e->buttons() & Qt::LeftButton)){
        _parent->move(e->globalPos() - dragPos);
        return ;
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *){
    m_drag = false;
}
