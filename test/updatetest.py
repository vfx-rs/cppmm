#! /usr/bin/env python

import os
import sys
import shutil

# If called with no args, update all the tests, otherwise just update the ones we're called for
tests_to_update = []
if len(sys.argv) > 1:
    tests_to_update = sys.argv[1:]

# Assume we're running from the build directory
# TODO: do some exploration to find out where we are
src_test_path = os.path.join(os.path.dirname(os.getcwd()), 'test')
print('src_test_path: ', src_test_path)
build_test_path = os.path.join(os.getcwd(), 'test')
print('build_test_path: ', build_test_path)

# Get the complete list of directories in the source test directory
src_test_dirs = [d for d in os.listdir(src_test_path) if os.path.isdir(os.path.join(src_test_path, d))]

# Get the complete list of directories in the build test directory
build_test_dirs = [d for d in os.listdir(build_test_path) if os.path.isdir(os.path.join(build_test_path, d))]
print(build_test_dirs)

if len(tests_to_update) == 0:
    # We want to do all tests
    tests_to_update = build_test_dirs

for t in tests_to_update:
    print('Considering {}'.format(t))
    if t in build_test_dirs and os.path.isdir(os.path.join(build_test_path, t, 'output')):
        if t in src_test_dirs:
            ref_path = os.path.join(src_test_path, t, 'ref')
            output_path = os.path.join(build_test_path, t, 'output')
            print('removing {}'.format(ref_path))
            print('copying {} to {}'.format(output_path, ref_path))
            shutil.rmtree(ref_path)
            shutil.copytree(output_path, os.path.join(ref_path))
        else:
            print('WARNING: asked to update test "{}" but no source present in {}'.format(t, src_test_path))
    else:
        print('WARNING: asked to update test "{}" but no output present in {}'.format(t, build_test_path))

