#include "bittools.h"
#include "data.h"
#include "ui_bittools.h"
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QString>
#include <QCoreApplication>
#include <QtScript>


BitTools::BitTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BitTools)
{
    ui->setupUi(this);
    load();
}

void BitTools::load(double amount)
    {
      QUrl qrl("http://api.bitvalor.com/v1/ticker.json");
      manager = new QNetworkAccessManager(this);
      connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*, amount)));
      QNetworkReply* reply = NULL;
      reply = manager->get(QNetworkRequest(qrl));
    }

void BitTools::replyFinished(QNetworkReply* reply, double amount)
    {
      QScriptEngine engine;
      Data lastinfo;
      time_by_exchange tbe;
      exchange bmf;
      QString data = (QString) reply->readAll();
      QScriptValue result = engine.evaluate(data);
      QScriptValue exchanges_lt_times = result.property("timestamp").property("exchanges");
      QScriptValueIterator it(exchanges_lt_times);
      while (it.hasNext()) {
         it.next();
         tbe.timeStampLastTrade = it.value().toInteger();
         tbe.id = it.name().toStdString();
         lastinfo.timestamp.exchanges.push_back(tbe);
      }
      QScriptValue exchanges_prices = result.property("ticker_24h").property("exchanges");
      QScriptValueIterator its(exchanges_prices);
      while (its.hasNext()) {
         bmf.id = its.name().toStdString();
         QScriptValue prices = its.value();
         bmf.lastPrice = prices.property("last").toNumber();
         lastinfo.lastticker.exchanges.push_back(bmf);
      }
    }
BitTools::~BitTools()
{
    delete ui;
}

void BitTools::on_pushButton_clicked()
{
    float amount;
    QString inputfromle;
    inputfromle = ui->lineEdit->text();
    inputfromle.replace(",",".");
    amount = inputfromle.toFloat();
    load(amount);
}

void BitTools::on_pushButton_2_clicked()
{
    load();
}
void BitTools::parsedatatoscreen(Data data, double amount)
{

}
