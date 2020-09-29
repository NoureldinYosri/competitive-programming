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



vector<bool> buildTypeMap(const vi & txt){
	int n = txt.size();
	vector<bool> isSType(n + 1, true);
	if(txt.empty()) return isSType;
	isSType[n-1] = false;
	for(int i = n-2; i >= 0; i--){
		if(txt[i] != txt[i+1]) isSType[i] = txt[i] < txt[i+1];
		else isSType[i] = isSType[i+1];
	}
	return isSType;
}

bool isLMSChar(int i, const vector<bool> & isSType){
	return i && isSType[i] && !isSType[i-1];
}


bool lmsSubstringsAreEqual(const vi & txt, const vector<bool> & isSType, int a, int b){
	if(a == sz(txt) || b == sz(txt)) return false;
	for(int i = 0;; i++) {
		bool aIsLMS = isLMSChar(i + a, isSType);
		bool bIsLMS = isLMSChar(i + b, isSType);
		
		if(i && aIsLMS && bIsLMS) return true;
		if(aIsLMS != bIsLMS) return false;
		
		if(txt[i + a] != txt[i + b]) return false;
	}
}

vi findBucketSizes(const vi & txt, int alphabetSize=256){
	vi freq(alphabetSize, 0);
	for(int c : txt) freq[c]++;
	return freq;
}

vi findBucketHeads(const vi & bucketSizes){
	vi pref;
	int sum = 1;
	for(int f : bucketSizes){
		pref.pb(sum);
		sum += f;
	}
	return pref;
}


vi findBucketTails(const vi & bucketSizes){
	vi pref;
	int sum = 1;
	for(int f : bucketSizes){
		sum += f;
		pref.pb(sum-1);
	}
	return pref;
}

vi guessLMSSort(const vi & txt, const vi & bucketSizes, const vector<bool> & isSType) {
	int n = sz(txt);
	vi guessedSuffixArray(n + 1, -1);
	auto bucketTails = findBucketTails(bucketSizes);
	loop(i, n){
		if(!isLMSChar(i, isSType)) continue;
		int bucketIndex = txt[i];
		guessedSuffixArray[bucketTails[bucketIndex]] = i;
		bucketTails[bucketIndex] --;
	}
	guessedSuffixArray[0] = n;
	return guessedSuffixArray;
}

void induceSortL(const vi & txt, vi & guessedSuffixArray, const vi & bucketSizes, const vector<bool> & isSType) {
	auto bucketHeads = findBucketHeads(bucketSizes);
	int n = sz(guessedSuffixArray);
	loop(i, n){
		if (guessedSuffixArray[i] == -1) continue;
		int j = guessedSuffixArray[i] - 1;
		if(j < 0) continue;
		if (isSType[j]) continue;
		int bucketIndex = txt[j];
		guessedSuffixArray[bucketHeads[bucketIndex]] = j;
		bucketHeads[bucketIndex] ++;
	}
}

void induceSortS(const vi & txt, vi & guessedSuffixArray, const vi & bucketSizes, const vector<bool> & isSType){
	auto bucketTails = findBucketTails(bucketSizes);
	for(int i = sz(guessedSuffixArray)-1; i >= 0; i--){
		int j = guessedSuffixArray[i] - 1;
		if(j < 0) continue;
		if(!isSType[j]) continue;
		int bucketIndex = txt[j];
		guessedSuffixArray[bucketTails[bucketIndex]] = j;
		bucketTails[bucketIndex] --;
	}
}

void summariseSuffixArray(const vi & txt, const vi & guessedSuffixArray, const vector<bool> & isSType,
								vi & summarytxt, int & summaryAlphabetSize, vi & summarySuffixOffsets){
	
	int n = sz(txt);
	vi lmsNames(n+1, -1);
	
	int currentName = 0;
	
	lmsNames[guessedSuffixArray[0]] = currentName;
	int lastLMSSuffixOffset = guessedSuffixArray[0];

	for(int i = 1; i < sz(guessedSuffixArray); i++){
		int suffixOffset = guessedSuffixArray[i];
		if (!isLMSChar(suffixOffset, isSType)) continue;
		
		if (!lmsSubstringsAreEqual(txt, isSType, lastLMSSuffixOffset, suffixOffset))
			currentName++;
		
		lastLMSSuffixOffset = suffixOffset;
		lmsNames[suffixOffset] = currentName;
	}
	for(int i = 0; i < sz(lmsNames); i++){
		int name = lmsNames[i];
		if(name == -1) continue;
		summarySuffixOffsets.push_back(i);
		summarytxt.push_back(name);
	}
	summaryAlphabetSize = currentName + 1;
}

