#include <iostream>
using namespace std;

int main() {
    int statusReg = 0b10110001;  // Read-only
    int controlReg = 0b00000000; // Firmware writes here
    int dataReg = 0b11001010;    // Reassignment demo[cite: 4]

    // 1. Pointer to constant data (Data cannot be changed via pointer)[cite: 4, 5]
    const int* regPtr1 = &statusReg;
    cout << "regPtr1 value: " << *regPtr1 << endl;
    // *regPtr1 = 0b11111111; // COMPILE ERROR: assignment of read-only location '*regPtr1'[cite: 5]
    regPtr1 = &dataReg; // ALLOWED: pointer can point to different address[cite: 5]

    // 2. Constant pointer to data (Address cannot be changed)[cite: 4, 5]
    int* const regPtr2 = &controlReg;
    *regPtr2 = 0b00001111; // ALLOWED: data modification through pointer[cite: 5]
    cout << "regPtr2 modified controlReg: " << *regPtr2 << endl;
    // regPtr2 = &dataReg; // COMPILE ERROR: assignment of read-only variable 'regPtr2'[cite: 5]

    // 3. Constant pointer to constant data (Neither address nor data can change)[cite: 4, 5]
    const int* const regPtr3 = &statusReg;
    cout << "regPtr3 value: " << *regPtr3 << endl;
    // *regPtr3 = 0b00000000; // COMPILE ERROR: assignment of read-only location[cite: 5]
    // regPtr3 = &dataReg;    // COMPILE ERROR: assignment of read-only variable 'regPtr3'[cite: 5]

    return 0;
}