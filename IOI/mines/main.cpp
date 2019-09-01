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

const int MAX = 600,B = 10;
int H,W;
int ctr[MAX][MAX],NG[MAX][MAX];
int C[B][B];
char G[MAX][MAX];

void init(){
	for(int n = 0;n < B;n++) {
		C[n][0] = C[n][n] = 1;
		for(int k = 1;k < n;k++)
			C[n][k] = C[n-1][k] + C[n-1][k-1];
	}
}

void changeScope(int x) {
	char iName[30],oName[30];
	sprintf(iName,"mines/mines.%d%d.in",x/10,x%10);
	sprintf(oName,"mines/mines.%d%d.out",x/10,x%10);

	freopen(iName,"r",stdin);
	freopen(oName,"w",stdout);
}

void read(){
	static char buffer[MAX + 10];
	scanf("%d %d",&H,&W);
	loop(i,H) {
		scanf("%s",buffer);
		loop(j,W) ctr[i][j] = buffer[j] - '0';
	}
}

bool inrange(int x,int s,int e){
	return s <= x && x <= e;
}


using cell = pair<int,pi>;
set<cell> S;

bool bt();

bool bt(int i,int k,vector<pi> & NGH,pi root) {
	int rem = sz(NGH) - i;
	if(rem < k) return 0;
	pi cur = NGH[i];

}


bool bt(){
	if(S.empty()) return 1;
	int cnt = S.begin()->first;
	pi cur = S.begin()->second;
	S.erase(S.begin());
	vector<pi> NGH;
	for(int dx = -1;dx <= 1;dx++)
		for(int dy = -1;dy <= 1;dy++){
			int x = cur.first + dx;
			int y = cur.second + dy;
			if(inrange(x,0,H-1) && inrange(y,0,W-1) && G[x][y] == 'E')
				NGH.push_back(pi(x,y));
		}
	assert(sz(NGH) == NG[cur.first][cur.second]);
	assert(sz(NGH) >= ctr[cur.first][cur.second]);
	sort(all(NGH),[](const pi & a,const pi & b) {
		int fa = C[NG[a.first][a.second]][ctr[a.first][a.second]];
		int fb = C[NG[b.first][b.second]][ctr[b.first][b.second]];
		return fa < fb;
	});
	bt(0,ctr[cur.first][cur.second],NGH,cur);
}

void solve(){
	S.clear();
	loop(i,H) {
		loop(j,W){
			NG[i][j] = 0;
			G[i][j] = 'E';
			for(int dx = -1;dx <= 1;dx++)
				for(int dy = -1;dy <= 1;dy++){
					int x = i + dx,y = j + dy;
					NG[i][j] += inrange(x,0,H-1) && inrange(y,0,W-1);
				}
			int cnt = C[NG[i][j]][ctr[i][j]];
			S.insert(mp(cnt,pi(i,j)));
		}
		G[i][W] = 0;
	}
	bt();
}

int main(){
	init();

	changeScope(1);
	read();
	solve();
	return 0;
}
