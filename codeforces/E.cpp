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
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int n,A[1 << 20];
double f(double x){
	double ans = 0,s1 = 0,s2 = 0;
	loop(i,n){
		s1 += A[i] - x;
		ans = max(ans,s1);
		s1 = max(s1,0.);
		s2 += A[i] - x;
		ans = max(ans,-s2);
		s2 = min(0.,s2);
	}
	//cout << s1 << " " << s2 << " " << x << " " << ans << endl;
	return ans;
}


int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	double s = -10000,e = 10000,m1,m2;
	for(int i = 0;i < 500 && abs(e - s) > 1e-8;i++){
	//	cout << s << " " << e << endl;
		m1 = s + (e - s)/3;
		m2 = m1 + (e - s)/3;
		if(f(m1) < f(m2)) e = m2 - 1e-8;
		else s = m1 + 1e-8;
	}
	printf("%.15f\n",min(f(s),f(e)));
	return 0;
}
