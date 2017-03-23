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

const int MAX = 1 << 20;
int n,l,x,y;
int A[MAX];

int main(){
	scanf("%d %d %d %d",&n,&l,&x,&y);
	loop(i,n) scanf("%d",A + i);
	bool foundX = 0,foundY = 0,foundXY = 0,foundXY2 = 0,foundXY3 = 0;
	int k,k2,k3;
	loop(i,n){
		foundX |= binary_search(A,A + n,A[i] + x);
		foundY |= binary_search(A,A + n,A[i] + y);
		if(binary_search(A,A + n,A[i] + x + y) ) {
			foundXY = 1;
			k = i;
		}
		if(A[i] + y <= l){
			if(binary_search(A,A + n,A[i] + y - x)) {
				foundXY2 = 1;
				k2 = i;
			}
		}
		if(A[i] >= x){
			if(binary_search(A,A + n,A[i] - x + y)) {
				foundXY3 = 1;
				k3 = i;
			}
		}
	}
	if(foundX && foundY) puts("0");
	else if(!foundX && !foundY){
		if(foundXY) printf("1\n%d\n",A[k] + x);
		else if(foundXY2) printf("1\n%d\n",A[k2] + y);
		else if(foundXY3) printf("1\n%d\n",A[k3] - x);
		else printf("2\n%d %d\n",x,y);
	}
	else if(!foundX) printf("1\n%d\n",x);
	else printf("1\n%d\n",y);	
	
	return 0;
}
