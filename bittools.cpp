#include "bittools.h"
#include "ui_bittools.h"
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

BitTools::BitTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BitTools)
{
    ui->setupUi(this);
    load();
}

void BitTools::load()
    {
      QUrl qrl("http://api.bitvalor.com/v1/ticker.json");
      manager = new QNetworkAccessManager(this);
      connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
      QNetworkReply* reply = NULL;
      reply = manager->get(QNetworkRequest(qrl));
    }

void BitTools::replyFinished(QNetworkReply* reply)
    {
      qDebug() << reply->readAll();
    }
BitTools::~BitTools()
{
    delete ui;
}
