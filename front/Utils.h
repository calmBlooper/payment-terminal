#ifndef UTILS_H
#define UTILS_H

#include <QRegExp>
#include <QString>

class Utils{
public:
    static int pin_times;
    static int maxNumberOfDigits;
    static QString service;
    static QRegExp emailRegex;
    static QRegExp digits;
    static QRegExp cardNumberRegex;
    static QRegExp phoneRegex;
    static QRegExp monthRegex;
    static QRegExp yearRegex;
    static QRegExp cvv2Regex;
    static QRegExp sumOfTransferRegex;
    static QRegExp pinRegex;
    static QString style_usual;
    static QString style_error;
    static QString exeption_style;
    static QRegExp login;
    static QRegExp any;
};
#endif // UTILS_H
