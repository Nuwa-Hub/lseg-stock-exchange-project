#ifndef FLOWER_CSVHANDLER_H
#define FLOWER_CSVHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include "Order.h"

using namespace std;

class CSVHandler {
public:
    unordered_set<string> uniqueFlowerNames;

    explicit CSVHandler(string filename) : filename(std::move(filename)) {}

    unordered_map<string, vector<Order>> convertCsvToOrderMap();

    void writeToCsv(queue<Order> trade_queue);

private:
    string filename;
     

};


#endif //FLOWER_CSVHANDLER_H
