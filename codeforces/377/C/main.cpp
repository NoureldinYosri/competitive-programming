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

int n,m;
const int oo = 1 << 29;
int S[111],per[20];
char command[20];
const int MAXK = 20;

int dp[20][1 << MAXK];

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",S + i);
	sort(S,S + n); reverse(S,S + n);
	scanf("%d",&m);
	loop(i,m) scanf(" %c %d",command + i,per + i),per[i]--;
	n = min(n,m);
	loop(i,m){
		int com = m-i-1;
		loop(ban,1 << m){
			if(popcnt(ban) < i) continue;
			dp[i][ban] = (2*per[com] - 1) * oo;
			if(command[com] == 'p'){
				loop(pos,n){
					if(ban & (1 << pos)){
						if(per[com]) 
							dp[i][ban] = min(dp[i][ban],(1-2*per[com])*S[pos]+(i ? dp[i-1][ban ^ (1 << pos)] : 0));
						else 
							dp[i][ban] = max(dp[i][ban],(1-2*per[com])*S[pos]+(i ? dp[i-1][ban ^ (1 << pos)] : 0));
					}
				}
			}
			else{
				dp[i][ban] = i ? dp[i-1][ban] : 0;
				loop(pos,n) {
					if(ban & (1 << pos)){
						if(per[com]) dp[i][ban] = min(dp[i][ban],i ? dp[i - 1][ban ^ (1<<pos)] : 0);
						else dp[i][ban] = max(dp[i][ban],i ? dp[i - 1][ban ^ (1<<pos)] : 0);
					}
				}
			}
		}
	}
	cout << dp[m-1][(1<<m)-1] << endl;
	return 0;
}
