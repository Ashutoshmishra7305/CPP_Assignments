#include <iostream>
#include <cstdlib> // rand(), srand()
#include <string>  // stoi(), stod()

using namespace std;

int main(int argc, char* argv[]) {
    // 1. Check missing/incorrect arguments
    if (argc != 4) {
        cout << "Usage  : ./sensor_monitor <warn_threshold> <critical_threshold> <num_readings>" << endl;
        cout << "Error  : Missing arguments." << endl;
        return 1;
    }

    // 2. Parse arguments from string to numeric types
    double warnThreshold = stod(argv[1]);
    double criticalThreshold = stod(argv[2]);
    int numReadings = stoi(argv[3]);

    // 3. Validation checks
    if (warnThreshold >= criticalThreshold) {
        cout << "Error  : warn_threshold must be strictly less than critical_threshold." << endl;
        return 1;
    }

    if (numReadings < 1 || numReadings > 500) {
        cout << "Error  : num_readings must be between 1 and 500." << endl;
        return 1;
    }

    // 4. Print Active Config
    cout << "Config : Warn=" << warnThreshold << "°C Critical=" << criticalThreshold 
         << "°C Readings=" << numReadings << endl;

    int normalCount = 0;
    int warningCount = 0;
    int criticalCount = 0;
    int shutdownCount = 0;

    // 5. Simulate readings using rand() % 70
    for (int i = 0; i < numReadings; i++) {
        int temp = rand() % 70; // 0 to 69

        if (temp >= 60) {
            shutdownCount++;
        } else if (temp >= criticalThreshold) {
            criticalCount++;
        } else if (temp >= warnThreshold) {
            warningCount++;
        } else {
            normalCount++;
        }
    }

    // 6. Print Classification Results
    cout << "Results: Normal:" << normalCount 
         << " Warning:" << warningCount 
         << " Critical:" << criticalCount 
         << " Shutdown:" << shutdownCount << endl;

    return 0;
}