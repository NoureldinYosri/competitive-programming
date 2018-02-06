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

const int MAX = 55;
vi plates[MAX],stacks[MAX*MAX];
int n,m;
int dp[MAX*MAX][MAX];

int solve(int h,int cur_stack){
	if(h == m) return 0;
	if(dp[h][cur_stack] != -1) return dp[h][cur_stack];
	int & ret = dp[h][cur_stack];
	ret = 1 << 29;
	int cost = 0;
	for(int st : stacks[h]){
		if(plates[st].back() != h && st != cur_stack) cost++;
	}
	for(int to : stacks[h + 1]){
		int tmp = 0 ;
		if(to == cur_stack){
			if(sz(stacks[h]) != 1) tmp++;
		}
		else{
			if(plates[cur_stack].back() != h) tmp++;
			if(binary_search(all(plates[to]),h)) tmp--;
		}
		//if(binary_search(all(plates[to]),h)) tmp--;
	//	if(h == 1 && cur_stack == 0) cerr << "to = " << to << " tmp = " << tmp << " cost =" << cost << " solve = "  << solve(h + 1,to)<< endl;
		ret = min(ret,solve(h + 1,to) + tmp + cost);
	}
	//cerr << "h = " << h << " cur_stack = " << cur_stack << " -> " << ret << " cost = " << cost << endl;
	return ret;
}

void preprocess(){
	loop(i,n) plates[i].resize(unique(all(plates[i])) - plates[i].begin());
	vi H;
	loop(i,n) for(int x : plates[i]) H.pb(x);
	sort(all(H));
	H.resize(unique(all(H)) - H.begin());
	loop(i,sz(H)) stacks[i].clear();
	loop(i,n) {
		for(int & x: plates[i]) {
			x = lower_bound(all(H),x) - H.begin();
			stacks[x].pb(i);
		}
	//	print(plates[i],int);
	}
	m = H.size() - 1;
	memset(dp,-1,sizeof dp);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
	#endif
	for(int t = 1;scanf("%d",&n) == 1;t++){
		loop(i,n){
			plates[i].clear();
			int m; scanf("%d",&m);
			while(m--){
				int x ; scanf("%d",&x);
				plates[i].pb(x);
			}
		}
		preprocess();
		int ans = 1 << 29;
		for(int st : stacks[0]) ans = min(ans,solve(0,st));
		printf("Case %d: %d\n",t,2*ans + n - 1);
	//	cerr << 2*ans + n - 1 << endl;
	}
	return 0;
}
