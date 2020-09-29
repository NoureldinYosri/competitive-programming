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

const int MAX = 200*1000 + 10;
int n, m;
int W[MAX];
int excess[MAX];
int X[MAX], Y[MAX];
vi who[MAX], ans;
bool done_meal[MAX], has_eaten[MAX];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &m, &n);
	for(int i = 1; i <= m; i++) scanf("%d", W + i);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", X + i, Y + i);
		who[X[i]].pb(i);
		who[Y[i]].pb(i);
	}
	queue<int> q;
	for(int i = 1; i <= m; i++){
		excess[i] = W[i] - sz(who[i]);
		if(excess[i] >= 0) {
			done_meal[i] = 1;
			q.push(i);
		}
	}
	while(!q.empty()){
		int meal = q.front(); q.pop();
		for(int p : who[meal]) if(!has_eaten[p]){
			has_eaten[p] = 1;
			ans.pb(p);
			int other_meal = X[p] + Y[p] - meal;
			if(!done_meal[other_meal]){
				excess[other_meal]++;
				if(excess[other_meal] >= 0){
					done_meal[other_meal] = 1;
					q.push(other_meal);
				}
			}
		}
	}
	if(sz(ans) != n) {
		puts("DEAD");
		return 0;
	}
	reverse(all(ans));
	for(int p : ans) {
		int a = X[p], b = Y[p];
		if(W[a] == 0 && W[b] == 0){
			puts("DEAD");
			return 0;			
		}
		W[a] -= W[a] > 0;
		W[b] -= W[b] > 0;
	}
	puts("ALIVE");
	for(int p : ans) printf("%d ", p);
	puts("");
	return 0;
}
