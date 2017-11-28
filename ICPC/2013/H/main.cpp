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

const int oo = 1 << 29;
int A[500],n;
int dp[500][500];
int memcost[500][500];
vi sortedSubArray[500][500];


void preprocess(){
	for(int s = 0;s < n;s++)
		for(int e = s;e < n;e++){
			range(k,s,e) sortedSubArray[s][e].pb(A[k]);
			sort(all(sortedSubArray[s][e]));
		}
}




bool valid(int s,int e){
	vi V{A + s,A + e + 1};
	sort(all(V));
	V.resize(unique(all(V)) - V.begin());
	if(sz(V) != e -s + 1) return 0;
	loop(i,sz(V)) if(V[i] != i+1) return 0;
	return 1;
}



bool isrev(int s,int e){
	vi V{A+s,A+e+1};
	reverse(all(V));
	return is_sorted(all(V));
}

int merge(int s,int k,int e){
	int cost = 0;
	vi U{A+s,A+k+1}; sort(all(U));
	vi V{A+k+1,A+e+1}; sort(all(V));
	while(!U.empty() && !V.empty()){
		cost++;
		if(U.back() > V.back()) U.pop_back();
		else V.pop_back();
	}
	return cost;
}

inline bool isThereLess(int s,int e,int v) {
	if(s > e) return 0;
	return sortedSubArray[s][e][0] < v;
}
inline bool isThereMore(int s,int e,int v) {
	if(s > e) return 0;
	return sortedSubArray[s][e].back() > v;
}

int getMergeCost(int s,int k,int e,int & cost){
	//was k open ?
	if(isThereLess(s,k-1,A[k])) cost--;
	//will k be open
	if(isThereLess(k+1,e,A[k])) cost++;
	//how many things will be open
	if(!isThereLess(s,k-1,A[k])) {
		vi & V = sortedSubArray[k+1][e];
		int x = INT_MAX;
		if(isThereMore(s,k,A[k])) {
			x = *upper_bound(all(sortedSubArray[s][k]),A[k]);
		}
		cost += lower_bound(all(V),x) - lower_bound(all(V),A[k]);
	}

	//how many things will be closed
	if(s < k && !isThereLess(k+1,e,A[k])){
		vi & V = sortedSubArray[s][k-1];
		if(isThereMore(k+1,e,A[k])){
			assert(sortedSubArray[k][e][0] == A[k]);
			int u = sortedSubArray[k][e][1];
			cost -= lower_bound(all(V),u) - lower_bound(all(V),A[k]);
		}
		else{
			cost -= V.end() - lower_bound(all(V),A[k]);
		}
	}
//	if(cost != merge(s,k,e)) {
//		cerr << "expected " << merge(s,k,e) << " found " << cost << endl;
//		prArr(A+s,k-s+1,int);
//		prArr(A+k+1,e-k,int);
//	}
//	assert(cost == merge(s,k,e));
	return cost;
}

int get_cost(int s,int e) {
	if(memcost[s][e] != -1) return memcost[s][e];
	if(is_sorted(A+s,A + e+  1)) return e-s;
	if(isrev(s,e)) return e-s;
	int & ret = memcost[s][e];
	ret = oo;
	int cost = 0;
	for(int k = s;k < e;k++)
		ret = min(ret,get_cost(s,k) + get_cost(k+1,e) + getMergeCost(s,k,e,cost));
	return ret;
}

int solve(int s,int e) {
	if(dp[s][e] != -1) return dp[s][e];
	int & ret = dp[s][e];
	ret = oo;
	if(valid(s,e)) return ret = get_cost(s,e);
	for(int k = s;k < e;k++)
		ret = min(ret,solve(s,k) + solve(k+1,e));
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	preprocess();
	memset(dp,-1,sizeof dp);
	memset(memcost,-1,sizeof memcost);
	int ans = solve(0,n-1);
	string s = "impossible";
#ifdef DEBUG
	s[0] = 'I';
#endif
	if(ans >= oo) puts(s.c_str());
	else cout << ans << endl;
	return 0;
}
