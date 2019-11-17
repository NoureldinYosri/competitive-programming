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

int n;
int A[1 << 20];
vi B;


void compress(){
	B = vi{A,A + n};
	sort(all(B));
	B.resize(unique(all(B)) - B.begin());
	loop(i,n) A[i] = upper_bound(all(B),A[i]) - B.begin();
}

int problem[1 << 20];
int reason[1 << 20];
int L[1 << 20];

int solve(){
	int m = sz(B);
	set<int> S;
	loop(i,m+1) problem[i] = 0;
	for(int i = n-1;i >= 0;i--) {
		int x = A[i];
		problem[x] |= !S.empty() && *S.begin() < x;
		if(problem[x]){
			auto ptr = S.lower_bound(x);
			ptr--;
			reason[x] = *ptr;
		}
		S.insert(x);
	}
	vi Rproblem{problem,problem + m + 1};
	S.clear();
	loop(i,m+1) problem[i] = 0;
	int ans = INT_MAX;
	for(int i = 0;i  < n;i++) {
		int x = A[i];
		problem[x] |= !S.empty() && *S.rbegin() > x;
		S.insert(x);
	}
//	prArr(problem+1,m,int);
	for(int x = 1;x <= m;x++)
		if(problem[x]){
			ans = m+1-x;
			break;
		}

	int val = 0;
	for(int x = 1;x <= m;x++) {
		if(problem[x]) val = x;
		L[x] = val;
	}
	set<pi> byProblem,byIndex;
	for(int x = 1;x <= m;x++) if(Rproblem[x]) {
		byProblem.emplace(reason[x],x);
		byIndex.emplace(x,reason[x]);
	}
	if(byIndex.empty()) return 0;
	ans = m+1-byIndex.begin()->first;
	for(int x = 1;x <= m;x++){
		int tmp = L[x];
		if(!byIndex.empty() && byIndex.begin()->first==x) {
			auto p = *byIndex.begin();
			byIndex.erase(byIndex.begin());
			swap(p.first,p.second);
			byProblem.erase(p);
		}
		while(!byProblem.empty() && byProblem.begin()->first <= x) {
			auto p = *byProblem.begin();
			byProblem.erase(byProblem.begin());
			swap(p.first,p.second);
			byIndex.erase(p);
		}
		if(!byIndex.empty()) tmp += m+1-byIndex.begin()->first;
		ans = min(ans,tmp);
//		cout << x << ": " << L[x] << " " << tmp << endl;
//		for(auto p : byProblem) cout << p << " ";
//		cout << endl;
//		for(auto p : byIndex) cout << p << " ";
//		cout << endl;
//		cout << endl;
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int Q; scanf("%d",&Q);
	while(Q--) {
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		n = unique(A,A + n) - A;
		compress();
		printf("%d\n",solve());
	}
	return 0;
}
#endif
