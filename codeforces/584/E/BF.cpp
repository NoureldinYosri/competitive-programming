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
//map<vi,int> D;
//int n;
//vi fr,to;
//
//
//
//int main(){
//	#ifdef HOME
//		freopen("in.in", "r", stdin);
//	#endif
//	scanf("%d",&n);
//	fr = vi(n,0);
//	to = vi(n,0);
//	loop(i,n) scanf("%d",&fr[i]);
//	loop(i,n) scanf("%d",&to[i]);
//
//	D[fr] = 0;
//	typedef pair<int,vi> state;
//	PQ<state,vector<state>,greater<state> > pq;
//	pq.push(mp(0,fr));
//	while(!pq.empty()){
//		int d = pq.top().first;
//		vi cur = pq.top().second;
//		pq.pop();
//		if(D[cur] != d) continue;
//		for(int i = 0;i< n;i++)
//			for(int j = i+1;j < n;j++) {
//				int nd = d + j - i;
//				swap(cur[i],cur[j]);
//				if(D.find(cur) == D.end()) D[cur] = INT_MAX;
//				if(nd < D[cur]) {
//					D[cur] = nd;
//					pq.push(mp(nd,cur));
//				}
//				swap(cur[i],cur[j]);
//			}
//	}
//	cout << D[to] << endl;
//	return 0;
//}
