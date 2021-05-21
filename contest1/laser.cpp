#include <iostream>
#include <algorithm>
using namespace std;
char a[105][105];
int laserX, laserY, laserD, endX, endY;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (a[i][j] != '.' && a[i][j] != '/' && a[i][j] != '\\') {
                if (a[i][j] == '*') {
                    endX = i;
                    endY = j;
                } else {
                    laserX = i;
                    laserY = j;
                    if (a[i][j] == '>') {
                        laserD = 1;
                    } else if (a[i][j] == 'v') {
                        laserD = 2;
                    } else if (a[i][j] == '<') {
                        laserD = 3;
                    } else {
                        laserD = 4;
                    }
                }
            }
        }
    }
    int startD = laserD;
    int startX = laserX;
    int startY = laserY;
    // ok setup complete now we follow the laser

    while(true) {
        //cout << "Before: " << laserX << " " << laserY << "\n";
        if (laserD == 1) {
            ++laserY;
        } else if (laserD == 2) {
            ++laserX;
        } else if (laserD == 3) {
            --laserY;
        } else {
            --laserX;
        }
        //cout << "After: " << laserX << " " << laserY << "\n";

        if (laserX >= n || laserY >= n) {
            //cout << "bounds\n";
            break;
        } else if (laserX < 0 || laserY < 0) {
            //cout << "bounds\n";
            break;
        }

        if (a[laserX][laserY] == '*') {
            cout << "YES\n";
            return 0;
        } else if (a[laserX][laserY] == '\\') {;
            if (laserD == 1) {
                laserD = 2;
            } else if (laserD == 2) {
                laserD = 1;
            } else if (laserD == 3) {
                laserD = 4;
            } else {
                laserD = 3;
            }
        } else if (a[laserX][laserY] == '/') {
            if (laserD == 1) {
                laserD = 4;
            } else if (laserD == 2) {
                laserD = 3;
            } else if (laserD == 3) {
                laserD = 2;
            } else {
                laserD = 1;
            }
        }
        if (laserX == startX && laserY == startY && laserD == startD) {
            //cout << "loop\n";
            break;
        }
    }
    cout << "NO\n";
    return 0;
}
