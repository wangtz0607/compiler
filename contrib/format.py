import sys


def convert_line_endings(source):
    source = source.replace('\r\n', '\n')
    source = source.replace('\r', '\n')
    return source


def trim_trailing_whitespaces(source):
    return '\n'.join([line.rstrip(' \t') for line in source.split('\n')])


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
            lines[i:j + 1] = sorted(lines[i:j + 1], key=str.lower)
            i = j
        i += 1
    return '\n'.join(lines)


def format(source):
    source = convert_line_endings(source)
    source = trim_trailing_whitespaces(source)
    source = trim_final_newlines(source)
    source = sort_includes(source)
    return source


def main():
    for path in sys.argv[1:]:
        with open(path, mode='r', encoding='utf-8') as file:
            source = file.read()
        formatted_source = format(source)
        if formatted_source != source:
            with open(path, mode='w', encoding='utf-8') as file:
                file.write(formatted_source)


if __name__ == '__main__':
    main()
