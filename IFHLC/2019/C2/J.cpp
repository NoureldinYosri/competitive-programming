#ifdef ACTIVE
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
using namespace std;

const int MAX = 100*1000 + 10,MAXA = 1000000000;



int P[MAX][2];
int A[MAX],B[MAX];
int n,m;

struct node{
	pi cur;
	int low[2],hi[2];
	node *l,*r;
};

vi I;

node* build(int s,int len,int d) {
	if(len == 0) return 0;
	sort(I.begin() + s,I.begin() + s + len,[d](const int & a,const int & b) {
		return P[a][d] < P[b][d];
	});
	node *ret = new node();
	fill(ret->low,ret->low+2,INT_MAX);
	fill(ret->hi,ret->hi+2,1);

	for(int i = 0;i < len;i++) {
		int k = I[s+i];
		loop(j,2) {
			ret->low[j] = min(ret->low[j],P[k][j]);
			ret->hi[j] = max(ret->hi[j],P[k][j]);
		}
	}
	int best = sz(I) + 1,c = -1;
	for(int i = 0;i < len;){
		int ctr = max(i,len - 1 - i);
		if(ctr < best){
			best = ctr;
			c = i;
		}
		int v = P[I[s+i]][d];
		while(i < len && P[I[s+i]][d] == v) i++;
	}
	assert(c >= 0);
	int k = I[s+c];
	ret->cur.first = P[k][0];
	ret->cur.second = P[k][1];
	ret->l = build(s,c,d^1);
	ret->r = build(s+c+1,len-c-1,d^1);
	return ret;
}

void erase(node *root) {
	if(!root) return;
	erase(root->l);
	erase(root->r);
	delete root;
}

ll cross(pi o,pi a,pi b) {
	a.first -= o.first; a.second -= o.second;
	b.first -= o.first; b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

int sgn(ll x) {
	return (x > 0) - (x < 0);
}

bool cond(node *root,pi a,pi b) {
	pi low (root->low[0],root->low[1]);
	pi hi  (root->hi[0],root->hi[1]);
	int s1 = sgn(cross(a,b,low)),s2 = sgn(cross(a,b,hi));
	return s1 && s2 && s1 == s2;
}

int query(node *root,pi a,pi b) {
	if(!root) return 0;
//	cerr << (root->cur) << " " << a << " " << b << endl;
//	prArr(root->low,2,int);
//	prArr(root->hi,2,int);
	if(cond(root,a,b)) return 0;
	int res = cross(root->cur,a,b) == 0;
	res += query(root->l,a,b);
	res += query(root->r,a,b);
	return res;
}

void tc(){
	scanf("%d %d",&n,&m);
	I.clear();
	loop(i,n) {
		int x,y;
		scanf("%d %d",&x,&y);
		P[i][0] = x;
		P[i][1] = y;
		I.push_back(i);
	}
	node* root = build(0,n,0);
	loop(i,m) {
		int a,b; scanf("%d %d",&a,&b);
		A[i] = a,B[i] = b;
		printf("%d\n",query(root,pi(a,0),pi(0,b)));
	}
	erase(root);
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		tc();
	}
	return 0;
}
#endif
