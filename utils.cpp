#ifndef ORDER_H
#define ORDER_H
#include "Order.h"


struct BuyOrderComparator {
    bool operator()(const Order& lhs, const Order& rhs) const {
        return lhs.price < rhs.price; // Change to > for descending order
    }
};

struct SellOrderComparator {
    bool operator()(const Order& lhs, const Order& rhs) const {
        return lhs.price > rhs.price; // Change to < for ascending order
    }
};

#endif // ORDER_H