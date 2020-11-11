#ifndef UTILS_H
#define UTILS_H

#include <QRegExp>
#include <QString>

class Utils{
public:
    static int maxNumberOfDigits;
    static int serviceType;
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
    static QRegExp login;
};
int Utils::serviceType = 0;
int Utils::maxNumberOfDigits = 0;
QRegExp Utils::emailRegex("");
QString Utils::service("");
QRegExp Utils::digits("[0-9]*");
QRegExp Utils::login("[A-Za-z_0-9]+");
QRegExp Utils::cardNumberRegex("(\\d{4}[ ]?){4}|\\d{4}[ ]?\\d{6}[ ]?\\d{5}");
QRegExp Utils::phoneRegex("^\\s*(?:\\+?(\\d{1,3}))?([-. (]*(\\d{3})[-. )]*)?((\\d{3})[-. ]*(\\d{2,4})(?:[-.x ]*(\\d+))?)\\s*$");
QRegExp Utils::monthRegex("01|02|03|04|05|06|07|08|09|10|11|12");
QRegExp Utils::yearRegex("^[2-9][0-9]");
QRegExp Utils::cvv2Regex("[0-9]{3}");
QRegExp Utils::sumOfTransferRegex("^([1]?[0-9]?[0-9]?[0-9]?[0-9])$|20000");
QString Utils::style_usual = "background-color: rgb(255, 255, 255); border-width: 3px; border-radius: 10px; border-color:  #331E38; border-style:solid; outline: 0;";
QString Utils::style_error = "background-color: rgb(255, 255, 255); border-width: 5px; border-radius: 10px; border-color:  red; border-style:solid; outline: 0;";
QRegExp Utils::pinRegex ("[0-9]{4}");
#endif // UTILS_H
