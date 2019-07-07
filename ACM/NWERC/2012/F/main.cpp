#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 1024 + 10;
char G[MAX][MAX];
int n;

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	vp matches;
	while(scanf("%d",&n) == 1) {
		loop(i,n) scanf("%s",G[i]);
		set<int> A,B;
		for(int i = 1;i < n;i++){
			if(G[0][i] == '1') A.insert(i);
			else B.insert(i);
		}
		for(;n > 1;n >>= 1) {
			cerr << n << endl;
			print(A,int);
			print(B,int);
			matches.clear();

			for(int b : B)
				loop(i,n)
					if(A.count(i)) {
						A.erase(i);
						matches.push_back(mp(i,b));
						break;
					}
			assert(!A.empty());
			matches.push_back(mp(0,*A.begin()));
			A.erase(A.begin());
			vi VA {all(A)},VB{all(B)};
			while(sz(VB) > 1) {
				int a = VB.back();
				VB.pop_back();
				int b = VB.back();
				VB.pop_back();
				matches.push_back(mp(a,b));
			}
			while(sz(VA) > 1) {
				int a = VA.back();
				VA.pop_back();
				int b = VA.back();
				VA.pop_back();
				matches.push_back(mp(a,b));
			}
			if(!VA.empty()) {
				assert(!VB.empty());
				matches.push_back(mp(VA[0],VB[0]));
				VA.pop_back();
				VB.pop_back();
			}
			VA.clear();
			VB.clear();
			A.clear();
			B.clear();
			for(auto p : matches) {
				int a = p.xx,b = p.yy;
				printf("%d %d\n",a,b);
				int w = a;
				if(G[a][b] == '0') w = b;
				if(G[0][w] == '1') A.insert(w);
				else if(w != 0) B.insert(w);
			}
		}
	}
	return 0;
}
