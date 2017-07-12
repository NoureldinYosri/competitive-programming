#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 100*1000 + 10;

int A[MAX];
int n;


int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	//	freopen("output.out", "w", stdout);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T){
		int k; scanf("%d %d",&n,&k);
		loop(i,n) scanf("%d",A + i);
		ll s = 0,e = 1LL << 50;
		while(s < e){
			ll m = s + (e - s + 1)/2;
			ll f = 0;
			loop(i,n) f += min(m,A[i] + 0LL);
			if(f >= k*m) s = m;
			else e = m - 1;
		}

		printf("Case %d: %lld\n",t,e);
	}
	return 0;
}
