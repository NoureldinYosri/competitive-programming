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


int n;
vector<vp> E;
vi fr, cost, loss;
vi id, W;
vi in_cycle, visID;


void init(){
	E.resize(n);
	fr.resize(n);
	cost.resize(n);
	loss.resize(n);
	id.resize(n);
	W.resize(n);
	in_cycle.resize(n);
	visID.resize(n);
	
	
	loop(i, n) id[i] = i, W[i] = 1;
}

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
}

void detect_cycles(vector<vi> & C){
	static vi V;
	fill(all(in_cycle), 0);
	fill(all(visID), 0);
	int visNum = 0;
	visID[0] = ++visNum;
	loop(i, n) if(i == find(i) && !visID[i]){
		int j = i;
		visNum++;
		V.clear();
		while(!visID[j]){
			V.pb(j);
			visID[j] = visNum;
			assert(fr[j] != -1);
			j = find(fr[j]);
		}
		if(visID[j] == visNum){
			C.emplace_back();
			C.back().pb(j);
			in_cycle[j] = 1;
			
			while(V.back() != j){
				C.back().pb(V.back());
				in_cycle[V.back()] = 1;
				V.pop_back();
			}
//			print(C.back(), int);
		}
	}
//	cerr << endl;
}

ll MST(){
	vector<vi> cycles;
	ll ret = 0;
	while(1){
		loop(i, n) if(i == find(i)){
			fr[i] = -1;
			cost[i] = INT_MAX * (i != 0);
		}
		
		loop(i, n) {
			while(!E[i].empty() && find(i) == find(E[i].back().first)) E[i].pop_back();
			if(!E[i].empty()){
				int j, c;
				j = E[i].back().first;
				c = E[i].back().second - loss[i];
				int k = find(i);
				if(c < cost[k]){
					cost[k] = c;
					fr[k] = j;
				}
			}
		}
/*		loop(i, n) if(i == find(i)) {
			int j = fr[i];
			if(j != -1) j = find(j);
			cerr << j << " " << i << " " << cost[i] << endl;
		}
		cerr << endl;
*/		
		cycles.clear();
		
		detect_cycles(cycles);
		
		if(cycles.empty()){
			ll tmp = 0;
			loop(i, n) if(i == find(i)) tmp += cost[i];
			ret += tmp;
			break;
		}
		
		ll tmp = 0;
		loop(i, n) if(i == find(i) && in_cycle[i]) tmp += cost[i];
		ret += tmp;
		
		loop(i, n) {
			int j = find(i);
			if(in_cycle[j])
				loss[i] += cost[j];
		}
		
		for(auto & V : cycles)
			for(int v : V)
				join(v, V[0]);
		
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int N; scanf("%d", &N);
	n = N + 1;
	init();
	
	for(int i = 1; i <= N; i++){
		int x, s; scanf("%d %d", &x, &s);
		for(int j = 0; j <= N; j++){
			int t; scanf("%d", &t);
			E[i].emplace_back(j, t);
		}
		E[i].emplace_back(x, s);
	}

	cout << MST() << endl;
	return 0;
}
