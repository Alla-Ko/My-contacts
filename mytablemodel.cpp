
#include "mytablemodel.h"
#include "mainwindow.h"
#include <QVariant>

myTableModel::myTableModel()
{

}
int myTableModel::rowCount(const QModelIndex &parent) const
{
    //return 5; // сделаем фиксированно 5 строк в таблице
    return contacts.size();
}
int myTableModel::columnCount(const QModelIndex &parent) const
{
    return 4; // количество колонок сделаем также фиксированным
}

QVariant myTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= contacts.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole) {
        QString unswer;
        if(index.column()==0)
        {
            unswer=contacts[index.row()].name;
        }
        if(index.column()==1)
        {
            unswer=contacts[index.row()].phone;
        }
        if(index.column()==2)
        {
            unswer=contacts[index.row()].email;
        }
        if(index.column()==3)
        {
            unswer=contacts[index.row()].address;
        }
        //unswer = QString("row = ") + QString::number(index.row()) + "  col = " + QString::number(index.column());
        // строкой выше мы формируем ответ. QString::number преобразует число в текст
        return QVariant(unswer);
    }
    return QVariant();
}
QVariant myTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("Phone");
        case 2:
            return tr("E-mail");
        case 3:
            return tr("Address");
        default:
            break;
        }
    }
    if (orientation == Qt::Vertical) {

        return QString::number(section+1);
    }
    return QVariant();
}
