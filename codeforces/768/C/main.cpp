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


int cnt[1024][2];
int aux[1024];
int A[1 << 20];
int main(){
	int n,k,x; scanf("%d %d %d",&n,&k,&x);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	loop(i,n) {
		int v = A[i];
		cnt[v][i & 1]++;
	}
	while(k--){
		loop(i,1024) aux[i] = cnt[i][1] + cnt[i^x][0];
		
		int sum = 0;
		loop(i,1024){
			cnt[i][0] = (aux[i] + 1 - (sum & 1))/2;
			cnt[i][1] = aux[i]  - cnt[i][0];
			sum += aux[i];
		}	
	}

	for(int i = 1023;i >= 0;i--) if(cnt[i][0] || cnt[i][1]){
		printf("%d ",i);
		break;
	}
	loop(i,1024) if(cnt[i][0] || cnt[i][1] ){
		printf("%d\n",i);
		break;
	}
	
	
	return 0;
}
