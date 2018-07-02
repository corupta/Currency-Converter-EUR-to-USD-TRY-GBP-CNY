#include "currencyConverter.h"

CurrencyConverter::CurrencyConverter(QWidget *parent) : QObject(parent) {
	myReader = new RateReader();
	tryAmount = 0.0;
	currentCurrency = USD;
	connect(myReader, SIGNAL(connectionCompleted()), SLOT(calculateResult()));

	QWidget *window = new QWidget;
	window -> setWindowTitle("Currency Converter by Halit & Yusuf for CMPE 230");

	inputNumber = new QDoubleSpinBox();
	inputNumber -> setDecimals(2);
	inputNumber -> setRange(0, 1e9);
	inputNumber -> setSingleStep(0.01);
	inputNumber -> setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	inputSlider = new QSlider(Qt::Horizontal);
	inputSlider -> setRange(0, 2e9);
	connect(inputNumber, SIGNAL(valueChanged(double)), SLOT(updateInputAmount(double)));
	connect(inputSlider, SIGNAL(valueChanged(int)), SLOT(divideUpdateInputAmount(int)));

	rateNumber = createLabel("Connecting...", Qt::AlignRight);
	amountNumber = createLabel("Connecting...", Qt::AlignRight);

	int leftSize = 120;
	for (int i = USD; i <= CNY; ++i) {
		buttons[i] = new CurrencyButton((CurrencyType)i, myReader -> getCurrencyName((CurrencyType)i), leftSize);
		connect(buttons[i], SIGNAL(currencySelected(CurrencyType)),
			this, SLOT(updateSelectedButton(CurrencyType)));
	}

	QHBoxLayout *inputRow = new QHBoxLayout;
	inputRow -> addStretch();
	inputRow -> addWidget(inputSlider);
	inputRow -> addWidget(inputNumber);
	inputRow -> addWidget(createLabel("EUR", Qt::AlignLeft));

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout -> addWidget(createLabel("EUR :", Qt::AlignCenter, leftSize));
	leftLayout -> addWidget(createLabel("Rate :", Qt::AlignCenter, leftSize));
	leftLayout -> addWidget(createLabel("Amount :", Qt::AlignCenter, leftSize));

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout -> addLayout(inputRow);
	rightLayout -> addWidget(rateNumber);
	rightLayout -> addWidget(amountNumber);

	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout -> addLayout(leftLayout);
	topLayout -> addLayout(rightLayout);

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	for (int i = 0; i < 4; ++i) {
		bottomLayout -> addWidget(buttons[i]);
	}

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout -> addLayout(topLayout);
	mainLayout -> addLayout(bottomLayout);

	mainLayout -> setSpacing(12);
	mainLayout -> setMargin(16);
	QFont myFont("Monospace", 16, QFont::Bold);
	QColor bgColor(210, 220, 140), fgColor(0, 60, 120);
	QPalette myPalette;
	myPalette.setColor(QPalette::Window, bgColor);
	myPalette.setColor(QPalette::Text, fgColor);
	myPalette.setColor(QPalette::WindowText, fgColor);
	window -> setFont(myFont);
	window -> setPalette(myPalette);

	window -> setLayout(mainLayout);
	window -> show();
}

QLabel* CurrencyConverter::createLabel(QString s, Qt::Alignment alignment, int width) {
	QLabel *result = new QLabel(s);
	result -> setAlignment(alignment | Qt::AlignVCenter);
	if (width) { // width is not 0
		result -> setFixedWidth(width);
	}
	return result;
}

void CurrencyConverter::calculateResult() {
	if (myReader -> connecting) {
		return;
	}
	double currRate = myReader -> getRate(currentCurrency);
	double convertedAmount = currRate * tryAmount;
	QString currencyName = myReader -> getCurrencyName(currentCurrency);
	QString rateResult = QString("%1").arg(currRate, 0, 'f') + " EUR/" + currencyName;
	QString amountResult = QString("%1").arg(convertedAmount, 0, 'f', 2) + " " + currencyName;
	rateNumber -> setText(rateResult);
	amountNumber -> setText(amountResult);
}

void CurrencyConverter::divideUpdateInputAmount(int intValue) {
	// EPSILON is a tiny number to prevent double errors. 
	// (Such as 100 being stored as 99.9999999...)
	int oldIntValue = (tryAmount + EPSILON) / 0.50;
	if (intValue != oldIntValue) {
		double newValue = intValue * 0.50;
		updateInputAmount(newValue);
	}
}

void CurrencyConverter::updateInputAmount(double newValue) {
	if (!doubleEquals(tryAmount, newValue)) {
		int newIntValue = (newValue + EPSILON) / 0.50;
		tryAmount = newValue;
		inputNumber -> setValue(newValue);
		inputSlider -> setValue(newIntValue);
		calculateResult();
	}
}

void CurrencyConverter::updateSelectedButton(CurrencyType newCurrency) {
	if (currentCurrency != newCurrency) {
		currentCurrency = newCurrency;
		calculateResult();
	}
}
