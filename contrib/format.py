import argparse
import re
import sys


def convert_line_endings(source):
    return source.replace('\r\n', '\n').replace('\r', '\n')


def expand_tabs(source):
    return source.replace('\t', '    ')


def trim_trailing_whitespaces(source):
    return '\n'.join([line.rstrip(' ') for line in source.split('\n')])


def trim_final_newlines(source):
    return source.rstrip('\n') + '\n'


def sort_includes(source):
    lines = source.split('\n')
    n = len(lines)
    i = 0
    while i < n:
        if lines[i].startswith('#include'):
            j = i
            while j + 1 < n and lines[j + 1].startswith('#include'):
                j += 1
            lines[i : j + 1] = sorted(
                lines[i : j + 1],
                key=lambda line: re.search(r'<(.*)>|"(.*)"', line).group().lower(),
            )
            i = j
        i += 1
    return '\n'.join(lines)


def reformat(source):
    source = convert_line_endings(source)
    source = expand_tabs(source)
    source = trim_trailing_whitespaces(source)
    source = trim_final_newlines(source)
    source = sort_includes(source)
    return source


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('input', nargs='+')
    parser.add_argument('--check', action='store_true')

    args = parser.parse_args()
    exit_code = 0

    for path in args.input:
        with open(path, mode='r', encoding='utf-8') as file:
            source = file.read()
        reformatted_source = reformat(source)
        if reformatted_source != source:
            if args.check:
                print(path)
                exit_code = 1
            else:
                with open(path, mode='w', encoding='utf-8') as file:
                    file.write(reformatted_source)

    return exit_code


if __name__ == '__main__':
    sys.exit(main())
