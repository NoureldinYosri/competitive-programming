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
 
const int MAXN = 300*1000 + 10, MAXST = 1 << 21;
int n;
int P[MAXN], Q[MAXN], R[MAXN];
int ST[MAXST], LA[MAXST];

void update(int cur, int v){
	ST[cur] += v;
	LA[cur] += v;
}
void push_down(int cur){
	if(!LA[cur]) return ;
	int left = 2*cur + 1, right = left + 1;
	update(left, LA[cur]);
	update(right, LA[cur]);
	LA[cur] = 0;
}
void push_up(int cur){
	LA[cur] = 0;
	int left = 2*cur + 1, right = left + 1;
	ST[cur] = max(ST[left], ST[right]);
}

void update(int cur, int s, int e, int l, int r, int v){
	if(l <= s && e <= r) return update(cur, v);
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v);
	else if(m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
	push_up(cur);
}






int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", P + i);
	loop(i, n) scanf("%d", Q + i);
	loop(i, n) R[P[i]] = i+1;
	
	
	
	int ans = n;
	update(0, 0, n, 0, R[n], 1);

	for(int i = 0;i < n;i++){
//		cout << "in " << ans  << " " << ST[0] << endl;
		while(ST[0] <= 0){
			ans--;
			update(0, 0, n, 0, R[ans], 1);
		}

		printf("%d%c", ans, " \n"[i==n-1]); 
		int x = Q[i];
//		cerr << "make " << x  << " a bomb" << endl;
		update(0, 0, n, 0, x, -1);
	}
	
	return 0;
}
