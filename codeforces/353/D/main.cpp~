#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

int n,A[1 << 20];
set<int> open;
map<int,int> ctr;
set<int> RRRR;

void f(set<int>::iterator p,int x){
	printf("%d ",*p);
	//cerr << *p << endl;
	ctr[*p]++;
	//if(ctr[*p] == 2) open.erase(p);
	ctr[x] = 0;
	open.insert(x);
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	open.insert(A[0]); 
	ctr[A[0]] = 0;
	range(i,1,n - 1){
		auto q = open.upper_bound(A[i]);
		if(q == open.begin()) f(q,A[i]);
		else {
			auto p = q; --p;
			if(q == open.end()) f(p,A[i]),RRRR.insert(*q);
			else{
				if(RRRR.find(*p) == RRRR.end()) f(p,A[i]),RRRR.insert(*p);
				else f(q,A[i]);
			}
		}	
	}
	return 0;
}
