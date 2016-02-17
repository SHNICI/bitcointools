#pragma once
#include <string>
#include <vector>
using namespace std;
class Data{
public:
	struct Timestamp {
		struct exchange{
			string id;
			long timeStampLastTrade; // timestamp do ultimo trade de cada exchange
			};
		public:
			vector<exchange> exchanges;
		};
	struct Ticker{
		struct exchange{
			string id;// Id da exchange
			double lastPrice; // ultimo preço do período em Reais
			double highPrice; // Maior Preço do período em Reais
			double lowPrice; // Menor Preço em Reais
			double volBTC; // Volume em BTC
			double averagePrice; // Preço médio em Reais no Período
			int tradesQty; // Quantidade de trades no período
			double money; // Volume em reais no período
			};
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


