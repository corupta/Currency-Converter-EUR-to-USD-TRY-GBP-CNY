#include <QString>

#ifndef DEFS
#define DEFS

// a safe way to check whether two doubles are equal
#define EPSILON 1e-6
#define doubleEquals(a, b) ((a) + EPSILON > (b) && (b) + EPSILON > (a))

// an enum to represent currency types USD/TRY/GBP/CNY
enum CurrencyType { USD, TRY, GBP, CNY };

#endif
