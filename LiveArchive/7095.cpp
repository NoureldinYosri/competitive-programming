#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int winnable[2001][2001];
int IDX[2001];
int A[2001];
	
void init(){
	int ctr = 0; int s = 0;
	A[0] = 1;
	while(ctr < 2000){
		int i = 1;
		while(i <= 2000 && A[i]) i++;
		s ++;
		if(s > 2000) break;
		range(j,1,i - 1) A[j] -= 1;
		A[i] = i;
		copy(A,A + 2001,winnable[s]);
		loop(j,2001) if(A[j]) IDX[s] = j;
	}
}

int main(){
	pre();init();
	int T,K,n;
	cin >> T;
	while(T--){
		cin >> K >> n;
		cout << K << " " << IDX[n] << endl;
		for(int i = 1;i <= IDX[n];i++){
			if((i - 1)%10) cout << " " ;
			cout << winnable[n][i];
			if(i == IDX[n] || i%10 == 0) cout << endl;
		}
	}
}
