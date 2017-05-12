#include "ReadyDelivery.h"

ReadyDelivery::ReadyDelivery() {	}

ReadyDelivery::ReadyDelivery(string truckFile, string deliveryFile, string itemFile) {
	m_truckFile = truckFile;
	m_deliveryFile = deliveryFile;
	m_itemFile = itemFile;
	LoadTruck();
	LoadDelivery();
	LoadItem();
}

void ReadyDelivery::LoadTruck() {
	vector<string> tokens;
	ifstream file(m_truckFile.c_str());
	string a, b;
	for (string line; getline(file, line);) {
		istringstream strm(line);
		strm >> a;
		strm >> b;
		// add tokens contents to m_truck vector
		m_truck.push_back(Truck<Item, MAX_CAPACITY>(a, atoi(b.c_str())));
	}
}

void ReadyDelivery::LoadDelivery() {
	vector<string> tokens;
	ifstream file(m_deliveryFile.c_str());
	string a, b, c;
	for (string line; getline(file, line);) {
		istringstream strm(line);
		strm >> a;
		strm >> b;
		strm >> c;
		m_delivery.push_back(Delivery(a, atoi(b.c_str()), atoi(c.c_str())));
	}
}

void ReadyDelivery::LoadItem() {
	vector<string> tokens;
	ifstream file(m_itemFile.c_str());
	string a, b;
	for (string line; getline(file, line);) {
		istringstream strm(line);
		strm >> a;
		strm >> b;
		// add tokens contents to m_item vector
		m_item.push_back(Item(a, atof(b.c_str())));
	}
}

vector< Truck<Item, MAX_CAPACITY> >& ReadyDelivery::GetTruck() {
	return m_truck;
}

vector<Delivery> ReadyDelivery::GetDelivery() {
	return m_delivery;
}

vector<Item> ReadyDelivery::GetItem() {
	return m_item;
}