#include "myclass.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QRegExp>
#include <QJsonArray>
#include <QTableWidget>
#include <QMainWindow>
#include <QVector>
#include <string>
#include <QMap>

using namespace std;
static int col = 0;
//static QString name = "";

MyClass::MyClass(QStringList *coins, QWidget *parent) : QLabel(parent)

{


    this->SymbolMap = new QMap<QString, QString>();
     manager = new QNetworkAccessManager(this) ;
     this->coins = coins;

     //this->mw = new QMainWindow;
     this->table = new QTableWidget(this->coins->length(), 3);
     table->setHorizontalHeaderLabels({"USD", "EUR", "GBP"});
     //mw->setCentralWidget(table);



     connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

     //mw->show();

     // Initiate retrieval of  the data from the web page.
     // When completed, slot replyFinished will be called.
     manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/coins/list")));
}
 //  {"id":"3x-long-bitmax-token-token","symbol":"btmxbull","name":"3X Long BitMax Token Token"}
void MyClass::replyFinished(QNetworkReply *reply)  {



     QString str ;
     QString symbol;
     QString pattern;
     QString data = (QString) reply->readAll();

     for(int i=0; i<coins->length(); i++){
              str = "https://api.coingecko.com/api/v3/simple/price?ids=";
              symbol = coins->at(i);
              pattern = "{\\Wid\\W:\\W([\\w-]+)\\W[^\\{]*\"";
              pattern.append(symbol);
              pattern.append("\"[^\\}]*");

              // read the data fetched from the web site
             // QString data = (QString) reply->readAll();

              //"{\\Wid\\W:\\W(.+)\\".+"
              // use pattern matching to extract the rate
              QRegularExpression rx(pattern);
              QRegularExpressionMatch match = rx.match(data);
              bool hasmatch = match.hasMatch();
              if ( hasmatch ) {
                this->SymbolMap->insert(match.captured(1), symbol);
                  str.append(match.captured(1));

                str.append("&vs_currencies=usd,eur,gbp");
              }
              else {
                str = QString("Error") ;
              }

            //name = coins->at(i);
            manager = new QNetworkAccessManager(this) ;
         manager->get(QNetworkRequest(QUrl(str)));
         connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished2(QNetworkReply*)));




     }

  }
 // {"bitcoin":{"usd":38871,"eur":32408,"gbp":27790}}
void MyClass::replyFinished2(QNetworkReply *reply1)  {




     QString data = (QString) reply1->readAll();

     //QRegExp rx1("(\\w+)");

     QRegExp rx(":(\\d+\\.?\\d+),\"(\\w+)\":(\\d+\\.?\\d+),\"(\\w+)\":(\\d+\\.?\\d+)");
     QRegExp nam("(\\w+)");


     //QString list;
    //rx1.indexIn(data);
    rx.indexIn(data);
    nam.indexIn(data);
     //list += rx.cap(1);
     this->ece = new QTableWidgetItem(SymbolMap->value(nam.cap(1)));
     table->setVerticalHeaderItem(col, ece);
     this->ece = new QTableWidgetItem(rx.cap(1));
     table->setItem(col, 0, ece);
     this->ece = new QTableWidgetItem(rx.cap(3));
          table->setItem(col, 1, ece);
      this->ece=new QTableWidgetItem(rx.cap(5));
      table->setItem(col, 2, ece);

      col++;



}

