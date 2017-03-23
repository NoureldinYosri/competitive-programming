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
int S[MAX],n,sk;
double P[MAX],SP[MAX];

int get(int i,int s){
	if(S[s] <= S[i] - sk) return -1;
	int e = n-1;
	while(s < e){
		int m = s + (e - s + 1)/2;
		if(S[m] > S[i] - sk) s = m;
		else e = m - 1;
	}
	return s;
}

int main(){
	scanf("%d %d",&n,&sk);
	loop(i,n) scanf("%d",S + i);
	loop(i,n) scanf("%lf",P + i),SP[i] = 1 - P[i] + (i ? SP[i - 1] : 0);
	double ans = 0.0;	
	loop(i,n){
		int j = i;
		while(j < n && S[i] == S[j]) j++;
		if(j == n) break;
		int p = get(i,j);
		if(p == -1){
			i = j - 1;
			continue;
		}
		for(;i < j;i++)
			ans += P[i] * (SP[p] - SP[j - 1]);			
		i--;
	}
	cerr << ans << endl;
	printf("%.10f\n",ans);
	return 0;
}
