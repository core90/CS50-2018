from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    return list(set(a.split('\n')).intersection(b.split('\n')))  # .split splits the string at given condition(for example: '\n')


def sentences(a, b):
    """Return sentences in both a and b"""

    return list(set(sent_tokenize(a)).intersection(sent_tokenize(b)))  # sent_tokenize splits the string into sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    c = len(a) - n + 1
    d = len(b) - n + 1
    list_a = list()
    list_b = list()

    for i in range(c):
        s = a[i:i + n]
        list_a.append(s)

    for j in range(d):
        t = b[j:j + n]
        list_b.append(t)

    list_c = list(set(list_a).intersection(list_b))

    return list_c
