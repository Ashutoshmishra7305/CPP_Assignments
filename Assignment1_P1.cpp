#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    double temp;
    cout << "Enter sensor temperature (C): ";
    cin >> temp;

    int statusCode;
    string statusLabel;

    // 1. Status classification using if-else
    if (temp < 0) {
        statusCode = -1;
        statusLabel = "SENSOR_ERROR";
    } else if (temp <= 29) {
        statusCode = 0;
        statusLabel = "NORMAL";
    } else if (temp <= 44) {
        statusCode = 1;
        statusLabel = "WARNING";
    } else if (temp <= 59) {
        statusCode = 2;
        statusLabel = "CRITICAL";
    } else {
        statusCode = 3;
        statusLabel = "SHUTDOWN";
    }

    double fahrenheit = (temp * 9.0 / 5.0) + 32.0;

    cout << fixed << setprecision(2);
    cout << "Temperature : " << temp << " C / " << fahrenheit << " F\n";
    cout << "Status      : " << statusLabel << "\n";
    cout << "Action      : ";

    // 2. Switch on status code
    switch (statusCode) {
        case -1: cout << "Sensor fault check wiring\n"; break;
        case 0:  cout << "No action required\n"; break;
        case 1:  cout << "Alert sent to supervisor\n"; break;
        case 2:  cout << "Cooling system triggered\n"; break;
        case 3:  cout << "Emergency shutdown initiated\n"; break;
    }

    // 3. Ternary operator relative to 25 C
    cout << "Reading     : " << ((temp > 25.0) ? "Above Average" : "Below Average") << "\n";

    return 0;
}