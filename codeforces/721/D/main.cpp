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



const int MAX = 2'000'000 + 10;
ll A[MAX];
int n,k,x;


struct cmp{
public:
	bool operator () (const int & a,const int & b){
		return tie(A[a],a) < tie(A[b],b);
	}
};
set<int,cmp> pos,neg,zero;

void work_pos(int sgn = 1){
	int u;
	if(sgn == 1) u = *pos.begin();
	else u = *pos.rbegin();
	pos.erase(u);
	A[u] += sgn*x;
	if(A[u] > 0) pos.insert(u);
	else neg.insert(u);
	k--;
}

void work_neg(int sgn = 1){
	int u;
	if(sgn == 1) u = *neg.rbegin();
	else u = *neg.begin(); 
	neg.erase(u);
	A[u] -= sgn*x;
	if(A[u] > 0) pos.insert(u);
	else neg.insert(u);
	k--;
}

int main(){
	scanf("%d %d %d",&n,&k,&x);
	ll mn = LLONG_MAX,mx = LLONG_MIN;	
	loop(i,n) {
		scanf("%lld",A + i),mn = min(mn,A[i]),mx = max(mx,A[i]);
		if(A[i] > 0) pos.insert(i);
		else if(A[i] < 0) neg.insert(i);
		else zero.insert(i);
	}
	while(!zero.empty() && sz(neg)%2 == 0 && k){
		int u = *zero.begin();
		zero.erase(u);
		A[u] -= x;
		neg.insert(u);
		k--;
	}
	while(!zero.empty()){
		int u = *zero.begin();
		zero.erase(u);
		A[u] += x;
		pos.insert(u);
		k--;
	}
	if(sz(neg)%2 == 0 && !pos.empty()){
		int u = *pos.begin();
		if((A[u] + x)/x <= k){
			pos.erase(u);
			k -= (A[u] + x)/x;
			A[u] -= ((A[u] + x)/x)*x;
			neg.insert(A[u]);
		}
	}
	if(sz(neg) & 1){
		while(k){
			if(pos.empty() && neg.empty()) break;
			else if(pos.empty()){
				work_neg();
			}
			else if(neg.empty()) {
				work_pos();
			}
			else {
				if(A[*pos.begin()] < abs(A[*neg.rbegin()])) {
					work_pos();
				}
				else {
					work_neg();
				}
			}
		}
	}
	else if(k){
		bool is_zero = 0;
		loop(i,n) is_zero |= A[i] == 0;
		if(!is_zero){
			loop(i,n){
				if(abs(A[i])%x == 0 && abs(A[i])/x <= k) A[i] = 0,is_zero = 1;
				if(is_zero) break;
			}
		}
		if(!is_zero){
			while(k){
				if(pos.empty() && neg.empty()) break;
				else if(!pos.empty()) work_pos(-1);
				else if(!neg.empty()) work_neg(-1);
				else {
					int u = *neg.begin(),v = *pos.rbegin();
					if(abs(u) > abs(v)) work_neg(-1);
					else work_pos(-1);		
				}				
			}
		}
	}
	loop(i,n) printf("%lld%c",A[i]," \n"[i==n-1]);
	return 0;
}
