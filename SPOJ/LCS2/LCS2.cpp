#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAX = 1 << 20;
char txt[MAX]; //input
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




vi getLCP(const vi & SA, const char *txt){
	vi lcp(sz(SA), 0);
	vi iSA(sz(SA));
	loop(i, sz(SA)) iSA[SA[i]] = i;
	
	for(int i = 0, l = 0; i < sz(iSA); i++){
		if(iSA[i] == sz(SA)-1) continue;
		int j = SA[iSA[i] + 1];
		
		while(txt[i + l] == txt[j + l]) l++;
		lcp[iSA[i] + 1] = l;
		
		if(l) l--;
	}	
	return lcp;
}

char buffer[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int N = 0;
	string special = "!@#$%^&*()";
	sort(special.rbegin(), special.rend());
	vi aux2;
	int m = 0;
	while(scanf("%s", buffer) == 1){
		int n = strlen(buffer);
		loop(i, n) {
			txt[N++] = buffer[i];
			aux2.pb(m);
		}
		txt[N++] = special[m]; 
		aux2.pb(m);
		m++;
	}
	

	if(m == 1){
		cout << N-1 << endl;
		return 0;
	}

	
	string s(txt);
	suffixSort(N);
	
	vi names(N);
	loop(i, N) names[i] = aux2[SA[i]];
	
	vi aux{SA, SA + N};
	vi lcp = getLCP(aux, txt);

/*	loop(i, N) {
		cerr << i << " " << pi(SA[i], names[SA[i]]) << " " << lcp[i] << " ";
		loop(j, N-SA[i]) cerr << (char)txt[SA[i] + j];
		cerr << endl;
	}
	*/


	deque<int> dq;
	vi cnt(m);
	int msk = 0, target = (1 << m) - 1;
	int ans = 0;
	
	for(int i = 0, j = 0; i < N; i++){
		if(j <= i) {
			j = i;
			dq.clear();
			msk = 0;
		}
		while(j < N && msk != target) {
			cnt[names[j]] ++; 
			msk |= 1 << names[j];
			while(!dq.empty() && lcp[dq.back()] >= lcp[j]) dq.pop_back();
			dq.pb(j);
			j++;			
		}
		if(!dq.empty() && dq.front() == i) dq.pop_front();
//		cerr << i << " " << j << " " << msk << " \t" << target << endl;
		if(msk == target){
			ans = max(ans, dq.empty() ? 0 : lcp[dq.front()]);
		}
		cnt[names[i]]--;
		if(cnt[names[i]] == 0) msk &= ~(1 << names[i]);
	}
	
	printf("%d\n", ans);
	return 0;
}
