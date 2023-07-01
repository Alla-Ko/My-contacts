
#include "mainwindow.h"
#include "./ui_mainwindow.h"

//#include "mytablemodel.h"
#include "QHeaderView"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myModel= new myTableModel();
    //Contact cont {"Alla Kokhaniuk","0506481310","alla@gmail.com","Chernivtsi, P.Orlyka,1g,28"};
    //Contact cont1{"Natalia Kokhaniuk","0635632436","nata@gmail.com","Lviv, Saharova,20"};
    // myModel->contacts.push_back(cont);
    //myModel->contacts.push_back(cont1);

    proxyModel = new MySortFilterProxyModel();
    proxyModel->setSourceModel(myModel);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setStyleSheet("QHeaderView::section { background-color:skyblue }");
    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->tableView->setSortingEnabled(true);
    ui->tableView-> sortByColumn ( 0 , Qt :: AscendingOrder );
    ui->tableView->horizontalHeader()->setSelectionMode( QAbstractItemView::NoSelection );
    //ui->tableView->verticalHeader()->sortIndicatorOrder();
    //proxyModel->headerData(0,)




    ui->tableView->verticalHeader()->setVisible(false);

    //ui->tableView->clearSpans();
    //ui->tableView->setSelectionModel(QItemSelectionModel::Current);




    //qDebug() <<"mymodel count raw"<<myModel->rowCount();
    //qDebug() <<"mymodel "<<myModel->contacts.size();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionAbout_triggered()
{
    help window;
    window.setModal(true);
    window.exec();
}



void MainWindow::on_actionExit_triggered()
{
    switch( QMessageBox::question(
        this,
        tr("Exit"),
        tr("Are you sure?"),

        QMessageBox::Yes |
        QMessageBox::Cancel ) )
    {
    case QMessageBox::Yes:
        QApplication::quit();;
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }

}


void MainWindow::on_actionADD_triggered()
{
    //qDebug() <<"on_actionADD_triggered1 "<<myModel->contacts.size();
    Add window;
    window.setModal(true);
    window.exec();

    if (window.cont.name.size())
        myModel->contacts.push_back(window.cont);


    proxyModel->invalidate();

}

void MainWindow::on_pushButton_clicked()
{
    QString search=ui->lineEdit->text();
    proxyModel->search_vn=search;
    proxyModel->setFilter();


}

void MainWindow::on_actionRemove_triggered()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();

    switch( QMessageBox::question(
        this,
        tr("Delete"),
        tr("Are you sure?"),

        QMessageBox::Yes |
            QMessageBox::Cancel ) )
    {
    case QMessageBox::Yes:
    {
        int y=0;


        QVector <int> rows;
        rows.push_back(proxyModel->mapToSource(indexes[0]).row());
        for(int i=1;i<indexes.size();i++)
        {
            if (std::count(rows.begin(), rows.end(), proxyModel->mapToSource(indexes[i]).row())) continue;
            rows.push_back(proxyModel->mapToSource(indexes[i]).row());
        }
        auto del_index=myModel->contacts.begin();
        foreach(auto r,rows) {
            if(y==0) del_index=myModel->contacts.begin()+r;
            else del_index=myModel->contacts.begin()+r-y;
            myModel->contacts.erase(del_index);
            y++;

        }
        proxyModel->invalidate();


        break;
    }

    case QMessageBox::Cancel:
        break;
    default:
        break;
    }





}


void MainWindow::on_actionEdit_contact_triggered()
{
    //редагування
    Add window;
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();
    if(indexes.size()>1)
    {
        QMessageBox::critical(this, "Mistake","More than 1 contact is selected");
        return;
    }
    if(indexes.empty())
    {
        QMessageBox::critical(this, "Mistake","No contact is selected");
        return;
    }
    QModelIndex index=proxyModel->mapToSource(indexes[0]);
    //QModelIndex index1=proxyModel->index(index);
    window.setcont(myModel->contacts[index.row()]);
    window.exec();

    if (window.cont.name.size())
        myModel->contacts[index.row()]=window.cont;


    proxyModel->invalidate();



}


void MainWindow::on_actionOpen_triggered()
{
    //читання з файлу
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QVector<Contact> contacts_open;
    Contact contactic;
    QDataStream in(&file);
    //qDebug() <<"відкрили файл";

    while(!in.atEnd())
    {

        in >> contactic.name;

        in >> contactic.phone;
        in >> contactic.email;
        in >> contactic.address;
        contacts_open.push_back(contactic);
        //qDebug() <<contactic.name;

    }
    file.close();

    if (contacts_open.isEmpty()) {
        QMessageBox::information(this, tr("No contacts in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    } else {
        myModel->contacts=contacts_open;
        proxyModel->invalidate();




    }
}


void MainWindow::on_actionSave_triggered()
{
    //запис у файл

    QFile file(fileName);


    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QDataStream out(&file);



    for(const Contact &con:myModel->contacts)
    {
       out << con.name;
       //qDebug() <<"щось записується ";
       out << con.phone;
       out << con.email;
       out << con.address;
    }
    file.close();
    QMessageBox::information(this, "Save data","The data is saved");


}

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex index3 = sourceModel()->index(sourceRow, 3, sourceParent);

    return (sourceModel()->data(index0).toString().contains(search_vn, Qt::CaseInsensitive)
            || sourceModel()->data(index1).toString().contains(search_vn, Qt::CaseInsensitive)
            ||sourceModel()->data(index2).toString().contains(search_vn, Qt::CaseInsensitive)
            ||sourceModel()->data(index3).toString().contains(search_vn, Qt::CaseInsensitive));

}

void MySortFilterProxyModel::setFilter()
{

    invalidateFilter();
}


void MainWindow::on_lineEdit_returnPressed()
{
    MainWindow::on_pushButton_clicked();
}

