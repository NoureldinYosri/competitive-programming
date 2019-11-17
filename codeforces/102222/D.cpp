#ifdef ACTIVE
#include <bits/stdc++.h>
using namespace std;

//double dp[20][1 << 20];
//int vis[20][1 << 20];
//
//double solve(int i,int msk,int n) {
//	if(i == n-1) return msk == (1 << i);
//	if(vis[i][msk] == n) return dp[i][msk];
//	vis[i][msk] = n;
//	double & res = dp[i][msk]; res = 0;
//	if(msk & (1 << i)) return res = solve(i+1,msk ^ (1 << i),n);
//	int m = n - i;
//	for(int j = 0;j < n;j++)
//		if(msk & (1 << j))
//			res += solve(i+1,msk ^ (1 << j),n) / m;
//	return res;
//}


double dp2[1 << 10][1 << 10];
int vis2[1 << 10][1 << 10];

double solve2(int people,int seats,int n) {
	if(people == (people & -people)) return people == seats;
	if(vis2[people][seats] == n) return dp2[people][seats];
	vis2[people][seats] = n;
	int m = 0;
	for(int i = 0;i < n;i++) if(people & (1 << i)) m++;
	assert(m > 1);
	double & ans = dp2[people][seats];
	ans = 0;
	for(int i = 0;i < n;i++)
		if(people & (1 << i)){
			if(i && (seats & (1 << i))) ans += solve2(people^(1<<i),seats^(1<<i),n)/m;
			else {
				for(int j = 0;j < n;j++)
					if(seats & (1 << j))
						ans += solve2(people^(1<<i),seats^(1<<j),n)/(m*m);
			}
		}
//	cout << people << " " << seats << ": " << ans << endl;
	return ans;
}

double solve(int n){
	int tot = (1 << n) - 1;
	return solve2(tot,tot,n);
}

int main(){
//	for(int n = 1;n <= 10;n++)
//		cout << n << ". " << solve(n) << endl;
//	cout << solve2(3,3,2) << endl;
	int T; scanf("%d",&T);
	for(int cn = 1;cn <= T;cn++) {
		int n,m; scanf("%d %d",&n,&m);
		double ans1 = 0.5 + (n == 1)*0.5;
		double ans2 = (m+1)/(2.0*m);
		printf("Case #%d: %.6f %.6f\n",cn,ans1,ans2);
	}
}
#endif
