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
class ScreenPosition {
public:
    ScreenPosition() {};
    ~ScreenPosition() {};
    void record(int type, int touchid, float a, float b);
    void createMessage();
    int getSleepTimeSpan();
    friend std::ifstream& operator>>(std::ifstream &is, ScreenPosition &sposition);
    friend std::ofstream& operator<<(std::ofstream &os, const ScreenPosition &dump); 
private:
    int timeSpan;
    int eventType;
    int touchId;
    float x;
    float y;
};
#endif
