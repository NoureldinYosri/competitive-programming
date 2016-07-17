#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
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


#define MAX (1 << 20)

char T[MAX];
char P[MAX];
int pf[MAX];
int n,m;


int GetLen(char c,int l){
	while(l && P[l] != c) l = pf[l - 1];
	if(P[l] == c) l++;
	return l;
}
 
void BuildFailure(){
	pf[0] = 0;
	range(i,1,n - 1) pf[i] = GetLen(P[i],pf[i - 1]);
}


int main(){
	int t;
	fgets(T,MAX,stdin);
	sscanf(T,"%d",&t);
	while(t--){
		fgets(T,MAX,stdin); m = strlen(T); T[--m] = '\0';
		fgets(P,MAX,stdin); n = strlen(P); P[--n] = '\0';
		BuildFailure();
		int l = 0,ans = -1;
		loop(i,m){
			l = GetLen(T[i],l);
			if(l == n){
				ans = i - n + 1;
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
