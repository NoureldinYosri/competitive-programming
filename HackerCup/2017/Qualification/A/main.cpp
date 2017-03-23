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

char out[][20] = {"white","black"};
const double PI = acos(-1);

int main(){
	int T; scanf("%d",&T);
	loop(t,T){
		int P,X,Y; scanf("%d %d %d",&P,&X,&Y); X -= 50,Y -= 50;
		int ans = -1;
		if(!X && !Y) ans = P > 0;
		else if(50*50 < X*X + Y*Y) ans = 0;
		else{
			double theta = atan2(Y,X);
			if(theta < 0) theta += 2*PI;
			if(theta < PI/2 || abs(theta - PI/2) < 1e-9) theta = PI/2 - theta;
			else {
				theta -= PI/2.0; theta = 2*PI - theta;
				assert(theta <= 2*PI || abs(theta - 2*PI) < 1e-9);
			}
			double phi = P/100.0 * 2*PI;
			ans = (theta < phi) || abs(theta - phi) < 1e-9;
		}
		assert(ans != -1);
		printf("Case #%d: %s\n",t+1,out[ans]);
	}		
	return 0;
}
