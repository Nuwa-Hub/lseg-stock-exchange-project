#include "TradeApplication.h"

void Trade::processOrders(const std::string& flower)
{
	vector<Order> flower_rows = this->order_map[flower];

	OrderBook order_book(flower);


	for (auto order : flower_rows)
	{

		string order_id = "ord";
		order_id.append(to_string(static_cast<int>(order.order_flow)));
		order.order_id = order_id;

		if (order.side == "1")
		{
			processBuyOrders(order_book, order);
			if (order.quantity != 0)
			{
				order_book.addBuyArr(order);
			}
		}
		else
		{
			processSellOrders(order_book, order);
			if (order.quantity != 0)
			{
				order_book.addSellArr(order);
			}
		}
	}
}


void Trade::processBuyOrders(OrderBook& order_book, Order& order)
{
	priority_queue<Order, std::vector<Order>, SellOrderComparator>* sell_book = &order_book.sell_orders;

	queue<pair<Order, string>> orderStatusMap;

	if (sell_book->empty())
	{
		orderStatusMap.push(std::make_pair(order, "New"));
	}
	else
	{
		if (sell_book->top().price > order.price)
		{
			orderStatusMap.push(std::make_pair(order, "New"));
          
		}
		else
		{
			while (order.quantity != 0)
			{
				if (sell_book->top().price > order.price)
				{
					break;
				}
				int sell_quantity = (sell_book->top().quantity);
				int buy_quantity = (order.quantity);
				int row_price = order.price;
				int sell_price = sell_book->top().price;

				order.price = sell_price;

				if (sell_quantity > buy_quantity)
				{
					Order top_sell_order = sell_book->top();
					top_sell_order.quantity = buy_quantity;
					sell_book->pop();
					sell_book->push(top_sell_order);
					orderStatusMap.push(std::make_pair(order, "Fill"));
                    
					order.quantity = 0;
					orderStatusMap.push(std::make_pair(order, "PFill"));
                    
					top_sell_order = sell_book->top();
					top_sell_order.quantity = sell_quantity - buy_quantity;
					sell_book->pop();
					sell_book->push(top_sell_order);
					break;
				}
				else if (sell_quantity < buy_quantity)
				{
					order.quantity = sell_quantity;
					orderStatusMap.push(std::make_pair(order, "PFill"));
                    
					order.price = row_price;
					order.quantity = buy_quantity - sell_quantity;
					orderStatusMap.push(std::make_pair(sell_book->top(), "Fill"));
                   
					sell_book->pop();
				}
				else
				{
					orderStatusMap.push(std::make_pair(sell_book->top(), "Fill"));
					orderStatusMap.push(std::make_pair(sell_book->top(), "Fill"));
                  
					sell_book->pop();
					order.quantity = 0;
					break;
				}
			}
		}
		
	}
	this->recordBook.insertRecords(orderStatusMap);
}

void Trade::processSellOrders(OrderBook& order_book, Order& order)
{
	priority_queue<Order, vector<Order>, BuyOrderComparator>* buy_book = &order_book.buy_orders;
	queue<pair<Order, string>> orderStatusMap;


	if (buy_book->empty())
	{
		orderStatusMap.push(std::make_pair(order, "New"));
       
	}
	else
	{
		if (buy_book->top().price < order.price)
		{
			orderStatusMap.push(std::make_pair(order, "New"));
           
		}
		else
		{
			while (order.quantity != 0)
			{

				if (buy_book->empty())
				{
					break;
				}
				if (buy_book->top().price < order.price)
				{
					break;
				}
				int buy_quantity = buy_book->top().quantity;
				int sell_quantity = (order.quantity);
				int row_price = order.price;
				int buy_price = buy_book->top().price;
				order.price = buy_price;

				if (buy_quantity > sell_quantity)
				{
					Order top_buy_order = buy_book->top();
					top_buy_order.quantity = sell_quantity;
					buy_book->pop();
					buy_book->push(top_buy_order);
					orderStatusMap.push(std::make_pair(order, "Fill"));
                    
					order.quantity = 0;
					orderStatusMap.push(std::make_pair(buy_book->top(), "Fill"));
                   
					top_buy_order = buy_book->top();
					top_buy_order.quantity = buy_quantity - sell_quantity;
					buy_book->pop();
					buy_book->push(top_buy_order);
					break;
				}
				else if (buy_quantity < sell_quantity)
				{
					order.quantity = buy_quantity;
					orderStatusMap.push(std::make_pair(order, "PFill"));
                   
					order.price = row_price;
					order.quantity = sell_quantity - buy_quantity;
					orderStatusMap.push(std::make_pair(buy_book->top(), "Fill"));
					buy_book->pop();

				}
				else
				{
					orderStatusMap.push(std::make_pair(buy_book->top(), "Fill"));
					orderStatusMap.push(std::make_pair(buy_book->top(), "Fill"));
					buy_book->pop();
					order.quantity = 0;
					break;
				}
			}
		}
		
	}
	this->recordBook.insertRecords(orderStatusMap);
}


