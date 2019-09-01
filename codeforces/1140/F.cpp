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


const int MAXQ = 300*1000 + 10,MAXST = 1 << 21;

vector<pi> ST[MAXST];

void update(int cur,int s,int e,int l,int r, pi p) {
	if(l <= s && e <= r) {
		ST[cur].push_back(p);
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,p);
	else if(m < l) update(right,m+1,e,l,r,p);
	else {
		update(left,s,m,l,m,p);
		update(right,m+1,e,m+1,r,p);
	}
}

using op = pair<int*,int>;
vector<op> hist;

inline void assign(int & x,int v) {
	hist.emplace_back(&x,x);
	x = v;
}

map<int,int> X,Y;
int nonZeroX,nonZeroY;

void dfs(int cur,int s,int e){
	int H = sz(hist);
	for(auto p : ST[cur]) {
		int x = p.first,y = p.second;
		if(!X[x]) assign(nonZeroX,nonZeroX + 1);
		assign(X[x],X[x] + 1);
		if(!Y[y]) assign(nonZeroY,nonZeroY + 1);
		assign(Y[y],Y[y] + 1);
	}
	if(s == e) printf("%lld\n",nonZeroX*(ll)nonZeroY);
	else {
		int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
		dfs(left,s,m);
		dfs(right,m+1,e);
	}
	while(sz(hist) > H) {
		auto p = hist.back();
		hist.pop_back();
		*p.first = p.second;
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; scanf("%d",&m);
	map<pi,int> mem;
	loop(i,m) {
		pi p; scanf("%d %d",&p.first,&p.second);
		if(mem.count(p)) {
			update(0,0,m-1,mem[p],i-1,p);
			mem.erase(p);
		}
		else mem[p] = i;
	}
	for(auto pt : mem) {
		auto p = pt.first;
		int t = pt.second;
		update(0,0,m-1,t,m-1,p);
	}
	dfs(0,0,m-1);
	return 0;
}
