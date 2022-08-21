#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;


int a, b, c, d, n;
char S[1 << 20];
char T[1 << 20];
bool taken[1 << 20];

void no() {
	puts("NO");
}

void tc() {
	scanf("%d %d %d %d %s", &a, &b, &c, &d, S);
	int cnt[2] = {0, 0};
	n = strlen(S);
	loop(i, n) cnt[S[i] == 'B'] ++;
	int s = a + b + c + d;
	if(n != a + b + 2*(c + d) || cnt[0] != s - b || cnt[1] != s - a) return no();
	int m = 0;
	int ctr[] = {a, b, c, d};
	for(int i = 0; i < n; ) {
		int j = i;
		while(j < n && S[i] == S[j]) j++;
		int len = j - i;
		int diff = max(len - 2, 0);
		if(len > 1) {
			if(i == 0 || j == n) diff = len - 1;
		}
		len -= diff;
		ctr[S[i] == 'B'] -= diff;
		loop(k, len) T[m++] = S[i];
		i = j;
	}
//	prArr(ctr, 4, int);
	T[m] = 0;
	int types[3] = {0, 0, 0};
	for(int i = 0, lst = -1; i < m; i++)  if(i + 1 == m || T[i] == T[i + 1]) {
		int len = i - lst;
		if(len & 1) {
			len --;
			ctr[T[lst + 1] == 'B']--;
			types[2] += len >> 1;
		} else {
			types[T[lst + 1] == 'B'] += len >> 1;
		}
		lst = i;
	}
	
/*	prArr(ctr, 4, int);
	prArr(types, 3, int);*/
	int d = min(ctr[2], types[0]);
	ctr[2] -= d;
	types[0] -= d;
/*	prArr(ctr, 4, int);
	prArr(types, 3, int);*/	
	d = min(ctr[3], types[1]);
	ctr[3] -= d;
	types[1] -= d;
	
/*	prArr(ctr, 4, int);
	prArr(types, 3, int);*/	loop(k, 2) {
		d = min(ctr[2 + k], types[2]);
		ctr[2 + k] -= d;
		types[2] -= d;
	}
/*	prArr(ctr, 4, int);
	prArr(types, 3, int);*/	loop(k, 2) {
		d = min(ctr[2 + k], types[k ^ 1] - 1);
		if(d == -1) continue;
		ctr[2 + k] -= d;
		types[k ^ 1] -= d + 1;
		if(d) {
			ctr[0] --;
			ctr[1]--;
		}
	}
	
/*	prArr(ctr, 4, int);
	prArr(types, 3, int);*/	
	loop(k, 3) {
		ctr[0] -= types[k];
		ctr[1] -= types[k];
	}

	if(*min_element(ctr, ctr + 4) < 0) return no();
	puts("YES");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
