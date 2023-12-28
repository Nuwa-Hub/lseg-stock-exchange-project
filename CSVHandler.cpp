#include "CSVHandler.h"


unordered_map<string, vector<Order>> CSVHandler::convertCsvToOrderMap()
{
	unordered_map<string, vector<Order>> order_map;
	ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		cerr << "Error opening file." << endl;
		return order_map;
	}

	string line;
    getline(inputFile, line); // Skip the first line (header)
	while (getline(inputFile, line))
	{
		istringstream lineStream(line);
		string field;
        vector<string> row = {  };

		while (getline(lineStream, field, ','))
		{
			row.push_back(field); // Store each field
		}
		// if final field is space or empty, remove it
		if (row.back().empty() || row.back() == " ")
		{
			row.pop_back();
		}
		Order order(row);
		if (order.error_message == "Accepted")
		{
			string flowerName = order.instrument;
			uniqueFlowerNames.insert(flowerName);
			order_map[flowerName].push_back(order);
		}
		else {
			string flowerName = "Error_Order";
			order_map[flowerName].push_back(order);
		}
		
	
	}

	inputFile.close(); // Close the file
	return order_map;
}

void CSVHandler::writeToCsv(queue<Order> trade_queue)
{
	ofstream outputFile(filename);
	if (!outputFile.is_open())
	{
		cerr << "Error opening output file." << endl;
		return;
	}

	// adds the header row first
	vector<string> trade_arr = { "Order ID", "Client Order ID", "Instrument", "Side",
								"Exec Status", "Quantity", "Price","Message"}; // header
	for (size_t i = 0; i < trade_arr.size(); ++i)
	{
		outputFile << trade_arr[i];
		if (i < trade_arr.size() - 1)
		{
			outputFile << ",";
		}
	}
	outputFile << endl;

	// Write each Order object as a CSVHandler row
	while (!trade_queue.empty())
	{
		Order top_order = trade_queue.front();
		trade_queue.pop();
		if (top_order.error_message != "Accepted")
		{
			outputFile
				<< top_order.order_id << "," 
				<< top_order.customer_id << ","
				<< top_order.instrument << ","
				<< top_order.side << ","
				<< top_order.exec_status << ","
				<< top_order.error_quantity << ","
				<< top_order.error_price << ","
				<< top_order.error_message << ","
				<< endl;
			continue;
		}	
		else {
			outputFile
				<< top_order.order_id << ","
				<< top_order.customer_id << ","
				<< top_order.instrument << ","
				<< top_order.side << ","
				<< top_order.exec_status << ","
				<< top_order.quantity << ","
				<< top_order.price << ","
				<< top_order.error_message << ","
				<< endl;
		}
	}

	// Close the output file
	outputFile.close();

	cout << "CSV file created successfully." << endl;
}







