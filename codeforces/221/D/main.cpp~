#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 5010;
int A[MAX][MAX],m,n; ll ans = 0;
char line[MAX];
int aux[MAX],AUX[MAX];

void sort(){
	int mx = 0;
	loop(i,m) mx = max(mx,aux[i] + 1);
	fill(AUX,AUX + m,0);
	loop(i,m) AUX[aux[i]]++;
	int idx = 0;
	loop(i,mx) while(AUX[i]--) aux[idx++] = i;
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) {
		scanf("%s",line);	
		loop(j,n){
			A[i][j] = line[j] - '0';
			if(j) A[i][j] += A[i][j]*A[i][j - 1];
		}
	}
	loop(j,n){
		loop(i,m) aux[i] = A[i][j];
		sort();
		loop(i,m) ans = max(ans,(m - i + 0LL)*aux[i]);		
	}	
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
