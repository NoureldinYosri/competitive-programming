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
#define len(A) A.length()
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

const int MAX = 3e5;
int BIT[MAX*2],V[MAX * 2],n,ans[MAX],S[MAX];
pi event[MAX * 2];


void update(int p){
	for(;p <= 2*n;p += LSOne(p)) BIT[p] ++;
}
int get(int p){
	int ret = 0;
	for(;p;p -= LSOne(p)) ret += BIT[p];
	return ret;
}

int main(){
	scanf("%d",&n);	
	loop(i,n){
		scanf("%d %d",&event[2*i].xx,&event[2*i + 1].xx);
		event[2*i].yy = event[2*i + 1].yy = i;
		V[2*i] = event[2*i].xx;
		V[2*i + 1] = event[2*i + 1].xx;
	}
	sort(V,V + 2*n);
	loop(i,2*n) event[i].xx = lower_bound(V,V + 2*n,event[i].xx) - V + 1;
	sort(event,event + 2*n);
	loop(i,2*n){
		int who = event[i].yy,x = event[i].xx;
		if(S[who] == 0) S[who] = x;
		else{
			ans[who] = get(x) - get(S[who] - 1);
			update(S[who]);
		}
	}
	loop(i,n) printf("%d\n",ans[i]);
	return 0;
}
