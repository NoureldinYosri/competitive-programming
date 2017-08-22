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
#define popcnt(x) __builtin_popcountll(x)
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

int f[1 << 20],n,n1,n2;
ll adj[40];


bool is_complete(ll msk){
	if(!msk) return 0;
	loop(i,n) if(msk & (1LL << i)) {
		ll a = adj[i] & msk;
		ll b = msk ^ (1LL << i);
		if(a != b) return 0;
	}
	return 1;
}



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int k; scanf("%d %d",&n,&k);
	n1 = n/2;
	n2 = (n + 1)/2;
	loop(i,n){
		loop(j,n){
			int x; scanf("%d",&x);
			if(x) {
				adj[i] |= 1LL << j;
			}
		}
	}

	int siz = 0;
	for(int msk = 0;msk < (1 << n1);msk++){
		if(is_complete(msk)) f[msk] = popcnt(msk);
		for(int omsk = msk;omsk;omsk ^= LSOne(omsk))
			f[msk] = max(f[msk],f[msk ^ LSOne(omsk)]);
		siz = max(siz,f[msk]);
	}

	for(int msk = 0;msk < (1 << n2);msk++) {
		ll tmp = msk; tmp <<= n1;
		if(is_complete(tmp)) {
			int omsk = 0;
			loop(i,n1) if((adj[i] & tmp) == tmp) omsk |= 1 << i;
			siz = max(siz,popcnt(msk) + f[omsk]);
		}
	}

	double ans = k*1.0*k*(siz - 1.0)/siz*0.5;
	printf("%.10f\n",ans);

	return 0;
}
