#ifndef FLOWER_ORDER_H
#define FLOWER_ORDER_H

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Order {
public:
    string customer_id;
    string instrument;
    string side;
    int quantity;
    int price;
    string order_id;
    string exec_status;
    string error_price;
    string error_quantity;
    string error_message;

    explicit Order(vector<string> &row);

private:
    static int nextOrderFlow;
    static unordered_set<std::string> uniqueIds;

    static string validateRow(vector<std::string> &row);

    static bool isValidNumber(const string& str);
};


#endif
