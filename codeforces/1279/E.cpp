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

const ll oo = 1LL << 60;

ll dp[55][55];

ll solve(int m,int n){
	if(m == 0 && n == 0) return 1;
	ll & ret = dp[m][n];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = 1;i <= n;i++){
		ret += solve(0 , n - i);
		ret = min(ret, oo);
	}
	return ret;
}




vi decompose(vi P){
	vi Q, vis(sz(P), 0);
	vector<vi> tmp;
	vi aux;
	int n = sz(P);
	loop(i,n) if(!vis[i]){
		int j = i;
		aux.clear();
		while(!vis[j]){
			aux.push_back(j);
			vis[j] = 1;
			j = P[j];
		}
		sort(all(aux));
		rotate(aux.begin(), max_element(all(aux)), aux.end());
		tmp.emplace_back(aux);
	}
	sort(all(tmp));
	for(auto V : tmp)
		for(int x : V)
			Q.push_back(x);
	return Q;
}

int bf(int n){
	
	vi P;
	loop(i,n) P.push_back(i);
	int ret = 0;
	do{
		vi T = decompose(P);
		if(P == T){
			ret++;
			cout << ret << ":";
			for(int x : P) cout << " " << x+1;
			cout << endl;
		}
	}while(next_permutation(all(P)));
	return ret;
}

vi P;

void gen(int n, ll k, int offset){
	if(n == 0) return;
	ll tot = 0;
	ll prv = 0;
	int i;
	for(i = 1;i <= n;i++){
		prv = tot;
		tot += solve(0, n - i);
		if(tot >= k) break;
	}
	assert(tot >= k);
	P.push_back(i + offset);
	for(int j = 1;j < i;j++)
		P.push_back(j + offset);
	gen(n - i, k - prv, i + offset);
}

void gen(int n, ll k){
	P.clear();
	if(solve(0,n) < k) {
		P.push_back(-1);
		return;
	}
	gen(n, k, 0);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
/*	memset(dp, -1, sizeof dp);
	int T; scanf("%d",&T);
	while(T--){
		int n; ll k; scanf("%d %lld",&n,&k);
		gen(n,k);
		for(int x : P) printf("%d ",x);
		puts("");
	}*/
	bf(5);
	return 0;
}
