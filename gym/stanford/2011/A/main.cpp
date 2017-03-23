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

char S[] = "RPS";

int solve(ll n,int lev,ll len){
	//cerr << n << " " << lev << " " << len << endl;
	if(!lev) {
		assert(1 <= n && n <= 3);
		return n - 1;
	}
	if(n > len){
		int k = solve(n - len,lev,len);
		return (k + 1)%3;
	}
	int k = solve((n - 1)%(len/3) + 1,lev - 1,len/3);
	k += (n - 1)/(len/3);
	k %= 3;
	return k;
}

int solve(ll n){
	if(n <= 3) return n - 1;
	int lev = 1;
	ll offset = 3,len = 3;
	while(offset + 2*len < n){
		offset += 2*len;
		len *= 3;
		lev++;
	}
	return solve(n,lev,len);
}

int main(){
	ll n;
	while(scanf("%lld",&n) == 1 && n){
		int k = solve(n);
	//	cerr << S[k] << endl;
		putchar(S[(k + 1)%3]);
		puts("");
	}
	
	return 0;
}
