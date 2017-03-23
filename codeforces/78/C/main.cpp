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

vi DIV;


int main(){
	int n,m,k;
	cin >> n >> m >> k;
	for(int i = 1;i*i <= m;i++)
		if(m%i == 0){
			DIV.pb(i);
			if(i*i != m) DIV.pb(m/i);
		}
	sort(all(DIV));
	reverse(all(DIV));
	while(!DIV.empty() && DIV.back() < k) DIV.pop_back();

	if(n%2 == 0 || DIV.size() <= 1) puts("Marsel");
	else puts("Timur");
	
	return 0;
}
