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

const int MAX = 100000 + 10;
int is_prime[MAX];

void sieve(){
	fill(is_prime,is_prime + MAX,1);
	range(i,2,MAX-1)
		if(is_prime[i])
			for(ll j = i*1LL*i;j < MAX;j += i)
				is_prime[j] = 0;
}

int main(){
	sieve();
	int n; cin >> n;
	if(n <= 2) puts("1");
	else puts("2");
	range(i,2,n+1) printf("%d%c",2 - is_prime[i]," \n"[i==n+1]);
	
	
	return 0;
}
