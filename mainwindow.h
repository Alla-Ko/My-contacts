
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytablemodel.h"
#include "help.h"
#include "add.h"
#include <QFile>
#include <QStandardPaths>
#include <QFileDialog>
#include <QSortFilterProxyModel>

//static QVector <Contact> g_contacts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MySortFilterProxyModel(QObject *parent = 0);
    QString search_vn;
    void setFilter();



protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    //bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:

};





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    inline static QString fileName =
        QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).value(0)
        + QStringLiteral("/text1.dat");

    //inline static QString fileName =QFileDialog::getSaveFileName();
    //inline static QString fileName=QFileDialog::getOpenFileName(this, "Open File","/home","DATA (*.DATA)");

    myTableModel *myModel;
    MySortFilterProxyModel *proxyModel;
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionADD_triggered();


    void on_pushButton_clicked();

    void on_actionRemove_triggered();


    void on_actionEdit_contact_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();



    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;

};









#endif // MAINWINDOW_H
