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


const int MAX = 30000*3;


vp V, Q;
int n;

int taken[MAX];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int R; scanf("%d %d", &n, &R);
	loop(i, n){
		int a, b; scanf("%d %d", &a, &b);
		if(b >= 0) V.emplace_back(a, b);
		else Q.emplace_back(a, -b);
	}
	
	sort(all(V));
	
	
	int ans = 0;
	for(auto [a, b] : V){
		if(a > R) break;
		ans ++;
		R += b;
	}
	

	sort(all(Q));
	
	reverse(all(Q));
	
	multiset<pi> MS;
	loop(i, sz(Q)) MS.emplace(Q[i].second, i);
	int i = 0;
	
	while(1){
		while(i < sz(Q) && Q[i].first > R){
			if(!taken[i]) MS.erase(pi(Q[i].second, i));
			i++;
		}
		if(MS.empty() || MS.begin()->first > R) break;
		ans++;
		R -= MS.begin()->first;
		taken[MS.begin()->second] = 1;
		MS.erase(MS.begin());
	}
	

	cout << ans << endl;	
	return 0;
}
