#pragma once
#include <string>
#include <vector>
using namespace std;
class exchange{
public:
    string id;// Id da exchange
    double lastPrice; // ultimo preço do período em Reais
};
class time_by_exchange{
public:
    string id;
    long timeStampLastTrade; // timestamp do ultimo trade de cada exchange
};
class Data{
public:
	struct Timestamp {
		public:
            vector<time_by_exchange> exchanges;
		};
	struct Ticker{
		vector<exchange> exchanges;
		};
	// variables
	Timestamp timestamp;
    Ticker lastticker; // Dados consolidados das ultima hora
	enum listaExchanges{BitcoinToYou,Basebit,Bitinvest,flowBTC,Foxbit,LocalBitcoins,MercadoBitcoin,NegocieCoins};
	//<summary>
	//  função para traduzir pela legenda o nome da exchange
    //</summary>
	string LegendaExchanges(string id){
		if(id=="B2U")
			return "BitcoinToYou";
		if(id=="BAS")
			return "Basebit";
		if(id=="BIV")
			return "Bitinvest";
		if(id=="FLW")
			return "flowBTC";
		if(id=="FOX")
			return "Foxbit";
		if(id=="LOC")
			return "LocalBitcoins";
		if(id=="MBT")
			return "Mercado Bitcoin";
		if(id=="NEG")
			return "Negocie Coins";

        }
};


