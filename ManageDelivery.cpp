#include "ManageDelivery.h"

ManageDelivery::ManageDelivery(vector< Truck <Item, MAX_CAPACITY> > truck,
	vector< Delivery > delivery,
	vector< Item > item) {
	m_truck = truck;
	m_delivery = delivery;
	m_item = item;
	StartDelivery();
}

void ManageDelivery::StartDelivery() {
	cout << "Trucks Loaded: " << m_truck.size() << endl;
	cout << "Deliveries Loaded: " << m_delivery.size() << endl;
	cout << "Items Loaded: " << m_item.size() << endl;
	cout << "Start Time: 0" << endl << endl;
	// separate deliveries into respective trucks, while maintaining truck capacity
	int currentCapacity;
	int numDeliveriesProcessed = 0;
	int full = 0;
	int numTruckItems = 0;
	int offsetIndex = 0;
	int currentItemFloor = 0;
	// full or ready to deliver
	bool fullTruck = false;
	bool trucksHaveDeliveriesLeft = true;
	// while there are deliveries left to process
	while (trucksHaveDeliveriesLeft) {
		// if all deliveries have been processed
		if (numDeliveriesProcessed == m_delivery.size()) {
			trucksHaveDeliveriesLeft = false;
			// hack the m_item array to store a value that DisplayItemLeft requires
			m_item.push_back(Item("tmp", offsetIndex));
			DisplayItemLeft();
		}
		// if all deliveries have not be processed
		else {
			// for each truck
			for (int i = 0; i < m_truck.size(); i++) {
				fullTruck = false;
				// reset values when the next truck in the loop is being evaluated 
				numTruckItems = 0;
				currentCapacity = 0;
				currentItemFloor = 0;
				// for each delivery not processed yet
				for (int j = numDeliveriesProcessed; j < m_delivery.size(); j++) {
					// if adding the next delivery does NOT exceed the current truck's capacity OR the truck contains all or the last deliveries
					if (currentCapacity + m_delivery[j].GetNumItem() <= m_truck[i].GetCapacity()) {
						// this delivery has been processed
						numDeliveriesProcessed++;

						currentCapacity += m_delivery[j].GetNumItem();
						m_truck[i].AddDelivery(m_delivery[j]);
					}
					// if adding the next delivery does exceed the current truck's capacity
					else {
						// increment $full, this represents the number of trucks that are full and can't add new deliveries
						fullTruck = true;
					}
				}
				// for each delivery
				for (int a = 0; a < m_truck[i].GetDelivery().size(); a++) {
					// set numTruckItems equal to the number of items in each delivery
					numTruckItems += m_truck[i].GetDelivery()[a].GetNumItem();
				}
				cout << "*****Loading Truck (" + m_truck[i].GetName() + ")*****" << endl;
				// for each item in m_item (offset)
				// this loops starts at the previous delivery's ending index
				// this loop ends at the maximum number of items in the truck's delivery
				for (int j = currentItemFloor + offsetIndex; j < numTruckItems + offsetIndex; j++) {

						// DEBUG:
						//cout << "Truck: " << i + 1 << ", item floor: " << currentItemFloor << ", actual index: " << j << ", item ceiling: " << numTruckItems + offsetIndex << ", trucks items: " << numTruckItems << ", offset: " << offsetIndex << endl;
						
						cout << m_item[j].GetName() + " loaded into " + m_truck[i].GetName() << endl;

				}
				// offset index
				offsetIndex += numTruckItems;
				// if the current truck does not have deliveries left
				cout << endl;		
				// if the current truck is full
				if (fullTruck || numDeliveriesProcessed == m_delivery.size()) {
					// deliver its items
					DeliverItem(i);
					// and reset its delivery vector
					m_truck[i].CompleteDelivery();
				}
			}
		}
	}
}

//should be called ManageTruckDelivery (int truck) {}
void ManageDelivery::DeliverItem(int j) {
	cout << "**Truck name: " + m_truck[j].GetName() + "**" << endl;
	if (m_truck[j].GetDelivery().size() == 0) {
		cout << "No deliveries" << endl;
	}
	int rtTime = 10;
	// for all deliveries in current truck (truck number j)
	for (int i = 0; i < m_truck[j].GetDelivery().size(); i++) {
		// add the current delivery's RTMinute to the truck's time (truck's time = 0 for its first run to a customer)
		rtTime += m_truck[j].GetDelivery()[i].GetRTMinute() + m_truck[j].GetTime();
		cout << "***********Delivery " << i + 1 << "***********" << endl;
		cout << "Delivery Time: " << rtTime << endl;
		cout << "Delivery For: " << m_truck[j].GetDelivery()[i].GetName() << endl;
		cout << "Delivered: " << m_truck[j].GetDelivery()[i].GetNumItem() << endl;
		// if last delivery in loop
		if (i == m_truck[j].GetDelivery().size() - 1) {
			// add this run's time to the truck's total time, which is going to be greater than zero for the next run
			m_truck[j].SetTime(rtTime);
		}
	}
	cout << endl;
}

void ManageDelivery::DisplayItemLeft() {
	// offset m_item to compensate for the previous items that were delivered 
	// would use tqueue for this, but it's useless in its current implementation ;)
	int offset = m_item[m_item.size() - 1].GetWeight();
	cout << "*****Items Left After Deliveries*****" << endl;
	// if there are items left
	if (m_item.size() - 1 - offset != 0) {
		// for all items left
		for (int i = offset - 1; i < m_item.size() -1; i++) {
			cout << "Item " << i - offset + 2 << " - Name: " + m_item[i].GetName() + " - Weight: " << m_item[i].GetWeight() << endl;
		}
	}
	else {
		cout << "No remaining items." << endl;
	}
}