#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtGui>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTableWidget>
#include <QMainWindow>

//this class has the table which the values of the coins are printed as a field.
//It also contains a list named "coins" which stores the name/symbol of the coins that are read from the input file.
//It has a SymbolMap which stores the id-symbol/name pairs in order to print them later to the table.
//It also has a QTableWidgetItem named ece. The currency values are kept as a QString.
//ece object is used to turn them to QTableWidget items so they can be added to the QTableWidget.
//It has a Qlabel and QNetworkAccessManager object to fetch the values of the coins from coingecko API.
class MyClass : public QLabel
{
    Q_OBJECT

    public:
      MyClass(QStringList *coins, QWidget *parent = 0);
      QStringList *coins;
      QTableWidgetItem *ece;
      QTableWidget *table;
      QMap<QString, QString> *SymbolMap;




    public slots:
      void replyFinished(QNetworkReply *reply);
      void replyFinished2(QNetworkReply *reply);

    private:
      QLabel *label;
      QNetworkAccessManager *manager ;
} ;
#endif
