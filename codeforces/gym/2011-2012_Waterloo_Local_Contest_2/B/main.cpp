#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

ll x,y,v;
int T;
char z[1 << 20];
int main(){
	scanf("%d",&T);
	while(T--){
		cin >> x >> y >> z;
		v = 0;		
		loop(i,strlen(z)) v = v*x + (isdigit(z[i]) ? (z[i] - '0') : (z[i] - 'A' + 10));
		int i = 0;
		while(v){
			int q = v%y;
			if(q <= 9) z[i++] = q + '0';
			else z[i++] = q + 'A' - 10;
			v /= y;
		}
		if(i) z[i] = '\0';
		else z[i++] = '0',z[i] = '\0';
		reverse(z,z + i);		
		puts(z);
	}	
	return 0;
}