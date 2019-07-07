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
//int getCost(vi V) {
//	int n = sz(V);
//	int ret = 0;
//	for(int i = 0;i < n;i++) {
//		int j = find(all(V),i) - V.begin();
//		if(j == i) continue;
//		if(j != n-1) {
//			ret++;
//			reverse(V.begin() + j,V.end());
//		}
//		ret++;
//		reverse(V.begin()+i,V.end());
//	}
//	return ret;
//}
//
//vi GetKth(int k,int n) {
//	vi V;
//	loop(i,n) V.push_back(i);
//	vector<vi> minimax;
//	int mx = -1;
//	do{
//		int c = getCost(V);
//		if(c > mx) mx = c,minimax.clear();
//		if(c == mx) minimax.push_back(V);
//	}while(next_permutation(all(V)));
//	return minimax[k-1];
//}
//
//ostream& operator << (ostream& st,const vi & V)  {
//	for(int i : V) st << (char)(i + 'A');
//	return st;
//}
//
//int main(int argc,char **argv){
//	vi p = GetKth(2011,11);
//	cout << p << endl;
//	return 0;
//}
