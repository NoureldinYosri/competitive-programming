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

char line[5010];
int n,k;
int dp[5010][5010];
int val[16][5010];
int aux[5010],lg[5010],ctr;
pi cand[5010*5010];

int solve(int s,int e){
	if(e <= s) return 1;
	if(dp[s][e] != -1) return dp[s][e];
	return dp[s][e] = (line[s] == line[e]) && solve(s + 2,e - 2);	
}

void PRINT(pi a){
	loop(i,a.yy) cerr << line[a.xx + i];
}

bool cmp(const pi & a,const pi & b){
	int l1 = a.yy,l2 = b.yy;
	int k = min(lg[l1],lg[l2]);
	if(val[k][a.xx] != val[k][b.xx]) return val[k][a.xx] < val[k][b.xx];
	if(min(l1,l2) == (1 << k)) return l1 < l2;
	int dl = min(l1,l2) - (1 << k);
	pi c = mp(a.xx + dl,l1 - dl),d = mp(b.xx + dl,l2 - dl);
	return cmp(c,d);
}


int main(){
	scanf("%s %d",line,&k);
	n = strlen(line);
	memset(dp,-1,sizeof dp);
	loop(j,n) loop(i,j+1) if(solve(i,j)) cand[ctr++] = mp(i,j - i + 1);
	loop(i,n) val[0][i] = line[i];	
	for(int k = 0;(1 << k) <= n;k++){
		loop(i,n) aux[i] = i;
		auto cmp = [k](const int & a,const int & b){
			if(val[k][a] != val[k][b]) return val[k][a] < val[k][b];
			if(a + (1 << k) >= n && b + (1 << k) >= n) return false;
			if(a + (1 << k) >= n) return true;
			if(b + (1 << k) >= n) return false;
			return val[k][a + (1 << k)] < val[k][b + (1 << k)];
		};
		sort(aux,aux + n,cmp);
		int r = 0;
		loop(i,n){
			if(i) r += cmp(aux[i - 1],aux[i]);
			val[k + 1][aux[i]] = r;
		}
	}
	lg[0] = -1;
	loop(i,n) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i + 1));
	int s = 0,e = ctr - 1; k--;
	while(s < e){
		int q = rand()%(e - s + 1) + s;
		swap(cand[s],cand[q]); int ptr = s;
		range(i,s+1,e) if(cmp(cand[i],cand[s])) swap(cand[i],cand[++ptr]);
		swap(cand[s],cand[ptr]);
		if(ptr == k) break;
		if(ptr < k) s = ptr + 1;
		else e = ptr - 1;
	}
	loop(i,cand[k].yy) putchar(line[cand[k].xx + i]);
	puts("");
	return 0;
}
