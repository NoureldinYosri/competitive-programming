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


const int MAXN = 300*1000 + 10,MAXQ = MAXN;
const int MAXST = 1 << 21;
vector<pi> ST[MAXST];
int n,m;
bool isQuery[MAXQ];

void update(int cur,int s,int e,int l,int r,pi ab) {
	if(l <= s && e <= r) {
		ST[cur].push_back(ab);
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,ab);
	else if(m < l) update(right,m+1,e,l,r,ab);
	else {
		update(left,s,m,l,m,ab);
		update(right,m+1,e,m+1,r,ab);
	}
}

int id[MAXN],W[MAXN];
int N;
using op = pair<int*,int>;

int get(int u,vector<op> & hist) {
	if(u == id[u]) return u;
	hist.emplace_back(&id[u],id[u]);
	// save id[u] = old
	return id[u] = get(id[u],hist);
}

void join(int a,int b,vector<op> & hist) {
	a = get(a,hist);
	b = get(b,hist);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	hist.emplace_back(&W[a],W[a]);
	hist.emplace_back(&id[b],id[b]);
	hist.emplace_back(&N,N);
	W[a] += W[b];
	id[b] = a;
	N--;
}

void dfs(int cur,int s,int e) {
	vector<op> hist;
	for(const pi & p : ST[cur])
		join(p.first,p.second,hist);
	if(s == e) {
		if(isQuery[s]) printf("%d\n",N);
	}
	else {
		int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
		dfs(left,s,m);
		dfs(right,m+1,e);
	}
	while(!hist.empty()) {
		*hist.back().first = hist.back().second;
		hist.pop_back();
	}
}

int main(){
	freopen("connect.in", "r", stdin);
	freopen("connect.out","w",stdout);
	scanf("%d %d",&n,&m);
	map<pi,int> E;
	loop(i,m) {
		char c; scanf(" %c",&c);
		if(c == '?') {
			isQuery[i] = 1;
			continue;
		}
		else {
			int a,b; scanf("%d %d",&a,&b);
			if(a > b) swap(a,b);
			if(c == '+') E[pi(a,b)] = i;
			else {
				int s = E[pi(a,b)];
				int e = i-1;
				update(0,0,m-1,s,e,pi(a,b));
				E.erase(pi(a,b));
			}
		}
	}
	for(auto pt : E) {
		pi p = pt.first;
		int s = pt.second;
		int e = m-1;
		update(0,0,m-1,s,e,p);
	}
	for(int i = 1;i <= n;i++) {
		id[i] = i;
		W[i] = 1;
	}
	N = n;
	if(m) dfs(0,0,m-1);
	return 0;
}
