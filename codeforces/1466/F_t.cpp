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

const int mod = 1e9 + 7;
int n, m;
set<int>* who[1 << 20];
vi ans;
int Rank;

set<int>* merge(set<int> *A, set<int> *B){
	if(!A) return B;
	if(!B) return A;
	if(A->size() < B->size()) swap(A, B);
	for(int x : *B) {
		if(A->count(x)) A->erase(x);
		else A->insert(x);
	}
	return A;
}

int id[1 << 20], W[1 << 20];
vi X[1 << 20];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a, int b){
	a = find(a);
	b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
}

bool done[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n){
		int z; scanf("%d", &z);
		loop(j, z){
			int x; scanf("%d", &x);
			x--;
			if(!who[x]) who[x] = new set<int>();
			who[x]->insert(i);
			X[i].push_back(x);
		}
	}
	iota(id, id + m, 0);
	fill(W, W + m, 1);
	loop(i, m){
		if(!who[i]) continue;
		while(!who[i]->empty()){
			int p = *who[i]->begin();
			if(done[p]){
				who[i]->erase(p);
			} else {
				break;
			}
		}
		if(who[i]->empty()) continue;
		int p = *who[i]->begin();
		done[p] = true;
		Rank++;	
		ans.push_back(p);
		if(sz(X[p]) > 1){
			int a = X[p][0], b = X[p][1];
			a = find(a);
			b = find(b);
			int j = (a == i) ? b : a;
			who[j] = merge(who[i], who[j]);				
			id[i] = j;
		}
	}
	int ans = 1;
	loop(i, Rank) {
		ans += ans;
		if(ans >= mod) ans -= mod;
	}
	printf("%d %d\n", ans, sz(::ans));
	sort(all(::ans));
	for(int x : ::ans) printf("%d ", x + 1);
	puts("");
	return 0;
}
