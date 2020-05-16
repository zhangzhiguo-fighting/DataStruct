#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    unordered_map<double, int> h; //理解：第一位数组下标， 第二位数组元素的值，底层是用哈希表维护的
    h[2.3] = 123;
    h[345.6] = 123456;
    cout << h[2.3] << endl;
    cout << h[345.6] << endl;
    cout << h[678] << endl;
    return 0;
}

