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


const int MAX = 50*1000 + 10;
int P[MAX][3];
int ord[MAX],n;

int solve1d(int s,int e) {
	for(int i = s;i+1 <= e;i += 2)
		printf("%d %d\n",ord[i]+1,ord[i+1]+1);
	int len = e-s+1;
//	cout << s << " " << e << ": " << ord[e]+1 << endl;
	if(len&1) return ord[e];
	return -1;
}

int solve2d(int s,int e){
	static vi aux;
	aux.clear();
	for(int i = s;i <= e;) {
		int j = i;
		int y = P[ord[i]][1];
		while(j <= e && P[ord[j]][1] == y) j++;
		int a = solve1d(i,j-1);
		if(a != -1) {
			if(aux.empty()) {
				aux.push_back(a);
			}
			else {
				printf("%d %d\n",aux.back()+1,a+1);
				aux.pop_back();
			}
		}
		i = j;
	}
	if(aux.empty()) return -1;
	else return aux.back();
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n){
		loop(j,3) scanf("%d",&P[i][j]);
		ord[i] = i;
	}
	sort(ord,ord + n,[](const int & a,const int & b) {
		loop(i,3) if(P[a][i] != P[b][i]) return P[a][i] < P[b][i];
		return a < b;
	});
	vi bank;
	for(int i = 0;i < n;){
		int j = i;
		int x = P[ord[i]][0];
		while(j < n && P[ord[j]][0] == x) j++;
		int a = solve2d(i,j-1);
		if(a != -1){
			if(bank.empty()) {
				bank.push_back(a+1);
			}
			else {
				printf("%d %d\n",bank.back(),a+1);
				bank.pop_back();
			}
		}
		i = j;
	}
//	print(bank,int);
	assert(bank.empty());
	return 0;
}
#endif
