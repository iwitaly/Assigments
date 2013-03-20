__author__ = 'iwitaly'
from os import read, write

def analizeForDots(text, pattern):
    while pattern[0] == '.':
        pattern = pattern[1:]
        text = text[1:]

        if pattern == '':
            write(1, 'True')
            return

    if pattern in text:
        write(1, 'True')
    else:
        write(1, 'False')

def withFirstCharacter(text, pattern):
    arr = pattern.split('.')

    if len(arr) == 2:
        if arr[1] not in text:
            write(1, 'False')
            return
        else:
            text = text[len(arr[1])-1:]
            pattern = pattern[len(arr[1])-1:]

            analizeForDots(text, pattern)
    else:
        if arr[0] not in text[:len(arr[0])]:
            write(1, 'False')
            return
        else:
            write(1, 'True')

def solve(text, pattern):
    """
    find pattern in the text
    :string text:
    :string patter:
    """
    if len(text) < len(pattern):
        write(1, 'wrong len')
        return

    firstCharacter = pattern.split('^')

    if len(firstCharacter) == 2:
        withFirstCharacter(text, pattern[1:])
    else:
        analizeForDots(text, pattern)

if __name__ == '__main__':
    text = 'dbabcdsg'
    pattern = '......'

    solve(text, pattern)