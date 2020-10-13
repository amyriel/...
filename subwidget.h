#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>
class subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit subwidget(QWidget *parent = nullptr);
    QPushButton *b;

signals:
    void mysignal();
public slots:
    void sendslot();
};

#endif // SUBWIDGET_H
