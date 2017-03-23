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
ll x1,x2,k,b;
pl Y[1 << 20];
set<ll> S;

int main(){
	scanf("%d %lld %lld",&n,&x1,&x2);
	loop(i,n){
		scanf("%lld %lld",&k ,&b);
		Y[i].xx = k*x1 + b;
		Y[i].yy = k*x2 + b;
	}
	sort(Y,Y + n);
	ll mx = LLONG_MIN;
	loop(i,n) {
		int j = i;
		while(j < n && Y[i].xx == Y[j].xx){
			if(mx > Y[j].yy){
				puts("YES");
				return 0;
			}
			j++;
		}
		for(;i < j;i++) mx = max(mx,Y[i].yy);
		i = j - 1;
	}	
	puts("NO");
	return 0;
}
