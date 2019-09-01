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

const int MAX = 310;
int H,S,m;
char G[MAX][MAX];
int ans[MAX*MAX];

int compress(int s,vi & V) {
	V.clear();
	for(int i = 0;i < H;) {
		int j = i;
		while(j < H && G[i][s] == G[j][s]) j++;
		V.push_back(j-i);
		i = j;
	}
	return G[0][s] == 'B';
}


vi C[MAX];
int color[MAX];

int dp[MAX][MAX][MAX][2];
int visID[MAX][MAX][MAX][2],visNum;


int solve(int i,int s,int k,int play) {
	vi & V = C[s];
	if(i == sz(V)) return 0;
	if(!k) return S*H;
	int & ret = dp[i][s][k][play];
	int & vid = visID[i][s][k][play];
	if(vid == visNum) return ret;
	vid = visNum;
	ret = S*H;
	if(i%2 == play) ret = min(ret,solve(i+1,s,k-1,play^1));
	ret = min(ret,solve(i+1,s,k,play) + V[i]);
	ret = min(ret,solve(i+1,s,k-1,play^1));
	return ret;
}

int match(int s,int k,int playB) {
	int c = color[s];
	int res = solve(0,s,k,playB^c);
//	print(C[s],int);
//	cerr << k << " " << playB << " " << c << " -> " << res << endl;

	return res;
}

void solve(){
	int len[2] = {0,0};
	loop(s,S) {
		C[s].clear();
		int c = color[s] = compress(s,C[s]);
		len[c] = max(len[c],sz(C[s]));
	}


	int res = max(len[0],len[1]) + (len[0] == len[1]);

	loop(i,S*H+1) ans[i] = res;
	visNum++;
	for(int i = res;i > 0;i--){
		int L = S*H;;
		loop(p,2) {
			int tmp = 0;
			loop(s,S) tmp += match(s,i,p);
			L = min(L,tmp);
		}
//		cerr << "\t" << L << ": " << i << endl;
		ans[L] = i;
	}
	loop(i,S*H) {
		res = min(res,ans[i]);
		ans[i] = res;
	}

//	prArr(ans,S*H,int);
//	loop(i,S*H) cerr << i << ". " << ans[i] << endl;
}

int main(){
//	freopen("grading.txt", "r", stdin);
//	freopen("out.out","w",stdout);
	freopen("in.in","r",stdin);
	tc(){
		scanf("%d %d %d",&H,&S,&m);
		loop(i,H) scanf("%s",G[i]);
		solve();
		printf("Case #%d:",t);
		loop(i,m) {
			int L; scanf("%d",&L);
			printf(" %d",ans[L]);
		}
		puts("");
	}
	return 0;
}
