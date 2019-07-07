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
//const int MAX = 500 + 10;
//char G[MAX][MAX];
//int H,W;
//int visCount[MAX][MAX];
//
//bool inGrid(int x,int y) {
//	if(x < 0 || x >= H) return 0;
//	if(y < 0 || y >= W) return 0;
//	return 1;
//}
//
//void goDown(int x,int y) {
//	if(!inGrid(x,y) || G[x][y] != '*') return;
//	visCount[x][y]++;
//	goDown(x+1,y);
//}
//void goRight(int x,int y) {
//	if(!inGrid(x,y) || G[x][y] != '*') return;
//	visCount[x][y]++;
//	goRight(x,y + 1);
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d %d",&H,&W);
//	loop(i,H) scanf("%s",G[i]);
//	pi up;
//	bool f = 0;
//	loop(r,H) loop(c,W) if(!f && G[r][c] == '*') up = mp(r,c),f = 1;
//	if(!f) {
//		cout << "NO" << endl;
//		return 0;
//	}
//	goDown(up.first,up.second);
//	pi left; f = 0;
//	loop(c,W) loop(r,H) if(!f && G[r][c] == '*') left = mp(r,c),f = 1;
//	goRight(left.first,left.second);
//
//	vector<pi> candPivot;
//	loop(r,H) loop(c,W) {
//		if(G[r][c] != '*') continue;
//		if(!visCount[r][c]) {
//			cout << "NO" << endl;
//			return 0;
//		}
//		if(visCount[r][c] != 1)
//			candPivot.emplace_back(r,c);
//	}
//	if(sz(candPivot) != 1) {
//		cout << "NO" << endl;
//		return 0;
//	}
//	pi pivot = candPivot[0];
//	int dx[] = {-1,0,1,0};
//	int dy[] = {0,-1,0,1};
//	loop(i,4) {
//		int x = pivot.first + dx[i];
//		int y = pivot.second + dy[i];
//		f = inGrid(x,y) && G[x][y] == '*';
//		if(!f){
//			cout << "NO" << endl;
//			return 0;
//		}
//	}
//	cout << "YES" << endl;
//	return 0;
//}
