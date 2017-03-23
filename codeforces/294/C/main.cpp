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
int A[1010],F[1001],r[1001],n,m;

int mul(int x,int y){
	return (x*1LL*y)%mod;
}

int POW(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int main(){
	F[0] = r[0] = 1;
	loop(i,1000) {
		F[i + 1] = mul(F[i],i + 1);
		r[i + 1] = POW(F[i + 1],mod - 2); 
	}
	scanf("%d %d",&n,&m);
	loop(i,m) scanf("%d",A + i);
	A[m] = 0;
	A[m + 1] = n + 1;
	m += 2;
	sort(A,A + m);
	vi len; int tot = 0;
	loop(i,m - 1) len.pb(A[i + 1] - A[i] - 1),tot += len.back();
	int ans = F[tot];
	for(int l : len) ans = mul(ans,r[l]);
	for(int i = 1;i < m - 2;i++) if(A[i + 1] - A[i] > 2) ans = mul(ans,POW(2,A[i + 1] - A[i] - 2));
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
