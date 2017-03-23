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

int n;
int A[1 << 20];
const int mod = 1e9 + 7;

int mul(int x,int y,int m){
	return (x*1LL*y)%m;
}

int pow_mod(int x,int p,int m){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(x,y,m);
		x = mul(x,x,m);
	}
	return mul(x,y,m);
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);	
	int ans = 1,sig0 = 1;
	loop(i,n){
		int p = A[i],q = 0,sum = 0;
		while(i + q < n && A[i + q] == A[i]) {
			q++;
			sum += q;
			if(sum >= mod - 1) sum -= mod - 1;
		}
		ans = mul(pow_mod(ans,q + 1,mod) , pow_mod(p,mul(sig0,sum,mod - 1),mod),mod);
		sig0 = mul(sig0,q + 1,mod-1);	
		i += q - 1;
	}
	cout << ans << endl;
	cerr << ans << endl;
	
	
	return 0;
}
