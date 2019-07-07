#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const double PI = acos(-1),EPS = 1e-9;
int n,L[1000];

double get_angle(double r,int L,int R) {
	double ret = 0;
	for(int i = L;i <= R;i++) {
		double ct = 1 - ::L[i]*::L[i]/(2*r*r);
		double t = acos(ct);
		assert(t == t);
		ret += t;
	}
	return ret;
}



double get_lower(int l,int r) {
	// return max(L[i])/2
	double mx = 0;
	range(i,l,r) mx = max(mx,L[i] + 0.0);
	return mx/2;
}
double get_upper(int l,int r) {
	double sum = 0;
	range(i,l,r) sum += L[i];
	return sum/2;
}

bool can_build(int l,int r) {
	int sum = 0,mx = 0;
	range(i,l,r) {
		sum += L[i];
		mx = max(mx,L[i]);
	}
	sum -= mx;
	return sum > mx;
}

bool leq(double a,double b) {
	return a < b || abs(a - b) < EPS;
}

bool is_center_inside(int l,int r){
	double Rmin = get_lower(l,r);
	double ang = get_angle(Rmin,l,r);
	return leq(2*PI,ang);
}

double getRinside(int l,int r) {
	double s = get_lower(l,r),e = get_upper(l,r);
	for(int i = 0;i < 64 && s < e;i++) {
		double mid = s + (e-s)/2.0;
		double ang = get_angle(mid,l,r);
		if(leq(ang,2*PI)) e = mid;
		else s = mid;
	}
	return s;
}

double get_side_angle(double x,double r) {
	double c = 1 - x*x/(2*r*r);
	double t = acos(c);
	assert(t == t);
	return t;
}

double get_upper_out(int l,int r) {
	return get_upper(l,r) * 10 ;
}

double f(double R,int l,int r) {
	int mx = *max_element(L+l,L+r+1);
	return get_angle(R,l,r) - 2*get_side_angle(mx,R);
}

double getRoutside(int l,int r) {
	double s = get_lower(l,r),e = get_upper_out(l,r);
	int mx = *max_element(L + l,L + r + 1);
	for(int i = 0;i < 64 && s < e;i++) {
		double mid = s + (e-s)/2.0;
		double ang = get_angle(mid,l,r),mxt = get_side_angle(mx,mid);
		ang -= mxt;
		if(ang < mxt) s = mid;
		else e = mid;
	}
	return s;
}

double get_area(int l,int r) {
	if(!can_build(l,r)) return 0.0;
	double R = 0,area = 0.0;
	if(is_center_inside(l,r)) {
		R = getRinside(l,r);
		range(i,l,r) {
			double c = 1 - (L[i]*L[i])/(2*R*R);
			double t = acos(c);
			assert(t == t);
			area += sin(t);
		}
	}
	else {
		int mx = 0,mxc = 0;
		range(i,l,r) {
			if(L[i] > mx) mx = L[i],mxc = 0;
			mxc += L[i] == mx;
		}
		assert(mxc == 1);
		R = getRoutside(l,r);
		range(i,l,r) {
			double c = 1 - (L[i]*L[i])/(2*R*R);
			double t = acos(c);
			assert(t == t);
			if(L[i] == mx)
				area -= sin(t);
			else
				area += sin(t);
		}
//		double ang = get_angle(R,l,r),mxt = get_side_angle(mx,R);
//		ang -= mxt;
//		cerr << ang << " " << mxt << " \t " << ang*180/PI << " -> " << area  << endl;
//		cerr << get_lower(l,r) << " " << get_upper_out(l,r) << " " << R << endl;
//		cerr << abs(ang - mxt) << endl;
	}
	area *= 0.5*R*R;
//	prArr(L+l,r-l+1,int);
//	cerr << area << endl;
	return area;
}

double dp[1000][1000];
double solve(int s,int e) {
	if(e-s <= 1) return 0;
	double & ret = dp[s][e];
	if(ret == ret) return ret;
	ret = get_area(s,e);
	int mxi = s,mxc = 0;
	for(int k = s;k <= e;k++) {
		if(L[k] > L[mxi])
			mxi = k,mxc = 0;
		mxc += L[k] == L[mxi];
	}
	if(mxc == 1)
		ret = max(ret,solve(s,mxi-1) + solve(mxi+1,e));
	return ret;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int t = 1; scanf("%d",&n) == 1 && n;t++) {
		loop(i,n) scanf("%d",L + i);
		loop(i,n) L[i + n] = L[i];
		memset(dp,-1,sizeof dp);
		double ans = solve(0,n-1);
		printf("Case %d: %.6f\n",t,ans);
	}
	return 0;
}
#endif
