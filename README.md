# Limit Densities of Patterns in Permutation Inflations

This code computes densities of patterns in the inflations of permutations with
formulas in [Limit Densities of Patterns in Permutation Inflations](https://arxiv.org/abs/1809.08490).
It also includes optimized programs to search for examples of permutations in
the `search/` directory, as well as an empirical verification through random
simulations.

To run, [Python 3](https://www.python.org/) and [C++](https://gcc.gnu.org/) are
required.

## Example

```python
from permutation import Permutation
from inflatable import inflated_density, is_inflatable

inflated_density(Permutation('12'), Permutation('1')) # => 1/2
inflated_density(Permutation('12'), Permutation('1234')) # => 7/8
inflated_density(Permutation('21'), Permutation('1234')) # => 1/8

is_inflatable(2, Permutation('472951836')) # => True
is_inflatable(3, Permutation('472951836')) # => False
is_inflatable(2, Permutation('2cbdf8419hea3576g')) # => True
is_inflatable(3, Permutation('2cbdf8419hea3576g')) # => True
```

```bash
$ cd search
$ g++ -std=c++11 inflatable_search.cpp -o inflatable_search
$ ./inflatable_search 17 1000000
#16932: 6,3,16,10,13,14,7,1,9,17,11,4,5,8,2,15,12
#41987: 16,5,4,10,11,12,3,1,9,17,15,6,7,8,14,13,2
#48276: 14,10,3,5,16,7,1,12,9,6,17,11,2,13,15,8,4
#51827: 4,7,15,12,5,17,10,2,9,16,8,1,13,6,3,11,14
#62293: 12,4,3,8,16,17,11,5,9,13,7,1,2,10,15,14,6
#66657: 3,7,14,10,13,17,6,2,9,16,12,1,5,8,4,11,15
#117786: 14,10,3,11,1,16,6,5,9,13,12,2,17,7,15,8,4
#117855: 8,1,13,15,7,12,16,4,9,14,2,6,11,3,5,17,10
#130945: 14,3,7,8,13,12,2,17,9,1,16,6,5,10,11,15,4
#151781: 11,2,14,12,13,3,8,1,9,17,10,15,5,6,4,16,7
#163406: 6,3,10,16,17,11,5,4,9,14,13,7,1,2,8,15,12
#173492: 10,14,13,2,7,1,12,3,9,15,6,17,11,16,5,4,8
#187820: 8,4,15,16,1,7,12,13,9,5,6,11,17,2,3,14,10
#195079: 7,13,3,17,4,10,6,16,9,2,12,8,14,1,15,5,11
#272570: 8,4,17,12,2,7,13,15,9,3,5,11,16,6,1,14,10
#280667: 5,14,8,2,17,11,6,15,9,3,12,7,1,16,10,4,13
#284963: 6,7,17,13,3,10,2,14,9,4,16,8,15,5,1,11,12
#285731: 13,4,8,16,1,7,12,15,9,3,6,11,17,2,10,14,5
...
```

```bash
$ python3 random_simulation.py
Generating permutation...

Computing densities...

pi  Expected   Sampled    Delta
===================================
123 0.14197531 0.14072019 -0.001255
132 0.17901235 0.17977029 0.000758
213 0.17901235 0.17949287 0.000481
231 0.17901235 0.17953448 0.000522
312 0.17901235 0.17940687 0.000395
321 0.14197531 0.14107529 -0.000900

Done!
```
