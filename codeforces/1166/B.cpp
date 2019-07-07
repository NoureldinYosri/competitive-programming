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
//string vowels = "aeiou";
//int K;
//string s;
//
//bool valid(int R,int C) {
//	if(R < sz(vowels) || C < sz(vowels)) return 0;
//	s.clear();
//	vector<string> G(R,string(C,' '));
//	loop(r,R){
//		int m = C - C%sz(vowels);
//		loop(c,m) G[r][c] = vowels[(r+c)%sz(vowels)];
//	}
//	for(int c = C - C%sz(vowels);c < C;c++){
//		loop(r,R) G[r][c] = vowels[r%sz(vowels)];
//	}
//	loop(r,R) loop(c,C) s.push_back(G[r][c]);
//	return 1;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	cin >> K;
//	for(int n = 1;n <= K;n++) {
//		if(K%n) continue;
//		int m = K/n;
//		if(valid(n,m)) {
//			cout << s << endl;
//			return 0;
//		}
//	}
//	cout << "-1" << endl;
//	return 0;
//}
