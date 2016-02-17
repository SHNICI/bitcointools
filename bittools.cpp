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

void BitTools::load(float amount)
    {
      QUrl qrl("http://api.bitvalor.com/v1/ticker.json");
      manager = new QNetworkAccessManager(this);
      connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
      QNetworkReply* reply = NULL;
      reply = manager->get(QNetworkRequest(qrl));
    }

void BitTools::replyFinished(QNetworkReply* reply, float amount)
    {
      QScriptEngine engine;
      Data lastinfo;
      qDebug() << reply->readAll();
      QString data = (QString) reply->readAll();
      QScriptValue result = engine.evaluate(data);
    }
BitTools::~BitTools()
{
    delete ui;
}
