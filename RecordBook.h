#ifndef FLOWER_RECORDBOOK_H
#define FLOWER_RECORDBOOK_H
#include <mutex>
#include <string>
#include <unordered_map>
#include <queue>
#include "Order.h"
#include <map>

class RecordBook {
    queue<Order> record_queue;
public:
    void insertRecords(queue<pair<Order, string>>& records);


    const queue<Order> &getRecordQueue() const;
};


#endif //FLOWER_RECORDBOOK_H
