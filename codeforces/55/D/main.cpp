#pragma GCC optimize ("O3")
#include <cstdio>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;
const int MAXD = 20,MAXLCM = 2520;
int dig[MAXD];
int D;
ll dp[MAXD][MAXLCM][50][2];
int visID[MAXD][MAXLCM][50][2],visNum;
int ID[MAXLCM + 10];
int val[50];
int trans[50][10];
int m;

void conv(ll N) {
	D = 0;
	do{
		dig[D++] = N%10;
		N /= 10;
	}while(N);
	reverse(dig,dig + D);
}

void pre(){
	set<int> S;
	for(int msk = 1;msk < (1 << 10);msk++) {
		int lcm = 1;
		for(int d = 0;d < 10;d++)
			if(msk & (1 << d))
				if(d > 1)
					lcm *= d/__gcd(d,lcm);
		S.insert(lcm);
	}
	m = 0;
	for(auto x : S){
		val[m] = x;
		ID[x] = m++;
	}
	for(int i = 0;i < m;i++){
		int a = val[i];
		for(int d = 0;d < 10;d++) {
			int b = a;
			if(d > 1) b *= d/__gcd(b,d);
			trans[i][d] = ID[b];
		}
	}
}

ll solve(int i,int r,int lcmID,bool areEqual) {
	int lcm = val[lcmID];
	if(i == D) return r%lcm == 0;
	ll & ret = dp[i][r][lcmID][areEqual];
	int & t = visID[i][r][lcmID][areEqual];
	if(t == visNum) return ret;
	t = visNum;
	ret = 0;
	int lim = areEqual ? dig[i] : 9;
	for(int d = 0;d <= lim;d++)
		ret += solve(i+1,(r*10 + d)%MAXLCM,trans[lcmID][d],areEqual && (d == dig[i]));
	return ret;
}

ll solve(ll N){
	conv(N);
//	visNum++;
//	return solve(0,0,0,1);
	for(int r = 0;r < MAXLCM;r++)
		for(int lcmID = 0;lcmID < m;lcmID++)
			for(int areEqual = 0;areEqual < 2;areEqual++)
				dp[D][r][lcmID][areEqual] = r%val[lcmID] == 0;
	for(int i = D-1;i >= 0;i--){
		for(int r = 0;r < MAXLCM;r++)
			for(int lcmID = 0;lcmID < m;lcmID++)
				for(int areEqual = 0;areEqual < 2;areEqual++){
					int lim = areEqual ? dig[i] : 9;
					ll & ret = dp[i][r][lcmID][areEqual];
					ret = 0;
					for(int d = 0;d <= lim;d++)
						ret += dp[i+1][(r*10+d)%MAXLCM][trans[lcmID][d]][areEqual&&(d==dig[i])];
				}
	}
	return dp[0][0][0][1];
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	pre();
	int T; scanf("%d",&T);
	while(T--) {
		ll l,r; scanf("%lld %lld",&l,&r);
		printf("%lld\n",solve(r) - solve(l-1));
	}
	return 0;
}
