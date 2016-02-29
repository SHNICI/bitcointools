#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <QtNetwork/QNetworkRequest>

using namespace std;

// Format class to prepare data for GUI
class Format {
public:
    static string format_price(double price){
        char buffer [50];
        sprintf(buffer, "R$ %.2f", price);
        return (string) buffer;
    }

    static string format_bitcoin(double price){
        char buffer [50];
        sprintf(buffer, "%.8f XBT", price);
        return (string) buffer;
    }

    static string format_percent(double percent){
        char buffer [50];
        sprintf(buffer, "%.2f %%", percent);
        return (string) buffer;
    }

    static string format_unix_timestamp(long unix_time){
        QDateTime timestamp;
        timestamp.setTime_t(unix_time);
        return timestamp.toString(Qt::SystemLocaleShortDate).toStdString();
    }

    static string key_to_name(string id){
        string ret = "";
        if(id=="B2U")
            ret = "BitcoinToYou";
        else if(id=="BAS")
            ret = "Basebit";
        else if(id=="BIV")
            ret = "Bitinvest";
        else if(id=="FLW")
            ret = "flowBTC";
        else if(id=="FOX")
            ret = "Foxbit";
        else if(id=="LOC")
            ret =  "LocalBitcoins";
        else if(id=="MBT")
            ret =  "Mercado Bitcoin";
        else if(id=="NEG")
            ret = "Negocie Coins";
        return ret;
    }
};


class Exchange{
public:
    string id;// Exchange's Symbol
    double last_price; // Last price in Reais

    friend ostream & operator<<(ostream & output, const Exchange & e){
        output << e.id << ": " << e.last_price;
        return output;
    }
};
class time_by_exchange{
public:
    string id;// Exchange's Symbol
    long time_stamp_last_trade; // Timestamp of last trade

    friend ostream & operator<<(ostream & output, const time_by_exchange & tbe){
        output << tbe.id << ": " << tbe.time_stamp_last_trade;
        return output;
    }
};
class Data{
public:
    struct Timestamp {
        vector<time_by_exchange> exchanges;
    };

    struct Ticker{
        vector<Exchange> exchanges;
    };
    // variables
    Timestamp timestamp; // Time of last trades by exchange
    Ticker lastticker; // Price of last trades by exchange
    enum listaExchanges{BitcoinToYou,Basebit,Bitinvest,flowBTC,Foxbit,LocalBitcoins,MercadoBitcoin,NegocieCoins};
};

class Opportunity{
public:
    double delta; // Profit
    double inprice; // Buy Price
    double outprice; // Sell Price
    string inexchange; // Exchange to buy from
    string outexchange; // Exchange to sell to
    double risk; // Risk of trade

    Opportunity(double delta,double inprice,double outprice,string inexchange,string outexchange, double risk):
        delta(delta) , inprice(inprice), outprice(outprice), inexchange(inexchange), outexchange(outexchange),risk(risk){}

    friend ostream & operator<<(ostream & output, const Opportunity & o){
        output << o.delta << " " << o.inprice << " (" << Format::key_to_name(o.inexchange) << ") "
               << o.outprice << " (" << Format::key_to_name(o.outexchange) << ") "
               << Format::format_price(o.risk) << endl;
        return output;
    }
};
bool operator<(const Opportunity &s1, const Opportunity &s2);

class Price{
public:
    string exchange_id; // Exchange's Symbol
    double price; // Last trade's price
    long time_stamp_last_trade; // Last trade's time

    Price(string exchange_id, double price, double time_stamp_last_trade):
        exchange_id(exchange_id) , price(price), time_stamp_last_trade(time_stamp_last_trade){}
};

