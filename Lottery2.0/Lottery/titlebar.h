#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0, int height = 40);
    ~TitleBar();

signals:    

public slots:
    void setTitle(QString title);

    void setIcon(QPixmap icon);

    void setBackColor(QString color);

    void resize();
private:
    QLabel *_icon;
    QLabel *_title;
    QPushButton *_close;
    QWidget *_parent;
    QHBoxLayout *_layout;

    int _height;

    bool m_drag;
    QPoint dragPos;

private slots:
    void closeClicked();

protected:
    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *);
};

#endif // TITLEBAR_H
