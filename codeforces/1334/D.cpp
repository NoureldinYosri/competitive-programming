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

const int MAXN = 100*1000 + 10;

int n;
ll len[MAXN], L, R;

inline void spit(int x, ll & cursor, ll L, ll R){
	cursor++;
	if(L <= cursor && cursor <= R){
		printf("%d ", x);
	}
}

void work(ll L, ll R){
	ll cursor = 0;
	for(int i = 1; i < n; i++){
		ll dc = 2*(n - i);
		if(cursor + dc < L) {
			cursor += dc;
			continue;
		}
		if(R <= cursor) return;
		
		ll old = cursor;
		for(int j = i+1; j <= n; j++){
			spit(i, cursor, L, R);
			spit(j, cursor, L, R);
		}
		
		cursor = old + dc;
	}		
	if(R == len[n]) printf("1 ");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	len[1] = 1;
	for(int i = 1;i+1 < MAXN; i++)
		len[i+1] = len[i] + 2*i;

	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %lld %lld", &n, &L, &R);
		work(L, R);
		puts("");
	}
	return 0;
}
