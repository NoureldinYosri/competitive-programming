#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;


ll a,b,c,d;
ll solve(){
	if(a > b) swap(a,b);
	if(c == d) return b - a;
	if(c%d == 0 || d%c == 0){
		if c%d == 0 :
			diff = b - a;
			diff -= diff%c;
			return b - a;
		
	}
	bool c1 = a%2 == b%2,c2 = c%2 == d%2;
	return c1 != c2;
}

int main(){
	int T; 
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld %lld %lld",&a,&b,&c,&d);
		printf("%lld\n",solve());
	}
	return 0;
}


