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

const int MAX = 100000000,MAXS = MAX + 10,MAXD = 768;
int prime[MAXS];
int DIV[MAXD];

void sieve(){
	for(int i = 2;i < MAXS;i++)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAXS;j += i)
				prime[j] = i;
		}
}



int main(){
	sieve();
	cerr << "done sieve" << endl;
	ll ans = 0;
	for(int i = 1;i <= MAX;i++){
		if(prime[i+1] != i+1) continue;
		if(i%4 != 2) continue;
		int n = i,cnt = 1,c = 1;
		DIV[0] = 1; 
		while(n > 1 && c){
			int p = prime[n],k = cnt,s = 0;
			while(n%p == 0 && c) {
				for(int j = 0;j < k && c;j++){
					DIV[cnt] = DIV[s+j]*p;
					if(prime[DIV[cnt] + i/DIV[cnt]] != DIV[cnt] + i/DIV[cnt]) c = 0;
					cnt++; 
				}
				s += k;
				n /= p;
			}
		}
		if(c) ans += i;
	}	
	cerr << ans << endl;
	return 0;
}
