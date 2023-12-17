#include "OrderBook.h"

OrderBook::OrderBook(std::string instrument) {
    this->instrument = std::move(instrument);
}

void OrderBook::addBuyArr(const Order& order)
{
    this->buy_orders.push(order);
}

void OrderBook::addSellArr(const Order& order)
{
    this->sell_orders.push(order);
}


