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
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

bool c = 1;
void merge(int s,int m,int e,vi & A){
	queue<int> q1,q2;
	range(i,s,m) q1.push(A[i]);
	range(i,m + 1,e) q2.push(A[i]);
	while(!q1.empty() && !q2.empty()){
		string st;
		cout << "1 " << q1.front() << " " << q2.front() << endl;
		cin >> st;
		if(st == "NO") {
			A[s++] = q2.front();
			q2.pop();
		}
		else {
			A[s++] = q1.front();
			q1.pop();
		}
	}
	for(;!q1.empty();q1.pop()) A[s++] = q1.front();	
	for(;!q2.empty();q2.pop()) A[s++] = q2.front();	
}

void sort(int s,int e,vi & A){
	if(s == e) return;
	int m = (s + e) >> 1;
	sort(s,m,A);
	sort(m + 1,e,A);
	merge(s,m,e,A);
}

int main(){
	int N;
	cin >> N;
	vi A(N);
	loop(i,N) A[i] = i + 1;
	sort(0,N - 1,A);  
	cout << "0";
	loop(i,N) cout << " " << A[i]*c;
	cout  << endl;	
	return 0;
}