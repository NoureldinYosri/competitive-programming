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


const int MAX = 5010;

int n;
int A[MAX];
ll dp[MAX];
ll mem[MAX];

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	A[0] = -1000 * 1000 * 1000 - 3;
	for(int i = 1;i <= n;i++) scanf("%d",A + i);

	vi ord;
	loop(i,n+1) ord.push_back(i);
	sort(all(ord),[](const int & a,const int & b) {
		return tie(A[a],a) < tie(A[b],b);
	});
	reverse(all(ord));
	loop(i,n+1) mem[i] = 1LL << 60;
	for(int i : ord) {
		ll & res = dp[i];
		if(i == n) res = 0;
		else {
			res = 1LL << 60;
			ll tmp = 0;
			for(int k = i;k <= n;k++){
				tmp += abs(A[i] - A[k]);
				res = min(res,tmp + ((k < n) ? mem[k+1] : 0));
			}
		}
		ll tmp = dp[i];
		for(int k = i;k >= 0;k--){
			tmp += abs(A[i] - A[k]);
			mem[k] = min(mem[k],tmp);
		}
	}
	cout << dp[0] << endl;
	return 0;
}
