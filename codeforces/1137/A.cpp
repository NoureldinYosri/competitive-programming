//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
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
//using namespace std;
//
//const int MAXN = 1000;
//int G[MAXN][MAXN],m,n;
//vi ROW[MAXN];
//vi COL[MAXN];
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d %d",&m,&n);
//	loop(i,m) loop(j,n) {
//		scanf("%d",&G[i][j]);
//		ROW[i].push_back(G[i][j]);
//		COL[j].push_back(G[i][j]);
//	}
//	loop(i,m) {
//		sort(all(ROW[i]));
//		ROW[i].resize(unique(all(ROW[i])) - ROW[i].begin());
//	}
//	loop(i,n) {
//		sort(all(COL[i]));
//		COL[i].resize(unique(all(COL[i])) - COL[i].begin());
//	}
//	loop(i,m) loop(j,n) {
//		int a = 0,b = 0,c = 0,d = 0;
//		a = lower_bound(all(ROW[i]),G[i][j]) - ROW[i].begin();
//		b = ROW[i].size() - a - 1;
//		c = lower_bound(all(COL[j]),G[i][j]) - COL[j].begin();
//		d = COL[j].size() - c - 1;
//		int x = max(a,c) + max(b,d) + 1;
//		printf("%d%c",x," \n"[j==n-1]);
//	}
//
//	return 0;
//}
