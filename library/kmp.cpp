
int GetLen(char c,int l,char *s){
	while(l && s[l] != c) l = pf[l - 1];
	if(s[l] == c) l++;
	return l;
}
 
void BuildFailure(char *s){
	pf[0] = 0;
	int n = strlen(s);
	range(i,1,n - 1) pf[i] = GetLen(s[i],pf[i - 1],s);
}
