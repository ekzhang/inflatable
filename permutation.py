from collections import Counter
import itertools
import operator

class Permutation(tuple):
    ALPHABET = '123456789abcdefghijklmnopqrstuvwxyz'

    def __new__(cls, iterable):
        indices = sorted(enumerate(iterable), key=operator.itemgetter(1))
        normalized = [None for _ in range(len(indices))]
        for order, (i, _) in enumerate(indices):
            normalized[i] = order
        return super(Permutation, cls).__new__(cls, normalized)

    def inverse(self):
        return Permutation(sorted(zip(range(len(self)), self), key=operator.itemgetter(1)))

    def compose(self, other):
        return Permutation(self[other[i]] for i in range(len(self)))

    def __mul__(self, other):
        return self.compose(other)

    def subperm(self, indices):
        return Permutation(self[i] for i in indices)

    def subperms(self, length):
        for indices in itertools.combinations(range(len(self)), length):
            yield self.subperm(indices)

    def occurrences(self, other):
        ret = 0
        for subperm in self.subperms(len(other)):
            if subperm == other:
                ret += 1
        return ret

    def occurrence_counts(self, length):
        return Counter(self.subperms(length))

    def inversions(self):
        ans = 0
        for i in range(len(self)):
            for j in range(i + 1, len(self)):
                if self[i] > self[j]:
                    ans += 1
        return ans

    def reverse(self):
        return Permutation(reversed(self))

    def __str__(self):
        return ''.join(self.ALPHABET[x] for x in self)

    def __repr__(self):
        return 'Permutation(%s)' % super(Permutation, self).__repr__()

    @classmethod
    def of_length(cls, n):
        for t in itertools.permutations(range(n), n):
            yield Permutation(t)

    def partitions(self):
        ret = []
        for include in itertools.product([False, True], repeat=len(self) - 1):
            segments = [[]]
            for i in range(len(self)):
                segments[-1].append(self[i])
                if i != len(self) - 1 and include[i]:
                    segments.append([])
            working = True
            for segment in segments:
                if max(segment) - min(segment) + 1 != len(segment):
                    working = False
            if working:
                ordering = Permutation(segments)
                ret.append(([len(segment) for segment in segments], ordering))
        return ret


def main():
    # Tests
    p = Permutation('31f25dabc')
    print(p)
    print(p.inverse())
    print(p * p.inverse())
    print(p.subperm([1, 4, 5, 6]))
    print(p.reverse())
    for q in Permutation.of_length(3):
        print(q, q * q)
    for lengths, ordering in p.partitions():
        print(lengths, ordering)
    print(p.occurrence_counts(3))


if __name__ == '__main__':
    main()
