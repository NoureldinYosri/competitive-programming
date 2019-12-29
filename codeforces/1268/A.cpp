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

int n,k;
vi A,B;
char buffer[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&k);
	scanf("%s",buffer);
	loop(i,n){
		int d = buffer[i] - '0';
		A.push_back(d);
		B.push_back(-1);
	}
	for(int i = 0;i < k;i++){
		int d = A[i];
		for(int j = i;j < n;j += k)
			B[j] = d;
	}
	if(B < A){
		int p = k-1;
		while(p >= 0 && B[p] == 9) p--;
		if(p == -1){
			B = vi(n+1,0);
			for(int i = 0;i < sz(B);i += k)
				B[i] = 1;
		}
		else {
			int d = B[p] + 1;
			for(int i = p;i < n;i += k)
				B[i] = d;
		}
	}
	if(sz(A) == sz(B)){
		int p = 0;
		while(p < k && B[p] == A[p]) p++;
		for(int i = p+1;i < k;i++)
			for(int j = i;j < n;j += k)
				B[j] = 0;		
	}
	printf("%d\n",sz(B));
	for(int x : B)
		printf("%d",x);
	puts("");
	return 0;
}
