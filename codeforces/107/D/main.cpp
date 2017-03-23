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

const int MAX = 170;

double C(int n,int k){
	double ans = 1;
	k = min(k,n - k);
	loop(i,k){
		ans = (ans * (n - i))/(i + 1);
	}
//	cerr << n << " " << k << " " << ans << endl;
	return ans;
}
int main(){
	int n,m,h,s = 0,tot; 
	cin >> n >> m >> h; n--;
	for(int i = 1;i <= m;i++){
		int a; cin >> a;
		if(i != h) s += a;
		else tot = a - 1;
	}
	tot += s;
	if(tot < n){
		cerr << -1 << endl;
		cout << -1 << endl;
		return 0;
	}
	double ans = 1; 
	if(n  <= s){
		cerr << s << " " << s - n << endl;
		cerr << tot << " " << tot - n << endl;
		double p = C(s,n);
		p /= C(tot,n);
		ans -= p;
	}
	cerr << ans << endl;
	printf("%.10f\n",ans);
	return 0;
}
