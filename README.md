# Currency-Converter-TRY-to-USD-EUR-GBP-CNY
### QT Project - Currency Converter TRY to USD/EUR/GBP/CNY

## Project Details
That's a project I've created as a university homework for the course, CMPE 230 - Systems Programming on Dec 20th, 2017.

Basically, that's a QT project that fetches data from fixer.io and shows converts the given TRY amount to USD/EUR/GBP/CNY.
However, since the fixer.io api has changed and the free plan only supports base as EUR, I updated the project to convert from EUR to USD/TRY/GBP/CNY.

What the project is about can be found via [Project.pdf](https://github.com/corupta/Currency-Converter-EUR-to-USD-TRY-GBP-CNY/blob/master/Project.pdf)

That's a qt project, and I did not used qt designer.
QT4+ is supported. (Lower versions may also support but are not tested.)

## Compile

I've always compiled on terminal/command prompt as I explained below.

To be practical, I created the below script line to compile and run the project automatically.
(I am usung Ubuntu, it is similar to compile in Windows but be careful not to forget to add the line "QT += network" in the bottom of the generated Currency-Converter.pro)

qmake -project && echo "QT += network" >> Currency-Converter.pro && qmake Currency-Converter.pro && make && ./Currency-Converter

Add a '&' in the end to open the program in the background (not connected to terminal)

the line "QT += network" had to be appended on the .pro file, in order to use QNetworkAccessManager (to connect to and fetch data from api.fixer.io)

Program can be rebuild with that command, if interested.

The required files for that purpose are below:

main.cpp
currencyConverter.h and currencyConverter.cpp
currencyButton.h and currencyButton.cpp
rateReader.h and rateReader.cpp

## Run

Just double click on the Currency-Converter to run.

For more details about how to use the project, check out [Report-Documentation.pdf](https://github.com/corupta/Currency-Converter-EUR-to-USD-TRY-GBP-CNY/blob/master/Report-Documentation.pdf)
