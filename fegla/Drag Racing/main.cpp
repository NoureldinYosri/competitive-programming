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
#define pl pair<ll,ll>
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


double s,ta,tb,d;

int main(){
	freopen("race.in", "r", stdin);
	int T; cin >> T;
	while(T--){
		cin >> s >> ta >> tb >> d;
		double ac = 60/ta,dc = 60/tb;
		double up = s/ac,down = s/dc;
		double ans = -1;
		if(0.5*ac*pow(up,2) + 0.5*dc*pow(down,2) <= d){
			double st = up + down,en = 1e9;
			for(int i = 0;i < 64 && en - st > 1e-9;i++){
				double m = st + (en - st)/2.0,dist = 0;
				dist = 0.5*ac*pow(up,2) + 0.5*dc*pow(down,2);
				dist += s*(m - up - down);
				if(dist >= d) en = m;
				else st = m;
			}
			ans = en;
		}
		else{
			double st = 0,en = s;
			for(int i = 0;i < 64 && en - st > 1e-9;i++){
				double m = st + (en - st)/2.0;
				double t1 = m/ac,t2 = m/dc;
				if(0.5*m*t1 + 0.5*m*t2 >= d) en = m;
				else st = m;
			}

			ans = en/ac + en/dc;
		}
		printf("%.9f\n",ans);;
	}
	return 0;
}
