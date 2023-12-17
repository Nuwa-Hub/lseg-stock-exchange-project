//
// Created by ACER on 12/14/2023.
//

#include <mutex>
#include "RecordBook.h"
mutex mtx;
void RecordBook::insertRecord(Order order, string exec_status)
{
    lock_guard<mutex> lock(mtx);
    order.exec_status = std::move(exec_status);
    this->record_queue.push(order);
}

const queue<Order> &RecordBook::getRecordQueue() const {
    return record_queue;
}

#include "RecordBook.h"
