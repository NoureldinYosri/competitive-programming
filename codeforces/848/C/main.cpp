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

struct entry{
	int key;
	ll val,sum;
public:
	entry():key(0),val(0),sum(0){}
	entry(int _key,int _val,int _sum):key(_key),val(_val),sum(_sum) {}
	bool operator < (const entry & o) const {
		return key < o.key;
	}
	bool operator < (const int & x) const {
		return key < x;
	}
	friend ostream& operator << (ostream & st, const entry & o)  {
		st << "(" << o.key << " ," << o.val << " ," << o.sum << ")";
		return st;
	}
};

const int MAX = 100*1000 + 10,MAXB = 350;
int A[MAX],n,m;
entry blk1[MAXB][MAXB],blk2[MAXB][MAXB];
int IDX1[MAXB],IDX2[MAXB],blkSize;
int lst[MAX],prv[MAX],nxt[MAX];
set<int> pos[MAX];

void fix(int u){
	IDX1[u] = IDX2[u] = 0;
	for(int i = 0,l = u*blkSize,r = min(l + blkSize,n);l < r;l++,i++){
		blk1[u][i] = entry(prv[l],l,0);
		blk2[u][i] = entry(nxt[l],l,0);
		IDX1[u]++;
		IDX2[u]++;
	}

	sort(blk1[u],blk1[u] + IDX1[u]);
	sort(blk2[u],blk2[u] + IDX2[u]);
	for(int i = 0;i < IDX1[u];i++)
		blk1[u][i].sum = blk1[u][i].val + (i ? blk1[u][i - 1].sum : 0);
	for(int i = 0;i < IDX2[u];i++)
		blk2[u][i].sum = blk2[u][i].val + (i ? blk2[u][i - 1].sum : 0);
}

void init(){
	blkSize = sqrt(n) + 1;
	fill(lst,lst + MAX,-1);
	for(int i = 0;i < n;i++){
		prv[i] = lst[A[i]];
		lst[A[i]] = i;
	}
	fill(lst,lst + MAX,n);
	for(int i = n-1;i >= 0;i--){
		nxt[i] = lst[A[i]];
		lst[A[i]] = i;
	}

	for(int u = 0;u <= (n-1)/blkSize;u++) fix(u);

	for(int i = 0;i < n;i++) pos[A[i]].insert(i);
}

int get_next(int val,int th){
	auto p = pos[val].lower_bound(th);
	if(p == pos[val].end()) return n;
	assert(*p != th);
	return *p;
}

int get_prev(int val,int th){
	auto p = pos[val].upper_bound(th);
	if(p == pos[val].begin()) return -1;
	--p;
	assert(*p != th);
	return *p;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);

	init();
	vi aux;
	while(m--){
		int type; scanf("%d",&type);
		if(type == 1){
			int p,val ; scanf("%d %d",&p,&val);
			p--;
			if(A[p] == val) continue;
			int nxt_cur = nxt[p];
			int prv_cur = prv[p];
			int nxt_new = get_next(val,p);
			int prv_new = get_prev(val,p);

			if(nxt_cur != n) prv[nxt_cur] = prv_cur;
			if(prv_cur != -1) nxt[prv_cur] = nxt_cur;

			nxt[p] = nxt_new;
			prv[p] = prv_new;
			if(nxt_new != n) prv[nxt_new] = p;
			if(prv_new != -1) nxt[prv_new] = p;

			pos[A[p]].erase(p);
			pos[val].insert(p);
			A[p] = val;

			aux.pb(p/blkSize);
			if(nxt_cur != n) aux.pb(nxt_cur/blkSize);
			if(nxt_new != n) aux.pb(nxt_new/blkSize);
			if(prv_cur != -1) aux.pb(prv_cur/blkSize);
			if(prv_new != -1) aux.pb(prv_new/blkSize);

			sort(all(aux));
			aux.resize(unique(all(aux)) - aux.begin());
			for(int u : aux) fix(u);
			aux.clear();
		}
		else {
			int l,r; scanf("%d %d",&l,&r);
			l--,r--;
			int u = l/blkSize,v = r/blkSize;
			ll ans = 0;
			if(u == v) {
				for(int i = l;i <= r;i++){
					if(prv[i] < l) ans -= i;
					if(nxt[i] > r) ans += i;
				}
			}
			else {
				for(int i = l,lim = (u + 1)*blkSize;i < lim;i++){
					if(prv[i] < l) ans -= i;
					if(nxt[i] > r) ans += i;
				}
				for(int i = v*blkSize;i <= r;i++){
					if(prv[i] < l) ans -= i;
					if(nxt[i] > r) ans += i;
				}
				for(++u;u < v;++u){
					int p = lower_bound(blk1[u],blk1[u] + IDX1[u],l) - blk1[u];
					--p;
					ll st = 0,en = 0;
					if(p != -1) st = blk1[u][p].sum;
					en = blk2[u][IDX2[u] - 1].sum;
					p = lower_bound(blk2[u],blk2[u] + IDX2[u],r+1) - blk2[u];
					--p;
					if(p != -1) en -= blk2[u][p].sum;
					ans += en - st;
				}
			}
			printf("%lld\n",ans);
		}
	}

	return 0;
}
