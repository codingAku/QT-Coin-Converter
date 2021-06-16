#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtGui>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class MyClass : public QLabel
{
    Q_OBJECT

    public:
      MyClass(QStringList *coins, QWidget *parent = 0);
      QString name;
      QStringList *coins;


    public slots:
      void replyFinished(QNetworkReply *reply);
      void replyFinished2(QNetworkReply *reply);

    private:
      QLabel *label;
      QNetworkAccessManager *manager ;
} ;
#endif
