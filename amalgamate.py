import argparse
import datetime
import re
import os

def add_warning(content):
    content += '/**\n'
    content += ' * WARNING:\n'
    content += ' * This file is automatically generated by amalgamate.py, any modifications to\n'
    content += ' * it will be overwritten by next generation.\n'
    content += ' * If you have any improvements / feature requests, please kindly report it to\n'
    content += ' * https://github.com/qgymib/libev so it can be keeped.\n'
    content += ' *\n'
    content += ' * GENERATE DATE: ' + str(datetime.datetime.now()) + '\n'
    content += ' */\n'
    return content

def add_license(content):
    # Read license
    license_file = open('LICENSE', 'r')
    license_lines = license_file.read().splitlines()
    license_file.close()
    # Write license
    content += '/**\n'
    for line in license_lines:
        content += ' * ' + line + '\n'
    content += ' */\n'
    return content

def process_file(content, src_path):
    # Read content
    f = open(src_path, 'r', encoding='UTF-8')
    data = f.read()
    f.close()
    # Replace #include
    data = re.sub('(#\\s*include\\s+"[-\\w/]+\\.h")', '/* AMALGAMATE: \\1 */', data)
    # Write content
    content += '///////////////////////////////////////////////////////////////////////////////\n'
    content += '// file: ' + src_path + '\n'
    content += '///////////////////////////////////////////////////////////////////////////////\n'
    #content += '#line 1 "' + src_path + '"\n'
    content += data
    return content

def read_content(path):
    f = open(path, 'r', encoding='UTF-8')
    data = f.read()
    f.close()
    return data

def do_amalgamate_header(hdr_list):
    content = ''
    content = add_license(content)
    content = add_warning(content)
    # Read content
    content += read_content(hdr_list[0])

    while True:
        m = re.search('#\\s*include\\s+"([-\\w/]+)\\.h"', content)
        if m == None:
            break
        for c in hdr_list:
            if c.find(m.group(1)) != -1:
                content = content[:m.start(0)] + read_content(c) + content[m.end(0):]

    return content

def do_amalgamate_source(src_hdr, src_hdr_os_win, src_hdr_os_unix, src, src_os_win, src_os_unix):
    content = ''
    content = add_license(content)
    content = add_warning(content)

    content += '#define EV_AMALGAMATE_BUILD\n'
    content += '#define _GNU_SOURCE\n'
    content += '#include "ev.h"\n'

    for source in src_hdr:
        content = process_file(content, source)

    content += '\n#if defined(_WIN32) /* AMALGAMATE: `#if defined(_WIN32)\' (1/3) */\n'
    for source in src_hdr_os_win:
        content = process_file(content, source)
    content += '\n#else /* AMALGAMATE: `#if defined(_WIN32)\' (2/3) */\n'
    for source in src_hdr_os_unix:
        content = process_file(content, source)
    content += '\n#endif /* AMALGAMATE: `#if defined(_WIN32)\' (3/3) */\n'

    for source in src:
        content = process_file(content, source)

    content += '\n#if defined(_WIN32) /* AMALGAMATE: `#if defined(_WIN32)\' (1/3) */\n'
    for source in src_os_win:
        content = process_file(content, source)
    content += '\n#else /* AMALGAMATE: `#if defined(_WIN32)\' (2/3) */\n'
    for source in src_os_unix:
        content = process_file(content, source)
    content += '\n#endif /* AMALGAMATE: `#if defined(_WIN32)\' (3/3) */\n'

    return content

if __name__ == '__main__':
    cmd_parser = argparse.ArgumentParser(
        prog = 'amalgamate',
        description = 'Amalgamate libev headers and sources')
    cmd_parser.add_argument('--out', required = True)
    cmd_parser.add_argument('--public_hdr', required = True)
    cmd_parser.add_argument('--src_hdr', required = True)
    cmd_parser.add_argument('--src_hdr_os_win', required = True)
    cmd_parser.add_argument('--src_hdr_os_unix', required = True)
    cmd_parser.add_argument('--src', required = True)
    cmd_parser.add_argument('--src_os_win', required = True)
    cmd_parser.add_argument('--src_os_unix', required = True)

    args = cmd_parser.parse_args()
    os.makedirs(args.out, exist_ok=True)

    content = do_amalgamate_header(args.public_hdr.split(','))
    dst_file = open(args.out + '/ev.h', 'w', encoding='UTF-8')
    dst_file.write(content)
    dst_file.close()

    content = do_amalgamate_source(
        args.src_hdr.split(','),
        args.src_hdr_os_win.split(','),
        args.src_hdr_os_unix.split(','),
        args.src.split(','),
        args.src_os_win.split(','),
        args.src_os_unix.split(','))
    dst_file = open(args.out + '/ev.c', 'w', encoding='UTF-8')
    dst_file.write(content)
    dst_file.close()
