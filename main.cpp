#include <QtCore>
#include <QApplication>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QStringList>
#include <QJsonObject>
#include <iostream>
#include <fstream>
#include <QMainWindow>


#include "myclass.h"

int main(int argc,char *argv[])
{
   QApplication a(argc, argv);
   const char* tmp = std::getenv("MYCRYPTOCONVERT");
   std::string env(tmp ? tmp : "");
   std::string myText;
   QStringList *coins = new QStringList();



   // Use a while loop together with the getline() function to read the file line by line
   //QFile file(tmp);

   //QTextStream in(&file);

  /* while(!in.atEnd()) {
       QString line = in.readLine();
       coins->append(line);
   }*/
     coins->append("Bitcoin");
     coins->append("Ethereum");
     coins->append("zoc");
     coins->append("Litecoin");
     coins->append("Monero");
     coins->append("Zcash");
     //coins->append("0chain");
   MyClass my(coins);

   QMainWindow *mw = new QMainWindow;
   //this->table = new QTableWidget(this->coins->length(), 3);
   //table->setHorizontalHeaderLabels({"USD", "EUR", "GBP"});
   mw->setCentralWidget(my.table);
   mw->show();


  // my.show();



   return a.exec();
}
