#include "TradeApplication.h"

void Trade::executeOrders(const std::string& flower)
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

	

	if (sell_book->empty())
	{

        this->recordBook.insertRecord(order, "New");
	}
	else
	{
		if (sell_book->top().price > order.price)
		{
            this->recordBook.insertRecord(order, "New");
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
                    this->recordBook.insertRecord(order, "Fill");
					order.quantity = 0;
                    this->recordBook.insertRecord(sell_book->top(), "PFill");
					top_sell_order = sell_book->top();
					top_sell_order.quantity = sell_quantity - buy_quantity;
					sell_book->pop();
					sell_book->push(top_sell_order);
					break;
				}
				else if (sell_quantity < buy_quantity)
				{
					order.quantity = sell_quantity;
                    this->recordBook.insertRecord(order, "PFill");
					order.price = row_price;
					order.quantity = buy_quantity - sell_quantity;
                    this->recordBook.insertRecord(sell_book->top(), "Fill");
					sell_book->pop();
				}
				else
				{
                    this->recordBook.insertRecord(order, "Fill");
                    this->recordBook.insertRecord(sell_book->top(), "Fill");
					sell_book->pop();
					order.quantity = 0;
					break;
				}
			}
		}
		
	}
}

void Trade::processSellOrders(OrderBook& order_book, Order& order)
{
	priority_queue<Order, vector<Order>, BuyOrderComparator>* buy_book = &order_book.buy_orders;

	if (buy_book->empty())
	{
        this->recordBook.insertRecord(order, "New");
	}
	else
	{
		if (buy_book->top().price < order.price)
		{

            this->recordBook.insertRecord(order, "New");
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
                    this->recordBook.insertRecord(order, "Fill");
					order.quantity = 0;
                    this->recordBook.insertRecord(buy_book->top(), "PFill");
					top_buy_order = buy_book->top();
					top_buy_order.quantity = buy_quantity - sell_quantity;
					buy_book->pop();
					buy_book->push(top_buy_order);
					break;
				}
				else if (buy_quantity < sell_quantity)
				{
					order.quantity = buy_quantity;
                    this->recordBook.insertRecord(order, "PFill");
					order.price = row_price;
					order.quantity = sell_quantity - buy_quantity;
                    this->recordBook.insertRecord(buy_book->top(), "Fill");
					buy_book->pop();

				}
				else
				{
                    this->recordBook.insertRecord(order, "Fill");
                    this->recordBook.insertRecord(buy_book->top(), "Fill");
					buy_book->pop();
					order.quantity = 0;
					break;
				}
			}
		}

	}
}


