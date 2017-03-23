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

const int mod = 1e9 + 7;

int POW(int x,ll y){
	if(!y) return 1;
	int z = 1;
	for(;y > 1;y >>= 1){
		if(y & 1) z = (z*1LL*x)%mod;
		x = (x*1LL*x)%mod;
	}
	return (x*1LL*z)%mod;
}

int main(){
	string buffer; 
	int n,k;	
	cin >> buffer >> k;
	int ans = 0; n = sz(buffer);
	loop(i,n) if(buffer[i] == '0' || buffer[i] == '5') {
		ans += POW(2,i);
		if(ans >= mod) ans -= mod;
	}
	int a = POW(2,k*1LL*n) - 1;
	if(a < 0) a += mod;
	int b = POW(2,n) - 1;
	if(b < 0) b += mod;
	a = (a * 1LL * POW(b,mod - 2) ) %mod;
	ans = (ans * 1LL * a)%mod;
	cout << ans << endl;
	return 0;
}
