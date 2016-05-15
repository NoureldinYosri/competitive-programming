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
using namespace std;

const int MAX = 1e5 + 1e3;
int pwr[MAX],n,m;
int cnt[MAX],last[MAX],nxt[MAX];
int block_size;

int process(int l,int r){
	r = min(r,n - 1);
	for(int i = r;i >= l;i--){
		if(i + pwr[i] > r) {
			nxt[i] = i + pwr[i];
			cnt[i] = 1;
			last[i] = i;
		}
		else{
			nxt[i] = nxt[i + pwr[i]];
			cnt[i] = 1 + cnt[i + pwr[i]];
			last[i] = last[i + pwr[i]];
		}
	}
}

void get(int v,int & x,int & y){
	x = 0,y = v;
	while(v < n){
		x += cnt[v];
		y = last[v];
		v = nxt[v];
	}
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",pwr + i);	
	block_size = sqrt(n) + 2; block_size = min(block_size,n);
	for(int i = 0;i < n;i += block_size) process(i,i + block_size - 1);
	while(m--){
		int a,b;
		scanf("%d %d",&a,&b); b--;
		if(a == 0){
			scanf("%d",pwr + b);
			int l = b/block_size,r;
			l *= block_size; r = min(l + block_size - 1,n - 1);
			process(l,r);
		}
		else{
			int x,y;
			get(b,x,y);
			printf("%d %d\n",y + 1,x);
		}
	}		
	return 0;
}
