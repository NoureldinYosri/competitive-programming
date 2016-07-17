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
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popCOUNT(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

struct pi{
	int xx,yy;
public:
	bool operator < (const pi & o) const {
		return (xx == o.xx) ? (yy < o.yy) : (xx < o.xx);
	}
};

const ll mod = 1e9 + 7;
pi P[5001];
int n;
ll dp[5001][5001],DP[5001][5001];
int COUNT[5001][5001],G[5001][5001],NXT[5001][5001];
int LAST[5001];
int V[5001];

ostream & operator << (ostream & stream,const pi & p){
	stream << "(" << p.xx << " ," << p.yy << ")";
	return stream;
}

inline void update(int x,int y,int v,int T[5001][5001] = G){
	for(;x <= n;x += LSOne(x)) for(int yy = y;yy <= n; yy += LSOne(yy)) T[x][yy] += v;
}

inline int get(int x,int y,int T[5001][5001] = G){
	int ans = 0;
	for(;x;x -= LSOne(x)) for(int yy = y;yy;yy -= LSOne(yy)) ans += T[x][yy];	
	return ans;
}

int main(){
	int T;
  	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		loop(i,n) {
			scanf("%d %d",&P[i].xx,&P[i].yy);
			V[i] = P[i].yy;
		}
		//cerr << "start preprocessing" << endl;
		// preprocess
		sort(V,V + n);
		int m = unique(V,V + n) - V;
		loop(i,n) P[i].yy = lower_bound(V,V + m,P[i].yy) - V;		
		sort(P,P + n);
		loop(i,n) LAST[P[i].yy] = -1;
		loop(i,n) update(P[i].yy + 1,i + 1,1);
		loop(i,n) update(P[i].yy + 1,i + 1,-1);
	}
	return 0;
}
