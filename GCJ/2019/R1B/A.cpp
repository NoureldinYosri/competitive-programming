//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//struct Arrow{
//	int x0,y0,dx,dy;
//public:
//	friend istream& operator >> (istream & st,Arrow a) {
//		st >> a.x0 >> a.y0;
//		char c; st >> c;
//		a.dx = (c == 'E') - (c == 'W');
//		a.dy = (c == 'N') - (c == 'S');
//		return st;
//	}
//};
//
//int m,n;
//Arrow A[500];
//
//struct node{
//	pi mx;
//	int lazy;
//	node *L,*R;
//};
//
//void push(node *root,int s,int e) {
//	if(root->lazy == 0) return;
//	if(!root->L) root->L = new node({{0,-s},0,NULL,NULL});
//	if(!root->R) root->R = new node({{0,-e},0,NULL,NULL});
//	root->L->mx.first += root->lazy;
//	root->R->mx.first += root->lazy;
//	root->L->lazy += root->lazy;
//	root->R->lazy += root->lazy;
//	root->lazy = 0;
//}
//
//node* update(node* root,int s,int e,int l,int r) {
//	if(!root) root = new node({{0,-s},0,NULL,NULL});
//	if(l <= s && e <= r) {
//		root->lazy++;
//		root->mx.first++;
//		return root;
//	}
//	push(root,s,e);
//	int mid = (s + e) >> 1;
//	if(r <= mid) root->L = update(root->L,s,mid,l,r);
//	else if(mid < l) root->R = update(root->R,mid+1,e,l,r);
//	else {
//		root->L = update(root->L,s,mid,l,mid);
//		root->R = update(root->R,mid+1,e,mid+1,r);
//	}
//	if(root->L) root->mx = max(root->mx,root->L->mx);
//	if(root->R) root->mx = max(root->mx,root->R->mx);
//	return root;
//}
//
//bool isH(Arrow & a) {
//	return a.dy == 0;
//}
//
//bool getIntersection(Arrow & a,Arrow & b,int & l,int & r) {
//	if(isH(a) && isH(b)) {
//		if(a.dy != b.dy) {
//			l = max(a.x0,b.x0);
//			r = n;
//			return 1;
//		}
//	}
//	if(!isH(a) && !isH(b)){
//		l = max(a.y0,b.y0);
//		r = n;
//		return 1;
//	}
//
//}
//
//pair<int,pi> getCand(Arrow & a,pi mx) {
//	pair<int,pi> ret;
//	ret.first = mx.first;
//	if(isH(a)) ret.second = mp(-a.x0,mx.second);
//	else ret.second = mp(mx.second,-a.y0);
//	return ret;
//}
//
//pi solve(){
//	pair<int,pi> ans (-1,{0,0});
//	loop(i,m) {
//		node *root = NULL;
//		loop(j,m){
//			int l,r;
//			if(!getIntersection(A[i],A[j],l,r)) continue;
//			root = update(root,0,n,l,r);
//		}
//		if(!root) continue;
//		pair<int,pi> cand = getCand(A[i],root->mx);
//		ans = max(ans,cand);
//	}
//	pi ret = ans.second;
//	ret.first *= -1;
//	ret.second *= -1;
//	return ans.second;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	PRESTDIO();
//	int T; cin >> T;
//	for(int t = 1;t <= T;t++) {
//		cin >> m >> n;
//		loop(i,m) cin >> A[i];
//		pi ans = solve();
//		cout << "Case #" << t << ": " << ans.first << " " << ans.second << endl;
//	}
//	return 0;
//}
