
#ifndef FLOWER_ORDERBOOK_H
#define FLOWER_ORDERBOOK_H

#include <vector>
#include <queue>
#include "Order.h"
#include "utils.cpp"

using namespace std;

class OrderBook {
public:
    string instrument;
    priority_queue<Order, std::vector<Order>, BuyOrderComparator> buy_orders;
    priority_queue<Order, std::vector<Order>, SellOrderComparator> sell_orders;

    explicit OrderBook(string instrument);

    void addSellArr(const Order &order);

    void addBuyArr(const Order &order);


};


#endif //FLOWER_ORDERBOOK_H
