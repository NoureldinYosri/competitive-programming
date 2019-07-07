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
const double PI = acos(-1);
using namespace std;

struct myShape{
    int len;
    ll vl,mid,vr;
    myShape() {
    	memset(this,0,sizeof *this);
    }
    myShape(ll a,ll b,ll c,int l) {
        len = l;
        vl = a;
        mid = b;
        vr = c;
    }

    bool right(){
        if (len == 1) return 1;
        if (vl != mid && vr != mid) return vl < mid && mid < vr;
        return vl < vr;
    }
	bool left(){
        if (len == 1) return 1;
        if (vl != mid && vr != mid) return vl > mid && mid > vr;
        return vl > vr;
    }
    void add(ll x) {
        vl += x;
        mid += x;
        vr += x;
    }
};

struct node{
	ll lazy;
    myShape L,R;
    int siz,mx;
    node(){
    	memset(this,0,sizeof *this);
    }
};

const int MAX = 1 << 19,MAXST = MAX << 1;
node ST [MAXST];
int A[MAX];


myShape mergeShape(myShape L,myShape R,int mode) {
	if (L.vr < R.vl) {
		if (L.right()) {
			ll mid = R.vl;
			if (R.vl < R.mid) mid = R.mid;
			return myShape(L.vl,mid,R.vr,L.len + R.len);
		}
		if (mode == -1) return L;
		return myShape(L.vr,R.mid,R.vr,1 + R.len);
	}
	else if (L.vr > R.vl) {
		if (R.left()) {
			ll mid = L.vr;
			if (L.mid > mid) mid = L.mid;
			return myShape(L.vl,mid,R.vr,L.len + R.len);
		}
		if (mode == 1) return R;
		return myShape(L.vl,L.mid,R.vl,L.len + 1);
	}
	if (mode == -1) return L;
	return R;
}

node merge(node L,node R) {
	node ret ;
	ret.siz = L.siz + R.siz;
	ret.L = L.L;
	ret.R = R.R;
	ret.mx = max(L.mx,R.mx);

	myShape tmp = mergeShape(L.R,R.L,0);

	ret.mx = max(ret.mx,tmp.len);

	if (L.L.len == L.siz) {
		ret.L = mergeShape(L.L,R.L,-1);
		ret.mx = max(ret.mx,ret.L.len);
	}
	if (R.R.len == R.siz) {
		ret.R = mergeShape(L.R,R.R,1);
		ret.mx = max(ret.mx,ret.R.len);
	}

	return ret;
}

void build(int cur,int s,int e) {
	if (s == e) {
		int x = A[s];
		ST[cur].L = ST[cur].R = myShape(x,x,x,1);
		ST[cur].mx = ST[cur].siz = 1;
		ST[cur].lazy = 0;
	}
	else {
		int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
		build(left,s,m);
		build(right,m+1,e);
		ST[cur] = merge(ST[left],ST[right]);
	}
}

void update(int cur,ll v) {
	ST[cur].lazy += v;
	ST[cur].L.add(v);
	ST[cur].R.add(v);
}

void push(int cur) {
	if (ST[cur].lazy == 0) return;
	int left = 2*cur + 1,right = left + 1;
	update(left,ST[cur].lazy);
	update(right,ST[cur].lazy);
	ST[cur].lazy = 0;
}

void update(int cur,int s,int e,int l,int r,int v) {
	if (l <= s && e <= r) update(cur,v);
	else {
		push(cur);
		int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
		if (r <= m) update(left,s,m,l,r,v);
		else if (m < l) update(right,m+1,e,l,r,v);
		else {
			update(left,s,m,l,m,v);
			update(right,m+1,e,m+1,r,v);
		}
		ST[cur] = merge(ST[left],ST[right]);
	}
}

int main(int argc,char **argv) {
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n ; scanf("%d",&n);
	for (int i = 1;i <= n;i++)
		scanf("%d",A + i);
	build(0,1,n);

	int m ; scanf("%d",&m);
	for (;m > 0;m--){
		int l,r,d; scanf("%d %d %d",&l,&r,&d);
		update(0,1,n,l,r,d);
		printf("%d\n",ST[0].mx);
	}

	return 0;
}



