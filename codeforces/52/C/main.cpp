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

const int MAX = 200000;
ll ST[(1 << 18) << 1];
ll LA[(1 << 18) << 1];
bool debug;

void update(int node,int s,int e,ll v){
	ST[node] += v;
	LA[node] += v;
}

void push(int node,int s,int e){
	if(!LA[node]) return;
	int m = (s + e) >> 1,left = node*2 + 1,right = left + 1;
	update(left,s,m,LA[node]);
	update(right,m+1,e,LA[node]);
	LA[node] = 0;
}

void update(int node,int s,int e,int l,int r,int v){
	if(l <= s && e <= r) return update(node,s,e,v);
	push(node,s,e);
	int m = (s + e) >> 1,left = node*2 + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,v);
	else if(m < l) update(right,m+1,e,l,r,v);
	else update(left,s,m,l,m,v),update(right,m+1,e,m+1,r,v);
	ST[node] = min(ST[left],ST[right]);
}

ll query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	push(node,s,e);
	int m = (s + e) >> 1,left = node*2 + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	else if(m < l) return query(right,m+1,e,l,r);
	else return min(query(left,s,m,l,m),query(right,m+1,e,m+1,r));		
}

int main(){
	int n; scanf("%d",&n);
	loop(i,n){
		int x; scanf("%d",&x);
		update(0,0,n-1,i,i,x);
	}	
	int m; scanf("%d\n",&m);
	loop(i,m){
		char buffer[100]; fgets(buffer,100,stdin);
		vi I;
		for(char *token = strtok(buffer," "); token;token = strtok(0," ")){
			int x; sscanf(token,"%d",&x);
			I.pb(x);
		}
		assert(2 <= sz(I) && sz(I) <= 3);
		if(sz(I) == 2) {
			if(I[0] <= I[1]) printf("%lld\n",query(0,0,n-1,I[0],I[1]));
			else {
				ll ans = query(0,0,n-1,I[0],n-1);
				ans = min(ans,query(0,0,n-1,0,I[1]));
				printf("%lld\n",ans);
			}
		}
		else if(I[0] <= I[1]) update(0,0,n-1,I[0],I[1],I[2]);
		else update(0,0,n-1,I[0],n-1,I[2]),update(0,0,n-1,0,I[1],I[2]);
	}
	
	
	return 0;
}
