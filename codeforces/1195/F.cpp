#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 300*1000 + 10;
const ll scaler = 3000000000LL;
int Start[MAX],End[MAX];
pi A[MAX];
int B[MAX];

int m;
int n;

int P[MAX][2];

void read(int id){
	int z; scanf("%d",&z);
	loop(i,z){
		scanf("%d %d",&P[i][0],&P[i][1]);
	}
	Start[id] = m;
	loop(i,z){
		int j = (i + 1)%z;
		int dx = P[j][0] - P[i][0];
		int dy = P[j][1] - P[i][1];
		int g = __gcd(abs(dx),abs(dy));
		dx /= g;
		dy /= g;
		A[m] = mp(dx,dy);
		m++;
	}
	End[id] = m-1;
}


struct node {
	int siz;
	node *l,*r;
};

node *insert(node *root,int s,int e,int p) {
	node *ret = new node();
	if(root) *ret = *root;
	ret->siz++;
	if(s == e) return ret;
	int mid = (s + e) >> 1;
	if(p <= mid) ret->l = insert(ret->l,s,mid,p);
	else ret->r = insert(ret->r,mid+1,e,p);
	return ret;
}

int getSize(node *u) {
	return u ? u->siz : 0;
}
node *getLeft(node *u) {
	return u ? u->l : 0;
}
node *getRight(node *u) {
	return u ? u ->r : 0;
}
int query(node *u,node *v,int s,int e,int l,int r) {
	if(l <= s && e <= r) return getSize(v) - getSize(u);
	int mid = (s + e) >> 1;
	if(r <= mid) return query(getLeft(u),getLeft(v),s,mid,l,r);
	if(mid < l) return query(getRight(u),getRight(v),mid+1,e,l,r);
	return query(getLeft(u),getLeft(v),s,mid,l,mid) +
			query(getRight(u),getRight(v),mid+1,e,mid+1,r);
}

node *T[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) read(i);
	map<pi,int> prv;
	for(int i = m-1;i >= 0;i--){
		pi v = A[i];
		if(prv.count(v)) B[i] = prv[v];
		else B[i] = m;
		prv[v] = i;
	}
	node *root = 0;
	int S = 0,E = m;
	loop(i,m) {
		root = T[i] = insert(root,S,E,B[i]);
	}
	int Q ;scanf("%d",&Q);
	while(Q-- ){
		int l,r; scanf("%d %d",&l,&r);
		l--,r--;
		l = Start[l];
		r = End[r];
		node *u = l ? T[l - 1] : 0;
		node *v = T[r];
		printf("%d\n",query(u,v,S,E,r+1,m));
	}

	return 0;
}
