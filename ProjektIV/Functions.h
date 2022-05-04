#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdint.h>
#include <vector>
#include <bitset>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <time.h>

double OperationTimeCalc(time_t time1, time_t time2);
uint8_t calculateHamingDistance(uint8_t bin1, uint8_t bin2);
void CompareFunction(const char* FirstFile, const char* SecondFile);
std::string FormattedTimestamp();
double Timestamp();