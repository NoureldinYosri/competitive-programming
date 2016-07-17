#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 10000000;
int prime[MAX + 1];
int A[MAX];

int main(){
	for(ll i = 2;i <= MAX;i++)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*i;j <= MAX;j += i)
				prime[j] = i;
		}
	int idx = 0,a,n;
	fscanf(stdin,"%d",&n);
	loop(i,n){
		fscanf(stdin,"%d",&a);
		while(a > 1){
			int p = prime[a];
			A[idx++] = p;
			while(a%p == 0) a /= p; 
		}
	}
	sort(A,A + idx);
	int m,b;
	fscanf(stdin,"%d",&m);
	while(m--){
		fscanf(stdin,"%d %d",&a,&b);
		auto u = lower_bound(A,A + idx,a);
		auto v = lower_bound(A,A + idx,b + 1);
		fprintf(stdout,"%lu\n",v - u);
	}
	return 0;
}
