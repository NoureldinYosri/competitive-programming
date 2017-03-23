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

char buffer[1024];
map<char,vector<vi> > M;
int N,Q;
string ord;
string q;
int ctr[17][44];

int main(){
	scanf("%d %d",&N,&Q);
	scanf("%s",buffer); ord = string(buffer);
	loop(i,N){
		vector<vi> R(17);
		loop(j,17){
			scanf("%s",buffer);
			loop(k,43) if(buffer[k] == '*') R[j].pb(k);
		}
		M[ord[i]] = R;
	}
	loop(i,Q){
		scanf("%s",buffer); q = string(buffer);
		for(char c : q){
			vector<vi> & R = M[c];
			loop(row,17){
				for(int col : R[row])
					ctr[row][col]++;
			}
		}
		printf("Query %d: ",i+1);
		for(char c : q){
			vector<vi> & R = M[c];
			bool found = 0;			
			for(int row = 0;row < 17 && !found;row++)
				for(int col : R[row])
					if(ctr[row][col] == 1){
						found = 1;
						break;
					}
			putchar(found ? 'Y' : 'N');
		}
		puts("");
		for(char c : q){			
			vector<vi> & R = M[c];
			loop(row,17)
				for(int col : R[row])
					ctr[row][col] = 0;
		}
	}
	
	return 0;
}
