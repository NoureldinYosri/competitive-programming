#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

ll name[64],sub[64];

int get_level(ll v) {
	int r = 0;
	while(v > 1) {
		v >>= 1;
		r ++;
	}
	return r;
}

ll add(ll a,ll b,ll mod) {
	b = (b%mod + mod)%mod;
	a = (a%mod + mod)%mod;
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

ll get_name(ll X,int l) {
	ll siz = 1LL << l,fst = 1LL << l;

	ll v = add(X ,-fst,siz);
	v = add(v,-name[l],siz);
	v = add(v,-sub[l],siz);

	return fst + v;
}

ll get_cur(ll X,int l) {
	ll siz = 1LL << l,fst = 1LL << l;

	ll v = add(X,-fst,siz);
	v = add(v ,name[l],siz);
	v = add(v ,sub[l],siz);

	return fst + v;
}

ll get_loc(ll X,int l) {
	ll siz = 1LL << l,fst = 1LL << l;

	ll v = add(X,-fst,siz);
	v = add(v,sub[l],siz);
	return fst + v;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int Q; scanf("%d",&Q);
	while(Q--) {
		int t; ll X;
		scanf("%d %lld",&t,&X);
		if(t == 1) {
			ll K; scanf("%lld",&K);
			int l = get_level(X);
			ll siz = 1LL << l;
			name[l] += K%siz;
			if(name[l] >= siz) name[l] -= siz;
		}
		else if(t == 2) {
			ll K; scanf("%lld",&K);
			int l = get_level(X);
			ll siz = 1LL << l;
			sub[l] += K%siz;
			if(sub[l] >= siz) sub[l] -= siz;
		}
		else {
			int l = get_level(X);
//			cerr << X << endl;
			X = get_cur(X,l);
//			cerr << X << endl;
			bool f = 1;
			for(;X > 1;f = 0) {
				if(!f) putchar(' ');
				printf("%lld",get_name(X,l));
				X >>= 1;
				l--;
				X = get_loc(X,l);
//				cerr << X << " -> " << get_name(X,l) << endl;
			}
			if(!f) putchar(' ');
			puts("1");
		}
	}
	return 0;
}
