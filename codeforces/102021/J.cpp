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


const int MAX = 300*1000 + 10;
int n;
int pieces[MAX][4];
bool used[MAX];

vi corners;
vi sides;

vector<vi> res;
map<int,vi> M;


bool make_fit(int lead,int a,int b){
	loop(i,4) {
		bool done = pieces[lead][0] == a && pieces[lead][1] == b;
		if(done) return 1;
		rotate(pieces[lead],pieces[lead] + 1,pieces[lead] + 4);
	}
	return 0;
}

bool build(int lead,vi *prv,vi & ret) {
	ret.push_back(lead);
	used[lead] = 1;
	int L = n;
	if(prv) L = prv->size();
	for(int i = 1;i < L;i++) {
		int left = pieces[ret.back()][2];
		if(left == 0) break;
//		cout << "left = " << left << endl;
		int up = prv ? pieces[(*prv)[i]][3] : 0;
		if(sz(M[left]) != 2) return 0;
		int v = M[left][0] + M[left][1] - ret.back();
//		print(M[left],int);
//		print(ret,int);
		if(used[v]) return 0;
		used[v] = 1;
		make_fit(v,left,up);
		ret.push_back(v);
	}
//	print(ret,int);
	if(pieces[ret.back()][2] != 0) return 0;
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		loop(j,4) scanf("%d",&pieces[i][j]);
	}
	if(n == 1) {
		int v = *max_element(pieces[0],pieces[0] + 4);
		if(v != 0) puts("impossible");
		else puts("1 1\n1");
		return 0;
	}
	int lead = 0,bc = 0;
	loop(i,n) {
		int ctr = 0;
		loop(j,4) {
			ctr += pieces[i][j] == 0;
			M[pieces[i][j]].push_back(i);
		}
		if(ctr == 0) continue;
		else if(ctr == 1) sides.push_back(i);
		else corners.push_back(i);
		if(ctr > bc) {
			lead = i;
			bc = ctr;
		}
	}
	if(!make_fit(lead,0,0)) {
		puts("impossible");
		return 0;
	}

	for(int r = 0;;r++) {
		if(r) {
			int s = pieces[res.back()[0]][3];
			if(sz(M[s]) != 2) {
				puts("impossible");
				return 0;
			}
			int v = M[s][0] + M[s][1] - res.back()[0];
			if(used[v]) {
				puts("impossible");
				return 0;
			}
			make_fit(v,0,s);
			lead = v;
		}
		vi row;
		if(!build(lead,sz(res) ? &res.back() : 0,row)) {
			puts("impossible");
			return 0;
		}
		res.push_back(row);
		int L = sz(res[0]);
		if(L != sz(row)) {
			puts("impossible");
			return 0;
		}
		if((r+1)*L == n) break;
	}
	int h = sz(res),w = sz(res[0]);
	printf("%d %d\n",w,h);
	loop(c,w) loop(r,h)  printf("%d%c",res[r][c]+1," \n"[r==h-1]);
	return 0;
}
