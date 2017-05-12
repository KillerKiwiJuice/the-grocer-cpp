#include "Item.h"

Item::Item() {	}

Item::Item(string iName, float iWeight) {
	m_name = iName;
	m_weight = iWeight;
}

string Item::GetName() const {
	return m_name;
}

float Item::GetWeight() const {
	return m_weight;
}