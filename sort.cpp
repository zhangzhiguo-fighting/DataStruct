#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

int main() {
    int a[100] = {2, 3, 4, 5, 1, 9, 6, 10};
    sort(a + 0, a + 8, cmp);
    for (int i = 0; i < 8; i++) {
        cout << a[i] << endl;
    }
    return 0;
}

