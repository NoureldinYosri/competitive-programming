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

const int MAX = 2e5 + 1000;
int txt[MAX]; //input
int iSA[MAX], SA[MAX]; //output
int cnt[MAX], nxt[MAX]; //internal
bool bh[MAX], b2h[MAX];

// Compares two suffixes according to their first characters
bool smaller_first_char(int a, int b){
  return txt[a] < txt[b];
}

void suffixSort(int n){
  //sort suffixes according to their first characters
  for (int i=0; i<n; ++i){
    SA[i] = i;
  }
  sort(SA, SA + n, smaller_first_char);
  //{SA contains the list of suffixes sorted by their first character}

  for (int i=0; i<n; ++i){
    bh[i] = i == 0 || txt[SA[i]] != txt[SA[i-1]];
    b2h[i] = false;
  }

  for (int h = 1; h < n; h <<= 1){
    //{bh[i] == false if the first h characters of SA[i-1] == the first h characters of SA[i]}
    int buckets = 0;
    for (int i=0, j; i < n; i = j){
      j = i + 1;
      while (j < n && !bh[j]) j++;
      nxt[i] = j;
      buckets++;
    }
    if (buckets == n) break; // We are done! Lucky bastards!
    //{suffixes are separted in buckets containing txtings starting with the same h characters}

    for (int i = 0; i < n; i = nxt[i]){
      cnt[i] = 0;
      for (int j = i; j < nxt[i]; ++j){
        iSA[SA[j]] = i;
      }
    }

    cnt[iSA[n - h]]++;
    b2h[iSA[n - h]] = true;
    for (int i = 0; i < n; i = nxt[i]){
      for (int j = i; j < nxt[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0){
          int head = iSA[s];
          iSA[s] = head + cnt[head]++;
          b2h[iSA[s]] = true;
        }
      }
      for (int j = i; j < nxt[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0 && b2h[iSA[s]]){
          for (int k = iSA[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
        }
      }
    }
    for (int i=0; i<n; ++i){
      SA[iSA[i]] = i;
      bh[i] |= b2h[i];
    }
  }
  for (int i=0; i<n; ++i){
    iSA[SA[i]] = i;
  }
}
// End of suffix array algorithm


// Begin of the O(n) longest common prefix algorithm
// Refer to "Linear-Time Longest-Common-Prefix Computation in Suffix
// Arrays and Its Applications" by Toru Kasai, Gunho Lee, Hiroki
// Arimura, Setsuo Arikawa, and Kunsoo Park.
int lcp[MAX];
// lcp[i] = length of the longest common prefix of suffix SA[i] and suffix SA[i-1]
// lcp[0] = 0
void getlcp(int n)
{
  for (int i=0; i<n; ++i)
    iSA[SA[i]] = i;

  lcp[0] = 0;

  for (int i=0, h=0; i<n; ++i)
  {
    if (iSA[i] > 0)
    {
      int j = SA[iSA[i]-1];
      while (i + h < n && j + h < n && txt[i+h] == txt[j+h])
          h++;
      lcp[iSA[i]] = h;

      if (h > 0)
        h--;
    }
  }
}

char buffer[MAX];
int id[MAX],m,offset = 128;
ll ans[MAX];
int E[MAX];

string output(int i) {
	string ret ,delim = "#$@%!()*&^-+=_[]";
	for(;i < m;i++) {
		if('a' <= txt[i] && txt[i] <= 'z')
			ret += (char) txt[i];
		else
			ret += delim[(txt[i]-128)%sz(delim)];
	}
	return ret;
}

const int MAXLG = 20;
int lg[MAX],sparse[MAX][MAXLG];

void buildSparse(){
	lg[0] = -1;
	for(int i = 1;i <= m;i++)
		lg[i] = lg[i-1] + (i == LSOne(i));
	loop(i,m) sparse[i][0] = lcp[i];
	loop(k,MAXLG-1)
		loop(i,m) {
			int j = i + (1 << k);
			if(j >= m) j = i;
			sparse[i][k+1] = min(sparse[i][k],sparse[j][k]);
		}
}

int RMQ(int i,int j) {
	i++;
	int l = lg[j - i + 1];
	return min(sparse[i][l],sparse[j - (1 << l) + 1][l]);
}

int len[MAX];
int contrib[MAX];
int nxtI[MAX];

int main(){
	freopen("standingout.in", "r", stdin);
#ifndef HOME
	freopen("standingout.out", "w", stdout);
#endif
	int n; scanf("%d",&n);
	loop(i,n){
		scanf("%s",buffer);
		for(char *p = buffer;*p;p++) {
			id[m] = i;
			txt[m] = *p;
			m++;
		}
		E[i] = m;
		id[m] = i;
		txt[m] = offset++;
		m++;
		len[i] = strlen(buffer);
	}
	suffixSort(m);
	getlcp(m);
	buildSparse();
//	loop(i,m) cerr << lcp[i] << " " << id[SA[i]] << " " << output(SA[i]) << endl;
	for(int i = 0;i < m;i++) {
		int j = SA[i],ID = id[j];
		ans[ID] += contrib[i] = E[ID] - j - lcp[i];
	}
//	prArr(ans,n,ll);
	nxtI[m-1] = m;
	for(int i=m-2;i >= 0;i--)
		if(id[SA[i]] == id[SA[i+1]]) nxtI[i] = nxtI[i+1];
		else nxtI[i] = i+1;
	for(int i = 0;i < m;i++) {
		int j = SA[i],ID = id[j],nxt = nxtI[i];
		int r = E[ID] - j - contrib[i],l = RMQ(i,nxt);
		ans[ID] -= max(0,l - r);
	}
//	prArr(ans,n,ll);

	loop(i,n) printf("%lld\n",ans[i]);
	return 0;
}
