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
//this static integer value keeps track of which column of the table is empty to be written.
static int col = 0;

//Constructor of the MyClass object.
MyClass::MyClass(QStringList *coins, QWidget *parent) : QLabel(parent)

{
  //SymbolMap of the object is created here.
  this->SymbolMap = new QMap<QString, QString>();
  manager = new QNetworkAccessManager(this);
  this->coins = coins;
  //the table for the currencies is created here.
  this->table = new QTableWidget(this->coins->length(), 3);

  table->setHorizontalHeaderLabels({"USD", "EUR", "GBP"});

  //in this signal, the general list of coins is fetched. This list contains ids, names and the symbols of all coins that currently exists in API.
  connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));

  manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/coins/list")));
}

//in this method, the full coin list is handled.
void MyClass::replyFinished(QNetworkReply *reply)
{

  QString str;
  QString symbol;
  QString pattern;
  QString data = (QString)reply->readAll();

  //Inside this for loop, a regex pattern which finds the ids of the symbols/names that are in "coins" list exists.
  //Also, the URL which fetches the values of currencies is created in this for loop. Then, this URL is requested again with another signal.
  //Finally, id of the current coin is matched with the same symbol/name that it was called and inserted to the SymbolMap.
  for (int i = 0; i < coins->length(); i++)
  {
    str = "https://api.coingecko.com/api/v3/simple/price?ids=";
    symbol = coins->at(i);
    pattern = "{\\Wid\\W:\\W([^\"]+)\\W[^\\{]*\"";

    pattern.append(symbol);
    pattern.append("\"[^\\}]*");


    QRegularExpression rx(pattern);
    QRegularExpressionMatch match = rx.match(data);
    bool hasmatch = match.hasMatch();
    if (hasmatch)
    {
      this->SymbolMap->insert(match.captured(1), symbol);
      str.append(match.captured(1));

      str.append("&vs_currencies=usd,eur,gbp");
    }
    else
    {
      str = QString("Error");
    }

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished2(QNetworkReply *)));
    manager->get(QNetworkRequest(QUrl(str)));
  }
}

//In this method, the string which carries the values of currencies is fetched.
//There also exists a regex pattern which matches only the numeric values of USD, EUR and GBP.
//The matches of that regex object are set to the unoccupied column/row of the table.
//This is where the SymbolMap of the MyClass object is used.
//Since we have the id of the coin, and we are required to print the symbol/name of the coin, we use the SymbolMap to find the name/symbol. It is also set to the table.
void MyClass::replyFinished2(QNetworkReply *reply1)
{

  QString data = (QString)reply1->readAll();

  QRegExp rx("\"usd\":([^,]+),\"eur\":([^,]+),\"gbp\":([^\\}]+)");
  QRegExp nam("\"([^\"]*)");

  rx.indexIn(data);
  nam.indexIn(data);
  this->ece = new QTableWidgetItem(SymbolMap->value(nam.cap(1)));
  table->setVerticalHeaderItem(col, ece);

  this->ece = new QTableWidgetItem(rx.cap(1));
  table->setItem(col, 0, ece);
  this->ece = new QTableWidgetItem(rx.cap(2));
  table->setItem(col, 1, ece);
  this->ece = new QTableWidgetItem(rx.cap(3));
  table->setItem(col, 2, ece);

  col++;
}
