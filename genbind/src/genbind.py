#!/usr/bin/env python3

"""genbind.

Usage:
    genbind.py <header-path>... [--namespace <ns>] [--namespace-internal <nsi>] [--namespace-public <nsp>] [-v <verbosity>] [--clang-arg <arg>...] [--output-path <path>] [--format]

Options:
    -v <level>, --verbosity <level>       Verbosity level of output. 0=Errors, 1=Warnings, 2=Info, 3=Debug, 4=Trace
    -n <ns>, --namespace <ns>             Target namespace from which to scrape bindable items (e.g. Imf_2_5)
    -i <nsi>, --namespace-internal <nsi>  The target library's internal #define for the namespace (e.g. OPENEXR_IMF_INTERNAL_NAMESPACE)
    -p <nsp>, --namespace-public <nsp>    The target library's public #define for the namespace (e.g. Imf)
    -a <arg>..., --clang-arg <arg>...     Arguments to pass to Clang, e.g. the include path to the library. Can be repeated
    -o <path>, --output-path <path>       Directory under which to write the output binding files. Will be created if it does not exist
    -f, --format                          Run clang-format on the output binding file
"""

import os
from docopt import docopt
import glob
import pathlib
import subprocess

def find_header_paths(input_paths: list):
    print('finding headers in ', input_paths)
    result = []
    for p in input_paths:
        if os.path.isfile(p):
            result.append(os.path.abspath(p))
        elif os.path.isdir(p):
            for fn in glob.iglob(p + '/**/*', recursive=True):
                base, ext = os.path.splitext(fn)
                if ext in ['.h', '.hpp', '.hxx', '.hh']:
                    result.append(os.path.abspath(fn))
        else:
            print(f"path {p} is not file or directory")

    return result

if __name__ == '__main__':
    args = docopt(__doc__)
    print(args)

    script_dir = pathlib.Path(__file__).parent.absolute()
    binary = os.path.join(script_dir, 'genbind')

    headers = find_header_paths(args['<header-path>'])

    options = []
    if '--verbosity' in args:
        options += ['-v', args['--verbosity']]
    if '--namespace' in args:
        options += ['-namespace', args['--namespace']]
    if '--namespace-internal' in args:
        options += ['-namespace-internal', args['--namespace-internal']]
    if '--namespace-public' in args:
        options += ['-namespace-public', args['--namespace-public']]
    if '--output-path' in args:
        options += ['-o', args['--output-path']]
    if '--clang-arg' in args:
        options.append('--')
        for a in args['--clang-arg']:
            options += a.split()

    for header in headers:
        cmd = [binary, header] + options
        subprocess.run(cmd)

