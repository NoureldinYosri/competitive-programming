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
//ll A[1 << 20],n,m;
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	cin >> n;
//	m = 2*n;
//	loop(i,m) scanf("%lld",A + i);
//	sort(A,A + m);
//	ll a = 0,b = 0;
//	loop(i,n) a += A[i];
//	loop(i,n) b += A[i + n];
//	if(a == b) {
//		ll x = A[0],y = A[m-1];
//		a += y - x;
//		b += x - y;
//		swap(A[0],A[m-1]);
//	}
//	if(a == b) cout << -1 << endl;
//	else {
//		loop(i,m) printf("%lld%c",A[i]," \n"[i==m-1]);
//	}
//	return 0;
//}
