#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QString>
#include <QPixmap>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0, const int height = 50);

    ~TitleBar();

signals:

public slots:

    void setTitle(const QString title);



    void setStyleSheet(const QString &styleSheet);

private:

    //父窗口
    QWidget *mParent;

    //图标
    QLabel *labelIcon;

    //文字标题
    QLabel *labelTitle;

    //窗体移动
    QPoint startPos;
    QPoint clickPos;
};

#endif // TITLEBAR_H
