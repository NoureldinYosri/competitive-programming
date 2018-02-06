#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;

const int MAXN = 200*1000 + 10,MAX = 3*MAXN + 1000;

void radixSort(int *A,int *val,int n) {
	static int aux[MAX],cnt[MAX],B[MAX];
	int mn = INT_MAX,mx = INT_MIN;
	loop(i,n) mn = min(mn,val[A[i]]),mx = max(mx,val[A[i]]);
	int alphabetSize = mx - mn + 1;
	loop(i,n) B[i] = val[A[i]] - mn;

	loop(i,alphabetSize) cnt[i] = 0;
	loop(i,n) if(B[i] < alphabetSize) cnt[B[i]+1]++;
	loop(i,alphabetSize-1) cnt[i+1] += cnt[i];

	loop(i,n) aux[cnt[B[i]]++] = A[i];
	loop(i,n) A[i] = aux[i];
}


void buildSuffixArray(int *txt,int *suffixArray,int *rank,int n){
	static int aux[MAX];
	if(n == 1) {
		suffixArray[0] = 0;
		return;
	}
	loop(i,3) txt[n + i] = 0;
	n++;
	int s0 = 0,s12 = 0;
	for(int i = 0;i < n;i += 3) suffixArray[s0++] = i;
	for(int i = 1;i < n;i += i%3) suffixArray[s0 + s12++] = i;

	for(int k = 2;k >= 0;k--){
		loop(i,n) aux[suffixArray[i]] = txt[suffixArray[i] + k];
		radixSort(suffixArray+s0,aux,s12);
	}

	rank[suffixArray[s0]] = 1;
	for(int i = 1,prv,cur;i < s12;i++) {
		prv = suffixArray[s0+i-1],cur = suffixArray[s0+i];
		bool eq = 1;
		for(int k = 0;k < 3 && eq;k++)
			eq &= txt[prv + k] == txt[cur + k];
		rank[cur] = rank[prv] + !eq;
	}

	if(rank[suffixArray[n-1]] != s12)  // not unique
	{
		int start = n + 2,m = 0;
		for(int i = 0;i < n;i++) if(i%3==1) suffixArray[s0 + m++] = i;
		for(int i = 0;i < n;i++) if(i%3==2) suffixArray[s0 + m++] = i;
		assert(m == s12);
		for(int i = 0;i < s12;i++) txt[start + i] = rank[suffixArray[s0 + i]];

		buildSuffixArray(txt+start,suffixArray+start,rank+start,s12);
		for(int i = 0;i < s12;i++){
			int a = suffixArray[start + i],b = suffixArray[s0 + a];
			aux[i] = b;
			rank[b] = i;
		}
		for(int i = 0;i < s12;i++)
			suffixArray[s0 + i] = aux[i];
	}

	loop(i,s0) aux[suffixArray[i]] = rank[suffixArray[i]+1];
	radixSort(suffixArray,aux,s0);
	loop(i,s0) aux[suffixArray[i]] = txt[suffixArray[i]];
	radixSort(suffixArray,aux,s0);

	loop(i,s0) rank[suffixArray[i]] = i+1;

	int i = 0,j = s0,m = 0;
	while(i < s0 && j < n){
		int a = suffixArray[i],b = suffixArray[j];
		if(txt[a] < txt[b]) aux[m++] = suffixArray[i++];
		else if(txt[a] > txt[b]) aux[m++] = suffixArray[j++];
		else if(b%3 == 1) {
			if(rank[a+1] < rank[b+1]) aux[m++] = suffixArray[i++];
			else aux[m++] = suffixArray[j++];
		}
		else {
			if(tie(txt[a+1],rank[a+2]) < tie(txt[b+1],rank[b+2])) aux[m++] = suffixArray[i++];
			else aux[m++] = suffixArray[j++];
		}
	}
	while(i < s0) aux[m++] = suffixArray[i++];
	while(j < n) aux[m++] = suffixArray[j++];

	loop(i,n-1) {
		suffixArray[i] = aux[i+1];
		rank[suffixArray[i]] = i;
	}

//	prArr(suffixArray,n-1,int);
}

void buildSuffixArray(const char *S,int *suffixArray,int *rank) {
	static int txt[MAX];
	int n = 0;
	for(;S[n];n++)	txt[n] = S[n];
	buildSuffixArray(txt,suffixArray,rank,n);
}

void getlcp(int *S,int *SA,int *R,int *lcp,int n)
{
  for (int i=0; i<n; ++i)
    R[SA[i]] = i;

  lcp[0] = 0;

  for (int i=0, h=0; i<n; ++i)
  {
    if (R[i] > 0)
    {
      int j = SA[R[i]-1];
      while (i + h < n && j + h < n && S[i+h] == S[j+h])
          h++;
      lcp[R[i]] = h;

      if (h > 0)
        h--;
    }
  }
}


int SA[MAX],R[MAX],id[MAX],lcp[MAX],txt[MAX],n;
char buffer[MAX];
int I[MAX],L[MAX],mx[MAX];

string toString(int s) {
	static string delim = "~!@#$%^&*()_-=+[]";
	string ret;
	for(;s < n;s++) {
		if(txt[s] < 128) ret += (char)txt[s] ;
		else ret += delim[txt[s] - 128];
	}
	return ret;
}
int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
//		freopen("out.out","w",stdout);
	#endif
	int T; scanf("%d",&T);
	loop(i,T){
		scanf("%s",buffer);
		I[i] = n;
		L[i] = strlen(buffer);
		for(int j = 0;buffer[j];j++) {
			id[n] = i;
			txt[n++] = buffer[j];
		}
		id[n] = i;
		txt[n++] = 128 + i;
	}
	buildSuffixArray(txt,SA,R,n);
	getlcp(txt,SA,R,lcp,n);

//	for(int i = 0;i < n;i++)
//		cerr << lcp[i] << ". [" << id[SA[i]] << "] " << toString(SA[i]) << endl;

	for(int i = 1,mn = n;i < n;i++){
		if(id[SA[i]] != id[SA[i-1]]) mn = n;
		mn = min(mn,lcp[i]);
		mx[i] = max(mx[i],mn);
	}


//	prArr(mx,n,int);
	for(int i = n-1,mn = 0;i >= 0;i--) {
		mx[i] = max(mx[i],mn);
		if(i && id[SA[i]] != id[SA[i-1]]) mn = n;
		mn = min(mn,lcp[i]);
	}

//	prArr(mx,n,int);
//	for(int i = 0;i < n;i++)
//		cerr << mx[i] << ". [" << id[SA[i]] << "] " << toString(SA[i]) << endl;

//	prArr(mx,n,int);

	for(int i = 0;i < n;i++) {
		int j = id[SA[i]];
		if(txt[SA[i]] < 128 && txt[SA[i] + mx[i]] < 128 && mx[i]+1 < L[j]) {
			L[j] = mx[i] + 1;
			I[j] = SA[i];
		}
	}


	for(int i = 0;i < T;i++){
//		printf("%d. ",L[i]);
		for(int j = 0;j < L[i];j++){
			putchar(txt[I[i] + j]);
//			cout << txt[I[i] + j] << " ";
		}
		puts("");
	}
	return 0;
}
