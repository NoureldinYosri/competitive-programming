/*#include <bits/stdc++.h>
using namespace std;

int n, k, si, vi;
vector <int> v[305];
vector <long long> s[305];

long long dp[305][100005];

bool check(int i, int m, int t1, int t2, int j){
	int L1 = 0, R1 = v[i].size() - (j - t1) / i + 1;
	while(L1 < R1){
		int mid1 = (L1 + R1) / 2;
		if(dp[i - 1][t2 * i + m] + s[i][j - t2 + mid1] >= dp[i - 1][t1 * i + m] + s[i][j - t1 + mid1])R1 = mid1;
		else L1 = mid1 + 1;
	}
	
	int L2 = 0, R2 = v[i].size() - (j - t2) / i;
	while(L2 < R2){
		int mid2 = (L2 + R2 + 1) / 2;
		if(dp[i - 1][t2 * i + m] + s[i][j - t2 + mid2] > dp[i - 1][j * i + m] + s[i][mid2])L2 = mid2;
		else R2 = mid2 - 1;
	}
	
	if(dp[i - 1][t2 * i + m] + s[i][j - t2] <= dp[i - 1][j * i + m])return false;
	if(L1 <= L2)return true;
	return false;
}
int main(){
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++){
		scanf("%d %d", &si, &vi);
		v[si].push_back(vi);
	}
	
	for(int i = 1; i <= 300; i++){
		sort(v[i].rbegin(), v[i].rend());
		s[i].push_back(0);
		for(int j = 0; j < v[i].size(); j++)
			s[i].push_back(s[i].back() + v[i][j]);
	}
	
	for(int i = 1; i <= 300; i++){
		for(int m = 0; m < i; m++){
			deque <long long> q;
			for(int j = m; j <= k; j += i){
				if((!q.empty()) && ((j - q.front()) / i > v[i].size()))
					q.pop_front();
				
				while(q.size() >= 2){
					int t1 = q.back();
					q.pop_back();
					int t2 = q.back();
					
					if(check(i, m, t2 / i, t1 / i, j / i)){
						q.push_back(t1);
						break;
					}
				}
				
				q.push_back(j);
				
				while(q.size() >= 2){
					int t1 = q.front();
					q.pop_front();
					int t2 = q.front();
					
					if(s[i][j / i - t1 / i] + dp[i - 1][t1] <= s[i][j / i - t2 / i] + dp[i - 1][t2])continue;
					else{
						q.push_front(t1);
						break;
					}
				}
				
				//cout << j << ' ' << q.front() << endl;
				dp[i][j] = s[i][j / i - q.front() / i] + dp[i - 1][q.front()];
			} 
		}	
	}
	
	for(int i = 1; i <= k; i++){
		if(i > 1)printf(" ");
		printf("%lld", dp[300][i]);
	}
	printf("\n");
	
	return 0;
}
*/
