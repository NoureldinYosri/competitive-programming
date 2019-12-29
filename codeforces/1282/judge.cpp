#include <bits/stdc++.h>
using namespace std;

string S;
using vi = vector<int>;

int getCost(string T) {
	int n = S.size(),m = T.size();
	vector<vi> dp (n+1,vi(m+1,0));
	for(int i = 0;i <= n;i++) dp[i][0] = i;
	for(int i = 0;i <= m;i++) dp[0][i] = i;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) {
			dp[i][j] = min(dp[i][j-1],dp[i-1][j]);
			dp[i][j] = min(dp[i][j],dp[i-1][j-1]);
			dp[i][j]++;
			if(S[i-1] == T[j-1])
				dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
		}
	return dp[n][m];
}

int main(int argc, char **argv){
	if(argc > 1) S = string(argv[1]);
	else {
		int ca = rand()%3;
		int cb = rand()%3;
		if(!ca && !cb) ca++;
		S = string(ca,'a') + string(cb,'b');
		random_shuffle(S.begin(),S.end());
	}
	freopen("log.log","w",stderr);
	cerr << S << endl;
	int L = S.size() + 2;
	for(;;){
		if(!L) {
			cout << -1 << endl;
			return 1;
		}
		L--;
		string T; cin >> T;
		int r = getCost(T);
		cout << r << endl;
		fflush(stdout);
		if(!r) break;
	}
	return 0;
}