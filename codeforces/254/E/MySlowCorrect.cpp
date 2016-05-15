#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 2e5;
int color[MAX],END[MAX],n,m,t,l,r,x;
set<int> start;
ll ST[MAX << 2][2];


void update(int node,int s,int e,int x){
	if(ST[node][1] == 0) {
		int m = (s + e) >> 1,left = node << 1,right = left | 1;
		update(left,s,m,x);
		update(right,m + 1,e,x);
		ST[node][0] = ST[left][0] + ST[right][0];
		return;	
	}
	ST[node][0] += (e - s + 1LL)*abs(x - ST[node][1]);
	ST[node][1] = x;	
}

void push(int node,int s,int e){
	if(ST[node][1] == 0 || s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	update(left,s,m,ST[node][1]);
	update(right,m + 1,e,ST[node][1]);
	ST[node][1] = 0;
}

void update(int node,int s,int e,int l,int r,int x){
	if(l <= s && e <= r) return update(node,s,e,x);
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,x);
	else if(m < l) update(right,m + 1,e,l,r,x);
	else{
		update(left,s,m,l,m,x);
		update(right,m + 1,e,m + 1,r,x);
	}
	ST[node][0] = ST[left][0] + ST[right][0];
}

ll query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node][0];
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	else if(m < l) return query(right,m + 1,e,l,r);
	else return query(left,s,m,l,m) + query(right,m + 1,e,m + 1,r);
}


void build(int node,int s,int e){
	if(s == e){
		ST[node][1] = s;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
}

void update(){
	for(int i = l;i <= r;){
		auto p = start.upper_bound(i); --p;
		if(*p < i){
			END[i] = END[*p];
			END[*p] = i - 1;
			start.insert(i);
		}
		else if(END[*p] > r){
			END[r + 1] = END[*p];
			color[r + 1] = color[*p];
			END[*p] = r;
			color[*p] = x;
			update(1,1,n,*p,r,x);
			start.erase(p);
			start.insert(r + 1);
			i = r + 1;		
		}
		else{
			i = END[*p] + 1;
			update(1,1,n,*p,END[*p],x);
			start.erase(p);
		}
	}
	start.insert(l);
	color[l] = x;
	END[l] = r;
}

void init(){
	build(1,1,n);
	range(i,1,n) {
		color[i] = i;
		END[i] = i;
		start.insert(i);
	}
}
int main(){
	scanf("%d %d",&n,&m);
	init();
	while(m--){
		scanf("%d %d %d",&t,&l,&r);
		if(t == 1){
			scanf("%d",&x);
			update();	
			cerr << "done update" << endl;
			cerr << query(1,1,n,l,r) << endl;					
		}
		else printf("%lld\n",query(1,1,n,l,r));
	}
	return 0;
}

