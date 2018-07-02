#include "currencyButton.h"

CurrencyButton::CurrencyButton(CurrencyType currency, QString currencyName, int width, QWidget* parent)
	: QPushButton(parent), currency(currency) {
	setText(currencyName);
	if (width) { // width is not 0
		setFixedWidth(width);
	}
	connect(this, SIGNAL(clicked()), SLOT(doWhenClicked()));
}

void CurrencyButton::doWhenClicked() {
	emit currencySelected(currency);
}

