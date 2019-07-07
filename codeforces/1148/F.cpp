#ifdef ACTIVE
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

const int MAX = 300*1000 + 10;
int n;
ll val[MAX],msk[MAX];
ll s;
ll tot = 0;

int sgnMsk(ll m){
	int s = 1;
	while(m) {
		s *= -1;
		m ^= LSOne(m);
	}
	return s;
}

int taboo[62];

int sgn(ll x) {
	return (x > 0) - (x < 0);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%lld %lld",val + i,msk + i);
		tot += val[i];
	}
	ll sum = tot;

	while(tot==0 || sgn(tot) == sgn(sum) || !s){
		int d = INT_MAX;
		loop(b,62) d = min(d,taboo[b]);
		loop(b,62) taboo[b] -= d;
		pair<ll,ll> mn (LLONG_MAX,0),mx(LLONG_MIN,0);
		bool f = 0;
		for(int t = 0;t < 10;t++) {
			ll sub = 0;
			loop(b,62) {
				if(taboo[b]) continue;
				if(rand()%2) sub |= 1LL << b;
			}
			ll ns = s ^ sub;
			if(!ns) continue;
			f = 1;
			ll tmp = 0;
			loop(i,n) tmp += val[i] * sgnMsk(ns&msk[i]);
			if(mp(tmp,sub) < mn)
				mn = mp(tmp,sub);
			if(mp(tmp,sub) > mx)
				mx = mp(tmp,sub);
		}
		if(f) {
			auto choice = mn;
			if(sum < 0) choice = mx;
			tot = choice.xx;
			s ^= choice.yy;
			loop(b,62) {
				taboo[b]--;
				taboo[b] = max(taboo[b],0);
				if((choice.yy >> b)&1)
					taboo[b] = 20;
			}
		}
//		cerr << tot << " " << sum << " " << cb << " " << s << " " << mn.xx << " " << mx.xx << endl;
//		prArr(taboo,62,int);
	}
	cout << s << endl;
	return 0;
}
#endif
