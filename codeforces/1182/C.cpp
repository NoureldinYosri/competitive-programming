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
//const int MAXN = 100*1000 + 10;
//char buffer[1 << 20];
//int len[MAXN];
//char ID[MAXN];
//int n;
//string S[MAXN];
//
//bool isVowel(char c) {
//	string vowels = "aeoiu";
//	for(char v : vowels)
//		if(c == v)
//			return 1;
//	return 0;
//}
//
//pair<int,char> read(){
//	scanf("%s",buffer);
//	int L = strlen(buffer);
//	char lst = 0;
//	int ctr = 0;
//	loop(i,L) if(isVowel(buffer[i])) lst = buffer[i],ctr++;
//	return mp(ctr,lst);
//}
//
//
//
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d",&n);
//	vector<pair<pair<int,char>,int>> V;
//	loop(i,n){
//		pair<int,char> p = read();
//		S[i] = string(buffer);
//		len[i] = p.first;
//		ID[i] = p.second;
//		V.emplace_back(p,i);
//	}
//	sort(all(V));
//	vector<pair<int,int> > E;
//	vi loser;
//	for(int i = 0;i < n;) {
//		int j = i;
//		while(j < n && V[i].first == V[j].first) j++;
//		int prv = -1;
//		for(;i < j;i++) {
//			int q = V[i].second;
//			if(prv != -1){
//				E.emplace_back(prv,q);
//				prv = -1;
//			}
//			else prv = q;
//		}
//		if(prv != -1) loser.push_back(prv);
//	}
//	sort(all(loser),[](const int & a,const int & b) {
//		return len[a] < len[b];
//	});
//	vector<pair<pi,pi> > ans;
//	for(int i = 0;i+1 < sz(loser) && !E.empty();) {
//		int a = loser[i],b = loser[i + 1];
//		if(len[a] != len[b]) {
//			i++;
//			continue;
//		}
//		ans.emplace_back(mp(a,b),E.back());
//		E.pop_back();
//		i += 2;
//	}
//	while(E.size() > 1) {
//		pi p = E.back(); E.pop_back();
//		pi q = E.back(); E.pop_back();
//		ans.emplace_back(p,q);
//	}
//	printf("%d\n",sz(ans));
//	for(auto p : ans) {
////		prp(p.first); prp(p.second);
////		cerr << endl;
//		int a00 = p.first.first,a01 = p.second.first;
//		int a10 = p.first.second,a11 = p.second.second;
//		printf("%s %s\n",S[a00].c_str(),S[a01].c_str());
//		printf("%s %s\n",S[a10].c_str(),S[a11].c_str());
//	}
//	return 0;
//}
