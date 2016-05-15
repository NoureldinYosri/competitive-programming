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

int n;
int boy[5000][2],girl[5000][2];

int main(){
	scanf("%d",&n);
	char s[3];
	int b = 0,g = 0,a,bb;	
	loop(i,n){
		scanf("%s %d %d",s,&a,&bb);
		if(s[0] == 'M') {
			boy[b][0] = a;
			boy[b++][1] = bb;
		}
		else{
			girl[g][0] = a;
			girl[g++][1] = bb;
		}
	}

	
	int choice = 1,tot = -1;
	range(d,1,366){
		int ctr1 = 0,ctr2 = 0;
		loop(i,b) {
			if (boy[i][0] <= d && d <= boy[i][1]) ctr1++;
		}
		loop(i,g) {
			if (girl[i][0] <= d && d <= girl[i][1]) ctr2++;
		}
		ctr1 = 2*min(ctr1,ctr2);
		if(ctr1 > tot){
			tot = ctr1;
			choice = d;
		}
	}
	cout << tot << endl;
	return 0;
}
