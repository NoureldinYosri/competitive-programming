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

int n;
ll F[51],k;

int main(){
	F[0] = F[1] = 1;
	for(int i = 2;i <= 50;i++) F[i] = F[i - 1] + F[i - 2];
	
	cin >> n >> k;
	set<int> S;
	loop(i,n) S.insert(i + 1);
	
	loop(i,n){
		auto p = S.begin();
		if(k > F[n - i - 1]) ++p,k -= F[n - i - 1];
		printf("%d%c",*p," \n"[i == n-1]);
		S.erase(p);
	}
	
	
	return 0;
}
