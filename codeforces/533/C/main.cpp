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

const int MAXN = 30;
int xp,yp,xv,yv;
string out[2] = {"Vasiliy","Polycarp"};

struct brute_force{
	int dp[MAXN][MAXN][MAXN][MAXN][2];
public:
	brute_force(){
		memset(dp,-1,sizeof dp);
	}
	int solve(int x_cur,int y_cur,int x_other,int y_other,int turn){
		if(x_cur == 0 && y_cur == 0) return 1;
		int & ret = dp[x_cur][y_cur][x_other][y_other][turn];
		if(ret != -1) return ret;
		ret = 0;
		if(x_cur && mp(x_cur-1,y_cur) != mp(x_other,y_other))
			ret |= 1 - solve(x_other,y_other,x_cur - 1,y_cur,turn ^ 1);
		if(y_cur && mp(x_cur,y_cur-1) != mp(x_other,y_other))
			ret |= 1 - solve(x_other,y_other,x_cur,y_cur - 1,turn ^ 1);
		if(x_cur && y_cur && !turn && mp(x_cur - 1,y_cur - 1) != mp(x_other,y_other))
			ret |= 1 - solve(x_other,y_other,x_cur - 1,y_cur - 1,1);
		return ret;
	}

};


struct optimal_solver{
public:
	int solve(int xp,int yp,int xv,int yv){
		if(xp == 0 && yp == 0) return 1;
		if(xv <= xp && yv <= yp) return 0;
		if(xp + yp > xv + yv) return 0;
		int distp = xp + yp,distv = max(xv,yv);
		if(distp <= distv) return 1;
		if(yp == yv && xp < xv) return 1;
		if(xp == xv) return 1;
		if(xp < xv) {
			int d = xv - xp;
			if(yv == yp + d || yv == yp + d + 1) return 1;
			if(yv >= yp + 1) return 1;
			return 0;
		}
		return 0;
	}
};


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> xp >> yp >> xv >> yv;
	auto solver = optimal_solver();

#ifdef BUILDING_OPT
/*	const int MAX = MAXN;
	auto solver1 = brute_force();
	auto solver2 = optimal_solver();
	for(xp = 0;xp < MAX;xp++)
		for(yp = 0;yp < MAX;yp++)
			for(xv = 0;xv < MAX;xv++)
				for(yv = 0;yv < MAX;yv++){
					if(xp == xv && yp == yv) continue; // invalid case
					// done cases
					if(xp == 0 && yp == 0) continue;
					if(xv <= xp && yv <= yp) continue;
					if(xp + yp > xv + yv) continue;
					int distp = xp + yp ,distv = max(xv,yv);
					if(distp <= distv) continue;
					if(yp == yv && xp < xv) continue;
					if(xp == xv) continue;
					if(xp < xv) {
						int d = xv - xp;
						if(yv == yp + d || yv == yp + d + 1) continue;
						if(yv >= yp + 1) continue;
						continue;
					}
					int ret = solver.solve(xp,yp,xv,yv,1);
					if(ret) cerr << yv - yp << " " <<  xp << " " << yp << " " << xv << " " << yv << " -> " << ret << endl;
	//				cerr<< ((xv - xp)%2 + 2)%2 << " " << ((yv - yp)% + 2)%2 << " -> " << ret << endl;
	//				cerr << distp << " " << distv << " -> " << ret << endl;
			//		assert(ret == 1);
				//	assert((xp < xv) || (yp < yv));
					if(xp < xv) assert(ret == 0);

					assert(solver1.solve(xp,yp,xv,yv,1) == solver2.solve(xp,yp,xv,yv));
*/				}
#endif
	cout << out[solver.solve(xp,yp,xv,yv)] << endl;
	return 0;
}
