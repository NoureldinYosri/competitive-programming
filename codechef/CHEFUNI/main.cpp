#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int S = 5;
int X,Y,Z,A,B,C;
bool debug = 0;
int dp[S + 1][S + 1][S + 1];

int solve(int x,int y,int z) {
	if(x == 0 && y == 0 && z == 0) return 0;
	if(x < 0 || y < 0 || z < 0) return 1 << 29;
	int & ret = dp[x][y][z];
	if(ret != -1) return ret;

	ret = min(solve(x - 1,y,z),min(solve(x,y-1,z),solve(x,y,z-1))) + A;
	ret = min(ret,min(solve(x - 1,y-1,z),min(solve(x,y-1,z-1),solve(x-1,y,z-1))) + B);
	ret = min(ret,solve(x-1,y-1,z-1) + C);
	return ret;
}

int plan2(int*,int,int ,int);

int plan1(int *r,int A,int B,int C) {
	if(debug) cerr << "plan1" << endl;
	// B <= 2*A and 3*B < 2*C
	// try to finish using only Bs
	C = min(C,3*A);
	C = min(C,A + B);

	int ret = 0;
	sort(r,r + 3);

	int steps = r[1] - r[0];
	ret += steps*B;
	r[1] -= steps;
	r[2] -= steps;


	int x = r[2] - r[1];
	if(r[2] < 2*x) x = min(r[0],r[2]/2);

	r[2] -= 2*x;
	r[1] -= x;
	r[0] -= x;

	ret += 2*x*B;

	sort(r,r + 3);
	int mn = r[0]/2;
	loop(i,3) r[i] -= 2*mn;
	ret += 3*B*mn;

	ret += r[0] * C;
	mn = r[0];
	loop(i,3) r[i] -= mn;

	int s = 0;
	loop(i,3) s += r[i] > 0;
	assert(s <= 1);

	ret += (r[0]  + r[1] + r[2]) * A;

	return ret;
}

int plan20(int *tr,int A,int B,int C) {
	int r[3];
	copy(tr,tr+3,r);
	sort(r,r + 3);
	assert(r[0] == r[1]);
	int x = r[2] - r[1];
	if(r[2] < 2*x) x = min(r[0],r[2]/2);
//	cerr << "x: " << x << endl;
//	prArr(r,3,int);

	r[2] -= 2*x;
	r[1] -= x;
	r[0] -= x;

	int ret = 2*x*B;
	sort(r,r + 3);
	ret += r[0] * C;
	r[1] -= r[0];
	r[2] -= r[0];
	r[0] = 0;

	ret += r[1] * B;
	r[2] -= r[1];
	r[1] = 0;

	ret += r[2]*A;
	return ret;
}

int plan2(int *r,int A,int B,int C){
	if(debug) cerr << "plan2" << endl;
	// B <= 2*A and 3*B > 2*C
	// try to finish using only Bs and Cs
	C = min(C,3*A);
	C = min(C,A + B);
	sort(r,r + 3);
	// make r[0] = r[1]
	int steps = r[1] - r[0];
	int a = steps*B;
	r[1] -= steps;
	r[2] -= steps;

	int b = plan20(r,A,B,C);


	int ret = 0;
	sort(r,r + 3);
	ret += r[0] * C;
	r[1] -= r[0];
	r[2] -= r[0];
	r[0] = 0;

	ret += r[1] * B;
	r[2] -= r[1];
	r[1] = 0;

	ret += r[2]*A;

	ret = min(ret + a,a + b);
	return ret;
}

int plan3(int *r,int A,int B,int C) {
	if(debug) cerr << "plan3" << endl;
	// B > 2*A
	// try to finish using only As and Cs
	C = min(C,3*A);
	C = min(C,A + B);

	int ret = r[0] * C;
	r[1] -= r[0];
	r[2] -= r[0];
	r[0] = 0;

	ret += (r[1] + r[2])*A;
	return ret;
}

int plan0(int *r,int A,int B,int C) {
	sort(r,r + 3);
	r[2] -= r[1];
	int ret = r[1] * B;
	r[1] = 0;
	sort(r,r + 3);
	r[2] -= r[1];
	ret += r[1] * B;
	r[1] = 0;

	ret += r[2] * A;
	return ret;
}

int solve(int X,int Y,int Z,int A,int B,int C){
	int r [] = {X,Y,Z},rt [] = {X,Y,Z};
	sort(r,r + 3);
	int ret = plan0(rt,A,B,C);
	if(B <= 2*A) {
		if(3*B <= 2*C) return min(ret,plan1(r,A,B,C));
		else return min(ret,plan2(r,A,B,C));
	}
	else return min(ret,plan3(r,A,B,C));
}




int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(_,1,T) {
		scanf("%d %d %d",&X,&Y,&Z);
		scanf("%d %d %d",&A,&B,&C);
		memset(dp,-1,sizeof dp);

		int ans = solve(X,Y,Z,A,B,C);
		printf("%d\n",ans);
	}
	return 0;
}

