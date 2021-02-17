import os
import sys
import subprocess
import shutil

astgen_exe = sys.argv[1]
binding_dir = sys.argv[2]
output_dir = sys.argv[3]
ref_dir = sys.argv[4]
if len(sys.argv) >= 5:
    astgen_args = sys.argv[5:]
else:
    astgen_args = []

# Clean up an existing output directory and make sure it exists fresh
shutil.rmtree(output_dir, ignore_errors=True)
os.makedirs(output_dir)

args = [astgen_exe, binding_dir, '-o', output_dir, '--'] + astgen_args
print('Running ' + ' '.join(args))

result = subprocess.Popen(args, stderr=subprocess.STDOUT, stdout=subprocess.PIPE) 
(stdout, _) = result.communicate(None)

if result.returncode != 0:
    print('astgen exited with non-zero return code {}'.format(result.returncode))
    print(stdout)
    sys.exit(result.returncode)

# diff with a crummy attempt to ignore paths
result = subprocess.Popen(['diff', '-I.*\"\/.*\/.*', output_dir, ref_dir], stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
(stdout, _) = result.communicate(None)

if result.returncode != 0:
    print(stdout)
    sys.exit(255)
