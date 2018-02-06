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
//const int MAX = 1e5;
//map<string,int> M;
//string S[MAX];
//char buffer[MAX];
//int n;
//
//int main(){
//	#ifdef HOME
//		freopen("in.in", "r", stdin);
//	#endif
//	scanf("%d",&n);
//	loop(i,n){
//		scanf("%s",buffer);
//		S[i] = string(buffer);
//		vector<string> V;
//		for(int j = 0;buffer[j];j++){
//			string tmp;
//			for(int k = j;buffer[k];k++) {
//				tmp += buffer[k];
//				V.pb(tmp);
//			}
//		}
//		sort(all(V));
//		V.resize(unique(all(V)) - V.begin());
//		for(string s : V)
//			M[s]++;
//	}
//
//	loop(i,n){
//		int ans = 0;
//		vector<string> V;
//		for(int j = 0;j < sz(S[i]);j++){
//			string tmp;
//			for(int k = j;k < sz(S[i]);k++) {
//				tmp += S[i][k];
//				V.pb(tmp);
//			}
//		}
//		sort(all(V));
//		V.resize(unique(all(V)) - V.begin());
//		for(string s : V)
//			ans += M[s] == 1;
//		printf("%d\n",ans);
//	}
//	return 0;
//}
