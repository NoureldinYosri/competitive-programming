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

const int MAX = 1000*1000 + 100;
int n,A[MAX];
int color[MAX];
map<int,vi> F;
int nxt[MAX];
int prv[MAX];
int ST[MAX][21],lg[MAX];

bool work(vi & V){
	if(sz(V) & 1) return 0;
	vi ST;
	for(int x : V){
		if(color[x]){
			if(ST.empty()) return 0;
			color[ST.back()] = 2;
			nxt[ST.back()] = x;
			prv[x] = ST.back();
			ST.pop_back();
		}
		else ST.pb(x);
	}	

	for(int x : ST) assert(!color[x]);

	int L = ST.size()/2;

	for(int i = 0;i < L;i++){
		int x = ST[i],y = ST[2*L - 1 - i];
		color[x] = 2;
		color[y] = 1;
		nxt[x] = y;
		prv[y] = x;
	}
	ST.clear();
	return 1;
}

int get_max(int l,int r){
	int len = lg[r - l + 1];
	return max(ST[l][len],ST[r - (1 << len) + 1][len]);
}

bool validate(){
	loop(r,n) if(color[r] == 1){
		int l = prv[r];
		if(l+1 == r) continue;
		if(get_max(l+1,r-1) > r) return 0;
	}	
	return 1;
}

void build(){
	lg[0] = -1;
	loop(i,MAX-1) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i+1));
	loop(i,n) ST[i][0] = nxt[i];
	loop(k,20){
		loop(i,n){
			int j = i + (1 << k);
			if(j >= n) j = i;
			ST[i][k + 1] = max(ST[i][k],ST[j][k]);
		}
	}
}

int main(){
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		F[A[i]].pb(i);
	}
	int m; scanf("%d",&m);
	loop(i,m){
		int x; scanf("%d",&x); x--;
		color[x] = 1;
	}
	memset(nxt,-1,sizeof nxt);
	for(auto & p : F){
		if(!work(p.yy)){
			puts("NO");
			return 0;
		}
	}
	loop(i,n) color[i] --;
	loop(i,n) cerr << A[i]*(2*color[i] - 1) << " ";
	cerr << endl;
	build();
	if(!validate()){
		puts("NO");
		return 0;
	}
	loop(i,n) color[i] --;
	puts("YES");
	loop(i,n) printf("%d%c",A[i]*(2*color[i] - 1)," \n"[i==n-1]);	
	return 0;
}
