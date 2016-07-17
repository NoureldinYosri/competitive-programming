#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
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

vi out[250];
int done[250][250];

void construct(int k){
	int q = 1;
	for(;q <= k*(k - 1)/2;q++){
		bool c = 0;
		for(int i = 0;i < k && !c;i++){
			if(sz(out[i]) < k - 1){
				out[i].pb(q);
				loop(j,k) if(!done[i][j] && i != j){
					done[i][j] = done[j][i] = 1;
					out[j].pb(q);
					c = 1;
					break;
				}
			}
		}
	}
//	loop(i,k) {print(out[i],int);}
}

int f(ll k){
	return k*(k - 1)/2;
}

int main(){
	int n;
	scanf("%d",&n);
	int s = 3,e = n;
	while(s < e){
		int m = s + (e - s + 1)/2;
		if(f(m) <= n) s = m;
		else e = m - 1;
	}
	printf("%d\n",s);
	construct(s);
	loop(i,s){
		loop(j,s - 1) printf("%d%s",out[i][j],(j == s - 2) ? "\n" : " ");		
	}	
	return 0;
}
