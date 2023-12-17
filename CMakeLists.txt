cmake_minimum_required(VERSION 3.26)
project(flower)

set(CMAKE_CXX_STANDARD 20)

add_executable(flower
        main.cpp
        
        Order.h
        Order.cpp
        OrderBook.h
        OrderBook.cpp
        CSVHandler.h
        CSVHandler.cpp
        "TradeApplication.h"
        "TradeApplication.cpp"
        RecordBook.cpp
        RecordBook.h
)