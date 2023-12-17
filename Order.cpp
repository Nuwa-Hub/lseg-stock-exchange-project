#include "Order.h"
#include <string>


int Order::nextOrderFlow = 1;

Order::Order(vector<std::string> &row)    {

    if (validateRow(row)) {
        order_flow = nextOrderFlow++;
        customer_id = row[0];
        instrument = row[1];
        side = row[2];
        quantity = stoi(row[3]);
        price = stoi(row[4]);
    }

}

bool Order::validateRow(vector<std::string>& row) {
    try
    {
        if (stoi(row[3]) < 0 || stoi(row[4]) < 0) {
            return false;
        }
    }
    catch (...)
    {
        return false;
    }
    //TODO: add more validations
    return true;
}