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
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 100'000 + 10;
int A[MAX],B[MAX],ord1[MAX],ans[MAX],n;
int C[MAX],D[MAX],E[MAX],ord2[MAX],cnt[MAX],m;
set<pi> alive;

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",A + i,B + i),ord1[i] = i;
	scanf("%d",&m);
	loop(i,m) scanf("%d %d %d",C + i,D + i,E + i),ord2[i] = i;
 	
	sort(ord1,ord1 + n,[](const int & a,const int & b){
		return A[a] < A[b];
	});
	sort(ord2,ord2 + m,[](const int & a,const int & b){
		return C[a] < C[b];
	});
	int i = 0,j = 0;
	for(;i < n;i++){
		while(j < m && C[ord2[j]] <= A[ord1[i]]) alive.insert(mp(D[ord2[j]],ord2[j])),j++;
		auto p = alive.lower_bound(mp(B[ord1[i]],-1));
		if(p == alive.end()){
			puts("NO");
			return 0;
		}
		ans[ord1[i]] = p->yy + 1;
		cnt[p->yy]++;
		if(cnt[p->yy] == E[p->yy]) alive.erase(p);
	}
	puts("YES");
	loop(i,n) printf("%d%c",ans[i]," \n"[i==n-1]);
	//prArr(ans,n,int);
	return 0;
}
