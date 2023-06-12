#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include"mainwindow.h"
#include"start.h"
#include"block.h"
namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();
    static int getshenm(){return shenm;}
    static int getcishu(){return cishu;}
    static int getroll(){return roll;}
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::setting *ui;
    static int shenm;
    static int cishu;
    static int roll;
};

#endif // SETTING_H
