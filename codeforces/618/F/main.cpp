#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 1000*1000 + 10,MAXK = 10*MAX;
int n;
ll SA[MAX],SB[MAX];
pi A[MAX],B[MAX];
bool vis[MAX];
pi M[MAX];

char buffer[MAXK];



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	fgets(buffer,MAXK,stdin);
	sscanf(buffer,"%d",&n);
	fgets(buffer,MAXK,stdin);
	int k = 0;
	for(char *token = strtok(buffer," \n");token;token = strtok(NULL," \n")){
		++k;
		sscanf(token,"%d",&A[k].xx);
		A[k].yy = k;
	}
	fgets(buffer,MAXK,stdin);
	k = 0;
	for(char *token = strtok(buffer," \n");token;token = strtok(NULL," \n")){
		++k;
		sscanf(token,"%d",&B[k].xx);
		B[k].yy = k;
	}
	loop(i,n) SA[i + 1] = A[i + 1].xx + SA[i];
	loop(i,n) SB[i + 1] = B[i + 1].xx + SB[i];
	int j = 0;
	vi out[2];
	loop(i,n+1){
		while(j + 1 <= n && SB[j + 1] <= SA[i]) j++;
		ll diff = SA[i] - SB[j];
		assert(diff <= n);
		if(!vis[diff]) M[diff] = mp(i,j),vis[diff] = 1;
		else{
			int sa = M[diff].xx,sb = M[diff].yy;
			for(++sa;sa <= i;sa++)
				out[0].pb(A[sa].yy);
			for(++sb;sb <= j;sb++)
				out[1].pb(B[sb].yy);
			break;
		}
	}
	if(out[0].empty()) puts("-1");
	else {
		printf("%d\n",sz(out[0]));
		loop(i,sz(out[0])) printf("%d%c",out[0][i]," \n"[i+1==sz(out[0])]);
		printf("%d\n",sz(out[1]));
		loop(i,sz(out[1])) printf("%d%c",out[1][i]," \n"[i+1==sz(out[1])]);
	}
	return 0;
}
