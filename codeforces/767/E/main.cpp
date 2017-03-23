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


const int MAX = 100'010;
ll W[MAX]; int n,C[MAX];
int X[MAX],Y[MAX];

struct cmp{
public:
	bool operator () (const int & a,const int & b){
		return tie(W[a],a) < tie(W[b],b);
	}
};
set<int,cmp> S;

int main(){
	int m; scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",C + i);
	loop(i,n) scanf("%lld",W + i);		
	ll ans = 0;
	loop(i,n){
		X[i] = C[i]/100;
		C[i]%=100;
		W[i] *= 100 - C[i];
		if(C[i]) S.insert(i);
		if(m < C[i] && !S.empty()){
			int j = *S.begin(); S.erase(S.begin());
			ans += W[j];
			if(j == i){
				m += 100 - C[j];
				X[j]++;
				continue;
			}
			m += 100;
			X[j]++;
			Y[j] = 0;
		}
		if(m < C[i]){
			m += 100 - C[i];
			Y[i] = C[i];
			ans += W[i];
			continue;
		}
		m -= C[i];
		Y[i] = C[i];
	}
	cout << ans << endl;
	loop(i,n) printf("%d %d\n",X[i],Y[i]);		
	
	return 0;
}
