#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>
#include<QString>
#include"netwindow.h"

namespace Ui {
class choose;
}

class choose : public QDialog
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = nullptr);
    ~choose();
    static QString strname;

private slots:
    void on_pushButton_clicked();

private:
    Ui::choose *ui;
};

#endif // CHOOSE_H
