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
//const int MAX = 200*1000 + 10;
//int n,m;
//int fr[MAX],to[MAX];
//vector<int> L[MAX];
//
//void canonize(int a,int b,int & u,int & len) {
//	u = min(a,b);
//	b = a+b-u;
//	a = u;
//	len = b-a;
//	if(abs(a+n-b) < len) {
//		len = abs(a+n-b);
//		u = b;
//	}
//}
//
//int dist(int a,int b) {
//	if(a > b) swap(a,b);
//	int d = b-a;
//	return min(d,abs(a+n-b));
//}
//
//int getLen(int c,int l,vector<int> & S,vector<int> & f) {
//	while(l && c != S[l]) l = f[l-1];
//	if(c == S[l]) l++;
//	return l;
//}
//
//vector<int> diff,fail;
//bool can(vector<int> & I,int len) {
//	if(I.empty()) return 1;
//	bool self = 1;
//	for(int a : I) {
//		int b = (a + len)%n;
//		int c = (b + len)%n;
//		self &= a == c;
//	}
//	if(self) return 1;
//	diff.clear();
//	fail.clear();
//	sort(I.begin(),I.end());
//	int q = I.size();
//	for(int i = 0;i < sz(I);i++){
//		int d = I[(i+1)%q] - I[i];
//		if(d < 0) d += n;
//		diff.push_back(d);
//		fail.push_back(0);
//	}
//	int l = 0;
//	for(int i = 1;i < q;i++)
//		fail[i] = l = getLen(diff[i],l,diff,fail);
//	for(int i = 0;i+1 < q;i++){
//		l = getLen(diff[i],l,diff,fail);
//		if(l == q) {
////			print(I,int);
////			print(diff,int);
////			cerr << "shift of " << (i+1) << endl;
//			return 1;
//		}
//	}
////	 cout << "fail:";
////	 print(I,int);
////	 print(diff,int);
//	 return 0;
//}
//
//bool bf(){
//	set<pair<int,int> > target;
//	for(int i = 0;i < m;i++) {
//		int a = min(fr[i],to[i]),b = max(fr[i],to[i]);
//		target.insert(make_pair(a,b));
//	}
//	for(int k = 1;k < n;k++) {
//		set<pair<int,int> > content;
//		bool y = 1;
//		for(int i = 0;i < m;i++) {
//			int a = (fr[i] + k)%n,b = (to[i] + k)%n;
//			if(a > b) swap(a,b);
//			pair<int,int> p = make_pair(a,b);
//			y &= target.count(p);
//			content.insert(p);
//		}
//		y &= sz(content) == m;
//		if(y) {
//			cerr << "brute force shift of " << k << endl;
//			return 1;
//		}
//	}
//	return 0;
//
//}
//
//bool validShift(int k) {
//	static 	set<pair<int,int> > target;
//	if(target.empty()) {
//		for(int i = 0;i < m;i++) {
//			int a = min(fr[i],to[i]),b = max(fr[i],to[i]);
//			target.insert(make_pair(a,b));
//		}
//	}
//
//	bool y = 1;
//	for(int i = 0;i < m && y;i++) {
//		int a = (fr[i] + k)%n,b = (to[i] + k)%n;
//		if(a > b) swap(a,b);
//		pair<int,int> p = make_pair(a,b);
//		y &= target.count(p);
//	}
//	return y;
//
//}
//
//int main() {
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d %d",&n,&m);
//	for(int i = 0;i < m;i++) {
//		scanf("%d %d",fr + i,to + i);
//		fr[i]--,to[i]--;
//	}
//
//	bool y = 0;
//	for(int k = 1;k < n && !y;k++)
//		if(n%k == 0)
//			y |= validShift(k);
//	cout << (y ? "Yes" : "No") << endl;
//	return 0;
//}
