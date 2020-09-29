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


const int MAXN = 200*1000 + 10, MAXST = 1 << 20;
int n;
int A[MAXN];
pi ST[MAXST];
char output[2][50] = {"NIE", "TAK"};
int cnt[MAXN];


void push_up(int cur){
	int left = 2*cur + 1, right = left + 1;
	ST[cur].first = min(ST[left].first, ST[right].first - ST[left].second);
	ST[cur].second = ST[left].second + ST[right].second;
}

void build(int cur, int s, int e){
	if(s == e){
		ST[cur].first = s - cnt[s];
		ST[cur].second = cnt[s];
		return ;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m+1, e);
	push_up(cur);
}

void update(int cur, int s, int e, int p){
	if(s == e){
		ST[cur].first = s - cnt[s];
		ST[cur].second = cnt[s];
		return ;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) update(left, s, m, p);
	else update(right, m+1, e, p);
	push_up(cur);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n;i++) {
		scanf("%d", A + i);
		cnt[A[i]]++;
	}
	build(0, 1, n);
	puts(output[ST[0].first >= 0]);
	int m; scanf("%d", &m);
	while(m--){
		int i, x; scanf("%d %d", &i, &x);
		cnt[A[i]]--;
		update(0, 1, n, A[i]);
		cnt[x]++;
		A[i] = x;
		update(0, 1, n, A[i]);
		puts(output[ST[0].first >= 0]);		
	}
	return 0;
}
