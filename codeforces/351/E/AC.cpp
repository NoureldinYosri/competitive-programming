#include<bits/stdc++.h>
using namespace std;
int n, k;
int t[200005];
double v[200005];
double invSum[200005];
double sum[200005];

#define getSum(L, R) (sum[R] - (L > 0 ? sum[L - 1] : 0))
#define getInvSum(L, R) (invSum[R] - (L > 0 ? invSum[L - 1] : 0))


inline double getVal(const int &L, const int &R) {
	if (R < L)
		return 0;
	return v[R] - (L > 0 ? v[L - 1] + getInvSum(L, R) * sum[L - 1] : 0) + R - L + 1;
}

inline double getDiff(const int &L, const int &x, const int &y) {
	return v[x] - v[y] + x - y - (L > 0 && y + 1 <= x ? sum[L - 1] * (getInvSum(y + 1, x)) : 0);
}

double dp[2][200005];

int V[200005];
int d[200005];

#define f(x, y, rem) (getVal(x, y) + dp[rem & 1][y + 1])

inline int D(int ind1, int ind2, int rem) {

	if (f(0, ind2, rem) >= f(0, ind1, rem) - 1e-9)
	    return -1;
	double diff = dp[rem & 1][ind2 + 1] - dp[rem & 1][ind1 + 1];
	int start = 0;
	int end = ind2 + 1;
	while (end - start > 1) {
		int index = (end + start) / 2;
		if (getDiff(index, ind1, ind2) > diff)
			start = index;
		else
			end = index;
	}
	return start;
}

int main() {
	ios::sync_with_stdio(false);

	scanf("%d%d", &n, &k);
//	double T = clock();
	for (int i = 0; i < n; i++)
// 		t[i] = rand() % 100000 + 1;
		scanf("%d", t + i);
	for (int i = 0; i < n; i++) {
		sum[i] = t[i];
		invSum[i] = 1.0 / t[i];
		if (i)
			sum[i] += sum[i - 1], invSum[i] += invSum[i - 1], v[i] = sum[i - 1]
					/ t[i] + v[i - 1];
	}
	for (int i = 0; i < n; i++)
		dp[0][i] = getVal(i, n - 1);

	for (int rem = 2; rem <= k; rem++) {
		int s = 0, t = 0, sz = 0;
		for (int i = n - 1; i >= 0; i--) {

			dp[1 ^ (rem & 1)][i] = 1 + dp[rem & 1][i + 1];

//			int start = max(s, t - 10);
//			int end = t;
//			while (end - start > 1) {
//				int mid = (end + start) >> 1;
//				if (D(V[mid], i, rem) >= d[mid])
//					end = mid;
//				else
//					start = mid;
//			}
//			sz -= t - end;
//			t = end;

			while (sz > 1) {
				d[t] = D(V[t - 1], i, rem);
				if (d[t - 1] > d[t])
					break;
				t--;
				sz--;
			}

			V[t] = i;
			if (sz <= 1 || d[t] != -1) {
				if (sz == 1)
					d[t] = D(V[t - 1], i, rem);
				t++;
				sz++;
			}

			while (sz > 1) {
				if (d[s + 1] >= i)
					s++, sz--;
				else
					break;
			}
			dp[1 ^ (rem & 1)][i] = f(i, V[s], rem);

		}
	}
	printf("%.9lf\n", dp[1 ^ (k & 1)][0]);
//	printf("%.9lf\n", (clock() - T) / CLOCKS_PER_SEC);
	return 0;
}
