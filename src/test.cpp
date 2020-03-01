#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include "screenPosition.h"
#include <string>
#include <thread>
#define BOOST_TEST_INCLUDE
#define BOOST_TEST_MODULE demo
#include "boost/test/included/unit_test.hpp"
using namespace std;
using namespace boost::unit_test;

class AddFixture {
    public:
        int a, b;
        ofstream outfile;
        ifstream inputfile;
        AddFixture() : a(0), b(0) {
            //BOOST_TEST_MESSAGE("AddFixture constructor");
        }
        ~AddFixture() {
            //BOOST_TEST_MESSAGE("AddFixture deconstructor");
        }
        void setup() {
            BOOST_TEST_MESSAGE("setup outfile");
            outfile.open("log.txt", ofstream::out);
        }
        void teardown() {
            BOOST_TEST_MESSAGE("teardown outfile");
            outfile.close();
        }
        void openConfigFile() {
            BOOST_TEST_MESSAGE("open configure file");
            inputfile.open("log.txt");
        }
        void closeConfigFile() {
            BOOST_TEST_MESSAGE("close configure file");
            inputfile.close();
        }
};

boost::shared_ptr<AddFixture> aFixture (new AddFixture);

BOOST_AUTO_TEST_SUITE(suite)
/*BOOST_FIXTURE_TEST_CASE(record_screen_position_dump, AddFixture) {
    BOOST_TEST_MESSAGE("Running RecordTest");
    BOOST_TEST_MESSAGE("  recording position 1");
    ScreenPosition sp; 
    sp.record(12,27,89);
    outfile << sp ;// dont put << endl here.
    BOOST_TEST_MESSAGE("  Sleeping for 2 seconds");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    BOOST_TEST_MESSAGE("  recording position 2");
    sp.record(12,89,78);
    outfile << sp ;
}*/
BOOST_AUTO_TEST_CASE(fixture_demo0, * fixture(boost::bind(&AddFixture::openConfigFile, aFixture), boost::bind(&AddFixture::closeConfigFile, aFixture))) {
    BOOST_TEST_MESSAGE("Running ReadTest");
    ScreenPosition sp;
    while (!aFixture->inputfile.eof()) {
        aFixture->inputfile >> sp;
    }
}
/*
BOOST_AUTO_TEST_CASE(fixture_demo1) {
    BOOST_TEST_MESSAGE("Running fixture_demo1");
}
*/
BOOST_AUTO_TEST_SUITE_END();
