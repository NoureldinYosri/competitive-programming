#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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

const int MAX = 1e5 + 1e2;
int A[MAX],n,m;
vi vals[MAX];

bool bump(int a,int b,int c){
	if(a < b && b > c) return 1;
	if(a > b && b < c) return 1;
	return 0;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m) scanf("%d",A + i);
	ll ans = LLONG_MAX,tot = 0;
	loop(i,m - 1) tot += abs(A[i] - A[i + 1]);
	m = unique(A,A + m) - A;
	//prArr(A,m,int);
	loop(i,m-1) {
		vals[A[i]].pb(A[i + 1]);
		vals[A[i + 1]].pb(A[i]);
	}
	ans = tot;
	range(i,1,n){
		sort(all(vals[i]));
		ll tmp = tot,sum = 0,run_sum = 0;
//		cerr << i << " : " ; print(vals[i],int);
		for(int x : vals[i]) tmp -= abs(x - i),sum += x;
		loop(j,sz(vals[i])){
			ll x = vals[i][j];
			run_sum += x; sum -= x;
			ll q = x*(j + 1) - run_sum + sum - x*(sz(vals[i]) - j - 1);
	//		cerr << i << " -> " << x << " = " << tmp << " + " << q << endl;
			ans = min(ans,tmp + q);
		}
	}
	cout << ans << endl;
	//cerr << ans << endl;
	return 0;
}
