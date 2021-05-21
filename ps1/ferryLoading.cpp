#include <iostream>
#include <vector>
using namespace std;
int main() {
    int numOfTests;
    cin >> numOfTests;
    for (int testNum = 0; testNum < numOfTests; ++testNum) {
        int capacity, time, numOfCars;
        cin >> capacity >> time >> numOfCars;
        vector<int> arrivialTime;
        for (int x = 0; x < numOfCars; ++x) {
            int tmp;
            cin >> tmp;
            arrivialTime.push_back(tmp);
        }

        int trips = numOfCars/capacity;
        if (numOfCars % capacity != 0) {
            ++trips;
        }

        int mins = 0;
        vector<int> readyToDepartTime;
        for (int x = arrivialTime.size() - 1; x >= 0; x -= capacity) {
            readyToDepartTime.push_back(arrivialTime[x]);
        }
        while (!readyToDepartTime.empty()) {
            if (readyToDepartTime.size() == 1) {
                if (readyToDepartTime.back() > mins) {
                    mins = readyToDepartTime.back();
                }
                mins += time;
                readyToDepartTime.pop_back();
            } else {
                if (readyToDepartTime.back() > mins) {
                    mins = readyToDepartTime.back();
                }
                mins += 2 * time;
                readyToDepartTime.pop_back();
            }
        }
        cout << mins << " " << trips << "\n";
    }
    return 0;
}
