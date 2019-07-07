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
//#include "my_math.h"
//
//ll n = 1000000000000LL;
//const string project = "project";
//
//
//int ctr[1 << 7];
//vector<char> S;
//
//bool endsInProject(bool mark){
//	if(sz(S) < sz(project)) return 0;
//	int msk = 0;
//	loop(i,sz(project)) msk |= 1 << project.find(S[sz(S)-1-i]);
//	if(msk == (1 << sz(project))-1) return 1;
//	if(mark) ctr[msk]++;
//	return 0;
//}
//
//int LEN = 7;
//
//int bt(int i) {
//	assert(sz(S) == i);
//	if(endsInProject(sz(S) == LEN)) return 0;
//	if(sz(S) == LEN) return 1;
//	int ret = 0;
//	for(char c : "project") {
//		if(!isalpha(c)) break;
//		S.push_back(c);
//		ret += bt(i+1);
//		S.pop_back();
//	}
//	return ret;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	for(LEN = 7;LEN <= 12;LEN++){
//		memset(ctr,0,sizeof ctr);
//		int ans = bt(0);
//		cout << ans << " =";
//		for(int p = 2;p*p <= ans;p++)
//			if(ans%p == 0) {
//				int e = 0;
//				while(ans%p == 0) e++,ans/=p;
//				cout << " " << p;
//				if(e > 1 ) cout << "^" << e;
//			}
//		if(ans > 1) cout << " " << ans;
//		cout << endl;
//		for(int i = 1;i < (1 << 7);i++)
//			if(popcnt(i) == 6)
//				cerr << ctr[i] << " ";
//		cerr << endl;
//	}
//	return 0;
//}
