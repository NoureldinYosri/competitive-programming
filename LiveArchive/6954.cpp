#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int main(){
	double n,p,s,v;
	while(scanf("%lf %lf %lf %lf\n",&n,&p,&s,&v) == 4){
		double m1,m2,f1,f2, st = 1e-15,e = 1e15;
		for(int i = 0;abs(e - st) > 1e-15 && i < 1000;i++){
		//	cout << st << " " << e << " ";			
			m1 = st + (e - st)/3.0;
			m2 = m1 + (e - st)/3.0;
			f1 = n*pow(log(n)/log(2),m1*sqrt(2))/(p * 1e9) + s/v * (1 + 1/m1);
			f2 = n*pow(log(n)/log(2),m2*sqrt(2))/(p * 1e9) + s/v * (1 + 1/m2);
		//	cout << m1 << " " << f1 << " " << m2 << " " << f2 << endl;
			if(!isfinite(f1)) e = m1 - 1e-15;
			else if(!isfinite(f2)) e = m2 - 1e-15;
			else if(f1 < f2) e = m2 - 1e-15;
			else st = m1 + 1e-15;
		}
		printf("%.15lf %.15lf\n",n*pow(log(n)/log(2),st*sqrt(2))/(p * 1e9) + s/v * (1 + 1/st),st);
	}
	return 0;
}

