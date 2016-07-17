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

char name[10000];
pi ord[26];

int main(){	
	int T,L;
	scanf("%d",&T);	
	while(T--){
		scanf("%s",name);
		L = strlen(name);
		loop(i,26) ord[i] = mp(0,i + 'a');
		loop(i,L) ord[name[i] - 'a'].xx++;
		sort(ord,ord + 26);
		int s = 0;
		while(ord[s].xx == 0)s++;
		L = 26 - s;
		if(L & 1) printf("%c\n",(char)ord[s + (L >> 1)].yy);
		else printf("%c%c\n",(char)ord[s + (L >> 1) - 1].yy,(char)ord[s + (L >> 1)].yy); 
	//	while(s < 26) cerr << "(" << ord[s].xx << " ," << (char)(ord[s].yy) << ") ",s++;
	//	cerr << endl;
	}
	return 0;
}
