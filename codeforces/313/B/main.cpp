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

char buffer[1 << 20];
int n,m,l,r;
int ctr[1 << 20];

int f(int i){
	if(i == n-1) return 0;
	return buffer[i] == buffer[i + 1];
}

int main(){
	scanf("%s %d",buffer,&m);
	n = strlen(buffer);
	loop(i,n) ctr[i] = f(i) + (i ? ctr[i - 1] : 0);

	while(m--){
		scanf("%d %d",&l,&r); l--,r--; r--;
		printf("%d\n",ctr[r] - (l ? ctr[l - 1] : 0));
	}
	
	
	return 0;
}
