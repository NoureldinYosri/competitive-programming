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

const int MAX = 1e5 + 1e2,mod = 1e9 + 7;
int F[MAX],inv[MAX];

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

int mul(int x,int y){
	return (x*1LL*y)%mod;
}

int POW(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1; p>>=1){
		if(p & 1) y = mul(y,x);
		x = mul(x,x);
	}
	return mul(x,y);
}

void init(){
	F[0] = inv[0] = 1;
	loop(i,MAX - 1) {
		F[i + 1] = mul(F[i],i + 1);
		inv[i + 1] = POW(F[i + 1],mod - 2);
	}
}

int C(int n,int k){
	if(k > n) return 0;
	int ret = F[n];
	ret = mul(ret,inv[k]);
	ret = mul(ret,inv[n - k]);
	return ret;
}

bool magicic(int x){
	char s[20]; sprintf(s,"%d",x);
	for(char *p = s;*p;p++)
		if(*p != '4' && *p != '7')
			return 0;
	return 1;
}

int n,k,muggle,magic;
int A[MAX];
int dp[2][MAX];

int main(){
	init();
	scanf("%d %d",&n,&k);
	loop(i,n){
		int x; scanf("%d",&x);		
		if(magicic(x)) A[magic++] = x;
		else muggle++;	
	}		
	sort(A,A + magic);
	n = 0;
	loop(i,magic){
		int j = i;
		while(j < magic && A[i] == A[j]) j++;
		A[n++] = j - i;
		i = j - 1;
	}
	magic = n;
	dp[0][0] = 1;//C(muggle,k);		
	int one = 1,other = 0;
	loop(i,n){
		loop(magic,k+1){
			dp[one][magic] = dp[other][magic];
			if(magic) {
				int tmp = (dp[other][magic - 1]*1LL*A[i])%mod;
				dp[one][magic] += tmp;
				if(dp[one][magic] >= mod) dp[one][magic] -= mod;
			}
		}
		one ^= other ^= one ^= other;
	}
	int ans = 0;
	loop(i,k+1) {
		int tmp = (C(muggle,k - i) *1LL* dp[other][i])%mod;
		ans += tmp;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << endl;
	return 0;
}
