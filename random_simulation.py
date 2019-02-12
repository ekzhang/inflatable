from permutation import Permutation
from inflatable import inflated_density
from fractions import Fraction
import math
import random


def test(tau, n):
    print('Generating permutation...\n')
    rnd = list(range(n))
    random.shuffle(rnd)
    inf = Permutation(p + x * n
        for x in tau
        for p in rnd)
    print('Computing densities...\n')
    cnts = inf.occurrence_counts(3)
    total = sum(count for pattern, count in cnts.most_common())
    print('pi  Expected   Sampled    Delta')
    print('===================================')
    for pi in Permutation.of_length(3):
        expected = float(inflated_density(pi, tau))
        sampled = cnts[pi] / total
        deviation = sampled - expected
        print('{} {:.8f} {:.8f} {:.6f}'.format(
            pi, expected, sampled, deviation))
    print('\nDone!')


if __name__ == '__main__':
    test(Permutation('472951836'), 30)
