//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//using vi = std::vector<int>;
//using pi = std::pair<int,int>;
//using ll = long long;
//using namespace std;
//
//int dp[50][50*10 + 10][10 + 5];
//
//class MeanMedian{
//	int Median,n;
//	int targetSum;
//	vi D;
//public:
//	int solve(int i,int k,int prv) {
//		if(i == n) return (k >= targetSum) ? 0 : (1 << 29);
//		k = min(k,targetSum);
//		int & ret = dp[i][k][prv];
//		if(ret != -1) return ret;
//		int low = prv,hi = 10;
//		if(i >= n/2) low = max(low,Median);
//
//		ret = 1 << 29;
//		for(int grade = low;grade <= hi;grade++)
//			ret = min(ret,solve(i+1,k + grade,grade) + grade*D[i]);
////		cout << i << " " << k << ": " << ret << endl;
//		return ret;
//	}
//	int minEffort(int needMean, int needMedian, vector <int> d){
//		sort(all(d));
//		reverse(all(d));
//		D = d;
//		n = d.size();
//		targetSum = needMean * n;
//		memset(dp,-1,sizeof dp);
//		Median = needMedian;
//		return solve(0,0,0);
//	}
//};
//
//int main(){
//	int needMean = 4;
//	int needMedian = 4;
//	vi d {30, 25, 20};
//	cout << MeanMedian().minEffort(needMean,needMedian,d) << endl;
//	return 0;
//}
