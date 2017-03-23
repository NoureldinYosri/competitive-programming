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

const int MAX = 2000010;
int A[MAX],n,m;
int len[MAX],pos[MAX];
vector<vi> lis;	

auto cmp = [](const vi & v,const int & b){
	return A[v.back()] < A[b];
};

void work(int i){
	if(lis.empty() || A[lis.back().back()] < A[i]) {
		lis.pb(vi{i});
		pos[i] = sz(lis) - 1;
	}
	else {
		auto p = lower_bound(all(lis),i,cmp);
		p->pb(i);
		pos[i] = p - lis.begin();
	}
	len[i] = sz(lis);
}

int main(){
	scanf("%d %d",&n,&m);
	vi ST;
	loop(i,n) {
		scanf("%d",A + i);
		work(i);
		ST.pb(i);
	}
	int M = n;
	loop(i,m){
		int t; scanf("%d",&t);
		if(t == 1){
			scanf("%d",A + M);
			work(M);
			ST.pb(M++);
		}
		else {
			int N = ST.back(); ST.pop_back();		
			assert(lis[pos[N]].back() == N);
			lis[pos[N]].pop_back();
			if(lis[pos[N]].empty()){
				assert(pos[N] == sz(lis) - 1);
				lis.pop_back();
			}	
		}
		printf("%d\n",ST.empty() ? 0 : len[ST.back()]);
	}
	
	return 0;
}
