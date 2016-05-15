name = "SAMANTHA";
ctr = 0;
L = [];

def validate(s):
	global ctr,L;
	if len(s) < 3: return;
	
	A = 0;
	for c in s: A |= c == 'A';
	if not A: return;
	
	i = 0;
	while i < len(s):
		if s[i] == 'A':
			j = i;
			while j < len(s) and s[j] == 'A': j += 1;
			if j - i != 1: return;
			i = j;
		else : i += 1;		 
	
	i = 0;
	while i < len(s):
		if s[i] != 'A':
			j = i;
			while j < len(s) and s[j] != 'A': j += 1;
			if j - i > 3: return;
			i = j;
		else : i = i + 1;
	ctr += 1;
	L.append(s);

def generate(i,s):
	if i == len(name):
		validate(s);
		return;
	generate(i + 1,s);
	generate(i + 1,s + name[i]);

generate(0,"");
