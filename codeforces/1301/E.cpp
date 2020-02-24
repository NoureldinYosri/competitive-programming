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


const int MAX = 500 + 10;
int n, m, q;
char G[MAX][MAX];
int S[4][MAX][MAX];
vector<vector<vi>> C;
string color = "RGYB";


int get_sum(int x_high, int y_high, int x_low, int y_low, const vector<vi> & G){
//	cerr << x_low << " " << y_low << " " << G.size() << endl;
	int sum = G[x_high][y_high];
	if(x_low) sum -= G[x_low-1][y_high];
	if(y_low) sum -= G[x_high][y_low-1];
	if(x_low && y_low) sum += G[x_low-1][y_low-1];
	return sum;
}

bool is_full(int x_high, int y_high, int s, int G[MAX][MAX]){
	int sum = G[x_high][y_high];
	int x_low = x_high - s + 1;
	int y_low = y_high - s + 1;
	if(x_low) sum -= G[x_low-1][y_high];
	if(y_low) sum -= G[x_high][y_low-1];
	if(x_low && y_low) sum += G[x_low-1][y_low-1];
	//cerr << x_low << " " << y_low << " " << x_high << " " << y_high << " " << sum << " " << G[x_high][y_high] << endl;
	return sum == s*s; 
}

bool is_good(int x_low, int y_low, int s){
	int hs = s/2;
//	cerr << "check red" << endl;
	if(!is_full(x_low + hs - 1, y_low + hs - 1, hs, S[0])) return 0;
//	cerr << "check green" << endl;
	if(!is_full(x_low + hs - 1, y_low + s - 1, hs, S[1])) return 0;
//	cerr << "check yellow" << endl;
	if(!is_full(x_low + s - 1, y_low + hs - 1, hs, S[2])) return 0;
//	cerr << "check blue" << endl;
	if(!is_full(x_low + s - 1, y_low + s - 1, hs, S[3])) return 0;
	return 1;
}



map<int, int> Ss;
vector<pair<int, pi> > rects;
int R[MAX];

void get_rects(){
	loop(i, n) loop(j, m){
		int v = find(all(color), G[i][j]) - color.begin();
		S[v][i][j] = 1;
	}
	loop(k, 4) loop(i, n) loop(j, m){
		if(i) S[k][i][j] += S[k][i-1][j];
		if(j) S[k][i][j] += S[k][i][j-1];
		if(i && j) S[k][i][j] -= S[k][i-1][j-1];
	}
	
	for(int s = 2;s <= n && s <= m; s += 2){
		for(int x = 0; x+s <= n; x++)
			for(int y = 0; y+s <= m; y++){
				if(is_good(x, y, s)){
					Ss[s];
					rects.emplace_back(s, pi(x+s-1, y+s-1));
				}
			}
		}
	
	Ss[0] ;
	int ctr = 0;
	for(auto & p : Ss){
		p.second = ctr++;
		R[p.second] = p.first;
	}
	loop(i, ctr) {
		C.emplace_back(n, vi(m, 0));
	}
	for(auto p : rects){
		int k = Ss[p.first];
		int x = p.second.first;
		int y = p.second.second;
		C[k][x][y]++;
	}
	loop(k, ctr){
		loop(i, n) loop(j, m){
			if(i) C[k][i][j] += C[k][i-1][j];
			if(j) C[k][i][j] += C[k][i][j-1];
			if(i && j) C[k][i][j] -= C[k][i-1][j-1];
		}
	}
}

int X1[1 << 20];
int Y1[1 << 20];
int X2[1 << 20];
int Y2[1 << 20];

bool check(int i, int k, int m){
	return get_sum(X2[i], Y2[i], X1[i] + m - 1, Y1[i] + m - 1, C[k]);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &q);
	loop(i, n) scanf("%s", G[i]);
	get_rects();
	loop(i, q){
		scanf("%d %d %d %d", X1 + i, Y1 + i, X2 + i, Y2 + i);
		X1[i]--;
		X2[i]--;
		Y1[i]--;
		Y2[i]--;
		
		int L = min(X2[i] - X1[i], Y2[i] - Y1[i]) + 1;
		int s = 0;
		auto ptr = Ss.upper_bound(L);
		ptr--;
		int e = ptr->second;
		while(s < e){
			int m = s + (e-s+1)/2;
//			cerr << "check " << m << " " << R[m] << " " << L << endl;
			if(check(i, m, R[m])) s = m;
			else e = m-1;
		}
		int ans = R[s] * R[s];
		printf("%d\n", ans);	
	}
	return 0;
}
