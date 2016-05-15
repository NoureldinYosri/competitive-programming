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

const int MAX = 100000;
int BIT[2][MAX + 1],n;
pi A[MAX];

inline void update(int p,int v,int *T){
	for(;p <= n;p += LSOne(p)) T[p] += v;
}

inline int get(int p,int *T){
	int ret = 0;
	for(;p;p -= LSOne(p)) ret += T[p];
	return ret;
}

int main(){
	while(scanf("%d",&n) == 1 && n){
		loop(i,n) BIT[0][i + 1] = BIT[1][i + 1] = 0;
		range(i,1,n) scanf("%d",&A[i].xx),A[i].yy = i;
		sort(A + 1,A + n + 1);
		range(i,1,n + 1){
			cerr << i << " " << A[i].yy << " " ;
			int a = 1 - ((get(A[i].yy,BIT[0]) & 1) << 1);
			int b = get(A[i].yy,BIT[1]);
			int j = a * A[i].yy + b; 
			cerr << j << endl;
	//		printf("%d%s",j,(i == n-1) ? "\n" : " ");
			update(1,1,BIT[0]); update(j + 1,-1,BIT[0]);
			a = -a;
			int c = i - a * A[i].yy - b;
			cerr << c << endl;			
			update(1,c,BIT[1]); update(j + 1,-c,BIT[1]);
		}
	}
	return 0;
}
