import os
import sys
import subprocess
import shutil

cppmm_exe = sys.argv[1]
binding_dir = sys.argv[2]
output_dir = sys.argv[3]
ref_dir = sys.argv[4]
if len(sys.argv) >= 5:
    cppmm_args = sys.argv[5:]
else:
    cppmm_args = []

# Clean up an existing output directory and make sure it exists fresh
shutil.rmtree(output_dir, ignore_errors=True)
os.makedirs(output_dir)

result = subprocess.Popen([cppmm_exe, binding_dir, '-o', output_dir, '--'] + cppmm_args, stderr=subprocess.STDOUT, stdout=subprocess.PIPE) 
(stdout, _) = result.communicate(None)

if result.returncode != 0:
    print('cppmm exited with non-zero return code {}'.format(result.returncode))
    print(stdout)
    sys.exit(result.returncode)

result = subprocess.Popen(['diff', output_dir, ref_dir], stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
(stdout, _) = result.communicate(None)

if result.returncode != 0:
    print(stdout)
    sys.exit(255)
