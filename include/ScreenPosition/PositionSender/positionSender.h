#include <fstream>
#include <iostream>
#include <chrono>
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/assign.hpp"
using namespace boost;
using namespace boost::assign;
#ifndef _DUMP_H
#define _DUMP_H
class PositionSender {
public:
    PositionSender() {};
    ~PositionSender() {};
    void record(int type, int touchid, float a, float b);
    void createMessage();
    int getSleepTimeSpan();
    bool isEmpty();
    friend std::ifstream& operator>>(std::ifstream &is, PositionSender &sposition);
    friend std::ofstream& operator<<(std::ofstream &os, const PositionSender &dump); 
private:
    int timeSpan;
    int eventType;
    int touchId;
    float x;
    float y;
    bool isEmptyStr = false;
};
#endif
