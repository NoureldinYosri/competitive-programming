#pragma GCC optimize ("O3")
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
using namespace std;


const int MAXN = 1000;
bool vis[MAXN][1 << 16];
char txt[MAXN + 10];
int n;

int fix(int msk){
	int ret = msk;
	loop(i, 4){
		int t = (msk >> (4*i)) & 0xf;
		if(t != 0xf) continue;
		ret &= ~(0xf << (4*i));
	}
	loop(j, 4){
		bool t = true;
		loop(i, 4) t &= (msk >> (i*4 + j)) & 1;
		if(!t) continue;
		loop(i, 4) ret &= ~(1 << (4*i + j));
	}
	return ret;
}

vector<pi> ans;

bool bt(int i, int msk){
	if(i == n) return true;
	msk = fix(msk);
	if(vis[i][msk]) return false;
	vis[i][msk] = true;

	int dx = txt[i] == '0', dy = txt[i] == '1';
	for(int sgn = -1; sgn <= 1; sgn += 2){
		for(int x = 0; x < 4; x++)
			for(int y = 0; y < 4; y++){
				if((msk >> (4*x + y)) & 1) continue;
				int nx = x + sgn * dx;
				int ny = y + sgn * dy;
				if(nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
				if((msk >> (4*nx + ny)) & 1) continue;
				ans.emplace_back(min(x, nx), min(y, ny));
				if(bt(i + 1, msk | (1 << (4*x + y)) | (1 << (4*nx + ny)))){
					
					return true;
				}
				ans.pop_back();
			}
	}
	return false;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> txt;
	n = strlen(txt);
	cerr << bt(0, 0) << endl;
	for(auto [x, y] : ans)
		printf("%d %d\n", x + 1, y + 1);
	return 0;
}
