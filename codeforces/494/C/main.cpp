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

const int MAXN = 100*1000 + 10,MAXQ = 5010,MAXLG = log(MAXN)/log(2) + 2;
int L[MAXQ],R[MAXQ],n,q;
double P[MAXQ];
int A[MAXN],ST[MAXN][MAXLG],lg[MAXN];
vi adj[MAXQ];
double dp[MAXQ][2*MAXQ + 1];
int MAXA;

inline int get_max(int l,int r){
	int len = lg[r - l + 1];
	return max(ST[l][len],ST[r - (1 << len) + 1][len]);
}
void build_sparse_table(){
	lg[0] = -1;
	loop(i,MAXN-1) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i+1));
	loop(i,n) ST[i][0] = A[i];
	loop(k,MAXLG-1)
		loop(i,n){
			int j = i + (1 << k);
			if(j >= n) j = i;
			ST[i][k + 1] = max(ST[i][k],ST[j][k]);
		}
	MAXA = get_max(0,n-1);
}


void read_input(){
	scanf("%d %d",&n,&q);
	loop(i,n) scanf("%d",A + i);
	L[0] = 0,R[0] = n-1,P[0] = 0;
	range(i,1,q) {
		scanf("%d %d %lf",L + i,R + i,P + i);
		L[i]--,R[i]--;
	}
	q++;
}

void build_tree(){
	vi ord; ord.reserve(q);
	loop(i,q) ord.pb(i);
	sort(all(ord),[](const int & a,const int & b){
		return mp(R[a] - L[a],b) < mp(R[b] - L[b],a);
	});
	for(int i = 0;i < q;i++)
		for(int j = i +1;j < q;j++) {
			int u = ord[i],v = ord[j];
			if(L[v] <= L[u] && R[u] <= R[v]){
				adj[v].pb(u);
	//			cerr << "add edge " << v << " " << u << endl;
				break;
			}
		}
}

double solve(int u,int target_diff){
	if(get_max(L[u],R[u]) > MAXA + target_diff) return 0;
	double & ret = dp[u][target_diff + MAXQ];
	if(ret == ret) return ret;
	if(target_diff - 1 > - MAXQ && abs(solve(u,target_diff - 1) - 1) < 1e-15) return ret = 1;
	ret = 0;
	double p_choice[2] = {1-P[u],P[u]};
	for(int choice = 0;choice <= 1;choice++){
		if(get_max(L[u],R[u]) + choice > MAXA + target_diff) break;
		double tmp = 1;
		for(auto v : adj[u]){
			double tmp2 = solve(v,target_diff - choice);
			//if(u == 3) cerr << u << " "<< target_diff << " choice = " << choice << " v = " << v << " tmp = " << tmp2 << endl;
			tmp *= tmp2;
		}
//		if(u == 3) cerr << u << " " << target_diff << " \t " << choice << " " << p_choice[choice] << " " << tmp << endl;
		ret += p_choice[choice] * tmp;
///		if(u == 3) cerr << "cur ret is " << ret << endl;
	}
	//cerr << u << " " << target_diff << " -> " << ret << endl;
	//prArr(p_choice,2,double);
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	read_input();
	build_sparse_table();
	build_tree();
	double ans = 0,lst = 0;
	memset(dp,-1,sizeof dp);
	for(int diff = 0;diff <= q;diff++){
		double p = solve(0,diff);
	//	assert(p >= lst);
	//	assert(p <= 1 || abs(p - 1) < 1e-15);
		ans += (MAXA + diff) * (p - lst);
		lst = p;
	//	cerr << diff << " " << p << endl;
	}
	printf("%.10f\n",ans);
	return 0;
}
