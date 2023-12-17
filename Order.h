#ifndef FLOWER_ORDER_H
#define FLOWER_ORDER_H

#include <iostream>
#include <vector>

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
    double order_flow;


    explicit Order(vector<string> &row);

private:
    static int nextOrderFlow;

    static bool validateRow(vector<std::string> &row);
};


#endif
