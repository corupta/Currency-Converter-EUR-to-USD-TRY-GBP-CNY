#include <QWidget>
#include <QApplication>
#include <QtGui>
#include "currencyConverter.h"
#include <iostream>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	CurrencyConverter currencyConverter;
	// program works in the constructor of this class

	return app.exec();
}
