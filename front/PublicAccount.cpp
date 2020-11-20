#include "PublicAccount.h"

std::ostream& operator<<(std::ostream& out, const PublicAccount& pa) {
	return out << "id-" << pa.getId() << ":" << pa.getBalance() << pa.getCurrency() << ',' << pa.getName() << " " << pa.getAddress() << std::endl;
}