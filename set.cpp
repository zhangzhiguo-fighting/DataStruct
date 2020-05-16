#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
using namespace std;

set<int> s;

int main() {
    //s.insert();
    //s.begin(), s.end(), s.erase();
    s.insert(2);
    s.insert(1);
    s.insert(1);
    s.insert(3);
    cout << *(s.begin()) << endl;
    s.erase(s.begin());
    cout << *(s.begin()) << endl;
    return 0;
}

