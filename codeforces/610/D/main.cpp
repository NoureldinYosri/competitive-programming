#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 200'010;
map<int,vp> H,V;
int n;
int BIT[MAX];
vi Y;
	
void add(int p,int v){
	for(;p <= sz(Y);p += LSOne(p))
		BIT[p] += v;
}

int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

void work(vp & A){
	for(auto & p : A)
		if(p.xx > p.yy)
			swap(p.xx,p.yy);

	int m = 0;
	vector<pair<pi,int> > I(2*sz(A)); 
	loop(i,sz(A)){
		I[m++] = mp(mp(A[i].xx,0),A[i].yy);
		I[m++] = mp(mp(A[i].yy,1),A[i].yy);
	}

	sort(all(I));
	A.clear();
	int l = -1,r = -2e9,f = 0;
	for(auto a : I){
		int v = a.xx.xx,q = a.yy;
		if(r < v){
			if(f) A.pb(mp(l,r));
			l = v;
			f = 1;
		}
		r = max(r,q);
	}
	A.pb(mp(l,r));
}

int main(){
	scanf("%d",&n);
	loop(i,n){
		int x1,y1,x2,y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if(x1 == x2) V[x1].pb(mp(y1,y2));
		else H[y1].pb(mp(x1,x2));
	}
	for(auto & p : H) work(p.yy);
	for(auto & p : V) work(p.yy);
/*
	cerr << "H :" << endl;
	for(auto & q : H) {
		cerr << q.xx << " : ";
		for(auto & p : q.yy) prp(p);
		cerr << endl;
	}
	cerr << "V :" << endl;
	for(auto & q : V) {
		cerr << q.xx << " : ";
		for(auto & p : q.yy) prp(p);
		cerr << endl;
	}
*/
	ll ans = 0;
	for(auto & A : H) for(auto & p : A.yy) ans += p.yy - p.xx + 1;
	for(auto & A : V) for(auto & p : A.yy) ans += p.yy - p.xx + 1;
//	cerr << ans << endl;	
		
	for(auto & p : H) Y.pb(p.xx);
	for(auto & p : V) for(auto & q : p.yy) Y.pb(q.xx),Y.pb(q.yy);
	sort(all(Y));
	Y.resize(unique(all(Y)) - Y.begin());
	vector<pair<pi,pi> > A;
	for(auto & q : H) {
		int y = q.xx;
		for(auto & p : q.yy) {
			A.pb(mp(mp(p.xx,-1),mp(y,y)));
			A.pb(mp(mp(p.yy,1),mp(y,y)));
		}
	}
		 
	for(auto & q : V) {
		int x = q.xx;
		for(auto & p : q.yy) 
			A.pb(mp(mp(x,0),mp(p.xx,p.yy)));
	}
	sort(all(A));
	for(auto p : A){
		if(p.xx.yy == -1){
			int y = upper_bound(all(Y),p.yy.xx) - Y.begin();
			add(y,1);
		}
		else if(!p.xx.yy) {
			int l = upper_bound(all(Y),p.yy.xx) - Y.begin();
			int r = upper_bound(all(Y),p.yy.yy) - Y.begin();
			ans -= get(r) - get(l - 1);
		}
		else{
			int y = upper_bound(all(Y),p.yy.xx) - Y.begin();
			add(y,-1);
		}
	}
//	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
