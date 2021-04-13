#! /usr/bin/env python3

import os
import base64

if __name__ == '__main__':
    resdir = os.path.join(os.path.abspath(os.path.dirname(__file__)), 'resources')

    cpp_str = ''
    arrays = []
    filenames = []

    i = 0
    for dirname, subdirs, files in os.walk(resdir):
        for f in files:
            abs_fn = os.path.join(dirname, f)
            if dirname == resdir:
                rel_fn = f
            else:
                relpath = os.path.relpath(dirname, resdir)
                rel_fn = os.path.join(relpath, f)

            fin = open(abs_fn)
            text = fin.read()
            fin.close()

            b64 = base64.b64encode(bytes(text, 'utf-8'))

            cpp_str = f'{cpp_str}static const char data_{i}[] = {{ "{b64.decode()}" }};\n\n'
            arrays.append(f'data_{i}');
            filenames.append(rel_fn)

            i += 1

    cpp_str = f'{cpp_str}const char* cppmm_resource_arrays[] = {{\n'
    for a in arrays:
        cpp_str = f'{cpp_str}    {a},\n'
    cpp_str = f'{cpp_str}}};\n\n'

    cpp_str = f'{cpp_str}const char* cppmm_resource_filenames[] = {{\n'
    for f in filenames:
        cpp_str = f'{cpp_str}    "{f}",\n'
    cpp_str = f'{cpp_str}}};\n\n'

    cpp_str = f'{cpp_str}int num_files() {{ return {i}; }}\n\n'
    cpp_str = f'{cpp_str}const char* cppmm_resource_filename(int i) {{ return cppmm_resource_filenames[i]; }}\n\n'
    cpp_str = f'{cpp_str}const char* cppmm_resource_array(int i) {{ return cppmm_resource_arrays[i]; }}\n\n'

    cpp_file = open('src/resources.cpp', 'w')
    cpp_file.write(cpp_str)
    cpp_file.close()

    hpp_str = '''
#pragma once
int num_files();
const char* cppmm_resource_array(int i);
const char* cppmm_resource_filename(int i);
'''
    hpp_file = open('src/resources.hpp', 'w') 
    hpp_file.write(hpp_str)
    hpp_file.close()



