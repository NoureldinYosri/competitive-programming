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

int n;
int P[1 << 20];
vi LIS, ctr, who;
struct node{
	pi left, right;
	int left_most;
	bool isSet, notOk;

	bool isOk() {
		if(!isSet) return true;
		return !notOk;
	}
	int getLeftMost(int s) {
		if(!isSet) return s;
		return left_most;
	}
};

node ST[1 << 20];

void update(int cur, int s, int e, int p, pi val) {
	if(s == e) {
		ST[cur].left = ST[cur].right = val;
		ST[cur].left_most = s;
		ST[cur].notOk = false;
		ST[cur].isSet = true;
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) {
		update(left, s, m, p, val);
	} else {
		update(right, m+1, e, p, val);
	}
	if(ST[left].isSet || ST[right].isSet) {
		ST[cur].isSet = true;
	}
	ST[cur].notOk = !(ST[left].isOk() && ST[right].isOk());
	ST[cur].left = ST[left].isSet ? ST[left].left : ST[right].left;
	ST[cur].right = ST[right].isSet ? ST[right].right : ST[left].right;
	if(ST[right].isOk()) {
		ST[cur].left_most = ST[left].getLeftMost(s);
	} else {
		ST[cur].left_most = ST[right].left_most;
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", P + i);
	int j = -1;
	ll ans = 0;
	loop(i, n) {
		int x = P[i];
		if(LIS.empty() || LIS.back() < x) {
			LIS.push_back(x);
			ctr.push_back(0);
			who.push_back(i);
		} else {
			int idx = upper_bound(all(LIS), x) - LIS.begin();
			int key = who[idx];
			pi val = pi(-idx, ctr[idx]);
			update(0, 0, n-1, key, val);
			LIS[idx] = x;
			ctr[idx]++;
		}
		cerr << ST[0].left_most+1 << ":" << i+1 << endl;
		ans += i - ST[0].left_most + 1;
	}
	cout << ans << endl;
	return 0;
}
