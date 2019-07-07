//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//
//struct clue{
//	vi guess;
//	int verdict;
//};
//
//vector<clue> clues;
//
//void readClues(){
//	string a,b,c;
//	while(cin >> a >> b >> c) {
//		clue c;
//		for(char d : a)
//			c.guess.push_back(d - '0');
//		sscanf(b.c_str(),";%d",&c.verdict);
//		clues.push_back(c);
//	}
//}
//
//vi S(16,-1);
//int taboo[16][10];
//
//bool isConsistent(){
//	for(clue c : clues) {
//		int ctr = 0;
//		for(int i = 0;i < 16;i++) {
//			ctr += S[i] == c.guess[i];
//		}
//		if(ctr > c.verdict) return 0;
////		cerr << ctr << " " << c.verdict << endl;
//	}
//	return 1;
//}
//
//void bt(int);
//
//void use(int r,int which,const vi & f,int prv = -1) {
//	static vi used;
//	if(!r) {
//		for(int p : f) {
//			int d = clues[which].guess[p];
//			if(S[p] == -1)
//				taboo[p][d]++;
//		}
//		bt(which+1);
//		for(int p : f) {
//			int d = clues[which].guess[p];
//			if(S[p] == -1)
//				taboo[p][d]--;
//			assert(taboo[p][d] >= 0);
//		}
//		return;
//	}
//	for(int j = prv + 1;j < sz(f);j++) {
//		int i = f[j];
//		int d = clues[which].guess[i];
//		S[i] = d;
//		used.push_back(i);
//		use(r-1,which,f,j);
//		used.pop_back();
//		S[i] = -1;
//	}
//}
//
//void bt(int i){
//	if(!isConsistent()) return;
//	if(i == sz(clues)) {
//		print(S,int);
//		exit(0);
//	}
//	const clue & c = clues[i];
//	int ctr = c.verdict;
//	vi free;
//	for(int i = 0;i < 16;i++) {
//		if(S[i] == -1) {
//			int d = c.guess[i];
//			if(!taboo[i][d])
//				free.push_back(i);
//		}
//		else if(S[i] == c.guess[i]) ctr--;
//	}
//	assert(ctr >= 0);
//	if(ctr > sz(free)) return;
//	use(ctr,i,free);
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	readClues();
//
//	sort(all(clues),[](const clue & a,const clue & b) {
//		return a.verdict < b.verdict;
//	});
//
////	bt(0);
//	S = vi{4,6,4,0,2,6,1,5,7,1,8,4,9,5,3,3};
//	assert(isConsistent());
//	for(int d : S) cerr << d ;
//	return 0;
//}
