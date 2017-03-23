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


int A[1 << 20],first[22],n;
ll B[1 << 21][2];
ll ST[1 << 22][2];
int LA[1 << 22];

vi merge(vi L,vi R,ll & inv){
	reverse(all(L));
	reverse(all(R));
	vi ret;
	while(!L.empty() && !R.empty()){
		if(L.back() <= R.back()) {
			ret.pb(L.back());
			L.pop_back();
		}
		else{
			ret.pb(R.back());
			R.pop_back();
			inv += sz(L);
		}
	}
	for(;!L.empty();L.pop_back()) ret.pb(L.back());
	for(;!R.empty();R.pop_back()) ret.pb(R.back());
	return ret;
}

void build(int pos,int s,int e,int d,vi & V){
	if(first[d] == -1) first[d] = pos;
	if(s == e) V.pb(A[s]);
	else{
		int m = (s + e) >> 1;
		vi L,R;
		build(2*pos + 1,s,m,d + 1,L);
		build(2*pos + 2,m+1,e,d + 1,R);
		V = merge(L,R,B[pos][0]);
		merge(R,L,B[pos][1]);
	}
}

void build_ST(int node,int s,int e){
	if(s == e){
		ST[node][0] = B[s][0];
		ST[node][1] = B[s][1];
		return;
	}
	int m = (s + e) >> 1,left = node * 2 + 1,right = left + 1;
	build_ST(left,s,m);
	build_ST(right,m+1,e);
	ST[node][0] = ST[left][0] + ST[right][0];
	ST[node][1] = ST[left][1] + ST[right][1];
}

void update(int node){
	swap(ST[node][0],ST[node][1]);
	LA[node] ^= 1;	
}


void push(int node){
	if(!LA[node]) return;
	int left = node * 2 + 1,right = left + 1;
	update(left);
	update(right);
	LA[node] = 0;
}

void update(int node,int s,int e,int p){
	if(p <= s ) return update(node);
	push(node);
	int m = (s + e) >> 1,left = node * 2 + 1,right = left + 1;
	if(p <= m) update(left,s,m,p);
	update(right,m+1,e,p);
	ST[node][0] = ST[left][0] + ST[right][0];
	ST[node][1] = ST[left][1] + ST[right][1];
}
int main(){
	scanf("%d",&n);
	loop(i,1 << n) scanf("%d",A + i);
	memset(first,-1,sizeof first);
	vi V; build(0,0,(1 << n) - 1,0,V);
	first[n + 1] = first[n] + (1 << n);
	build_ST(0,0,first[n + 1]-1);	
	int m,a;
	scanf("%d",&m);
	loop(i,m){
		scanf("%d",&a);
		update(0,0,first[n + 1] - 1,first[n - a]);
		printf("%lld\n",ST[0][0]);
	}

	return 0;
}
