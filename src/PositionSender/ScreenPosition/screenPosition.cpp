#include <fstream>
#include <iostream>
#include <chrono>
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/assign.hpp"
#include "screenPosition.h"
#include "messageManager.h"
#include "boost/tokenizer.hpp"
#include "boost/typeof/typeof.hpp"
#include "boost/lexical_cast.hpp"

using namespace boost;

void ScreenPosition::record(int type, int tid, float a, float b) {
    eventType = type;
    touchId = tid;
    x = a;
    y = b;
}
int ScreenPosition::getSleepTimeSpan() {
    return timeSpan;
}

void ScreenPosition::createMessage() {
    MessageManager::getInstance().createMessage(eventType, touchId, x, y);
}

std::ofstream& operator<<(std::ofstream &os, const ScreenPosition &dump) {
    static std::chrono::steady_clock::time_point pr = std::chrono::steady_clock::now();
    static bool isEntry = true;
    std::vector<std::string> v;
    if (isEntry) {
        v = list_of (lexical_cast<std::string>(0))
                    (lexical_cast<std::string>(dump.eventType))
                    (lexical_cast<std::string>(dump.touchId))
                    (lexical_cast<std::string>(dump.x))
                    (lexical_cast<std::string>(dump.y));
        isEntry = false;
    } else {
        std::chrono::steady_clock::time_point tmp = pr;
        pr = std::chrono::steady_clock::now();
        v = list_of (lexical_cast<std::string>(std::chrono::duration_cast<std::chrono::milliseconds>(pr - tmp).count()))
                    (lexical_cast<std::string>(dump.eventType))
                    (lexical_cast<std::string>(dump.touchId))
                    (lexical_cast<std::string>(dump.x))
                    (lexical_cast<std::string>(dump.y));
    }
    os << join(v, ",") << std::endl; 
}

std::ifstream& operator>>(std::ifstream &ifs, ScreenPosition &sposition) {
    std::string str;
    ifs >> str;
    if (str.empty()) return ifs;
    //tmp.c_str returns a const char *, steps below create a char * and copy values;
    //char *cstr = new char [tmp.length() + 1]; 
    //std::strcpy(cstr, tmp.c_str());
    escaped_list_separator<char> sep;
    tokenizer<escaped_list_separator<char>> tok(str, sep);
    std::vector<float> value;
    for (BOOST_AUTO(pos, tok.begin()); pos != tok.end(); ++pos) {
        try {
            value.push_back(lexical_cast<float>(*pos));
        } catch (bad_lexical_cast &e) {
            std::cout << "error: " << e.what() << std::endl;
        }
    }
    sposition.timeSpan = static_cast<int>(value[0]);
    sposition.eventType = static_cast<int>(value[1]);
    sposition.touchId = static_cast<int>(value[2]);
    sposition.x = value[3];
    sposition.y = value[4];
    return ifs;
}
