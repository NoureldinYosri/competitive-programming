#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

int H,W;
bool is_black[200 + 5][50*4 + 5];
bool vis[200 + 5][50*4 + 5];
char buffer[100];
int id[200 + 5][50*4 + 5];
set<int> S[200*50*4 + 5];

string hex2bin(char c) {
	int v = 0;
	if(isdigit(c)) v = c - '0';
	else v = c - 'a' + 10;
	string ret(4,'0');
	for(int i = 0;i < 4;i++)
		ret[4-1-i] += (v >> i) & 1;
	return ret;
}

char cnt2char[] = "WAKJSD";
int dx[] = {-1,0,1,0},dy[] = {0,-1,0,1};

void flood_fill(int x,int y,int idx,bool type) {
	if(x < 0 || y < 0 || x >= H || y >= W) return ;
	if(vis[x][y]) return;
	if(!is_black[x][y] == type) return;
	id[x][y] = idx;
	vis[x][y] = 1;
	if(type){
		loop(r,4) flood_fill(x+dx[r],y+dy[r],idx,type);
	}
	else{
		range(dx,-1,1) range(dy,-1,1)
				flood_fill(x+dx,y+dy,idx,type);
	}
}


void save_as_image(){
	FILE *f = fopen("out.ppm","wb");
	fprintf(f, "P6\n%i %i 255\n", W, H);
	loop(r,H) loop(c,W) {
		fputc((1 - is_black[r][c])*255,f);
		fputc((1 - is_black[r][c])*255,f);
		fputc((1 - is_black[r][c])*255,f);
	}
	fclose(f);
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int t = 1;scanf("%d %d",&H,&W) == 2 && !(H==0 && W==0);t++) {
		loop(r,H+2)loop(c,W*4+2) {
			vis[r][c] = 0;
			is_black[r][c] = 0;
		}
		for(int r = 0;r < H;r++) {
			scanf("%s",buffer);
			for(int c = 0;c < W;c++) {
				string v = hex2bin(buffer[c]);
				for(int i = 0;i < 4;i++){
					is_black[r + 1][4*c + i + 1] = v[i] == '1';
				}
			}
		}
		W = W*4 + 2;
		H += 2;
//			save_as_image();
		int ctr = 0;
		loop(r,H) loop(c,W) if(!vis[r][c]) {
			S[ctr].clear();
			flood_fill(r,c,ctr++,is_black[r][c]);
		}
		loop(x,H) loop(y,W) if(is_black[x][y]) {
			loop(r,4) {
				int nx = x + dx[r],ny = y + dy[r];
				if(nx < 0 || ny < 0 || nx >= H || ny >= W || is_black[nx][ny]) continue;
				S[id[x][y]].insert(id[nx][ny]);
			}
		}
		vi V;
		set<int> done;
		loop(y,W) loop(x,H) if(is_black[x][y] && !done.count(id[x][y])) {
			done.insert(id[x][y]);
			int cnt = S[id[x][y]].size() - 1;
			assert(0 <= cnt && cnt <= 5);
			V.push_back(cnt);
		}
		string s = "";
		for(int c : V) s += cnt2char[c];
		sort(all(s));
		printf("Case %d: %s\n",t,s.c_str());
	}
	return 0;
}
