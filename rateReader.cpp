#include "rateReader.h"
#include <QRegExp>
#include <stdlib.h>
#include <string>

RateReader::RateReader() : connecting(true) {
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply *)), SLOT(replyFinished(QNetworkReply *)));
//	corupta.net is my site (I used it when I could not connect to api.fixer.io)
//	Deprecated with new fixer.io api 
//	manager -> get (QNetworkRequest(QUrl("http://fixer.corupta.net")));
//	Deprecated with new fixer.io api 
//	manager -> get (QNetworkRequest(QUrl("https://api.fixer.io/latest?base=TRY")));
	manager -> get (QNetworkRequest(QUrl("http://data.fixer.io/api/latest?access_key=5debd2b7adf29c0cf9932ce9ac61d628")));
	
}

QString RateReader::getCurrencyName(CurrencyType currency) {
	switch(currency) {
		case USD:
			return "USD";
		case TRY:
			return "TRY";
		case GBP:
			return "GBP";
		case CNY:
			return "CNY";
		default:
			return "";
	}
}

void RateReader::replyFinished(QNetworkReply* reply) {
	QString str;
	int pos = 0;
	QString data = (QString) reply -> readAll();
	std::string currencyNames[4] = {"USD", "TRY", "GBP", "CNY"};
	for (int i = 0; i < 4; ++i) {
		std::string myRx = "\"" + currencyNames[i] + "\":(\\d+.\\d+)";
		QRegExp rx(myRx.c_str());
		if (rx.indexIn(data, pos) != -1) {
			rates[i] = rx.cap(1).toDouble();
		} else {
			rates[i] = -1;
		}
	}
	connecting = false;
	emit connectionCompleted();
}
double RateReader::getRate(CurrencyType currency) {
	return rates[currency];
}
