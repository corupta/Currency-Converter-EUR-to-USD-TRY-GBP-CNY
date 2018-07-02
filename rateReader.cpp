#include "rateReader.h"
#include <QRegExp>
#include <stdlib.h>
#include <string>

RateReader::RateReader() : connecting(true) {
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply *)), SLOT(replyFinished(QNetworkReply *)));
//	corupta.net is my site (I used it when I could not connect to api.fixer.io)
//	manager -> get (QNetworkRequest(QUrl("http://fixer.corupta.net")));
	manager -> get (QNetworkRequest(QUrl("https://api.fixer.io/latest?base=TRY")));
}

QString RateReader::getCurrencyName(CurrencyType currency) {
	switch(currency) {
		case USD:
			return "USD";
		case EUR:
			return "EUR";
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
	std::string currencyNames[4] = {"USD", "EUR", "GBP", "CNY"};
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
