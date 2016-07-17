#include <cstdio>
#include <algorithm>

using namespace std;

int n, dat[100003];
int dtf[100003];
int dtb[100003];

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; i++) {
		scanf("%d",&dat[i]);
		if (i == 0 || dat[i] <= dat[i-1]) {
			dtf[i] = 1;
		} else {
			dtf[i] = dtf[i-1] + 1;
		}
	}
	for(int i = n-1; i >= 0; i--) {
		if (i == n-1 || dat[i] >= dat[i+1]) {
			dtb[i] = 1;
		} else {
			dtb[i] = dtb[i+1] + 1;
		}
	}
	int ans = 1;
	for(int i = 0; i < n; i++) {
		int left = 0, right = 0;
		if (i == 0) left = 0;
		else left = dtf[i-1];
		if (i == n-1) right = 0;
		else right = dtb[i+1];
		if (dat[i-1] + 1 < dat[i+1]) {
			ans = max(ans, left + right + 1);
		} else {
			ans = max(ans, max(left, right) + 1);
		}
	}
	printf("%d\n",ans);
	return 0;
}
