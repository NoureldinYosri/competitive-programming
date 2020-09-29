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


string S;
int n, k;

vector<vi> commands;


bool work(){
	static vi pos;
	pos.clear();
	for(int i = 0;i + 1 < n ; i++) if(S[i] == 'R' && S[i+1] == 'L') pos.pb(i);
	if(pos.empty()) return 0;
	for(int i : pos){
		S[i] = 'L';
		S[i+1] = 'R';
	}
	commands.emplace_back(pos);
	return 1;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> k >> S;
	while(work());
	int K = 0;
	for(auto & V : commands) K += sz(V);
	if(k < sz(commands) || k > K) {
		puts("-1");
		return 0;
	}
	int rem = sz(commands);
	for(auto & V : commands){
		rem--;
		int d = min(sz(V), k - rem);
		k -= d;
		while(d > 1){
			printf("1 %d\n", V.back() + 1);
			V.pop_back();
			d--;
		}
		printf("%d", sz(V));
		for(int x : V) printf(" %d", x+1);
		puts("");
	}
	return 0;
}
