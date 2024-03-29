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


const int MAXN = 222;
int n;
char S[MAXN];
int A[MAXN];

bool solve(vi & tmp){
	int p = 0;
	loop(i,n){
		int x = A[i] ^ p;
//		cout << x << " ";
		p = 0;
		if(x) {
			p = 1;
			tmp.push_back(i+1);
		}
	}
//	cout << endl;
	return !p;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %s",&n,S);
	loop(i,n) A[i] = S[i] == 'W';
	
	bool f = 0;
	vi *res = 0;
	loop(p,2){
		loop(i,n) A[i] ^= p;
		vi tmp;
		if(solve(tmp)){
			f = 1;
			if(res) {
				if(tmp.size() < res->size())
					res = new vi(tmp);
			}
			else res = new vi(tmp);
		}
	}
	if(f){
		vi ans = *res;
		printf("%d\n",sz(ans));
		for(int x : ans) printf("%d ",x);
		puts("");
	}
	else puts("-1");
	return 0;
}
