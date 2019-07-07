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

const int MAXN = 1 << 20;
struct rect{
	ll x,y,a;
};

typedef pair<ll,ll> line;
auto f = [](const line & L,const ll & x) {
	return L.first*x + L.second;
};

rect R[MAXN];
int n;
deque<line> dq;
ll lo,hi;

ll g(line a,line b) {
	ll s = lo,e = hi + 1;
	while(s < e) {
		ll m = s + (e-s)/2;
		if(f(b,m) >= f(a,m)) e = m;
		else s = m+1;
	}
	return s;
}

void insert(line L) {
	assert(dq.empty() || dq.back().first < L.first);
	int s = sz(dq);
	while(s > 1 && g(dq[s-2],L) <= g(dq[s-2],dq[s-1])) {
		dq.pop_back();
		s--;
	}
	dq.push_back(L);
}

ll query(ll x) {
	while(sz(dq) > 1 && f(dq[0],x) <= f(dq[1],x)) dq.pop_front();
	return f(dq[0],x);
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld %lld %lld",&R[i].x,&R[i].y,&R[i].a);
	sort(R,R + n,[](const rect & a,const rect & b) {
		return a.x < b.x;
	});
	hi = LLONG_MIN;
	lo = LLONG_MAX;
	loop(i,n) {
		ll x = -R[i].y;
		lo = min(lo,x);
		hi = max(hi,x);
	}

	ll ans = 0;
	insert(line(0,0));
	for(int i = 0;i < n;){
		int j = i;
		ll bv = 0;
		while(j < n && R[i].x == R[j].x){
			const rect & r = R[j++];
			ll v = r.x*r.y - r.a + query(-r.y);
			bv = max(bv,v);
		}
		ans = max(ans,bv);
		insert(line(R[i].x,bv));
		i = j;
	}
	printf("%lld\n",ans);
	return 0;
}
