import os
import sys
import subprocess
import shutil

astgen_exe = sys.argv[1]
asttoc_exe = sys.argv[2]
binding_dir = sys.argv[3]
output_dir = sys.argv[4]
ref_dir = sys.argv[5]
if len(sys.argv) >= 6:
    astgen_args = sys.argv[6:]
else:
    astgen_args = []

# Clean up an existing output directory and make sure it exists fresh
shutil.rmtree(output_dir, ignore_errors=True)
os.makedirs(output_dir)

output_ast_dir = os.path.join(output_dir, 'ast')
output_c_dir = os.path.join(output_dir, 'c')

# Generate AST
args = [astgen_exe, binding_dir, '-o', output_ast_dir, '--'] + astgen_args
print('Running ' + ' '.join(args))

result = subprocess.Popen(args, stderr=subprocess.STDOUT, stdout=subprocess.PIPE) 
(stdout, _) = result.communicate(None)
print(stdout)

if result.returncode != 0:
    print('astgen exited with non-zero return code {}'.format(result.returncode))
    sys.exit(result.returncode)


# Generate C
args = [asttoc_exe, output_ast_dir, '-o', output_c_dir]
print('Running ' + ' '.join(args))

result = subprocess.Popen(args, stderr=subprocess.STDOUT, stdout=subprocess.PIPE) 
(stdout, _) = result.communicate(None)
print(stdout)

if result.returncode != 0:
    print('asttoc exited with non-zero return code {}'.format(result.returncode))
    sys.exit(result.returncode)


# diff entire directory with a crummy attempt to ignore paths
result = subprocess.Popen(['diff', '-I\s*\"\/.*\/.*', output_dir, ref_dir], stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
(stdout, _) = result.communicate(None)

if result.returncode != 0:
    print(stdout)
    sys.exit(255)
