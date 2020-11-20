#include "Utils.h"
int Utils::maxNumberOfDigits = 0;
int Utils::pin_times = 3;
QRegExp Utils::emailRegex("");
QString Utils::service("");
QRegExp Utils::digits("[0-9]*");
QRegExp Utils::any(".+");
QRegExp Utils::login("[A-Za-z_0-9]+");
QRegExp Utils::cardNumberRegex("(\\d{4}[ ]?){4}|\\d{4}[ ]?\\d{6}[ ]?\\d{5}");
QRegExp Utils::phoneRegex("^\\s*(?:\\+?(\\d{1,3}))?([-. (]*(\\d{3})[-. )]*)?((\\d{3})[-. ]*(\\d{2,4})(?:[-.x ]*(\\d+))?)\\s*$");
QRegExp Utils::monthRegex("0?[1-9]|1[0-2]");
QRegExp Utils::yearRegex("^[2-9][0-9]");
QRegExp Utils::cvv2Regex("[0-9]{3}");
QRegExp Utils::sumOfTransferRegex("^([1]?[0-9]?[0-9]?[0-9]?[0-9])$|20000");
QString Utils::style_usual = "background-color: rgb(255, 255, 255); border-width: 3px; border-radius: 10px; border-color:  #331E38; border-style:solid; outline: 0;";
QString Utils::style_error = "background-color: rgb(255, 255, 255); border-width: 5px; border-radius: 10px; border-color:  red; border-style:solid; outline: 0;";
QString Utils::exeption_style = "background-color: #331E38;border-radius: 10px;border-width: 3px;border-color:  #d30000;border-style:solid;color:#d30000; outline : 0;";
QRegExp Utils::pinRegex("[0-9]{4}");


