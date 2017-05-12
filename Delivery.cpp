#include "Delivery.h"

Delivery::Delivery() {	}	
Delivery::Delivery(string name, int numItem, int rtMinute) {
	m_name = name;
	m_numItem = numItem;
	m_rtMinute = rtMinute;
}

string Delivery::GetName() const {
	return m_name;
}

int Delivery::GetNumItem() const {
	return m_numItem;
}

int Delivery::GetRTMinute() const {
	return m_rtMinute;
}