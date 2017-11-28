#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAXN = 100*1000 + 10,MAX = 2*MAXN;
int id[MAX],W[MAX];
int n,m;
int A[MAX],B[MAX],C[MAX];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

int join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	return 1;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	int k = 2*n;
	range(i,1,2*n) id[i] = i,W[i] = 1;
	loop(i,m){
		scanf("%d %d %d",A + i,B + i,C + i);
		if(C[i]) k -= join(A[i],B[i]);
	}
	loop(i,m) if(!C[i]) {
		if(find(A[i]) == find(B[i])) {
			puts("0");
			return 0;
		}
		join(A[i] + n,B[i] + n);
	}
	range(i,1,n) k -= join(i,i + n);
	int ans = 1,mod = 1000*1000*1000 + 7;
	while(k-- > 1) {
		ans <<= 1;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << endl;
	return 0;
}
