#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtGui>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTableWidget>
#include <QMainWindow>

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
