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
 
int A[1024],n,k;
 
int main(){
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%d",A + i);
	int ans = 0;
	if(n == 1){
	
	}	
	else{
		range(i,1,n-1) {
			ans += max(k - (A[i] + A[i - 1]),0);
			A[i] += max(k - (A[i] + A[i - 1]),0);
		}
	}
	printf("%d\n",ans);
	loop(i,n) printf("%d%c",A[i]," \n"[i==n-1]);
	return 0;
}
