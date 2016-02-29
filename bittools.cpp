#include "bittools.h"
#include "data.h"
#include "ui_bittools.h"
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include <QCoreApplication>
#include <QStandardItemModel>
#include <QtScript>
#include <vector>
#include <iostream>

BitTools::BitTools(QWidget *parent) : QMainWindow(parent), ui(new Ui::BitTools)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white;");
    load();
}

// Function to connect with server and get data, call's replyFinished() when done
void BitTools::load()
{
    QUrl qrl("http://api.bitvalor.com/v1/ticker.json");
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    QNetworkReply* reply = NULL;
    reply = manager->get(QNetworkRequest(qrl));
}
// Get's load() data and store it on objects, calls parsedatatoscreen() when done
void BitTools::replyFinished(QNetworkReply* reply)
{
    QScriptEngine engine;
    Data lastinfo;
    time_by_exchange tbe;
    Exchange bmf;
    QString data = (QString) reply->readAll();
    QScriptValue result = engine.evaluate("(" + data + ")");
    QScriptValue exchanges_lt_times = result.property("timestamp").property("exchanges");
    QScriptValueIterator it(exchanges_lt_times);
    while (it.hasNext()) {
        it.next();
        tbe.time_stamp_last_trade = it.value().toInteger();
        tbe.id = it.name().toStdString();
        lastinfo.timestamp.exchanges.push_back(tbe);
    }
    QScriptValue exchanges_prices = result.property("ticker_24h").property("exchanges");
    QScriptValueIterator its(exchanges_prices);
    while (its.hasNext()) {
        its.next();
        bmf.id = its.name().toStdString();
        QScriptValue prices = its.value();
        bmf.last_price = prices.property("last").toNumber();
        lastinfo.lastticker.exchanges.push_back(bmf);
    }
    parsedatatoscreen(lastinfo);
}

BitTools::~BitTools(){
    delete ui;
}

void BitTools::on_pushButton_clicked(){
    // On calculate button click fire request to get data and update it on the screen
    load();
}

bool operator<(const Opportunity &s1, const Opportunity &s2){
    if(s1.delta > s2.delta){
        return true;
    }
    else{
        return false;
    }
}

//  Function to get data provided by replyFinished() and parse it to screen with formatting
void BitTools::parsedatatoscreen(Data data){
    vector<Opportunity> opportunity;
    vector<Opportunity>::iterator op_it;
    vector<Exchange>::iterator it, j;
    vector<time_by_exchange>::iterator tbe_it;
    vector<Price> prices;
    vector<Price>::iterator p_it;
    Exchange exchange, exchange2;
    double delta, risk;
    int date_delta;
    QDateTime time, currentDateTime;
    double amount = ui->money->text().replace(",",".").toDouble();
    // a loop to scan the STL container
    for (it = data.lastticker.exchanges.begin(); it != data.lastticker.exchanges.end(); ++it) {
        exchange = *it;
        // a loop to scan the STL container
        for (j = data.lastticker.exchanges.begin(); j != data.lastticker.exchanges.end(); ++j) {
            exchange2 = *j;
            if (j != it){
                delta = (exchange.last_price - exchange2.last_price) * (amount == 0 ? 1 : amount/exchange2.last_price);
                if (delta>0){
                     risk = (amount == 0 ? 1 : amount/exchange2.last_price)/(exchange.last_price - exchange2.last_price);
                     qDebug() << risk;
                     for (tbe_it = data.timestamp.exchanges.begin(); tbe_it != data.timestamp.exchanges.end(); ++tbe_it){
                         if(tbe_it->id==exchange2.id){
                             time.setTime_t(tbe_it->time_stamp_last_trade);
                             currentDateTime = QDateTime::currentDateTime();
                             date_delta = (time.secsTo( currentDateTime) );
                             risk = risk*date_delta/60;
                         }
                         if(tbe_it->id==exchange.id){
                             time.setTime_t(tbe_it->time_stamp_last_trade);
                             currentDateTime = QDateTime::currentDateTime();
                             date_delta = (time.secsTo( currentDateTime) );
                             risk = risk*date_delta/60;
                         }
                     }
                     opportunity.push_back(Opportunity(delta,exchange2.last_price,exchange.last_price,exchange2.id,exchange.id,risk));
                }
            }
        }
    }
    sort(opportunity.begin(),opportunity.end());
    QStandardItemModel *model = new QStandardItemModel(opportunity.size(), 4);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Profit")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Buy Price")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Sell Price")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Risk")));

    for (op_it = opportunity.begin(); op_it != opportunity.end(); ++op_it){
        int index = op_it - opportunity.begin();
        QStandardItem *delta = new QStandardItem(QString::fromStdString(Format::format_price(op_it->delta)));
        model->setItem(index, 0, delta);

        QStandardItem *price_1 = new QStandardItem(QString::fromStdString(Format::format_price(op_it->inprice) + " (" + op_it->inexchange + ")"));
        model->setItem(index, 1, price_1);

        QStandardItem *price_2 = new QStandardItem(QString::fromStdString(Format::format_price(op_it->outprice) + " (" + op_it->outexchange + ")"));
        model->setItem(index, 2, price_2);

        QStandardItem *risk = new QStandardItem(QString::fromStdString(Format::format_percent(op_it->risk)));
        model->setItem(index, 3, risk);
    }

    ui->opportunities->setModel(model);

    ui->opportunities->setColumnWidth(0, 100);
    ui->opportunities->setColumnWidth(1, 150);
    ui->opportunities->setColumnWidth(2, 150);
    ui->opportunities->setColumnWidth(3, 100);

    model = new QStandardItemModel(opportunity.size(), 4);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Exchange")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Price")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Bitcoins")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Time")));

    for (it = data.lastticker.exchanges.begin(); it != data.lastticker.exchanges.end(); ++it){
        for (tbe_it = data.timestamp.exchanges.begin(); tbe_it != data.timestamp.exchanges.end(); ++tbe_it){
            if (it->id == tbe_it->id)
                prices.push_back(Price(it->id, it->last_price, tbe_it->time_stamp_last_trade));
        }
    }

    for (p_it = prices.begin(); p_it != prices.end(); ++p_it){
        int index = p_it - prices.begin();
        QStandardItem *name = new QStandardItem(QString::fromStdString(Format::key_to_name(p_it->exchange_id)));
        model->setItem(index, 0, name);

        QStandardItem *price = new QStandardItem(QString::fromStdString(Format::format_price(p_it->price)));
        model->setItem(index, 1, price);

        QStandardItem *bitcoin = new QStandardItem(QString::fromStdString(Format::format_bitcoin(amount == 0 ? 1 : amount/p_it->price)));
        model->setItem(index, 2, bitcoin);

        QStandardItem *time = new QStandardItem(QString::fromStdString(Format::format_unix_timestamp(p_it->time_stamp_last_trade)));
        model->setItem(index, 3, time);
    }

    ui->prices->setModel(model);

    ui->prices->setColumnWidth(0, 100);
    ui->prices->setColumnWidth(1, 100);
    ui->prices->setColumnWidth(2, 150);
    ui->prices->setColumnWidth(3, 150);
}
