//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vl vector<long long>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//const double PI = acos(-1);
//using namespace std;
//
//int X,Y,Z,A,B,C;
//
//int dp[100 + 1][100 + 1][100 + 1];
//vector<vi> dr;
//vi cost;
//
//
//int solve(int x,int y,int z) {
//	if(x == X && y == Y && z == Z) return 0;
//	if(x > X || y > Y || z > Z) return 1 << 29;
//	int & ret = dp[x][y][z];
//	if(ret != -1) return ret;
//	ret = INT_MAX;
//	for(int i = 0;i < 7;i++) {
//		vi d = dr[i];
//		ret = min(ret,solve(x+d[0],y+d[1],z+d[2]) + cost[i]);
//	}
////	cerr << x << " " << y << " " << z << " \t " << ret << endl;
//	return ret;
//}
//
//int main(){
//	#ifdef HOME
//		freopen("in.in", "r", stdin);
//	#endif
//	int T; scanf("%d",&T);
//	range(t,1,T) {
//		scanf("%d %d %d",&X,&Y,&Z);
//		scanf("%d %d %d",&A,&B,&C);
//		dr = vector<vi>{{1,0,0},{0,1,0},{0,0,1},{1,1,0},{0,1,1},{1,0,1},{1,1,1}};
//		cost = vi {A,A,A,B,B,B,C};
//		memset(dp,-1,sizeof dp);
//		printf("%d\n",solve(0,0,0));
//	}
//	return 0;
//}
