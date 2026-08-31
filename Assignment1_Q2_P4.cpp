#include <iostream>
using namespace std;

// Pointer-to-pointer (int**) used to return pointers to min/max directly inside original buffer[cite: 4, 5]
bool parsePacket(const int* rawData, int size, const int** outMin, const int** outMax) {
    if (size <= 0 || rawData == nullptr) { //[cite: 4]
        return false;
    }

    const int* minLoc = rawData;
    const int* maxLoc = rawData;

    for (int i = 1; i < size; i++) {
        if (*(rawData + i) < *minLoc) {
            minLoc = rawData + i;
        }
        if (*(rawData + i) > *maxLoc) {
            maxLoc = rawData + i;
        }
    }

    *outMin = minLoc;
    *outMax = maxLoc;
    return true;
}

int main() {
    int packet[] = {45, 12, 67, 8, 55, 31}; //[cite: 4]
    const int* minPtr = nullptr;
    const int* maxPtr = nullptr;

    if (parsePacket(packet, 6, &minPtr, &maxPtr)) { //[cite: 4]
        cout << "Calibration Min: " << *minPtr << endl;
        cout << "Calibration Max: " << *maxPtr << endl;
    } else {
        cout << "Packet parsing failed!" << endl;
    }

    return 0;
}