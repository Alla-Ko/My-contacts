#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QMessageBox>
#include "mytablemodel.h"
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "mytablemodel.h"

class Validator{
    QRegularExpression reg;
public:
    Validator (QString str){
        reg=QRegularExpression (str);
    }
    virtual bool isValid(QString somestring){
        QRegularExpressionMatch regmatch=reg.match(somestring);
        return regmatch.hasMatch();
    }
};



namespace Ui {

class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    Contact cont;
    void setcont(Contact editcont);
    ~Add();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Add *ui;
};

#endif // ADD_H
