#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
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

int L[5],R[5],n;
vi aux;

double greater_than(int i,int t){
	if(R[i] <= t) return 0;
	if(t < L[i]) return 1;
	return (R[i] - t)/(R[i] - L[i] + 1.0);
}

double less_eq(int i,int t){
	if(t < L[i]) return 0;
	if(R[i] <= t) return 1;
	return (t - L[i] + 1.0)/(R[i] - L[i] + 1.0);
}

double eq(int i,int t){
	if(L[i] <= t && t <= R[i]) return 1.0/(R[i] - L[i] + 1.0);
	else return 0;
}

double less_than(int i,int t){
	if(t <= L[i]) return 0;
	if(R[i] < t) return 1;
	return (t - L[i])/(R[i] - L[i] + 1.0);	
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",L + i,R + i);
	double ans = 0;
	range(t,1,10000){
		loop(msk,1 << n){
			if(!msk) continue;
			double tmp = 1;
			if(popcnt(msk)	> 1){
				loop(i,n) 
					if(msk & (1 << i)) tmp *= eq(i,t);
					else tmp *= less_than(i,t);	
		//		if(abs(tmp) > 1e-15) cerr << "s2 " << t << " " << tmp << endl;
				ans += tmp*t;
			}
			tmp = 1;
	
			loop(i,n) {
				if(msk & (1 << i)) tmp *= eq(i,t);
				else aux.pb(i);
			}
			for(int x : aux){
				double tmp2 = tmp * greater_than(x,t);
		//		if(abs(tmp2) > 1e-15) cerr << "s1 for " << x << " "  << t << " " << tmp2 << endl;
				for(int y : aux) if(x != y) tmp2 *= less_than(y,t);
				ans += tmp2 * t;
			}			
			aux.clear();
		}
	}
	printf("%.10f\n",ans);
	cerr << ans << endl;
	
	return 0;
}
