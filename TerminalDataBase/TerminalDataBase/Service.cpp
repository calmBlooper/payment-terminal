#include "Service.h"

std::ostream& operator<<(std::ostream& out, const Service& s) {
	return out << "id-" << s.getId() << ":" << s.getName() << '(' << s.getServiceType() << ")," << s.getCommission() << '%' << std::endl;
}