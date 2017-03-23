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

int read(){
	int a,b; scanf("%d.%d",&a,&b);
	return b;
}


int main(){
	int n; scanf("%d",&n);
	int sum1 = 0,sum2 = 0,x = 0,y = 0;
	loop(i,2*n) {
		int a = read(); 
		sum2 += a;
		if(a == 0) x++;
		else y++;
	}
	//cerr << x << " " << y << endl;
	int ctr = 0;
	while(y > 1 && abs(sum1 + 1000 - sum2) < abs(sum1 - sum2)) sum1 += 1000,y -= 2,ctr++;
	while(x >= 2 && abs(sum1 + 1000 - sum2) < abs(sum1 - sum2) && ctr){
		sum1 += 1000;
		x -= 2;
		ctr--;
	}
	int diff = min(x,y);
	y = max(0,y - x);
	assert(y%2 == 0);
	while(y) sum1 += 1000,y -= 2;
	while(diff && abs(sum1 + 1000 - sum2) < abs(sum1 - sum2)){
		sum1 += 1000;
		diff--;
	}
	//cerr << sum1 << " " << sum2 << endl;
	
	int d = abs(sum1 - sum2);
	printf("%d.",d/1000);
	d %= 1000;	
	if(d < 100) putchar('0');
	if(d < 10) putchar('0');
	printf("%d",d);
	puts("");
	return 0;
}
