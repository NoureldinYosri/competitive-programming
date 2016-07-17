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

const int MAX = 1 << 20;
pl A[MAX];
char line[MAX];
ll n,SQRT;
ll S ;


void preprocess(){
	S = 0;
	loop(i,n) S += A[i].xx;
	SQRT = sqrt(S + 0.0) + 10.0;
	while(SQRT*1LL*SQRT > S) SQRT--;
}

void read_input(){
	scanf("%s",line);
	int L = strlen(line); n = 0;
	loop(i,L){
		int j = i;
		while(isdigit(line[j])) j++;
		A[n].yy = line[j] == 'T';
		line[j] = 0;
		sscanf(line + i,"%lld",&A[n++].xx);
		i = j;
	}
	preprocess();
}

ll solve(){
	ll ans1 = 0,ans2 = 0;
	ll remaining = SQRT,zeros = 0,ones = 0,p = 0;
	loop(i,n){
		if(A[i].xx == 0) continue;
		if(remaining != SQRT){
			if(A[i].xx < remaining){
				remaining -= A[i].xx;
				ones += A[i].xx*A[i].yy;
				zeros += A[i].xx*(1 - A[i].yy);
			}
			else{
				A[i].xx -= remaining;
				ones += remaining*A[i].yy;
				zeros += remaining * (1 - A[i].yy);
				if(p) ans1 += ones,ans2 += zeros;
				else  ans1 += zeros,ans2 += ones;
				remaining = SQRT;
				ones = zeros = 0;
				p ^= 1;
				i--;
			}
		}
		else{
			ll tmp = A[i].xx/SQRT;
			ans1 += (tmp/2)*SQRT;
			ans2 += (tmp/2)*SQRT;
			if(tmp & 1){
				if(A[i].yy) {					
					if(p) ans1 += SQRT;
					else ans2 += SQRT;
				}
				else{
					if(p) ans2 += SQRT;
					else ans1 += SQRT;
				}
				p ^= 1;	
			}
			remaining = SQRT - A[i].xx%SQRT;
			ones = (SQRT - remaining)*A[i].yy;
			zeros = (SQRT - remaining)*(1 - A[i].yy);
		}
	}
	if(p) ans1 += ones,ans2 += zeros;
	else ans1 += zeros,ans2 += ones;
	return max(ans1,ans2);
}


int main(){
//	freopen("doomed.in","r",stdin);	
	int T;
	scanf("%d",&T);
	while(T--){
		read_input();
		printf("%lld\n",solve());		
	}
	return 0;
}
