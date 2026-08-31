#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cout << "Enter number of readings (N <= 100): ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Invalid buffer size!" << endl;
        return 1;
    }

    double buffer[100];
    cout << "Enter " << n << " temperature readings:\n";
    for (int i = 0; i < n; i++) {
        cin >> buffer[i];
    }

    // 1. Valid readings display & Skip error readings using continue
    int errorCount = 0;
    cout << "\nReadings entered : " << n << endl;
    cout << "Valid readings   : ";
    for (int i = 0; i < n; i++) {
        if (buffer[i] < 0) {
            errorCount++;
            continue; // Skip sensor fault
        }
        cout << buffer[i] << " ";
    }
    cout << "\nSkipped (errors) : " << errorCount << endl;

    // 2. Scan for first CRITICAL reading (>= 45.0) using break
    int firstCriticalIndex = -1;
    double firstCriticalVal = 0.0;
    for (int i = 0; i < n; i++) {
        if (buffer[i] >= 45.0) {
            firstCriticalIndex = i;
            firstCriticalVal = buffer[i];
            break; // Stop immediately on first critical value
        }
    }

    if (firstCriticalIndex != -1) {
        cout << "First CRITICAL   : Index " << firstCriticalIndex << " -> " << firstCriticalVal << "°C" << endl;
    } else {
        cout << "First CRITICAL   : None" << endl;
    }

    // 3. Single Pass Analysis: Min, Max, Average & Category Counts
    double minTemp = 1e9;
    double maxTemp = -1e9;
    double sum = 0;
    int validCount = 0;

    int normalCount = 0, warningCount = 0, criticalCount = 0, shutdownCount = 0;

    for (int i = 0; i < n; i++) {
        if (buffer[i] < 0) continue; // Ignore faults

        validCount++;
        sum += buffer[i];

        if (buffer[i] < minTemp) minTemp = buffer[i];
        if (buffer[i] > maxTemp) maxTemp = buffer[i];

        if (buffer[i] <= 29.0) {
            normalCount++;
        } else if (buffer[i] <= 44.0) {
            warningCount++;
        } else if (buffer[i] <= 59.0) {
            criticalCount++;
        } else {
            shutdownCount++;
        }
    }

    // 4. Output Summary
    cout << fixed << setprecision(2);
    if (validCount > 0) {
        double avg = sum / validCount;
        cout << "Min: " << minTemp << "°C  Max: " << maxTemp << "°C  Avg: " << avg << "°C" << endl;
    }

    cout << "Normal: " << normalCount 
         << "  Warning: " << warningCount 
         << "  Critical: " << criticalCount 
         << "  Shutdown: " << shutdownCount << endl;

    return 0;
}
