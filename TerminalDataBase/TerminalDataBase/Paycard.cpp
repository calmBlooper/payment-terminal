#include "Paycard.h"

std::ostream& operator<<(std::ostream& out, const Paycard& p) {
	return out << "id-" << p.getId() << ":" << p.getAccountId() << '|' << p.getCardNumber() << '|' << p.getCvv() << '|' << p.getExpMonth() << '|' << p.getExpYear() << "|" << p.getPin() << "|" << std::endl;
}