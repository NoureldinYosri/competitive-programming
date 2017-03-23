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

int f[103];
int st[103],siz[103],working[103],ord[103];

int main(){
	int t,m,x; scanf("%d %d",&t,&m);
	fill(f,f + m + 1,1);
	char buffer[100]; 	
	for(int id = 1;t--;){
		scanf("%s",buffer);
		if(buffer[0] == 'a'){
			scanf("%d",&x);
			bool found = 0;
			for(int i = 1;i <= m && !found;i++) if(f[i]) {
				int j = i;
				while(j <= m && f[j]) j++;
				if(j - i >= x) {
					found = 1;
					working[id] = 1;
					st[id] = i;
					siz[id] = x;
					loop(k,x) f[i + k] = 0;
					printf("%d\n",id);
					id++;
				}
				i = j - 1;
			}
			if(!found) puts("NULL");
		}
		else if(buffer[0] == 'e'){
			scanf("%d",&x);
			if(x < 1 || x >= id || !working[x]) puts("ILLEGAL_ERASE_ARGUMENT");
			else{
				working[x] = 0;
				loop(j,siz[x]) f[st[x] + j] = 1;
			}
		}
		else{
			int k = 0;
			range(j,1,id-1) if(working[j]) ord[k++] = j;
			if(!k) continue;
			sort(ord,ord + k,[](const int & a,const int & b){
				return st[a] < st[b];
			});
			int offset = 1;
			loop(j,k) {
				st[ord[j]] = offset;
				offset += siz[ord[j]];
			}
			fill(f,f + m + 1,1);
			fill(f,f + offset,0);
		}
	}	
	
	
	return 0;
}
