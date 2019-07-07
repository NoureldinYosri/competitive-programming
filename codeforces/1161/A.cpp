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
//int n,K;
//int X[1 << 20];
//int lst[1 << 20],pref[1 << 20];
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d %d",&n,&K);
//	loop(i,K) scanf("%d",X + i);
//	set<int> S;
//	memset(lst,-1,sizeof lst);
//	loop(i,K) {
//		lst[X[i]] = i;
//		S.insert(X[i]);
//		for(int x = X[i] - 1;x <= X[i]+1;x += 2)
//			if(x >= 1 && x <= n && !S.count(x))
//				pref[i]++;
//	}
//	ll ans = 0;
//	for(int i = 1;i <= n;i++){
//		int j = lst[i];
//		int tmp = 0;
//		if(j == -1) {
//			tmp = 1;
//			if(i > 1) tmp++;
//			if(i+1 <= n) tmp++;
//		}
//		else tmp = pref[j];
//		ans += tmp;
//	}
//	cout << ans << endl;
//	return 0;
//}
