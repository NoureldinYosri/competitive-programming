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

const int MAXN = 1 << 20, MAXT = MAXN << 1;
int V[MAXT], n;
pi P[MAXN];
bool taken[MAXT], done[MAXN];
queue<int> q;
int cand[MAXN];
vi people[MAXT];

void bfs(int root, int T, int ctr[2]){
	q.push(root);
	done[root] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		ctr[0]++;
		for(int t : vi{P[u].first, P[u].second}) if(t <= T && !taken[t]) {
			ctr[1]++;
			taken[t] = 1;
			for(int v : people[t]) if(!done[v]) q.push(v), done[v] = 1;			
		}
	}
}

bool can(int T){
	static vi aux;
	fill(taken, taken + T + 1, 0);
	fill(done, done + n, 0);
	while(!q.empty()) q.pop();
	
	
	int ctr[2];
	loop(root, n) if(!done[root]) {
		ctr[0] = ctr[1] = 0;
		bfs(root, T, ctr);
		if(ctr[0] > ctr[1]) return 0;
	}
	return 1;
}

int ord[MAXN];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	int m = 0;
	loop(i, n) {
		scanf("%d %d", &P[i].first, &P[i].second);
		V[m++] = P[i].first;
		V[m++] = P[i].second;
	}
	sort(V, V + m);
	m = unique(V, V + m) - V;
	
	loop(i, n) ord[i] = i;
	sort(ord, ord + n, [](const int & a, const int & b){
		return P[a].first < P[b].first;
	});
	for(int k = 0, j = 0; k < n; k++){
		int i = ord[k];
		while(V[j] < P[i].first) j++;
		P[i].first = j;
	}
	sort(ord, ord + n, [](const int & a, const int & b){
		return P[a].second < P[b].second;
	});
	for(int k = 0, j = 0; k < n; k++){
		int i = ord[k];
		while(V[j] < P[i].second) j++;
		P[i].second = j;
	}
	
	
	int mx = 0;
	loop(i, n) {
		people[P[i].first].pb(i);
		people[P[i].second].pb(i);
		mx = max(mx, P[i].first);
	}
	if(!can(m-1)) {
		puts("-1");
		return 0;
	}
	int s = mx, e = m-1;
	while(s < e){
		int m = (s + e) >> 1;
		if(can(m)) e = m;
		else s = m+1;
	}
	cout << V[s] << endl;
	return 0;
}
