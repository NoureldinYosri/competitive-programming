#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

const int MAX = 1 << 20;
pair<pl,int> A[MAX];
int m,n;
ll ans[MAX << 1][2];
ll ST[MAX << 2];
multi_set<pi> unused;

void build(int node,int s,int e){
	if(s == e){
		ST[node] = A[s].xx.yy;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
	ST[node] = max(ST[left],ST[right]);
}

int update(int node,int s,int e,int a,int b){
	if(s == e){
		if(A[s].xx.xx <= a && a <= A[s].xx.yy){
			//cerr << A[s].xx.xx << " <= " << a << " <= " << A[s].xx.yy << endl;
			A[s].xx.yy += b;
			ans[A[s].yy][0]++;
			ans[A[s].yy][1] += b;
			ST[node] = A[s].xx.yy;
			return s;
		}
		else return -1;
	}	
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	int x;	
	if(a <= ST[left]) x= update(left,s,m,a,b);
	else x= update(right,m+1,e,a,b);
	ST[node] = max(ST[left],ST[right]);
	return x;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) {
		int a,b;	
		scanf("%d %d",&a,&b);
		A[i].xx.xx = a;
		A[i].xx.yy = a + b;
		A[i].yy = i;
		ans[i][1] = b;
	}
	sort(A,A + n);
	build(1,0,n - 1);
	auto it = unused.begin();
	loop(i,m){
		int a,b,p;
		scanf("%d %d",&a,&b);
		unused.insert(mp(a,b));
		it = unused.end();
		int c = -1;		
		do{
			if(it != unused.end()) unused.erase(it);
			if(c == -1) c = a;
			else c = A[c].xx.xx;		
			it = unused.lower_bound(mp(c,-1));
		}while(it != unused.end() && (c = update(1,0,n - 1,it->xx,it->yy)) >= 0);
	}	
	
	loop(i,n) printf("%I64d %I64d\n",ans[i][0],ans[i][1]);
	return 0;
}
 
