#include "myclass.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QRegExp>
#include <QJsonArray>
#include <QTableWidget>
#include <QMainWindow>
#include <QVector>
MyClass::MyClass(QStringList *coins, QWidget *parent) : QLabel(parent)
{



     manager = new QNetworkAccessManager(this) ;
     this->name = "Bitcoin";
     this->coins = coins;


     connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished2(QNetworkReply*)));

     // Initiate retrieval of  the data from the web page.
     // When completed, slot replyFinished will be called.
     manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd,eur,gbp")));
}
 //  {"id":"3x-long-bitmax-token-token","symbol":"btmxbull","name":"3X Long BitMax Token Token"}
void MyClass::replyFinished(QNetworkReply *reply)  {



     QString str ;
     QString data = (QString) reply->readAll();

     for(int i=0; i<coins->length(); i++){
         QString symbol = coins->at(i);
        // QString symbol = "0.5X Long Bitcoin Cash Token";
         QString str = "https://api.coingecko.com/api/v3/simple/price?ids=";
         QString pattern = "{\\Wid\\W:\\W([\\w-]+)\\W[^\\{]*";
         pattern.append(symbol);
         pattern.append("[^\\}]+");
         // read the data fetched from the web site
         QString data = (QString) reply->readAll();
         //"{\\Wid\\W:\\W(.+)\\".+"
         // use pattern matching to extract the rate
         QRegularExpression rx(pattern);
         QRegularExpressionMatch match = rx.match(data);
         bool hasmatch = match.hasMatch();
         if ( hasmatch ) {
           str.append(match.captured(1));
           str.append("&vs_currencies=usd,eur,gbp");
         }
         else {
           str = QString("Error") ;
         }
         manager = new QNetworkAccessManager(this) ;
         this->name = symbol;
         connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished2(QNetworkReply*)));
         manager->get(QNetworkRequest(QUrl(str)));



     }

  }
 // {"bitcoin":{"usd":38871,"eur":32408,"gbp":27790}}
void MyClass::replyFinished2(QNetworkReply *reply)  {

    QTableWidget *table = new QTableWidget(this->coins->length(), 3);
    table->setHorizontalHeaderLabels({"USD", "EUR", "GBP"});

     QString data = (QString) reply->readAll();

     //QRegExp rx1("(\\w+)");

     QRegExp rx(":(\\d+\\.?\\d+),\"(\\w+)\":(\\d+\\.?\\d+),\"(\\w+)\":(\\d+\\.?\\d+)");

     QString list;
    //rx1.indexIn(data);
    rx.indexIn(data);
     list += rx.cap(1);
     QTableWidgetItem *ece = new QTableWidgetItem(rx.cap(1));
     table->setItem(0, 0, ece);
     ece = new QTableWidgetItem(rx.cap(3));
          table->setItem(0, 1, ece);
      ece=new QTableWidgetItem(rx.cap(5));
      table->setItem(0, 2, ece);
      ece = new QTableWidgetItem(this->name);
      table->setVerticalHeaderItem(0, ece);


     QMainWindow *mw = new QMainWindow;
     mw->setCentralWidget(table);
     mw->show();

}

