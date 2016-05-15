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

const int MAX = 3e5;
int A[MAX],B[MAX],n,m;
vector<pi> ord;
int OUT[MAX];

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n){
		scanf("%d",A + i);
		B[i] = A[i];
	}
	loop(i,m){
		int a,b;
		scanf("%d %d",&a,&b);
		while(!ord.empty() && ord.back().yy <= b) ord.pop_back();
		ord.pb(mp(a,b));
	}
	int k1 = n - 1,k2 = n - 1,k3 = 0;
	if(!ord.empty()){
		for(;k2 > ord[0].yy - 1;){
			OUT[k1--] = A[k2--];
		}
		sort(B,B + ord[0].yy);
	}
	ord.pb(mp(0,0));
	for(int i = 0;i < sz(ord) - 1;i++){
		if(ord[i].xx == 1){
			while(ord[i].yy > ord[i + 1].yy){
				OUT[k1--] = B[k2--];
				ord[i].yy--;
			}
		}
		else{
			while(ord[i].yy > ord[i + 1].yy){
				OUT[k1--] = B[k3++];
				ord[i].yy--;
			}
		}
	}
	loop(i,n) printf("%d%s",OUT[i],(i == n - 1) ? "\n" : " ");
	return 0;
}
