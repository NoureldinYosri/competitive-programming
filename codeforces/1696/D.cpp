#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

int P[1 << 20], pos[1 << 20], n;
int mxR[1 << 20];
int mnR[1 << 20];
int nxt[2][1 << 20];
int prv[2][1 << 20];
int dist[1 << 20];

void go(function<bool(int, int)> f, int *R) {
	static vi ST;
	ST.clear();
	for(int i = n-1; i >= 0; i--) {
		while(!ST.empty() && f(P[ST.back()], P[i])) ST.pop_back();
		R[i] = ST.empty() ? n : ST.back();
		ST.push_back(i);
	}
}

void preprocess() {
	go(greater<int>(), mnR);
	go(less<int>(), mxR);
	loop(i, n) pos[P[i]] = i;
	loop(i, n) {
		nxt[0][i] = mnR[i];
		nxt[1][i] = mxR[i];
	}
	loop(c, 2) loop(i, n) {
		prv[c][nxt[c][i]] = i;
	}
}

void erase(int j, int *nxt, int *prv) {
	if(prv[j] == -1 || nxt[j] == n) return;
	int a = prv[j], b = nxt[j];
	prv[b] = a;
	nxt[a] = b;
}

void bfs() {
	static queue<int> q;
	fill(dist, dist + n, -1);
	while(!q.empty()) q.pop();
	dist[0] = 0;
	q.push(0);
//	prArr(mnL, n, int);
//	prArr(mxR, n, int);
	for(;!q.empty(); q.pop()) {
		int i = q.front();
		if(i == n-1) break;
		for(int j = mxR[i]; j != n && j < mnR[i]; j = mxR[j]) {
//			cerr << "type0: " << i + 1 << " " << j + 1 << endl;
			if(dist[j] == -1) {
				dist[j] = dist[i] + 1;
				erase(j, nxt[1], prv[1]);
				q.push(j);
			}
		}
		for(int j = mnR[i]; j != n && j < mxR[i]; j = mnR[j]) {
//			cerr << "type1: " << i + 1 << " " << j + 1 << endl;
			if(dist[j] == -1) {
				dist[j] = dist[i] + 1;
				q.push(j);
				erase(j, nxt[0], prv[0]);
			}
		}
	}
}

void tc() {
	scanf("%d", &n);
	loop(i, n) {
		scanf("%d", P + i);
		P[i]--;
	}
	preprocess();
	bfs();
	printf("%d\n", dist[n - 1]);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
