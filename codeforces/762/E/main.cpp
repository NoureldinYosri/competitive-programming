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

const int MAX = 100*100;

struct node{
	int siz;
	node *l,*r;
};

int R[1 << 20],X[1 << 20],f[1 << 20];
int ord[1 << 20];
int n,k;
int F[1 << 20];
vector<node*> T[1<<20];
vi XS[1<<20];
bool debug;

node* update(node *root,int s,int e,int p){
	node *ret = new node(); 
	if(root) *ret = *root;
	ret->siz++;
	if(s == e) return ret;
	int m = s + (e - 0LL - s)/2;
	if(p <= m) ret->l = update(ret->l,s,m,p);
	else ret->r = update(ret->r,m+1,e,p);
	return ret;
}

int query(node *u,node *v,int s,int e,int p){
	if(debug) cerr << s << " " << e << " " << p << " " << v << endl;
	if(e <= p) return (v ? v->siz : 0) - (u ? u->siz : 0);
	int m = s + (e - 0LL - s)/2;
	int ret = query(u ? u->l : 0,v ? v->l : 0,s,m,p);
	if(p > m) ret += query(u ? u->r : 0,v ? v->r : 0,m+1,e,p);
	return ret;
}


int main(){
	int mxD = 2000000000;
	scanf("%d %d",&n,&k);
	loop(i,n){
		scanf("%d %d %d",X + i,R + i,f + i);
		ord[i] = i;
		F[i] = f[i];
	}		
	sort(ord,ord + n,[](const int & a,const int & b){
		return X[a] < X[b];
	});
	sort(F,F + n);
	int m = unique(F,F + n) - F;
	ll ans = 0;
	loop(i,n){
		int cur = ord[i];
		range(diff,-k,k) if(binary_search(F,F + m,f[cur] + diff)){
			int other_frq = *lower_bound(F,F + m,f[cur] + diff);
			int idx = lower_bound(all(XS[other_frq]),X[cur] - R[cur]) - XS[other_frq].begin();
			if(idx == sz(XS[other_frq])) continue;
			node* u = idx ? T[other_frq][idx - 1] : 0;
			node* v = T[other_frq].back();
			//debug = (f[cur] + diff) == 5;
			ans += query(u,v,-mxD,mxD,mxD) - query(u,v,-mxD,mxD,X[cur] - 1);
		}
		node *root = 0;
		int frq = *lower_bound(F,F + m,f[cur]);
		if(!T[frq].empty()) root = T[frq].back();
//		cerr << "add " << X[cur] + R[cur] << " to " << f[cur] << endl;	
		T[frq].pb(update(root,-mxD,mxD,X[cur] + R[cur]));
		XS[frq].pb(X[cur]);
	}	
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
