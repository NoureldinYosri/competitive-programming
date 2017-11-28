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
#define popcnt(x) __builtin_popcount(x)
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


const int MAX = 25*1000;
double POW[MAX + 10];



void get(double & alpha,double & beta,int l,int w){
	//alpha / POW[l] + beta = 0
	//alpha * POW[w] + beta = 1
	double c = POW[w] - 1/POW[l];
	alpha = 1/c;
	beta = 1 - alpha*POW[w];
}


int main(){
	double x ,p;
	while(scanf("%lf %lf",&x,&p) == 2){
		x /= 100;
		p /= 100;
		double base = (1 - p)/p;
		POW[0] = 1;
		for(int i = 1;i <= MAX;i++){
			POW[i] = POW[i - 1] * base;
			if(POW[i] < 1e-50) POW[i] = 0;
		}
/*		double ans = 0.0;
		for(int l = 0;l <= MAX;l++)
			for(int w = l==0;w <= 2500;w++){
				double alpha,beta;
				double c = POW[w] - 1/POW[l];
				alpha = 1/c;
				beta = 1 - alpha*POW[w];

				double p = alpha + beta;
				double profit = p*w - (1-p)*(1-x)*l;
				ans = max(ans,profit);
			}
*/
		double alpha,beta,c,f,p,ans = 0.0;
		for(int w = 0;w <= 2500;w++){
			int s = w==0,e = MAX;
			while(s < e){
				int l = (s + e) >> 1;
				c = POW[w] - 1/POW[l];
				alpha = 1/c;
				beta = 1 - alpha*POW[w];
				p = alpha + beta;
				f = p*w - (1-p)*(1-x)*l;
				l++;
				c = POW[w] - 1/POW[l];
				alpha = 1/c;
				beta = 1 - alpha*POW[w];
				p = alpha + beta;
				f = p*w - (1-p)*(1-x)*l - f;
				l--;
				if(f <= 0) e = l;
				else s = l + 1;
			}
			int l = s;
			c = POW[w] - 1/POW[l];
			alpha = 1/c;
			beta = 1 - alpha*POW[w];
			p = alpha + beta;
			f = p*w - (1-p)*(1-x)*l;
			ans = max(ans,f);
		}

		printf("%.9f\n",ans);
	}


}