vi makeSuffixArrayByInducedSorting(const vi &, const int);

vi makeSummarySuffixArray(const vi & summaryString, const int summaryAlphabetSize){
	if(summaryAlphabetSize == sz(summaryString)){
		int n = sz(summaryString);
		vi summarySuffixArray(n+1, -1);
		summarySuffixArray[0] = n;
		for(int x = 0; x < n; x++){
			int y = summaryString[x];
			summarySuffixArray[y+1] = x;
		}
		return summarySuffixArray;
	} else {
		return makeSuffixArrayByInducedSorting(
             summaryString,
             summaryAlphabetSize);
	}
	
}

vi accurateLMSSort(const vi & txt, const vi & bucketSizes, const vector<bool> & isSType,
         const vi & summarySuffixArray, const vi & summarySuffixOffsets){

	int n = sz(txt);
	vi suffixOffsets(n+1, -1);
	auto bucketTails = findBucketTails(bucketSizes);
	for(int i = sz(summarySuffixArray)-1; i > 0; i--){
		int stringIndex = summarySuffixOffsets[summarySuffixArray[i]];
		int bucketIndex = (stringIndex < n) ? txt[stringIndex] : 0;
		suffixOffsets[bucketTails[bucketIndex]] = stringIndex;
		bucketTails[bucketIndex] --;
	}
	suffixOffsets[0] = n;
	return suffixOffsets;
 }

vi makeSuffixArrayByInducedSorting(const vi & txt, const int alphabetSize = 256){
	auto typemap = buildTypeMap(txt);
	

	auto bucketSizes = findBucketSizes(txt, alphabetSize);
	

	auto guessedSuffixArray = guessLMSSort(txt, bucketSizes, typemap);


	induceSortL(txt, guessedSuffixArray, bucketSizes, typemap);
	induceSortS(txt, guessedSuffixArray, bucketSizes, typemap);

	vi summarytxt, summarySuffixOffsets;
	int summaryAlphabetSize; 
	summariseSuffixArray(txt, guessedSuffixArray, typemap, summarytxt, summaryAlphabetSize, summarySuffixOffsets);


	auto summarySuffixArray = makeSummarySuffixArray(
		summarytxt,
		summaryAlphabetSize
	);
	

	auto result = accurateLMSSort(txt, bucketSizes, typemap,
			summarySuffixArray, summarySuffixOffsets);


	induceSortL(txt, result, bucketSizes, typemap);
	induceSortS(txt, result, bucketSizes, typemap);

	return result;
}


vi string2seq(string s){
	vi txt{s.begin(), s.end()};
	return txt;
}

inline int getChar(const vi & txt, int i){
	return (i < sz(txt)) ? txt[i] : -1;
}

vi getLCP(const vi & SA, const vi & txt){
	vi lcp(sz(SA), 0);
	vi iSA(sz(SA));
	loop(i, sz(SA)) iSA[SA[i]] = i;
	
	for(int i = 0, l = 0; i < sz(iSA); i++){
		if(iSA[i] == sz(SA)-1) continue;
		int j = SA[iSA[i] + 1];
		
		while(getChar(txt, i + l) == getChar(txt, j + l)) l++;
		lcp[iSA[i] + 1] = l;
		
		if(l) l--;
	}	
	return lcp;
}

char txt[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	
	scanf("%s", txt);
	int n = strlen(txt);
	copy(txt, txt + n, txt + n);
	txt[2*n] = 0;
	string s(txt);
	vi itxt = string2seq(s);
	vi SA = makeSuffixArrayByInducedSorting(itxt);	
	vi lcp = getLCP(SA, itxt);

	int j = 0;
	for(; j < sz(SA); j++) {
		if(SA[j] >= n) continue;
		break;
	}
	int ans = SA[j];
	while(j+1 < sz(SA) && lcp[j+1] >= n){
		j++;
		ans = min(ans, SA[j]);
	}
	cout << ans << endl;
	return 0;
}
