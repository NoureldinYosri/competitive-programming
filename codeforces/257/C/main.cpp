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
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const double PI = acos(-1);

int ccw(pi a,pi b){
	return a.xx*b.yy - a.yy *b.xx;
}

bool cmp(const pi & a,const pi & b){
	if(a.yy > 0 && b.yy > 0) return ccw(a,b) > 0;
	if(a.yy < 0 && b.yy < 0) return ccw(a,b) > 0;
	if(a.yy > 0 && b.yy < 0) return 1;
	if(a.yy < 0 && b.yy > 0) return 0;
	assert(!a.yy || !b.yy);
	if(!a.yy && !b.yy) return a.xx > b.xx;
	else if(!a.yy) {
		if(a.xx > 0) return 1;
		return b.yy < 0;
	}
	else{
		if(b.xx > 0) return 0;
		return a.yy > 0;
	}
}

double get_angle(pi p){
	double t = atan2(p.yy,p.xx);
	if(t < 0) t += 2*PI;
	return t*180/PI;
}

int main(){
	int n; scanf("%d",&n);
	vp P(n);
	loop(i,n) scanf("%d %d",&P[i].xx,&P[i].yy);
	sort(all(P),&cmp);
	
	//for(auto p : P) prp(p);
	//cerr << endl;

	double ans = get_angle(P.back());	
	loop(i,n-1) ans = min(ans,360 - get_angle(P[i + 1]) + get_angle(P[i]));
	ans = min(ans,-get_angle(P[0]) + get_angle(P.back()));
	cerr << ans << endl;
	printf("%.10f\n",ans);	
	
	return 0;
}
