#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char s[20];
char out[20];

int main(){
	int T; ll n;
	scanf("%d",&T);
	while(T--){
		scanf(" IAO'%s",s); sscanf(s,"%lld",&n);
		ll y = 1989,p10 = 10,t;
		loop(i,strlen(s)) {
			y += p10;
			p10 *= 10;
		}
		if(s[0] == '9') y -= p10/10;
		cerr << y << " " << n << " " ;		
		sprintf(out,"%lld",y);
		sprintf(out + strlen(out) - strlen(s),"%s",s);
		sscanf(out + strlen(out) - strlen(s),"%lld",&t);
		printf("%s\n",out);
		cerr << out << endl;
	}
	return 0;
}
