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
//const int MAXC = 100*1000 + 10;
//map<int,int> ID[MAXC],W[MAXC];
//
//int find(int a,map<int,int> & id,map<int,int> & w){
//	if(!id.count(a)) id[a] = a,w[a] = 1;
//	return id[a] = (a == id[a]) ? a : find(id[a],id,w);
//}
//void join(int a,int b,map<int,int> & id,map<int,int> & w) {
//	a = find(a,id,w);
//	b = find(b,id,w);
//	if(w[a] < w[b]) swap(a,b);
//	id[b] = a;
//	w[a] += w[b];
//}
//bool areConnected(int a,int b,int c) {
//	return find(a,ID[c],W[c]) == find(b,ID[c],W[c]);
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	int n,m,C,q;
//	scanf("%d %d %d %d",&n,&m,&C,&q);
//	loop(e,m) {
//		int a,b,c; scanf("%d %d %d",&a,&b,&c);
//		join(a,b,ID[c],W[c]);
//	}
//	int a = 1,b = 3,c = 1;
//	cerr << find(a,ID[c],W[c]) << " " << find(b,ID[c],W[c]) << endl;
//	loop(i,q) {
//		char c; scanf(" %c",&c);
//		if(c == '+') {
//			int a,b,color; scanf("%d %d %d",&a,&b,&color);
//			join(a,b,ID[color],W[color]);
//		}
//		else {
//			int a,b; scanf("%d %d",&a,&b);
//			bool y = 0;
//			for(int c = 1;c <= C && !y;c++){
//				cerr << a << " " << b << " " << c << ": " << areConnected(a,b,c) << endl;
//				y = areConnected(a,b,c);
//			}
//			puts(y ? "Yes" : "No");
//		}
//	}
//	return 0;
//}
