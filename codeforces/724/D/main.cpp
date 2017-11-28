#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

int n,m;
char S[1 << 20];
vi IDX[128];
vi aux;




void work(int x,set<int> & S,set<int> & E) {
	while(!E.empty()){
		auto p = E.lower_bound(x);
		if(p == E.end()) break;
		if(*p - x >= m) break;
		S.erase(*p - m + 1);
		E.erase(p);
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %s",&m,S);
	n = strlen(S);

	loop(i,n) IDX[(int)(S[i] - 'a')].pb(i);
	set<int> S,E;
	loop(i,n-m+1) S.insert(i),E.insert(i + m - 1);
	string out;
	for(int c = 0;c < 26 && !S.empty();c++) {
		vi & pos = IDX[c];
		int ctr = 0;
		while(!E.empty() && sz(pos) > 1) {
			int x = pos.back(); pos.pop_back();
			auto p = S.upper_bound(x);
			if(p == S.begin()) {
				ctr++;
				continue;
			}
			--p;
			if(*p > pos.back()) {
				work(x,S,E);
				out.pb(c + 'a');
			}
			else ++ctr;
		}
		if(!E.empty() && sz(pos) == 1) {
			out.pb(c + 'a');
			work(pos.back(),S,E);
			pos.pop_back();
		}
		if(S.empty()) break;
		while(ctr) {
			--ctr;
			out.pb(c + 'a');
		}
	}
	cout << out << endl;
	return 0;
}
