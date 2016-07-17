#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
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

const int MAX = 1 << 20;
int prime_factor[MAX];

multiset<int> P;

void sieve(){
	loop(i,MAX) prime_factor[i] = i;
	for(ll i = 2;i < MAX;i++)
		if(prime_factor[i] == i){
			for(ll j = i*i;j < MAX;j += i)
				prime_factor[j] = i;
		}
}

map<int,int> M[2];

void factor(int n,int c){
	vector<pi> ret;
	while(n > 1){
		int p = prime_factor[n],ctr = 0;
		if(M[c].find(p) == M[c].end()) M[c][p] = 0;
		while(n%p == 0){
			n /= p;
			ctr++;
		}
		M[c][p] = max(M[c][p],ctr);
	}
}


int main(){
	sieve();
	int n,k;
	scanf("%d %d",&n,&k);
	factor(k,0);
	loop(i,n){
		int a;
		scanf("%d",&a);
		factor(a,1);
	}
	bool c = 1;
	for(auto p : M[0]) {
		if(M[1].find(p.xx) == M[1].end()) M[1][p.xx] = 0;
		if(M[1][p.xx] < p.yy) c = 0;
		if(!c) break;
	}	
	if(!c) puts("No");
	else puts("Yes");
	return 0;
}

