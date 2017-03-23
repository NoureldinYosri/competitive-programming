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

const int MAX = 1e6 + 10;
const int MAXLG = 22;
int val[1 << MAXLG];
int ans[MAX],A[MAX];

void insert(int u){
	int msk = 0;
	loop(i,MAXLG) if(!(u & (1 << i))) msk |= 1 << i;
	val[msk] = u; 
}

int dfs(int msk){
	if(val[msk] != -2) return val[msk];
	val[msk] = -1;
	int omsk = (1 << MAXLG) - 1; omsk ^= msk;
	for(;omsk && val[msk] == -1;omsk ^= LSOne(omsk))
		val[msk] = dfs(msk | LSOne(omsk));
	return val[msk];
}

int main(){
	fill(val,val + (1 << MAXLG),-2);
	int n; scanf("%d",&n);	
	loop(i,n){
		scanf("%d",A + i);
		insert(A[i]);
	}
	loop(i,1 << MAXLG) if(val[i] == -2) dfs(i);
	loop(i,n) {
		int msk = 0;
		loop(j,MAXLG) if(A[i] & (1 << j)) msk |= 1 << j;
		printf("%d%c",val[msk]," \n"[i == n-1]);
	}
	return 0;
}
