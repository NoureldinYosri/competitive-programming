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
//
//ll dp[12][12][1 << 9][1 << 9];
//
//int R = 12,C = 9;
//
//#define checkBit(msk,i) ((msk >> (i)) & 1)
//
//string bin(int x) {
//	if(x == 0) return "0";
//	string ret;
//	while(x) {
//		ret += (x&1) + '0';
//		x >>= 1;
//	}
////	reverse(all(ret));
//	return ret;
//}
//
//ll solve(const int row,const int col,const int cur,const int nxt) {
//	if(col == C) return solve(row+1,0,nxt,cur);
//	if(row == R) return cur == 0 && nxt == 0;
//	ll & ret = dp[row][col][cur][nxt];
//	if(ret != -1) return ret;
//	ret = 0;
//	if(checkBit(cur,col)) ret = solve(row,col+1,cur & ~(1 << col),nxt);
//	if(col + 1 < C) {
//		int up [] = {1,1,1,1,1,0,0,1};
//		int dwn[] = {1,0,0,1,1,1,1,1};
//		for(int i = 0;i < 4;i++) {
//			int f = 2*i;
//			bool can = 1;
//			for(int j = 0;j < 2;j++) {
//				int s = f + j;
//				if(up [s] && checkBit(cur,col+j)) can = 0;
//				if(dwn[s] && checkBit(nxt,col+j)) can = 0;
//			}
//			int nn = cur,tnxt = nxt;
//			if(can) {
//				for(int j = 0;j < 2;j++) {
//					int s = f + j;
//					if(up [s]) nn |= 1 << col << j;
//					if(dwn[s]) tnxt |= 1 << col << j;
//				}
//				can &= checkBit(nn,col);
//				if(!can) continue;
//				nn &= ~(1 << col);
//				ll tmp = solve(row,col+1,nn,tnxt);
////				if(row==0 && col==0) {
////					cout << up[f] << up[f+1] << endl;
////					cout << dwn[f] << dwn[f+1] << endl;
////					cout << bin(nn) << " " << bin(tnxt) << ": " << tmp << endl;
////				}
//				ret += tmp;
//			}
//		}
//	}
//	if(col + 2 < C) {
//		bool can = !checkBit(cur,col) && !checkBit(cur,col+1) && !checkBit(cur,col+2);
//		if(can) ret += solve(row,col+1,cur | (6 << col),nxt);
//	}
//	if(row + 2 < R) {
//		bool can = !checkBit(cur,col) && !checkBit(nxt,col);
//		if(can) ret += solve(row,col+1,cur | (1 << col),nxt | (1 << col));
//	}
//
//	return ret;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	memset(dp,-1,sizeof dp);
//	cout << solve(0,0,0,0) << endl;
//	return 0;
//}
