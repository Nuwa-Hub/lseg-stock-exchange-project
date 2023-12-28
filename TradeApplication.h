#ifndef FLOWER_TRADE_H
#define FLOWER_TRADE_H

#include <vector>
#include <queue>
#include <mutex>
#include <unordered_map>
#include "Order.h"
#include "OrderBook.h"
#include "RecordBook.h"

using namespace std;
extern mutex mtx;

class Trade {
public:
    RecordBook recordBook;
    unordered_map<string, vector<Order>> order_map;

    void processOrders(const string &flower);
    void processErrorOrders();

private:

    void processBuyOrders(OrderBook &order_book, Order &order);

    void processSellOrders(OrderBook &order_book, Order &order);

};


#endif
