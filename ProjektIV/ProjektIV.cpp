
#include <iostream>
#include "Functions.h"
#include <fstream>
using namespace std;

void printSize(const string& address) {
    fstream motd(address.c_str(), ios::binary | ios::in | ios::ate);
    if (motd) {
        fstream::pos_type size = motd.tellg();
        cout << size << "B";
    }
    else {
        perror(address.c_str());
    }
};

void createFile(const string name, const int count, const char value) {
    int i = 0;
    ofstream MyFile(name);

    for (i = 0; i < count; i++) {
        MyFile << value;
    }
};

void createFileRandom(const string name, const int count, const char value1, const char value2) {
    int i = 0;
    ofstream MyFile(name);

    for (i = 0; i < 90; i++) {
        MyFile << value1;
    }
    for (i = 90; i < count; i++) {
        MyFile << value2;
    }
};

uint8_t calculateHamingDistance(uint8_t n1, uint8_t n2)
{
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;

    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
};

double Timestamp()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    return chrono::system_clock::to_time_t(now);
};

string FormattedTimestamp()
{
    time_t timestamp = Timestamp();
    struct tm timeinfo;
    char buffer[80];
    time(&timestamp);
    localtime_s(&timeinfo, &timestamp);
    strftime(buffer, 80, "%H:%M:%S", &timeinfo);
    string str(buffer);
    return str;
};

void CompareFunction(const char* FirstFile, const char* SecondFile) {
    string Starting = FormattedTimestamp();
    ifstream file1 (FirstFile, ios::binary);
    ifstream file2 (SecondFile, ios::binary);
    long long int iloscBitow = 0, ber = 0;
    char a{};
    char b{};

    auto start_time = chrono::high_resolution_clock::now();

    while (!file1.eof())
    {
        file1 >> a;
        file2 >> b;

        if (file1.eof()) { break; } 

        iloscBitow = iloscBitow + 8;
        ber = calculateHamingDistance(a, b) + ber;
    }
   auto end_time = chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    cout << "Program started at: " << Starting << endl;
    cout << "Comparing :" << FirstFile << " and " << SecondFile << endl;
    cout << "Compared bits : " << iloscBitow << endl;
    cout << "Different bits : " << ber << endl;
    cout << "Calc time : " << time/chrono::microseconds(1) << " microsecond" << endl;
    cout << "End calculation" << endl;
    
    //Open log file
    ofstream log;
    log.open("log.txt", ios_base::app);

    if (log.good())
    {
        log << "Program started at: " << Starting << endl;
        log << "Comparing :" << FirstFile << " and " << SecondFile << endl;
        log << "Compared bits : " << iloscBitow << endl;
        log << "Different bits : " << ber << endl;
        log << "Calc time : " << time/chrono::microseconds(1) << " microsecond" << endl;
        log << "End calculation" << endl;
        log.close();
    }
    else
        cout << "There is a problem with file log";"/n";
};

int main(int argc, char* argv[])
{
    /* createFile("100bytes_1.bin", 100, 0x55);
    createFile("100bytes_2.bin", 100, 0x55);
    createFileRandom("100bytes_3_changed_by_10_bytes.bin", 100, 0x55, 0x45);
    createFile("400MB_1.bin", 419430400, 0x55);
    createFile("400MB_2.bin", 419430400, 0x50);
    cout << "wykonano create file";
    */
    std::cout << "BER Checker!" << std::endl;
    std::cout << "argc = : " << argc << std::endl;

    int iter = 0;
    for (iter = 0; iter < argc; iter++) {
        std::cout << "argv[" << iter << "] =" << argv[iter]<<std::endl;
    }
    CompareFunction(argv[1], argv[2]);
}

