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
	pi LR[2];
	int state;
};

const int MAX = 100*1000 + 10, MAXST = 1 << 20;
int state[MAX][2];
node ST[MAXST];
int n;

void build(int cur,int s,int e){
	loop(i, 2) ST[cur].LR[i] = pi(3*MAX, -3);
	ST[cur].state = 0;
	if(s == e) return;
	int m = (s + e) >> 1, left = 2*cur+1, right = left+1;
	build(left,s,m);
	build(right,m+1,e);
}

void push_up(int cur,int left,int right){
	ST[cur].state = ST[left].state | ST[right].state;
	loop(i, 2){
		int a = ST[left].LR[i].second;
		int b = ST[right].LR[i^1].first;
		if(a <= 0 || a > n) continue;
		if(b <= 0 || b > n) continue;
		int d = abs(a - b);
		if(d <= 1) ST[cur].state = 1;
	}
	
	loop(i, 2){
		ST[cur].LR[i].first = min(ST[left].LR[i].first, ST[right].LR[i].first);
		ST[cur].LR[i].second = max(ST[left].LR[i].second, ST[right].LR[i].second);
	}
	
}

void update(int cur,int s,int e, int r, int c){
	if(s == e) {
		state[s][r] ^= 1;
//		cout << s << " " << r << " -> " << state[s][r] << endl;
		loop(i, 2) ST[cur].LR[i] = state[s][i] ? pi(s,s) : pi(MAX*3,-3);
		ST[cur].state = state[s][0] && state[s][1];
//		cout << s << " " << ST[cur].LR[0] << " " << ST[cur].LR[1] << " " << ST[cur].state << endl;
		return ;
	}
	int m = (s + e) >> 1, left = 2*cur+1, right = left+1;
	if(c <= m) update(left,s,m,r,c);
	else update(right, m+1,e,r,c);
	push_up(cur, left, right);
//	cout << s << " " << e << " " << ST[cur].LR[0] << " " << ST[cur].LR[1] << " " << ST[cur].state << endl;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int q; scanf("%d %d",&n,&q);
	build(0,1,n);
	while(q--){
		int r, c; scanf("%d %d",&r,&c);
		r--;
		update(0, 1, n, r, c);
		bool cond = ST[0].state;
		cond |= state[1][0];
		cond |= state[n][1];
		puts(cond ? "NO" : "YES");
	}
	
	
	return 0;
}
