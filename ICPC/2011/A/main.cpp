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

int a,m,p,q,r,s;

bool read(){
	scanf("%d %d",&a,&m);
	scanf("%d %d",&p,&q);
	scanf("%d %d",&s,&r);
	return !(a==0 && m==0 && p==0 && q==0 && r==0 && s==0);
}

vi As;
vi Ms;
auto cmp = [](const vi & a,const vi & b) {
	int sa = accumulate(all(a),0LL) + sz(a) ;
	int sb = accumulate(all(b),0LL) + sz(b);
	if(sa != sb) return sa < sb;
	int i = 0;
	for(;i < sz(a) || i < sz(b);i++) {
		int xa = 0,xb = 0;
		if(i < sz(a)) xa = a[i];
		if(i < sz(b)) xb = b[i];
		if(xa > xb) return true;
		if(xa < xb) return false;
	}
	return false;
};

vi tmp;
bool found;
void bt(int i,ll sum,ll st,ll en) {
	if(st <= sum && sum <= en){
		As = min(As,tmp,cmp);
		found = 1;
		return;
	}
	if(sum > en) return;
	if(i == sz(Ms))	return;
	if(cmp(As,tmp)) return;
	ll mi = Ms[sz(Ms)-1-i];
	ll k = max((st - sum)/mi,0LL);
	ll mn = max(0LL,k-1),mx = max(k+1,0LL);
	for(;mx >= mn;mx--) {
		tmp[i] = mx;
		bt(i+1,sum + mx*mi,st,en);
		tmp[i] = 0;
	}
}

const int oo = INT_MAX-40;

int solve(){
	As = vi({oo});
	ll mg = 1;
	// r <= p*m^g + sum a * d_i * m^i
	// q*m^g + sum a*d_i * m^i <= s
	found = 0;
	if(s <= p && q <= r) return 2;
	if(m == 1) {
		ll d = (s - p + a - 1)/a;
		if(d < 0) return 0;
		if(q + d*a > r) return 0;
		As = vi({(int)d});
		return 1;
	}
	Ms.clear();
	for(int g = 0;q*mg <= r;mg *= m,g++) {
		Ms.push_back(mg);
		ll st = (s - p*mg + a - 1)/a;
		ll en = (r - q*mg)/a;
		if(st > en) continue;
		tmp = vi(g+1,0);
		bt(0,0,st,en);
	}
	return found;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	for(int cn = 1;read();cn++) {
		printf("Case %d:",cn);
		int res = solve();
		if(res == 0) puts(" impossible");
		else if(res == 2) puts(" empty");
		else {
			int ctr = 0;
			for(int a : As) {
				if(a) {
					if(ctr) printf(" %dM",ctr);
					printf(" %dA",a);
					ctr = 0;
				}
				ctr++;
			}
			if(ctr > 1) printf(" %dM",ctr-1);
			puts("");
		}
	}
	return 0;
}
