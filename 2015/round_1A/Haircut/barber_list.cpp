#include "barber_list.hpp"

barber_list::barber_list()
{

}

barber_list::~barber_list() {

}

void barber_list::add_barber(int efficiency) {
	barber newbarber(list.size(), efficiency, 0);
	list.push(newbarber);
}

int barber_list::add_client() {
	barber freebarber = list.top();

	int num = freebarber.m_num;

	freebarber.m_accu += freebarber.m_eff;

	list.pop();
	list.push(freebarber);

	return num;
}

bool barber_list::barber_comparison::operator()(const barber& lhs, const barber& rhs) {
	if (lhs.m_accu > rhs.m_accu)
		return true;
	
	if (lhs.m_accu < rhs.m_accu)
		return false;

	return lhs.m_num > rhs.m_num;
}


barber_list::barber::barber(int num, int eff, int accu)
	: m_num(num)
	, m_eff(eff)
	, m_accu(accu)
{
}
