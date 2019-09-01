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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


const int MAX = 200*1000 + 10,MAXST = 1 << 20;
ll A[MAX];
int n;
pair<ll,int> ST[MAXST];
ll LA[MAXST];
int P[MAX];

auto cmp = [](const pair<ll,int> & a,const pair<ll,int> & b) {
	if(a.first != b.first) return a.first < b.first;
	return a.second > b.second;
};

void build(int cur,int s,int e) {
	if(s == e) {
		ST[cur] = mp(A[s],s);
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[cur] = min(ST[left],ST[right],cmp);
//	cout << s << " " << e << " " << ST[cur] << endl;
}

void update(int cur,ll v) {
	ST[cur].first += v;
	LA[cur] += v;
}
void push(int cur){
	if(!LA[cur]) return ;
	int left = 2*cur + 1,right = left + 1;
	update(left,LA[cur]);
	update(right,LA[cur]);
	LA[cur] = 0;
}


void update(int cur,int s,int e,int l,int r,ll v) {
	if(l <= s && e <= r) {
//		cout << s << " " << e << " contains " << v << endl;
		return update(cur,v);
	}
	push(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,v);
	else if(m < l) update(right,m+1,e,l,r,v);
	else  {
		update(left,s,m,l,m,v);
		update(right,m+1,e,m+1,r,v);
	}
	ST[cur] = min(ST[left],ST[right],cmp);
//	cout << s << " " << e << ": " << ST[cur] << endl;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
//	freopen("out.out","w",stdout);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld",A + i);
	build(0,0,n-1);
	ll oo = n*(n + 1LL)/2 + 10;
	for(int i = 1;i <= n;) {
		int j = ST[0].second;
		P[j] = i++;
		update(0,0,n-1,j,j,oo);
		if(j+1 <= n-1) {
			update(0,0,n-1,j+1,n-1,-P[j]);
		}
	}
	loop(i,n) printf("%d%c",P[i]," \n"[i==n-1]);
	return 0;
}
