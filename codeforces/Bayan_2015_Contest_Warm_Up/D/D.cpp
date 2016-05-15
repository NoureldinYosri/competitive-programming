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

const int MAX = 1e5 + 1e3;
int ST[MAX][20],lg[MAX];
int A[MAX],n;

void init(){
	lg[0] = -1;
	loop(i,n) {
		lg[i + 1] = lg[i];
		int j = i + 1;
		if(j == LSOne(j)) lg[j]++;
	}
	loop(i,n) ST[i][0] = A[i];
	loop(k,18){
		loop(i,n){
			if(i + (1 << k) < n) ST[i][k + 1] = __gcd(ST[i][k],ST[i + (1 << k)][k]);
			else ST[i][k + 1] = ST[i][k];
		}
	} 
}

int get(int a,int b){
	int l = lg[b - a + 1];
	return __gcd(ST[a][l],ST[b - (1 << l) + 1][l]);
}

map<int,ll> f;

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	init();
	loop(i,n){
		int st = i;
		while(st < n){
			int s = st,e = n - 1;
			while(s < e){
				int m = s + (e - s + 1)/2;
				if(get(i,m) == get(i,st)) s = m;
				else e = m - 1;
			}
			int v = get(i,st) ;
			if(f.find(v) == f.end()) f[v] = 0;
			ll L = s - st + 1;
			f[v] += L;
			st = s + 1;
		}
	}
	int m ,a;
	scanf("%d",&m);
	while(m--){
		scanf("%d",&a);
		if(f.find(a) == f.end()) printf("0\n");
		else printf("%lld\n",f[a]);
	}
	return 0;
}
