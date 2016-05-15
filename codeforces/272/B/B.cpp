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

char s1[20],s2[20];
int n;
int F[20];

int main(){
	F[0] = 1; loop(i,19) F[i + 1] = F[i] * (i + 1);
	scanf("%s %s",s1,s2);	
	n = strlen(s1);
	int tot = 0,x = 0,ctr = 0;
	loop(i,n) tot += (s1[i] == '+') ? 1 : -1;
	loop(i,n){
		if(s2[i] == '+') x++;
		else if(s2[i] == '-') x--;
		else ctr++;
	}
	x = abs(x - tot);
	if(x > ctr || ((ctr - x) & 1)) puts("0");
	else {
		int b = (ctr - x) >> 1,tmp;
		tmp = F[ctr]/F[ctr - b]/F[b];
		printf("%.12f\n",tmp*1.0/(1 << ctr));
	}
	return 0;
}
