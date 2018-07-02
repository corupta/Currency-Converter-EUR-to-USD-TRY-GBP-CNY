#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "defs.h"

// NOTE: instead of fetching rates on each button click, we've decided to cache the results and use it on all button clicks
// In fact, after caching the results, we were able to have the program calculate the conversion results not only when buttons were clicked
// but also when the input for turkish liras were changed too. Since the program doesn't need to send a new http request for each conversion
// which would create a big overhead, thus require less conversion (only on button clicks).
// Also, fixer.io specifically asked for "Please cache results whenever possible."
class RateReader : public QObject {
	Q_OBJECT

	public:
		// constructor that sets connecting to 0, and makes the rate request to api.fixer.io
		// requests api.fixer.io/latest?base=TRY to fetch the rates for all currency types from TRY by one http request
		// so that both api.fixer.io's servers and this program would need less internet connection & work faster.
		// (good for fixer.io and they have specifically wanted such usage by telling "Please cache results whenever possible.")
		RateReader();
		// a function that returns the rate for a given currency type (USD/EUR/GBP/CNY)
		double getRate(CurrencyType);
		// returns the name of a given currency type (USD/EUR/GBP/CNY) as a string (USD -> "USD", etc.)
		QString getCurrencyName(CurrencyType currency);
		// true until the connection & getting rates from api.fixer.io is completed.
		bool connecting;

	signals:
		// a signal emitted when the connection is completed => so that the main object can call calculation functions from now on.
		void connectionCompleted();

	private slots:
		// called when the network connection finished with a reply (api.fixer.io)
		// extract USD, EUR, GBP, CNY rates from the json reply, using regexes.
		void replyFinished(QNetworkReply *reply);

	private:
		// an array to store fetched rates for currencies (USD/EUR/GBP/CNY)
		// note that CurrencyType is an enum where USD=0, EUR=1, GBP=2, CNY=3
		double rates[4];
		// NetworkAccessManager used to communicate via api.fixer.io
		QNetworkAccessManager *manager;
};
