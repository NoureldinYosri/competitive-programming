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


int n;
int A[1 << 20];
int val[1 << 20];

bool isHill(int i){
	return i && A[i - 1] < A[i] && i + 1 < n && A[i] > A[i + 1];
}
bool isVally(int i){
	return i && A[i - 1] > A[i] && i + 1 < n && A[i] < A[i + 1];	
}

bool getVal(int i){
	return isHill(i) || isVally(i);
}

void tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	int tot = 0;
	loop(i, n) tot += val[i] = getVal(i);
	int ans = tot;
	static vp aux;
	static vi cand;
	loop(i, n){
		int tmp = tot;
		aux.clear();
		cand.clear();
		for(int j = i-1; j <= i + 1; j++)
			if(j >= 0 && j < n){
				aux.emplace_back(j, A[j]);
				cand.push_back(A[j] - 1);
				cand.push_back(A[j]);
				cand.push_back(A[j] + 1);
				tmp -= val[j];
			}
		sort(all(cand));
		cand.resize(unique(all(cand)) - cand.begin());
		for(int x : cand) {
			A[i] = x;
			int f = tmp;
			for(auto [j, _] : aux)
				f += getVal(j);
			ans = min(ans, f);
		}
		for(auto [j, v] : aux)
			A[j] = v;
	}
	printf("%d\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
