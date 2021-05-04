import os
import sys
import subprocess
import shutil

astgen_exe = sys.argv[1]
asttoc_exe = sys.argv[2]
binding_dir = sys.argv[3]
output_dir = sys.argv[4]
project_name = sys.argv[5]
ref_dir = sys.argv[6]
if len(sys.argv) >= 7:
    astgen_args = sys.argv[7:]
else:
    astgen_args = []

# Clean up an existing output directory and make sure it exists fresh
shutil.rmtree(output_dir, ignore_errors=True)
os.makedirs(output_dir)

output_ast_dir = os.path.join(output_dir, 'ast')

# Generate AST
args = [astgen_exe, binding_dir, '-o', output_ast_dir, '--'] + astgen_args
print('Running ' + ' '.join(args))

result = subprocess.Popen(args, stderr=subprocess.STDOUT, stdout=subprocess.PIPE) 
(stdout, _) = result.communicate(None)
print(stdout)

if result.returncode != 0:
    print('astgen exited with non-zero return code {}'.format(result.returncode))
    sys.exit(result.returncode)


# Generate C and Rust
args = [asttoc_exe, output_ast_dir, '-o', output_dir, '-p', project_name]
print('Running ' + ' '.join(args))

result = subprocess.Popen(args, stderr=subprocess.STDOUT, stdout=subprocess.PIPE) 
(stdout, _) = result.communicate(None)
print(stdout)

if result.returncode != 0:
    print('asttoc exited with non-zero return code {}'.format(result.returncode))
    sys.exit(result.returncode)


# Run cargo test on Rust
rustdir = os.path.join(output_dir, "%s-sys" % project_name)
rust_src_dir = os.path.join(rustdir, 'src')

# copy the test file over if there is one
test_file = os.path.join(os.path.dirname(binding_dir), 'test.rs')
if os.path.isfile(test_file):
    shutil.copyfile(test_file, os.path.join(rust_src_dir, 'test.rs'))

result = subprocess.Popen(['cargo', 'test'], cwd=rustdir, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, shell=False)
(stdout, _) = result.communicate(None)

# Remove cargo build stuff
shutil.rmtree(os.path.join(rustdir, 'target'), ignore_errors=True)
os.remove(os.path.join(rustdir, 'Cargo.lock'))

if result.returncode != 0:
    print('cargo test failed')
    print(stdout)
    sys.exit(255)

# diff entire directory with a crummy attempt to ignore paths
ignore_regex = '-I\s*\"\/.*\/.*'
result = subprocess.Popen(['diff', '-r', ignore_regex, output_dir, ref_dir], stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
(stdout, _) = result.communicate(None)

if result.returncode != 0:
    print(stdout)
    sys.exit(255)

