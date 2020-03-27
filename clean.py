import os
import shutil
import filecmp

def is_empty_cpp(path):
	if '.cpp' not in path: return False
	return filecmp.cmp(path, '../workspace/cp-library/templates/template.cpp')

def should_delete(path, file_name):
	if path == '' or path == '.': return False
	if '~' in file_name: return True
	if 'git' in file_name or 'git' in path: return False
	if '.' not in file_name: return True
	if '.cpp' not in file_name and '.java' not in file_name: return True
	return is_empty_cpp(os.path.join(path, file_name))


for path, folders, files in os.walk('.'):
	for file_name in files:
		to = os.path.join(path, file_name)
		if should_delete(path, file_name):
			print(path, to)
			os.remove(to)