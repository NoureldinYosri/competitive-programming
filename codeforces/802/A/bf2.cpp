/*#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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

const int MAX = 400000 + 10;
int A[MAX],K,n;
vi IDX[MAX];

void read(){
	scanf("%d %d",&n,&K);
	loop(i,n) {
		scanf("%d",A + i);
		A[i]--;
	}
}

int solve(){
	loop(i,n) IDX[A[i]].pb(i);
	set<int> S;
	int ans = 0;
	loop(i,n) {
		int cur = A[i];
		if(S.find(cur) != S.end()) continue;
		if(sz(S) < K) {
			ans++;
			S.insert(cur);
			continue;
		}
		int c = -1,nxt = i;
		for(int x : S){
			auto it = upper_bound(all(IDX[x]),i);
			int to = n;
			if(it != IDX[x].end()) to = *it;
			if(to > nxt) {
				c = x;
				nxt = to;
			}
		}
		ans++;
		S.erase(c);
		S.insert(cur);
	}
	return ans;
}

int main(){
	read();
	printf("%d\n",solve());
	return 0;
}
*/
