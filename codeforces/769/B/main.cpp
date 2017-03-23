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

const int MAX = 101;
int A[MAX],n,ord[MAX];

int main(){
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		ord[i] = i;
	}
	sort(ord + 1,ord + n,[](const int & a,const int & b){
		return A[a] > A[b];
	});
	int j = 1;
	vi have {0};
	vp tell;
	while(j < n){
		if(have.empty()){
			puts("-1");
			return 0;
		}
		int cur = have.back(); have.pop_back();
		while(j < n && A[cur]--){
			tell.emplace_back(cur + 1,ord[j] + 1);
			have.pb(ord[j++]);
		}
	}
	printf("%d\n",sz(tell));
	for(auto e : tell) printf("%d %d\n",e.xx,e.yy);
	return 0;
}
