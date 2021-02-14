#pragma GCC optimize ("O3")
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
using namespace std;

vi idx[1 << 20];
int A[1 << 20];
int n;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n){
		scanf("%d", A + i);
		idx[A[i]].push_back(i);
	}
	loop(x, n + 1) idx[x].push_back(n);
	int ans = 0;
	array<int, 2> B = {0, 0};
	
	loop(i, n){
		int a = A[i];
		if(B[0] != a && B[1] != a){
			int j = *upper_bound(all(idx[B[0]]), i);
			int k = *upper_bound(all(idx[B[1]]), i);
			ans++;	
			if (j < k){
				B[0] = a;
			} else {
				B[1] = a;
			}
		} else if(B[0] != a){
			B[0] = a;
			ans++;
		} else {
			ans += B[1] != a;
			B[1] = a;
		}
	}
	
	
	cout << ans << endl;
	return 0;
}
