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

const int MAX = 1 << 20;
int fst[MAX],lst[MAX];
int A[MAX],n;
int B[MAX],m;
map<int,ll> dp[MAX];

struct node{
	int siz;
	node *l,*r;
};

node* build(int s,int e){
	node *ret = new node();
	if(s == e) return ret;
	int m = (s + e) >> 1;
	ret->l = build(s,m);
	ret->r = build(m+1,e);
	return ret;
}

node* update(node *root,int s,int e,int p){
	node *ret = new node();
	*ret = *root;
	ret->siz++;
	if(s == e) return ret;
	int m = (s + e) >> 1;
	if(p <= m) ret->l = update(root->l,s,m,p);
	else ret->r = update(root->r,m+1,e,p);
	return ret;
}

int query(node *u,node *v,int s,int e,int p){
	if(p <= s) return v->siz - u->siz;
	int m = (s + e) >> 1;
	if(m < p) return query(u->r,v->r,m+1,e,p);
	else return query(u->l,v->l,s,m,p) + query(u->r,v->r,m+1,e,p);
}

node *T[MAX];

map<int,int> choice[MAX];

int get_cost(int s,int e,int target){
	if(s > e) swap(s,e);
	ll ret = query(T[s - 1],T[e],0,m-1,target) - 1;
	//cerr << s << " " << e << " and " << target << " -> " << ret << endl;
	return ret;
}

ll solve(int target,int pos){
	if(target == m) return 0;
	if(dp[target].find(pos) != dp[target].end()) return dp[target][pos];
	ll a = solve(target + 1,lst[target]) + get_cost(pos,fst[target],target) + get_cost(fst[target],lst[target],target) + 1;
	ll b = solve(target + 1,fst[target]) + get_cost(lst[target],pos,target) + get_cost(fst[target],lst[target],target) + 1;
	if(pos > fst[target]) {
		int s = fst[target],e = pos;
		int tmp = query(T[s-1],T[e],0,m-1,target);
		if(target + 1 < m) tmp -= query(T[s-1],T[e],0,m-1,target + 1);
		a -= tmp - 1;
	}
	if(pos < lst[target]){
		int s = pos,e = lst[target];
		int tmp = query(T[s-1],T[e],0,m-1,target);
		if(target + 1 < m) tmp -= query(T[s-1],T[e],0,m-1,target + 1);
		b -= tmp - 1;
	}
	choice[target][pos] = a < b;
	return dp[target][pos] = min(a,b);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i),B[i-1] = A[i];
	sort(B,B + n);
	m = unique(B,B + n) - B;
	range(i,1,n) A[i] = lower_bound(B,B + m,A[i]) - B;
	range(i,1,n) lst[A[i]] = i;
	for(int i = n;i > 0;i--) fst[A[i]] = i;
/*	prArr(A+1,n,int);
	prArr(fst,m,int);
	prArr(lst,m,int);
*/	T[0] = build(0,m-1);
	for(int i = 1;i <= n;i++) T[i] = update(T[i - 1],0,m-1,A[i]);
	cout << solve(A[0],1) << endl;
/*	for(int pos = 1,target = 0; target < m;target++){
		cerr << "at " << pos << " with cost " << dp[target][pos] << endl;
		if(choice[target][pos]) pos = fst[target];
		else pos = lst[target];
	}
*/	return 0;
}
