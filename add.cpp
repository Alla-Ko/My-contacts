#include "add.h"
#include "ui_add.h"

//#include "mainwindow.h"
#include <QDebug>
#include <QVector>
Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);


    QRegularExpression r_name("^[\\wЄ-ЯҐа-їґ]{1}(( [\\S])?[\\S]){0,25}");
    QValidator *validator_name=new QRegularExpressionValidator(r_name,this);
    ui->NamEdit->setValidator(validator_name);
    QRegularExpression r_phone("[0-9]{10}");
    QValidator *validator_phone=new QRegularExpressionValidator(r_phone,this);
    ui->PhoneEdit->setValidator(validator_phone);
    QRegularExpression r_email("((^[-_0-9A-Za-z]{1}[%!\\+-_0-9A-Za-z\\.]{0,62}[-_0-9A-Za-z]{1})|(^[-_0-9A-Za-z]{1}))[@]{1}(([0-9A-Za-z]{1}[-0-9A-Za-z]*(\\.)?){1,2}[-A-Za-z0-9]{2,}$)");
    QValidator *validator_email=new QRegularExpressionValidator(r_email,this);
    ui->EmailEdit->setValidator(validator_email);
}

Add::~Add()
{
    delete ui;
}


void Add::on_buttonBox_accepted()
{


    //qDebug() <<"перед on_buttonBox_accepted "<<contacts.size();
    //Contact cont;

    QString newname=ui->NamEdit->text();
    QString newaddress=ui->AddressEdit->toPlainText();
    QString newphone=ui->PhoneEdit->text();
    QString newemail=ui->EmailEdit->text();

    Validator valid_email("(?!.*(\\.\\.))(?!.*@.*@)((^[-_0-9A-Za-z]{1}[%!\\+-_0-9A-Za-z\\.]{0,62}[-_0-9A-Za-z]{1})|(^[-_0-9A-Za-z]{1}))[@]{1}(([0-9A-Za-z]{1}[-0-9A-Za-z]*(\\.)?){1,2}[-A-Za-z0-9]{2,}$)");
    if(!newname.size())QMessageBox::critical(this, "Mistake","No name");
    if(!newphone.size())QMessageBox::critical(this, "Mistake","No phone");

    if ((valid_email.isValid(newemail)||!newemail.size())&&newname.size()&&newphone.size())
    {
        cont.name=newname;
        cont.address=newaddress;
        cont.phone=newphone;
        cont.email=newemail;
    }
    if (!valid_email.isValid(newemail)&&newemail.size())
     {
        QMessageBox::critical(this, "Mistake","Invalid email format");
     }




    //myModel->contacts.push_back(cont);
    //contacts.push_back(cont);
    //qDebug() <<"on_buttonBox_accepted "<<contacts.size();

}

void Add::setcont(Contact editcont)
{
     ui->NamEdit->setText(editcont.name);
     ui->AddressEdit->setPlainText(editcont.address);
     ui->EmailEdit->setText(editcont.email);
     ui->PhoneEdit->setText(editcont.phone);

}

