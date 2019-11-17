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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


using DS = set<pair<double,pi>>;
const int MAX = 1 << 20;
double pos[MAX],lstTime[MAX];
int speed[MAX],n;
set<int> cars;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	vector<pi> I;
	loop(i,n){
		int s,v; scanf("%d %d",&s,&v);
		I.emplace_back(s,v);
	}
	sort(all(I));
	for(int i = 0;i < n;i++) {
		pos[i] = I[i].first;
		speed[i] = I[i].second;
//		cout << I[i] << endl;
		lstTime[i] = 0;
		cars.insert(i);
	}
	DS collisionTime;
	vector<DS::iterator> ptr(n,collisionTime.end());
	for(int i = 0;i+1 < n;i++){
		int dist = pos[i+1] - pos[i];
		int gain = speed[i] - speed[i+1];
		if(gain <= 0) continue;
		double t = dist*1.0/gain;
		ptr[i] = collisionTime.emplace(t,pi(i,i+1)).first;
	}
	double ans = 0;
	while(!collisionTime.empty()) {
		double ct = collisionTime.begin()->first;
		assert(ct >= ans - 1e-9);
		int j = collisionTime.begin()->second.first;
		int k = collisionTime.begin()->second.second;
//		printf("@%.3f %d %d\n",ct,j,k);

		collisionTime.erase(ptr[j]);
		auto itr = cars.find(j);
		assert(itr != cars.end());

		int i = -1;
		if(itr != cars.begin()) {
			auto itr2 = itr;
			itr2--;
			i = *itr2;
		}
		cars.erase(j);

		ans = ct;
		pos[k] += (ct - lstTime[k])*speed[k];
		lstTime[k] = ct;

		if(i == -1) continue;

		pos[i] += (ct - lstTime[i])*speed[i];
		lstTime[i] = ct;

		if(ptr[i] != collisionTime.end())
			collisionTime.erase(ptr[i]);
		ptr[i] = collisionTime.end();

		int gain = speed[i] - speed[k];
		double dist = pos[k] - pos[i];
		if(gain <= 0) continue;

		ptr[i] = collisionTime.emplace(ct + dist/gain,pi(i,k)).first;
	}


	printf("%.10f\n",ans);
	return 0;
}
