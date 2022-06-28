#include "Clock.h"

void Clock::start() {
	mStart = system_clock::now();
}

void Clock::stop() {
	mEnd = system_clock::now();
}

double Clock::getDurationMs() {
	return (double) duration_cast<milliseconds>(mEnd - mStart).count();
}

double Clock::getDurationS() {
	return (double) duration_cast<seconds>(mEnd - mStart).count();
}

void Clock::printResultMs(std::string str) {
	cout << str << ": " << duration_cast<milliseconds>(mEnd - mStart).count() << "ms" << endl;
}

void Clock::printResultS(std::string str) {
	cout << str << ": " << duration_cast<seconds>(mEnd - mStart).count() << "s" << endl;
}
