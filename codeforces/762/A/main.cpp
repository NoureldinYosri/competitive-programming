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

ll DIV[1 << 20];

int main(){
	ll n,k,num = 1; cin >> n >> k;
	vector<pl> fact;
	for(ll i = 2;i*i <= n;i++)
		if(n%i == 0){
			int ctr = 0;
			while(n%i == 0){
				ctr++;
				n /= i;
			}
			fact.pb(mp(i,ctr));
			num *= ctr + 1;
		}
	if(n > 1) fact.pb(mp(n,1)),num <<= 1;
	if(num < k) {
		puts("-1");
		return 0;
	}
	assert(num <= (1 << 20));
	int m = 1;
	DIV[0] = 1;
	for(auto q : fact){
		ll p = q.xx; int e = q.yy,len = m,s = 0;
		loop(i,e) 
			loop(j,len){
				DIV[m++] = DIV[s++] * p;
				assert(m < (1 << 20));
			}
	}
	sort(DIV,DIV + m);
	//prArr(DIV,m,ll);
	cout << DIV[k - 1] << endl;
	cerr << DIV[k - 1] << endl;
	return 0;
}
