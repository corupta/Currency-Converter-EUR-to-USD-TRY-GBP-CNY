#include <QtGui>
#include "rateReader.h"
#include "currencyButton.h"

// that is the main class
class CurrencyConverter : public QObject {
	Q_OBJECT

private:
	// current / last entered amount in turkish liras - default is 0
	double tryAmount;
	// current / last chosen currency type (an enum either of USD/EUR/GBP/CNY) - default is USD
	CurrencyType currentCurrency;

	// a class to get exchange rates for try from the api.fixer.io
	RateReader *myReader;

	// a slider to input tryAmount
	QSlider* inputSlider;
	// an input box to input tryAmount
	QDoubleSpinBox *inputNumber;
	// QLabels in which the results of the exchange to be presented
	// ratenumber is the rate of the chosen currency type over turkish liras
	// amountnumber is the tryAmount converted to the chosen currency type from turkish liras
	QLabel *rateNumber, *amountNumber;

	// the four buttons in buttom (USD/EUR/GBP/CNY)
	// since currency type is an enum of 0=USD, 1=EUR, 2=GBP, 3=CNY
	// button[USD] is the button with the label USD
	CurrencyButton* buttons[4];

	// a method that creates and returns a QLabel with the given label string, aligment and width
	static QLabel* createLabel(QString s, Qt::Alignment alignment, int width = 0);

private slots:
	// called when tryAmount changed / currentCurrency is changed / getting rates from the api succeeded.
	// rateNumber and amountNumber is calculated and presented.
	void calculateResult();
	// called when tryAmount is changed via spin box => changes tryAmount and calls calculateResult
	void updateInputAmount(double newValue);
	// called when tryAmount is changed via slider => multiplies the slider change by 0.50 and calls updateInputAmount with this value.
	// 0.50 is a number multiplier to have the slider(uses int) work with 1 billion range on a double with 2 decimals.
	void divideUpdateInputAmount(int intValue);
	// called when one of the buttons on the bottom are pressed
	// changes currentCurrency to the pressed button's currency and calls calculateResult
	void updateSelectedButton(CurrencyType newCurrency);

public:
	// constructor, where the whole widget is prepared and ran.
	CurrencyConverter(QWidget *parent = 0);
};
