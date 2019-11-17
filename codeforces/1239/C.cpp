#ifdef DEBUG
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


const int MAX = 100*1000 + 10;

struct node{
	int watcherCount;
	int inSeatCount;
};

int n,P;
int T[MAX];
ll ans[MAX];
queue<int> q;
node ST[1 << 20];

void build(int cur,int s,int e) {
	ST[cur].watcherCount = 0;
	ST[cur].inSeatCount = e-s+1;
	if(s==e) return;
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
}

void seatUnseat(int cur,int s,int e,int p,int v) {
	ST[cur].inSeatCount += v;
	if(s == e) return;
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	if(p <= m) seatUnseat(left,s,m,p,v);
	else seatUnseat(right,m+1,e,p,v);
}

void makeUnMakeWatcher(int cur,int s,int e,int p,int v) {
	ST[cur].watcherCount += v;
	if(s == e) return;
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	if(p <= m) makeUnMakeWatcher(left,s,m,p,v);
	else makeUnMakeWatcher(right,m+1,e,p,v);
}

vi moveToQueue;

bool getReady(int cur,int s,int e,int cnt) {
	if(cnt < s || ST[cur].watcherCount == 0) return 0;
	if(s == e) {
		moveToQueue.push_back(s);
		return 1;
	}
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	if(getReady(left,s,m,cnt)) return 1;
	cnt += ST[left].inSeatCount;
	return getReady(right,m+1,e,cnt);
}

ll QT = 0;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&P);
	loop(i,n) scanf("%d",T + i);

	set<pair<ll,int>> events;
	loop(i,n) events.emplace(T[i],i);

	build(0,0,n-1);

	vi aux;

	while(!events.empty()){
		auto cur = *events.begin();
		ll t = cur.first;
		aux.clear();

		bool f = 0;
		while(!events.empty() && events.begin()->first == t) {
			int p = events.begin()->second;
			events.erase(events.begin());
			aux.push_back(p);
		}
//		cerr << t << ". ";
//		print(aux,int);

		while(!aux.empty() && aux.back() != -1){
			int u = aux.back(); aux.pop_back();
			makeUnMakeWatcher(0,0,n-1,u,1);
		}

		moveToQueue.clear();

		while(!aux.empty()){
			assert(aux.back() == -1);
			assert(!q.empty());
			aux.pop_back();
			int u = q.front(); q.pop();
			ans[u] = t;
//			cerr << u << ": " << t << endl;
			// return u to his seat
			seatUnseat(0,0,n-1,u,1);
		}
		getReady(0,0,n-1,0);

		for(int u : moveToQueue) {
			q.push(u);
			events.emplace(QT = max(QT,t) + P,-1);
			seatUnseat(0,0,n-1,u,-1);
			makeUnMakeWatcher(0,0,n-1,u,-1);
		}
//		print(moveToQueue,int);
	}
	loop(i,n) printf("%lld%c",ans[i]," \n"[i==n-1]);
//	loop(i,n) fprintf(stderr,"%lld%c",ans[i]," \n"[i==n-1]);
	return 0;
}
#endif
