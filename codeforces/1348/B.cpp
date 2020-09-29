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

vi A, B;
int K;


void read(){
	int n; scanf("%d %d", &n, &K);
	A.resize(n);
	for(int & a : A) scanf("%d", &a);
}

int count_dist(){
	return set<int>{all(A)}.size();
}

void bt(int i){
	if(i == sz(A)) return; 
	int x = A[i];
	if(B[sz(B) - K] == x){
		B.pb(x);
		return bt(i+1);
	}
	B.pb(B[sz(B)-K]);
	bt(i);	
}

void get_answer(){
	B.clear();
	for(int x : A) B.pb(x);
	sort(all(B));
	B.resize(unique(all(B)) - B.begin());
	while(sz(B) < K) B.pb(B.back());
	bt(0);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		read();
		if(count_dist() > K){
			puts("-1");
			continue;
		}
		get_answer();
		printf("%d\n", sz(B));
		for(int x : B) printf("%d ", x);
		puts("");
	}
	return 0;
}
