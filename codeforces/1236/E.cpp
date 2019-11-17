#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


int n,m;
int A[1 << 20];

map<int,int> lst;

int getR(int x) {
	loop(i,m){
		if(x == n) return n;
		if(x+1 == A[i]) continue;
		x++;
	}
	return min(x+1,n);
}

int aux [1 << 20];
int *L = aux + (1 << 19);


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(i,m){
		scanf("%d",A + i);
	}
	deque<int> R(n+1,1);
	R[0] = 0;
//	print(R,int);
	loop(i,m){
		R.push_front(0);
		int lst = R.back();
		R.pop_back();
		R.back() += lst;

		int x = A[i];
		int cnt = R[x];
		R[x] = 0;
		if(x-1 > 0) R[x - 1] += cnt;
//		print(R,int);
	}

	R.push_front(0);
	int lst = R.back(); R.pop_back();
	R.back() += lst;

//	print(R,int);

	for(int x = 1;x <= n;x++) L[x] = 1;

	loop(i,m){
		L++;
		int lst = L[0];
		L[0] = 0;
		L[1] += lst;

		int x = A[i];
		int cnt = L[x];
		L[x] = 0;
		if(x + 1 <= n) L[x + 1] += cnt;
	}
	L++;
	lst = L[0];
	L[0] = 0;
	L[1] += lst;

//	print(R,int);
//	prArr(L,n+1,int);

	vi Rs,Ls;
	for(int x = 1;x <= n;x++)
		while(R[x]) {
			Rs.push_back(x);
			R[x]--;
		}
	for(int x = 1;x <= n;x++)
		while(L[x]) {
			Ls.push_back(x);
			L[x]--;
		}

	ll ans = 0;
	loop(i,min(sz(Ls),sz(Rs))){
		int l = Ls[i],r = Rs[i];
		ans += max(r-l+1,0);
//		cout << l  << " " << r  << " " << getR(i+1) << endl;
	}
	cout << ans << endl;
	return 0;
}
#endif
