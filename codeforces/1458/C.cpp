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

struct matrix{
	vector<vi> content;
	int dx, dy, dv;
	string name;
	int visId;
	int R, C;
	matrix(){
		dx = dy = dv = 0;
		name = "";
		visId = R = C = -1;
		content = vector<vi>();
	}
	matrix(int n){
		dx = dy = dv = 0;
		name = "";
		visId = R = C = -1;
		content = vector<vi>();
		content.resize(n, vi(n, 0));
	}
};

int n, m, visNum;
char buffer[1 << 20];
map<vector<vi>, int> v2m;

vector<vi> getRowInv(const vector<vi> & M){
	vector<vi> R(n, vi(n, 0));
	loop(i, n) loop(j, n) R[i][M[i][j]] = j;
	return R;
}
vector<vi> getColInv(const vector<vi> & M){
	vector<vi> C(n, vi(n, 0));
	loop(i, n) loop(j, n) C[M[i][j]][j] = i;
	return C;
}

vector<matrix> VM;

void dfs(int idx){
//	cerr << "get R" << endl;
	vector<vi> R = getRowInv(VM[idx].content);
//	cerr << "get C" << endl;
	vector<vi> C = getColInv(VM[idx].content);
//	cerr << "assign" << endl;
	if(!v2m.count(R)) {
		VM.emplace_back();
		VM.back().content = R;
		VM.back().name = VM[idx].name + "R";
		v2m[R] = sz(VM) - 1;
		dfs(sz(VM) - 1);
	}
	if(!v2m.count(C)){
		VM.emplace_back();
		VM.back().name = VM[idx].name + "C";
		VM.back().content = C;
		v2m[C] = sz(VM) - 1;
		dfs(sz(VM) - 1);
	}
	VM[idx].R = v2m[R];
	VM[idx].C = v2m[C];
}

void build(){
	scanf("%d %d", &n, &m);
	VM.clear();
	VM.emplace_back(n);
	loop(i, n) loop(j, n){
		scanf("%d", &VM[0].content[i][j]);
		VM[0].content[i][j]--;
	}
	v2m.clear();

	v2m[VM[0].content] = 0;
	VM[0].name = "M";
	dfs(0);
}

void rowShift(int, int);
void colShift(int, int);
void incVal(int, int);

void rowShift(int idx, int v){
	if(VM[idx].visId == visNum) return;
	//cout << "rowShift of " << v << " for " << (VM[idx].name) << endl;
	VM[idx].visId = visNum;
	VM[idx].dy += v;
	incVal(VM[idx].R, 1);
	colShift(VM[idx].C, 1);
}
void colShift(int idx, int v){
	if(VM[idx].visId == visNum) return ;
	//cout << "colShift of " << v << " for " << (VM[idx].name) << endl;
	VM[idx].visId = visNum;
	VM[idx].dx += v;
	incVal(VM[idx].C, v);
	rowShift(VM[idx].R, v);
}
void incVal(int idx, int v) {
	if(VM[idx].visId == visNum) return ;
	//cout << "valShift of " << v << " for " << (VM[idx].name) << endl;
	VM[idx].visId = visNum;
	VM[idx].dv += v;
	colShift(VM[idx].C, v);
	rowShift(VM[idx].R, v);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		build();
		scanf("%s", buffer);
		int idx = 0;
		loop(i, m){
			char c = buffer[i];
			visNum++;
			if(c == 'R' || c == 'L' || c == 'D' || c == 'U'){
				int dy = (c == 'R') - (c == 'L');
				int dx = (c == 'D') - (c == 'U');
				if(dy) {
					rowShift(idx, -dy);
				} else {
					colShift(idx, -dx);
				}
			} else if(c == 'I'){
				idx = VM[idx].R;
			} else {
				idx = VM[idx].C;
			}
		}
		//cout << "print " << (VM[idx].dx) << " " << (VM[idx].dy) << " " << (VM[idx].dv)  << endl;
		loop(i, n) loop(j, n) {
			int u = ((i + VM[idx].dx)%n + n)%n;
			int v = ((j + VM[idx].dy)%n + n)%n;
			int x = VM[idx].content[u][v];
			x = ((x + VM[idx].dv)%n + n)%n;
			printf("%d%c", x + 1, " \n"[j == n-1]);
		}
	}
	return 0;
}
/*	1 2 3
	2 3 1
	3 1 2
*/
