#pragma GCC optimize ("O3")
#include <cstdio>
#include <algorithm>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define mp make_pair
#define ll long long
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
using namespace std;



const int MAX = 2010;
int n,m;
bool A[MAX][MAX];
char s[MAX + 10];
short row[MAX][MAX],col[MAX][MAX],diag[MAX][MAX];
short BIT[2*MAX][MAX];
pair<short,short> head_DIAG[2*MAX][MAX];
pair<short,short> nxt[MAX][MAX];


inline void update(short i,short v,short *T){
	for(;i < MAX;i += LSOne(i)) T[i] += v;
}
inline short get(short i,short *T){
	short ret = 0;
	for(;i;i ^= LSOne(i)) ret += T[i];
	return ret;
}


inline bool valid1(int i,int j,int l){
	short x = i + l - 1,y = j + l - 1;
	short r1 = row[i][y] - (j ? row[i][j - 1] : 0);
	if(r1 != l) return 0;
	short c1 = col[x][j] - (i ? col[i-1][j] : 0);
	if(c1 != l) return 0;
	short d = diag[x][y] - ((i && j) ? diag[i-1][j - 1] : 0);
	return d == l;
}
inline bool valid2(short i,short j,short l){
	short x = i - l + 1,y = j - l + 1;
	swap(x,i);
	swap(y,j);
	short r2 = row[x][y] - (j ? row[x][j - 1] : 0);
	if(r2 != l) return 0;
	short c2 = col[x][y] - (i ? col[i-1][y] : 0);
	if(c2 != l) return 0;
	short d = diag[x][y] - ((i && j) ? diag[i-1][j - 1] : 0);
	return d == l;
}




int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	fill(&head_DIAG[0][0],&head_DIAG[2*MAX][0],mp(-1,-1));
	loop(i,n) {
		scanf("%s",s);
		loop(j,m) {
			A[i][j] = s[j] - '0';
			row[i][j] = col[i][j] = diag[i][j] = A[i][j];
			if(i) col[i][j] += col[i-1][j];
			if(j) row[i][j] += row[i][j - 1];
			if(i && j) diag[i][j] += diag[i-1][j-1];
		}
	}
	ll ans = 0;
	short s,e,L,d,x,y,t;
	loop(i,n)loop(j,m) if(A[i][j]){
		s = 1,e = min(i,j) + 1;
		while(s < e) {
			short m = s + ((e - s + 1) >> 1);
			if(valid2(i,j,m)) s = m;
			else e = m - 1;
		}
		L = s;
		d = i - j + MAX;
		if(i){
			x = head_DIAG[d][i-1].xx,y = head_DIAG[d][i-1].yy;
			while(x != -1) {
				update(x+1,-1,BIT[d]);
				t = nxt[x][y].xx;
				y = nxt[x][y].yy;
				x = t;
			}
		}
		ans += 1 + get(i+1,BIT[i-j+MAX]) - get(i-L+1,BIT[i-j+MAX]);

		s = 1,e = min(n-i,m-j);
		while(s < e) {
			short m = s + ((e - s + 1) >> 1);
			if(valid1(i,j,m)) s = m;
			else e = m - 1;
		}
		nxt[i][j] = head_DIAG[d][i+s-1];
		head_DIAG[d][i+s-1] = mp(i,j);
		update(i+1,1,BIT[i-j+MAX]);
	}
	printf("%lld\n",ans);
	return 0;
}
