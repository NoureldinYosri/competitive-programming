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

const int MAX = 1 << 20;
char out[3][50] = {"Takeover Incorporated","Buyout Limited","tie"};
ll A[MAX],B[MAX];
int n,m;

int solve(PQ<ll> pq[2],int turn){
	int nochange = 0;
	while(!pq[0].empty() && !pq[1].empty()){
	//	cerr << "player " << char('A' + turn) << " : ";
		if(pq[turn].top() > pq[turn ^ 1].top()) {
	//		cerr << "erases " << pq[turn ^ 1].top() << " from other player" << endl;
			pq[turn ^ 1].pop();
			nochange = 0;
		}
		else if(pq[turn].size() > 1){
			ll x = pq[turn].top(); pq[turn].pop();
			ll y = pq[turn].top(); pq[turn].pop();
			pq[turn].push(x + y);
	//		cerr << "merges " << x << " and " << y << endl;
			nochange = 0;
		}
		else nochange++;
		if(nochange == 3) return 2;
	//	else cerr << "can't play" << endl;
		turn ^= 1;
	}
	//cerr << "========================" << endl;
	return (pq[1].empty() ? 0 : 1);
}

int solve(){
	PQ<ll> pq[2];
	loop(i,n) pq[0].push(A[i]);
	loop(i,m) pq[1].push(B[i]);
	if(!solve(pq,0)) return 0;
	loop(i,2){
		while(!pq[i].empty()) pq[i].pop();
	}
	loop(i,n) pq[0].push(A[i]);
	loop(i,m) pq[1].push(B[i]);
	if(n > 1){
		ll x = pq[0].top(); pq[0].pop();
		ll y = pq[0].top(); pq[0].pop();
		pq[0].push(x + y);
		return solve(pq,1);
	}
	else return 1;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	for(int t = 1;scanf("%d %d",&n,&m) == 2;t++){
		loop(i,n) scanf("%lld",A + i);
		loop(i,m) scanf("%lld",B + i);
		printf("Case %d: %s\n",t,out[solve()]);
	}
	return 0;
}
