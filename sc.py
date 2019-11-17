from os import walk,system

ext = set()
for path,subs,files in walk('.'):
	break


for sub in subs:
	if sub in ['RemoteSystemsTempFiles','.git']: continue
	for path,_,files in walk('./' + sub):
		for f in files:
			if '.' not in f:
				system('rm %s/%s'%(path,f))
				print(f)
				continue
			i = f.index('.')
			ext = f[(i+1):].strip()
			if "cpp" not in ext:
				# system('rm %s/%s'%(path,f))
				print(ext)
