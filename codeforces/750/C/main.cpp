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

ll e = 200*1000*100 + 1900 + 1e4;
ll s = -e;

int main(){
	int n,d,c; scanf("%d",&n);
	bool bound = 0;
	while(n--){
		scanf("%d %d",&c,&d); 
		if(d == 1){
			if(1900 > e) {
				puts("Impossible");
				return 0;
			}
			s = max(s,1900LL);
		}
		else{
			if(s >= 1900) {
				puts("Impossible");
				return 0;
			}
			e = min(e,1899LL);
			bound = 1;
		}
		s += c;
		e += c;
	}
	if(bound) printf("%lld\n",e);
	else puts("Infinity");
	return 0;
}
