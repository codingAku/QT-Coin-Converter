#include <QtCore>
#include <QApplication>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QStringList>
#include <QJsonObject>
#include <iostream>
#include <fstream>


#include "myclass.h"

int main(int argc,char *argv[])
{
   QApplication a(argc, argv);
   const char* env = std::getenv("MYCRYPTOCONVERT");
   std::ifstream MyReadFile(env);
   std::string myText;
   QStringList *coins = new QStringList();



   // Use a while loop together with the getline() function to read the file line by line
   while (getline (MyReadFile, myText)) {
     // Output the text from the file
     QString qstr = QString::fromStdString(myText);
     coins->append(qstr);

   }

   MyClass my(coins);


   my.show();



   return a.exec();
}
