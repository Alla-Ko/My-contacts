
#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H




#include <QItemSelection>
#include <QTabWidget>
#include <QStandardPaths>



class AddressWidget: public QTabWidget
{
    Q_OBJECT
public:
    AddressWidget(QWidget *parent = nullptr);
    void readFromFile();
    void writeToFile();

public slots:


signals:
void selectionChanged (const QItemSelection &selected);
private:
    void setupTabs();

};
#endif // ADDRESSWIDGET_H
