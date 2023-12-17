#ifndef FLOWER_RECORDBOOK_H
#define FLOWER_RECORDBOOK_H


#include <queue>
#include "Order.h"

class RecordBook {
    queue<Order> record_queue;
public:
    void insertRecord(Order order, string exec_status);

    const queue<Order> &getRecordQueue() const;
};


#endif //FLOWER_RECORDBOOK_H
