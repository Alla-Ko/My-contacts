
#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H
#include <QModelIndex>
//#include "mainwindow.h"
struct Contact
{
    QString name;
    QString phone;
    QString email;
    QString address;
};

class myTableModel:public QAbstractTableModel
{
private:


    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
public:
    myTableModel();
    int rowCount(const QModelIndex &parent) const;
    QVector <Contact> contacts;
};

#endif // MYTABLEMODEL_H
