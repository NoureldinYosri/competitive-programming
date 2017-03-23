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

const int MAX = 100*1000 + 10;
ll n,l,r;
ll A[MAX],B[MAX],C[MAX],ord[MAX];

int main(){
	scanf("%lld %lld %lld",&n,&l,&r);
	loop(i,n) scanf("%lld",A + i);
	loop(i,n) scanf("%lld",C + i);
	loop(i,n) ord[i] = i;
	sort(ord,ord + n,[](const int & a,const int & b){
		return C[a] < C[b];
	});
	ll belief = l-r;
	loop(j,n){
		int i = ord[j];
		ll x = max(belief,l - A[i]);
		if(x + A[i] > r) {
			puts("-1");
			return 0;
		}
		B[i] = x + A[i];
		belief = x + 1;
	}
	loop(i,n) printf("%lld%c",B[i]," \n"[i==n-1]);
	return 0;
}
