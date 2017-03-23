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


void buildZ(char *P,int L,int *Z){
	int l = 0,r = 0;
	Z[0] = L;	
	range(i,1,L - 1){
		if(i > r){
			l = r = i;
			while(r < L && P[r - l] == P[r]) r++;
			Z[i] = r - l; 
			r--;
		}
		else{
			int k = i - l;
			if(Z[k] < r - i + 1) Z[i] = Z[k];
			else{
				l = i;
				while(r < L && P[r - l] == P[r]) r++;
				Z[i] = r - l;
				r--;
			}
		}
	}
}

const int MAX = 1 << 20;
int Z[MAX],n,k;
int valid[MAX];
int info[MAX];
char P[MAX];

int main(){
	scanf("%d %d %s",&n,&k,P);
	buildZ(P,n,Z + 1);
	//prArr(Z+1,n,int);
	int cur = 0;
	range(i,1,n){
		cur += info[i];
		valid[i] |= cur > 0;
		if(i%k) continue;
		int l = i/k,c = 1;
		for(int j = 1;j <= i;j += l)
			c &= Z[j] >= l;
		valid[i] |= c;
		if(c && i != n && Z[i + 1]){
			info[i + 1] ++;
			info[i + 1 + min(Z[i + 1],l)] --;				
			//i += Z[i + 1];
		}
	}
	range(i,1,n) printf("%d",valid[i]);
	puts("");
//	prArr(valid+1,n,int);
	return 0;
}
