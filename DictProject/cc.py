import subprocess, os, sys
from glob import glob

cwd = os.getcwd()
i, file_name = 0, []

for file in glob(cwd + "\\*.c"):
	# print(os.path.basename(file))
	file_name.append(os.path.basename(file))

if len(sys.argv) > 1 and len(sys.argv) < 3:
	prog_name = sys.argv[1]
	cmd = "gcc -o " + prog_name
	
	for name in file_name:
		cmd += " " + name 

	print(cmd)
	subprocess.run(cmd)

else:
	print("error")