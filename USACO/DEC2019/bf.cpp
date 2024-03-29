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


int n,m;
int W[100];
int ord[100];
int L[100],R[100];
bool taken[100];

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#else
//	freopen("pieaters.in", "r", stdin);
//	freopen("pieaters.out", "w", stdout);
#endif
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%d %d %d",W + i,L + i,R + i);
		ord[i] = i;
		L[i]--,R[i]--;
	}
	int ans = 0;
	do{
		int tmp = 0;
		fill(taken,taken + m,0);
		loop(j,n){
			int i = ord[j];
			bool alive = 0;
			for(int k = L[i];k <= R[i];k++){
				alive |= !taken[k];
				taken[k] = 1;
			}
			tmp += W[i] * alive;
		}
		ans = max(ans,tmp);
	}while(next_permutation(ord, ord + n));
	cout << ans << endl;
	return 0;
}
