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


char out[][20] = {"cslnb", "sjfnb"};
int A[1 << 20], n;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i, n) scanf("%d",A + i);
	sort(A, A+n);
	int problems = 0;
	int c = -1;
	for(int i = 0;i < n;){
		int j = i;
		while(j < n && A[i] == A[j]) j++;
		problems += j-i-1;
		if(j-i-1) c = i;
		i = j;
	}
	if(problems > 1){
		puts(out[0]);
		return 0;
	}
	int flag = 0,d = 0;
	if(problems == 1){
		if(A[c] == 0){
			puts(out[0]);
			return 0;
		}
		assert(c >= 0);
		A[c]--;
		if(c && A[c] == A[c-1]){
			puts(out[0]);
			return 0;
		}
		flag = 1;
	}
	loop(i, n){
		if(A[i] < i){
			d = 0;
			break;
		}
		d ^= (A[i] - i) & 1;
	}
	d ^= flag;
	puts(out[d]);
	return 0;
}
