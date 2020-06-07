#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
//求逆序队
int merger_sort(int *num, int n) {
    if (n <= 1) return 0;
    int ans = 0, mid = n / 2;
    ans += merger_sort(num, mid);
    ans += merger_sort(num + mid, n - mid);
    int *temp = (int *)malloc(sizeof(int) * n);
    int p1 = 0, p2 = mid, k = 0;
    while (p1 < mid || p2 < n) {
        if (p2 == n || (p1 < mid && num[p1] <= num[p2])) {
            temp[k++] = num[p1++];
        } else {
            //调整
            ans += mid - p1;
            temp[k++] = num[p2++];
        }
    }
    for (int i = 0; i < k; i++) num[i] = temp[i];
    return ans;
}

int main() {
    int n, a[100];
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << merger_sort(a, n) << endl;
    return 0;
}
