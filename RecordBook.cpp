//
// Created by ACER on 12/14/2023.
//

#include <mutex>
#include "RecordBook.h"
mutex mtx;


void RecordBook::insertRecords(queue<pair<Order, string>>& records)
{
    lock_guard<mutex> lock(mtx);

    while (!records.empty())
    {
        pair<Order, string> record = records.front();
        records.pop();
        record.first.exec_status = std::move(record.second);
        this->record_queue.push(record.first);
    }
}
const queue<Order> &RecordBook::getRecordQueue() const {
    return record_queue;
}

#include "RecordBook.h"
