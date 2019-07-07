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

const int MAXN = 100*1000 + 10,oo = 2 << 20;
int n;
int X[MAXN],Y[MAXN];


bool read(){
	scanf("%d",&n);
	if(n == -1) return 0;
	loop(i,n) scanf("%d %d",X + i,Y + i);
	return 1;
}

struct rect{
	int x_low,y_low;
	int x_high,y_high;
	friend ostream& operator << (ostream & st,const rect & r) {
		st << "{(" << r.x_low << ", " << r.y_low << ")";
		st << "(" << r.x_high << ", " << r.y_high << ")}";
		return st;
	}
};

struct bracket{
	int x,y_low,y_high,sgn;
};

struct node{
	node *L,*R;
	int cnt,active;
};

int get_active(node *root) {
	return root ? root->active : 0;
}

int calc_active(node *root,int L) {
	if(root->cnt > 0) return L;
	if(root->cnt < 0) return 0;
	return get_active(root->L) + get_active(root->R);
}

void update(node *root,int v,int L) {
	root->cnt += v;
	root->active = calc_active(root,L);
}

node* update(node *root,int s,int e,int l,int r,int v) {
	if(!root) root = new node();
	if(l <= s && e <= r) update(root,v,e-s+1);
	else{
		int m = (s + e) >> 1;
		if(r <= m) root->L = update(root->L,s,m,l,r,v);
		else if(m < l) root->R = update(root->R,m+1,e,l,r,v);
		else {
			root->L = update(root->L,s,m,l,m,v);
			root->R = update(root->R,m+1,e,m+1,r,v);
		}
		root->active = calc_active(root,e-s+1);
	}
	return root;
}


ll area(vector<rect> V) {
	static vector<bracket> B;
	B.clear();
	ll ret = 0;
	for(auto r : V){
		B.push_back(bracket({r.x_low,r.y_low,r.y_high,1}));
		B.push_back(bracket({r.x_high+1,r.y_low,r.y_high,-1}));
	}
	sort(all(B),[](const bracket & a,const bracket & b) {
		return tie(a.x,a.sgn) < tie(b.x,b.sgn);
	});
//	for(auto b : B)
//		cerr << "@" << b.x << " " << ")("[b.sgn==1] << b.y_low << " " << b.y_high  << endl;
	int s = INT_MAX,e = INT_MIN;
	for(auto b : B) {
		s = min(s,b.y_low);
		e = max(e,b.y_high);
	}
	node *root = 0;
	int lst = B[0].x - 1;
	for(int i = 0;i < sz(B);) {
		int x = B[i].x;
		ll h = get_active(root);
		ll w = x - lst;
		ret += h*w;
		int j = i;
		while(j < sz(B) && B[i].x == B[j].x) {
			root = update(root,s,e,B[j].y_low,B[j].y_high,B[j].sgn);
			j++;
		}
//		cerr << x << " " << root->active << endl;
		lst = x;
		i = j;
	}
	return ret;
}

bool get_intersection(rect a,rect b,rect & c) {
	if(a.x_low > b.x_low) swap(a,b);
	if(a.x_high < b.x_low) return 0;
	int x_low = b.x_low,x_high = a.x_high;
	if(a.y_low > b.y_low) swap(a,b);
	if(a.y_high < b.y_low) return 0;
	int y_low = b.y_low,y_high = a.y_high;
	c = rect({x_low,y_low,x_high,y_high});
	return 1;
}


bool alive(int t) {
	static vector<rect> V;
	V.clear();
	int r1 = t,r2 = t;//(t + 1)/2,r2 = t/2;
	rect me({-r1,-r1,r1,r1});
	loop(i,n) {
		rect mummy({X[i] - r2,Y[i] - r2,X[i] + r2,Y[i] + r2});
		rect inter;
//		cerr << me << " /\\ " << mummy << " = ";
		if(get_intersection(mummy,me,inter)) {
			V.push_back(inter);
//			cerr << inter << endl;
		}
//		else cerr << "{}" << endl;
	}
	ll tot = (2*r1 + 1LL)*(2*r1 + 1);
	ll A = area(V);
//	cerr << A << " " << tot << endl;
	return A < tot;
}

int solve(){
	int s = 0,e = oo;
	while(s < e) {
		int m = s + (e-s+1)/2;
		if(alive(m)) s = m;
		else e = m - 1;
	}
	if(s == oo) return -1;
	return s + 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int cn = 1;read();cn++) {
		int ans = solve();
		printf("Case %d: ",cn);
		if(ans == -1)puts("never");
		else printf("%d\n",ans);
	}
	return 0;
}
