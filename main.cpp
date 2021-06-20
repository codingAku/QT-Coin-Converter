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
using namespace std;
//Main method of the program.
//Environment variable's value is read here and QMainWindow is created here. QTable of the MyClass object is also attached to it here.
//Names of the coins are read from the input file and stored in MyClass object's QStringList named "coins".
//Filling of the table and fetch of the values from API is done inside MyClass constructor. In main, MyClass object's constructor is called.
int main(int argc,char *argv[])
{
   QApplication a(argc, argv);
   const char* tmp = std::getenv("MYCRYPTOCONVERT");
   std::string env(tmp ? tmp : "");
   std::string myText;
   QStringList *coins = new QStringList();

   std::ifstream reader(env);
   std::string coin;


while(getline(reader,coin)){

     QString qstr = QString::fromStdString(coin);
     coins->append(qstr);

}
   MyClass my(coins);

   QMainWindow *mw = new QMainWindow;
   mw->setCentralWidget(my.table);
   mw->show();

   return a.exec();
}
