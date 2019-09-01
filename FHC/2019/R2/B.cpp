#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 5 << 10;
int id[MAX],W[MAX],n,m;

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}

void init(){
	loop(i,n) id[i] = i,W[i] = 1;
}

vi V;


int dp[MAX][MAX],visNum[MAX][MAX],visID;
int choice[MAX][MAX];
int color[MAX];

int solve(int i,int K) {
	if(i == -1) return K;
	int & ret = dp[i][K];
	int & v = visNum[i][K];
	int & ch = choice[i][K];
	if(v == visID) return ret;
	ret = 1 << 29;
	v = visID;
	ch = 0;
	int cur = find(V[i]);
	for(int c = 0;c < 2;c++) {
		int tmp = 0,w = W[cur]*c;
		if(w <= K) tmp = solve(i-1,K-w);
		if(tmp < ret){
			ret = tmp;
			ch = c;
		}
	}
	return ret;
}

int main(){
	freopen("bitstrings_as_a_service.txt", "r", stdin);
	freopen("out.out","w",stdout);
	tc(){
		scanf("%d %d",&n,&m);
		init();
		loop(c,m) {
			int i,j; scanf("%d %d",&i,&j);
			i--,j--;
			while(i < j) {
				join(i,j);
				i++; j--;
			}
		}
		V.clear();
		loop(i,n) if(find(i) == i) V.push_back(i);
//		print(V,int);
		visID++;
		int best = solve(sz(V)-1,(n+1)/2);
//		cerr << best << endl;
//		for(int v : V) cerr << W[v] << " ";
//		cerr << endl;
//		print(V,int);
		for(int i = sz(V)-1,K = (n+1)/2;i >= 0;i--) {
			int c = choice[i][K];
			if(c != 0 && c != 1) cerr << K << " " << c << endl;
			assert(c == 0 || c == 1);
//			cerr << V[i] << " " << c << endl;
			int cur = V[i];
			color[cur] = c;
			K -= W[cur]*c;
		}
		printf("Case #%d: ",t);
		loop(i,n) {
			int c = color[find(i)];
			putchar("01"[c]);
		}
		puts("");
	}
	return 0;
}
#endif
