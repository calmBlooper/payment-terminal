#include "MobileAccount.h"

std::ostream& operator<<(std::ostream& out, const MobileAccount& pa) {
	return out << "id-" << pa.getId() << ":" << pa.getBalance() << pa.getCurrency() << ',' << pa.getNumber() << std::endl;
}