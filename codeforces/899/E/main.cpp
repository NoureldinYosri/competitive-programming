#pragma GCC optimize ("O3")
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

struct quanta{
	int l,r,val,cnt;
	bool operator < (const quanta & o) const {
		if(cnt != o.cnt) return cnt < o.cnt;
		return l > o.l;
	}
};


struct node{
	quanta pref,suff,mx;
	int siz;
	node(){
		memset(this,0,sizeof *this);
	}
	node(int pos,int val) {
		pref = quanta({pos,pos,val,1});
		suff = quanta({pos,pos,val,1});
		mx = quanta({pos,pos,val,1});
		siz = 1;
	}
};

const int MAX = 200*1000 + 10,MAXP2 = 1 << 18;
int A[MAX],n;
node ST[MAXP2*2];

quanta merge(quanta left,quanta right) {
	if(left.cnt == 0) return right;
	if(right.cnt == 0) return left;
	quanta ret;
	ret.cnt = left.cnt + right.cnt;
	ret.l = left.l;
	ret.r = right.r;
	ret.val = left.val;
	assert(left.val == right.val);
	return ret;
}

node merge(node left,node right) {
	if(left.siz == 0) return right;
	if(right.siz == 0) return left;

	node ret;
	ret.siz = left.siz + right.siz;
	ret.mx = max(left.mx,right.mx);
	ret.pref = left.pref;
	ret.suff = right.suff;

	if(left.suff.val == right.pref.val)
		ret.mx = max(ret.mx,merge(left.suff,right.pref));

	if(left.pref.cnt == left.siz && left.pref.val == right.pref.val)
		ret.pref = merge(left.pref,right.pref);

	if(right.suff.cnt == right.siz && left.suff.val == right.suff.val)
		ret.suff = merge(left.suff,right.suff);

	ret.mx = max(ret.mx,ret.pref);
	ret.mx = max(ret.mx,ret.suff);
	return ret;
}

void build(int cur,int s,int e) {
	if(s == e) {
		ST[cur] = node(s,A[s]);
		return;
	}
	int m = (s + e) >> 1,left = cur * 2 + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[cur] = merge(ST[left],ST[right]);
}


void clear(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r) {
		memset(&ST[cur],0,sizeof ST[cur]);
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) clear(left,s,m,l,r);
	else if(m < l) clear(right,m+1,e,l,r);
	else clear(left,s,m,l,m),clear(right,m+1,e,m+1,r);
	ST[cur] = merge(ST[left],ST[right]);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	build(0,0,n-1);
	int ans = 0;
	while(ST[0].mx.cnt) {
//		cerr << ST[0].mx.val << endl;
		ans++;
		clear(0,0,n-1,ST[0].mx.l,ST[0].mx.r);
	}
	printf("%d\n",ans);
	return 0;
}
