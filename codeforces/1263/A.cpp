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



int A[3];


int bf(){
	vi V{A,A + 3};
	sort(all(V));
	int ret = 0;
	while(V[1]){
		ret++;
		V[1]--;
		V[2]--;
		sort(all(V));
	}
	return ret;
}

int solve(){
	int A[3];
	copy(::A, ::A + 3, A);
	sort(A,A + 3);
	int d = A[1] - A[0];
	int ret = d;
	A[1] -= d;
	A[2] -= d;
//	cout << d << endl;
//	prArr(A, 3, int);
	// d = A[2] - A[0]
	if(A[2] >= A[0] + A[1]){
		return ret + A[0] + A[1];
	}
	// A[2] - d = A[1] - d/2
	// d/2 = A[2] - A[1]
	d = 2*(A[2]-A[1]);
	int x = min(d/2, A[0]);
	int y = d - x;
	ret += d;
	A[0] -= x;
	A[1] -= y;
	A[2] -= d;
	assert(A[0] >= 0 && A[1] >= 0 && A[2] >= 0);
	sort(A, A + 3);
//	cout << d << endl;
//	prArr(A, 3, int);
	int k = A[0] - (A[0] & 1);
	ret += 3*k/2;
	A[0] -= k;
	A[1] -= k;
	A[2] -= k;
//	prArr(A, 3, int);
	while(A[1]){
		ret++;
		A[1]--;
		A[2]--;
		sort(A,A + 3);
	}
	
	return ret;	
}

void test(){
	for(int t = 0;t < 10000;t++){
		loop(i,3) A[i] = rand()%1000;
		if(solve() != bf()){
			cout << "failed on {" <<  A[0] << ", " << A[1] << ", " << A[2] << "}" << endl;
			exit(0);
		}
	}
	cout << "passed" << endl;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		loop(i,3) scanf("%d", A + i);

		printf("%d\n",solve());
	}
//	test();
/*	A[0] = 6;
	A[1] = 9;
	A[2] = 13;
	cout << bf() << endl;
	cout << solve() << endl;
*/	return 0;
}
