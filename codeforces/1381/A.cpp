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


char buffer[1 << 20];
void read(int n, vi & A){
	A.clear();
	scanf("%s", buffer);
	loop(i, n) A.push_back(buffer[i] - '0');
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	vi A, B, ans;
	deque<int> dq;
	while(T--){
		int n; scanf("%d", &n);
		read(n, A);
		read(n, B);
		ans.clear();
		dq.clear();
//		print(A, int);
//		print(B, int);
		loop(i, n) dq.push_back(i);
		for(int c = 0, mode = 0; n; n--){
			int target = B[n-1];
			int ime = (mode == 0) ? dq.back() : dq.front();
			int me = A[ime] ^ c;
			
			if(me != target){
				int i_zero = (mode == 0) ? dq.front() : dq.back();
				int zero = A[i_zero] ^ c;
				if(zero != me){
					ans.push_back(1);
					A[i_zero] ^= 1;
				}
				ans.push_back(n);
				c ^= 1;
				mode ^= 1;
			} 
			if(mode == 1) dq.pop_front();
			else dq.pop_back();
	//		cerr << "\t" << c  << " " << mode << endl;
		}
		
		printf("%d", sz(ans));
		for(int p : ans) printf(" %d", p);
		puts("");
	}
	return 0;
}
