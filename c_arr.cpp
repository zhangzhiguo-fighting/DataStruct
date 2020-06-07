#include <iostream>
/*树状数组
 * lowbit函数：求数字x中二进制表示的最后一位1
 * 查询操作：维护前缀和，向前统计，i - lowbit(i)
 * 更新操作：更新单点的值，先后更新，i + lowbit(i)*/
using namespace std;
#define MAX_N 1000
#define lowbit(x) ((x) & (-x))
int c[MAX_N + 5] = {0};

void add(int i, int val, int n) {
    while (i <= n) c[i] += val, i += lowbit(i);
    return ;
}

int S(int i) {
    int sum = 0;
    while (i) sum += c[i], i -= lowbit(i);
    return sum;
}

int main() {
    int n, a;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		add(i, a, n);
	}
	for(int i = 1; i <= n; i++) {
		cout << i << " : " << c[i] << endl;
	}
	return 0;
}
