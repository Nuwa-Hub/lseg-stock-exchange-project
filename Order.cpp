#include "Order.h"
#include <string>


int Order::nextOrderFlow = 1;
unordered_set<std::string> Order::uniqueIds;

Order::Order(vector<std::string> &row)    {
    const string& message = validateRow(row);
    
    if (message == "Accepted") {
        order_id = "ord"+ to_string(nextOrderFlow++);
        customer_id = row[0];
        instrument = row[1];
        side = row[2];
        quantity = stoi(row[3]);
        price = stoi(row[4]);
        error_message = message;
    }
    else {
        order_id = "ord" + to_string(nextOrderFlow++);
        customer_id = row[0];
        instrument = row[1];
        side = row[2];
        error_quantity = row[3];
        error_price =row[4];
        error_message = message;
	}

}

bool Order::isValidNumber(const string& str) {
    try {
        if (stoi(str) > 0) {
            return true;
        }
        return false;
    }
    catch (...) {
        return false;
    }
}

string Order::validateRow(vector<std::string>& row) {

    if (uniqueIds.find(row[0]) != uniqueIds.end()) {
        return "ID column should be unique!";
    }
    else {
        uniqueIds.insert(row[0]);
    }
    if (row.size() != 5) {
       
		return "Row should have 5 columns!";
	}
    if (!isValidNumber(row[3])) {
        return "Quntity column should be valid!";
    }
    if (!isValidNumber(row[4])) {
		return "Price column should be valid!";
	}
    if (row[2] != "2" && row[2] != "1") {
		return "Side column should be either Buy or Sell!";
	}
    if (row[1] != "Rose" && row[1] != "Lavender" && row[1] != "Tulip" && row[1] != "Orchid" && row[1] != "Lotus") {
        return "Instrument column should be either Rose, Lavender, Tulip, Orchid or Lotus!";
    }
    
    //TODO: add more validations
    return "Accepted";
}