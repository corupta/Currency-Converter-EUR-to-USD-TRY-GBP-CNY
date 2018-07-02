#include <QPushButton>
#include "defs.h"

// a qpushbutton class that recieves the width, currency type and currency name
// instead of the classic clicked signal, it gives a signal with the currency type of the button
// currency type is an enum that is either of USD/TRY/GBP/CNY
// currency name is its string representation
class CurrencyButton : public QPushButton {
	Q_OBJECT

	private:
		// currencyType of this button
		CurrencyType currency;

	private slots:
		// function to be called when clicked, and emits a signal with the currency of this button
		void doWhenClicked();

	signals:
		// the signal to be emitted when this button is clicked
		void currencySelected(CurrencyType currency);
	public:
		// constructor that constructs a QPushButton, using the currencyName and width arguments
		// also sets the currency of this button class
		CurrencyButton(CurrencyType currency, QString currencyName, int width = 0, QWidget* parent = 0);

};
