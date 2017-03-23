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

char T[100*1000 + 1],P[100][1000 + 1];
int n,L,len[100],pf[100][1000];
int mx[100][100*1000 + 1],soFar[100];
int can[100];

int GetLen(char c,int l,char *P,int *pf){
	while(l && P[l] != c) l = pf[l - 1];
	if(P[l] == c) l++;
	return l;
}
void BuildFailure(char *P,int *pf){
	pf[0] = 0;
	for(int i = 1;P[i];i++) pf[i] = GetLen(P[i],pf[i - 1],P,pf);
}


int main(){
	scanf("%s %d",T,&n); L = strlen(T);
	loop(i,n){
		scanf("%s",P[i]);
		len[i] = strlen(P[i]);
		BuildFailure(P[i],pf[i]);
	}
	loop(i,L){
		loop(j,n){
			soFar[j] = GetLen(T[i],soFar[j],P[j],pf[j]);
			mx[j][i + 1] = max(soFar[j], mx[j][i]);
		}
	}
	memset(pf,0,sizeof pf);
	memset(soFar,0,sizeof soFar);
	loop(i,n){
		reverse(P[i],P[i] + len[i]);
		BuildFailure(P[i],pf[i]);		
	}
	for(int i = L - 1;i >= 0;i--){
		loop(j,n){
			soFar[j] = GetLen(T[i],soFar[j],P[j],pf[j]);
			if(mx[j][i] >= len[j] - soFar[j] && soFar[j] && len[j] - soFar[j]) {
				can[j] = 1;	
			}
		}
	}
	int ans = 0;
	loop(i,n) ans += can[i];
	cout << ans << endl;
	return 0;
}
