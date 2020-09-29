#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

struct node{
	int mx;
	int pref, suff, sum;
	void push_up(const node & L, const node & R){
		sum = L.sum + R.sum;
		pref = max(L.pref, L.sum + R.pref);
		suff = max(R.suff, L.suff + R.sum);
		mx = max({L.mx, R.mx, L.suff + R.pref});
		mx = max({mx, sum, pref, suff});
	}
	node(){
		mx = INT_MIN;
		pref = suff = sum = 0;
	}
	node(int v){
		mx = pref = suff = sum = v;
	}
	friend ostream& operator << (ostream & os, const node & u){
		os << "{" << u.mx << ", " << u.pref << ", " << u.suff << ", " << u.sum << "}";
		return os;
	}
};

node ST[2][1 << 20];

void insert(int cur, int s, int e, int p, int r, node *ST){
	if(s == e){
		ST[cur] = node(r);
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) insert(left, s, m, p, r, ST);
	else insert(right, m+1, e, p, r, ST);
	ST[cur].push_up(ST[left], ST[right]);
}


int main(){
	freopen("stones.in", "r", stdin);
#ifndef HOME
	freopen("stones.out", "w", stdout);
#endif
	
	string str = "?><";
	int n; scanf("%d", &n);
	int mx[2] = {0};
	
	loop(i, n){
		if(i == 4) break;
		int r, s; scanf("%d %d", &r, &s);
		s--;
		mx[s] = max(mx[s], r);
		insert(0, 1, n, r, 1, ST[s]);
		insert(0, 1, n, r, -1, ST[s^1]);

		int winner = mx[1] > mx[0];
		cerr << "cand is " << winner + 1 << " adv is " << ST[winner^1][0] << endl;
		if(ST[winner^1][0].mx > 1) winner = 0;
		else winner++;
		printf("%c\n", str[winner]);
	}
	
	return 0;
}
