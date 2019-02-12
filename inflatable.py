from permutation import Permutation
from fractions import Fraction
import math


def inflated_density(pi, tau):
    ret = Fraction()
    for b, sigma in pi.partitions():
        cur = Fraction(1)
        for x in b:
            cur /= math.factorial(x) ** 2
        cur *= math.factorial(len(pi))
        cur *= tau.occurrences(sigma)
        ret += cur
    ret /= len(tau) ** len(pi)
    return ret


def is_inflatable(k, tau):
    for pi in Permutation.of_length(k):
        if inflated_density(pi, tau) != Fraction(1, math.factorial(k)):
            return False
    return True


def main():
    # Test 3-inflatable permutation of length 17
    tau = Permutation('2cbdf8419hea3576g')
    print('Densities in inflation of', tau)
    for pi in Permutation.of_length(3):
        print(pi, inflated_density(pi, tau))

    # Incorrect example from Cooper & Petrarca
    tau = Permutation('472951836')
    print('Densities in inflation of', tau)
    for pi in Permutation.of_length(3):
        print(pi, inflated_density(pi, tau))


if __name__ == '__main__':
    main()
