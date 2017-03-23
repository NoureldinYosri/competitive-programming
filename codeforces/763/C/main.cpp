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

const int MAX = 100*1000 + 10;
int A[MAX],n;
int B[MAX];
int pref[MAX],suff[MAX];

int main(){
	int mod; scanf("%d %d",&mod,&n);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	map<int,int> M;
	A[n] = A[0];
	loop(i,n){
		B[i] = A[i + 1] - A[i];	
		if(B[i] < 0) B[i] += mod;
		M[B[i]]++;
	}
	if(M.size() == 1){
		printf("%d %d\n",A[0],M.begin()->xx);
		return 0;	
	}
	if(M.size() == 2){
		if(min(M.begin()->yy,M.rbegin()->yy) == 1){
			int x = (M.begin()->yy == 1) ? M.begin()->xx : M.rbegin()->xx;
			int y = (M.begin()->yy == 1) ? M.rbegin()->xx : M.begin()->xx;
			loop(i,n){
				if(B[i] == x) {
					printf("%d %d\n",A[i + 1],y);
					return 0;
				}
			}
		}
	}
	puts("-1");
	return 0;
}
