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
//const int MAX = 300*1000 + 10;
//int S[MAX],ord[MAX];
//int T[MAX],n;
//vector<pair<pi,int> > ans;
//
//bool solve(){
//	sort(T,T + n);
//	sort(ord,ord + n,[](const int & a,const int & b) {
//		return S[a] < S[b];
//	});
//	queue<int> q;
//	loop(i,n) {
//		int j = ord[i];
//		if(S[j] == T[i]) continue;
//		if(S[j] < T[i]) {
//			q.push(i);
//			continue;
//		}
//		while(S[j] != T[i] && !q.empty()) {
//			int t = q.front();
//			int p = ord[t];
//			int d = min(T[t] - S[p],S[j] - T[i]);
//			if(d) ans.push_back(mp(mp(p,j),d));
//			S[p] += d;
//			S[j] -= d;
//			if(S[p] > S[j]) return 0;
//			if(S[p] == T[t]) q.pop();
//		}
//		if(S[j] != T[i]) return 0;
//	}
//	sort(S,S + n);
//	loop(i,n) if(S[i] != T[i]) return 0;
//	return 1;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d",&n);
//	loop(i,n){
//		scanf("%d",S + i);
//		ord[i] = i;
//	}
//	loop(i,n) scanf("%d",T + i);
//	if(!solve()) puts("NO");
//	else {
//		puts("YES");
//		printf("%d\n",sz(ans));
//		for(auto p : ans)
//			printf("%d %d %d\n",p.xx.xx+1,p.xx.yy+1,p.yy);
//	}
//	return 0;
//}
