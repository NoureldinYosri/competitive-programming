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

const int MAX = 100;
int H[MAX],n,k;

struct cmp{
public:
	bool operator () (const int & a,const int & b){
		return tie(H[a],a) < tie(H[b],b);
	}
};


int main(){
	scanf("%d %d",&n,&k);
	if(n == 1){
		puts("0 0");
		return 0;
	}
	set<int,cmp> S;
	loop(i,n) scanf("%d",H + i),S.insert(i);	
	vp V;
	while(k--){
		int i = *S.begin(),j = *S.rbegin();
		if(abs(H[j] - H[i]) <= 1) break;
		S.erase(i),S.erase(j);
		V.pb(mp(j,i));
		H[j]--,H[i]++;
		S.insert(i);
		S.insert(j);
	}
	printf("%d %d\n",H[*S.rbegin()] - H[*S.begin()],sz(V));
	for(auto p : V) printf("%d %d\n",p.xx+1,p.yy+1	);
	return 0;
}
