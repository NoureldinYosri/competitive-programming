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

char P[1 << 20],T[1 << 10], U[1 << 20];
int Z[1 << 20];
int main(){
	scanf("%s %s",P,T);
	strcpy(U,T);
	int L = strlen(U);
	U[L++] = '$';
	strcpy(U + L,P);
	L = strlen(U);
	int l = 0, r = 0;
	loop(i,L) {
 		if (r < i) {
  			l = i;
			r = i;
    			while (r < L && U[r-l] == U[r]) r++;
    			Z[i] = r-l; r--;
  		} else {
    			int k = i-l;
    			if (Z[k] < r-i+1) Z[i] = Z[k];
    			else {
      				l = i;
      				while (r < L && U[r-l] == U[r]) r++;
      				Z[i] = r-l;
				r--;
    			}
  		}
	}
	int s = strlen(T) + 1,n = strlen(T);
	int ans = 0;	
	while(s < L){
		if(Z[s] == n) {
			ans ++;
			s += n;
		}
		else s++;
	}
	cout << ans << endl;
	return 0;
}
