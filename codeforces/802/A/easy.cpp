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
int lst[MAX],nxt[MAX];

void read(){
	scanf("%d %d",&n,&K);
	loop(i,n) {
		scanf("%d",A + i);
		A[i]--;
	}
}

void preprocess(){
	loop(i,n) lst[A[i]] = n;
	for(int i = n-1;i >= 0;i--){
		nxt[i] = lst[A[i]];
		lst[A[i]] = i;
	}
}

int solve(){
	int ans = 0;
	set<pi> byNxt;
	loop(i,n){
		int cur = A[i];
		if(byNxt.find(mp(i,cur)) != byNxt.end()) byNxt.erase(mp(i,cur));
		else if(sz(byNxt) < K) ans++;
		else {
			ans++;
			byNxt.erase(*byNxt.rbegin());
		}
		byNxt.insert(mp(nxt[i],cur));
	}
	return ans;
}

int main(){
	read();
	preprocess();
	printf("%d\n",solve());
	return 0;
}
*/
