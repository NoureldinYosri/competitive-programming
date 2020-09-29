import os,sys
import shutil 
import argparse



parser = argparse.ArgumentParser()
parser.add_argument('-J','--judge', help='judge name',default = 'codeforces')
parser.add_argument('-C','--contest_id', help = 'contest id', default = None)
parser.add_argument('-P','--problem_name', help = 'problem name', default = None)
parser.add_argument('-D','--create_directory', default = False, action = 'store_true')

args = parser.parse_args()

path = args.judge

if args.contest_id is None and args.problem_name is None:
	print('no data')
	exit(0)
	
if args.contest_id is not None:
	path = os.path.join(path, args.contest_id)

if args.create_directory and args.problem_name:
	path = os.path.join(path, args.problem_name)

if not os.path.exists(path):
	os.makedirs(path)

templates_path = '../workspace/cp-library/templates/'
for f in 'template.cpp','tester.py':
	shutil.copy(os.path.join(templates_path, f),path)

os.system('touch ' + os.path.join(path, 'in.in'))

if any([judge in path for judge in ('codeforces', 'atcoder')]):
	n = 6
	if "codeforces" in path and int(args.contest_id) >= 10**5:
		n = 13
	for k in range(n):
		c = chr(ord('A') + k)
		to = os.path.join(path,c + '.cpp')
		if not os.path.exists(to):
			shutil.copy(os.path.join(path,'template.cpp'), to) 
	os.remove(os.path.join(path,'template.cpp'))

elif args.problem_name is not None:
	to = os.path.join(path,args.problem_name + '.cpp')
	if not os.path.exists(to):
		shutil.copy(os.path.join(path,'template.cpp'), to) 
	os.remove(os.path.join(path,'template.cpp'))	