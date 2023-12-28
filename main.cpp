#include "TradeApplication.h"
#include "CSVHandler.h"
#include <thread>


using namespace std;

int main(int argc, char* argv[])
{
  /*  if (argc != 2)
    {
        cout << "Please enter the input file path as an argument.\n";
        return 1;
    }*/

    const string INPUT_FILE_PATH = "../../../examples/ex5.csv";
    //const string INPUT_FILE_PATH = argv[1];

    cout << "start..." << endl;

    // read the csv file and store the orders in unordered map flower_fields
    CSVHandler read_file(INPUT_FILE_PATH);
    unordered_map<string, vector<Order>> new_order_map = read_file.convertCsvToOrderMap();

    Trade tradeInstance{};

    // Set up the order_map or any other configurations.
    tradeInstance.order_map = new_order_map;

    const int num_threads = 6;
    vector<thread> threads;

    for (string flower : read_file.uniqueFlowerNames )
    {
		threads.emplace_back(&Trade::processOrders, &tradeInstance, flower);
	}

    threads.emplace_back(&Trade::processErrorOrders, &tradeInstance);

    // Wait until threads are completed
    for (auto& thread : threads) {
        thread.join();
    }

    // making the final csv file
    CSVHandler write_file("execution_report.csv");
    write_file.writeToCsv(tradeInstance.recordBook.getRecordQueue());
    cout << "End..." << endl;
    return 0;
}