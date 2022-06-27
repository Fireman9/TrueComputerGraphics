#ifndef TRUECOMPUTERGRAPHICS_SRC_CLOCK_H_
#define TRUECOMPUTERGRAPHICS_SRC_CLOCK_H_

#include <chrono>
#include <string>
#include <iostream>

using namespace std::chrono;
using std::cout;
using std::endl;

class Clock {
public:
	void start();
	void stop();

	double getDurationMs();
	double getDurationS();

	void printResultMs(std::string str);
	void printResultS(std::string str);

private:
	time_point<system_clock> mStart;
	time_point<system_clock> mEnd;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_CLOCK_H_
