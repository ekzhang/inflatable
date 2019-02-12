#include <algorithm>
#include <iostream>
#include <string>

const int N = 17;
const int M = N / 2;
int S[N];
int A[M];

// 012: 0
// 021: 1
// 102: 2
// 120: 3
// 201: 4
// 210: 5
inline int perm_id(int a, int b, int c) {
	if (a < b && a < c) {
		if (b < c)
			return 0;
		else
			return 1;
	}
	else if (a < b || a < c) {
		if (b < c)
			return 2;
		else
			return 3;
	}
	else {
		if (b < c)
			return 4;
		else
			return 5;
	}
}

inline bool is_inflatable(int* P) {
	int inversions = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			inversions += P[i] > P[j];
		}
	}
	if (inversions * 2 != N * (N - 1) / 2)
		return false;

	int val1 = (2 * N - 7) * (N * (N - 1) * (N - 2)) / 6;
	int val2 = (4 * N - 5) * (N * (N - 1) * (N - 2)) / 6;
	if (val1 % (12 * (N - 2)) || val2 % (24 * (N - 2)))
		return false;
	val1 /= 12 * (N - 2);
	val2 /= 24 * (N - 2);

	int cnt[6] = {0};
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			for (int k = j + 1; k < N; k++) {
				cnt[perm_id(S[i], S[j], S[k])]++;
			}
		}
	}

	return (cnt[0] == val1 && cnt[5] == val1
		&& cnt[1] == val2 && cnt[2] == val2
		&& cnt[3] == val2 && cnt[4] == val2);
}

int main() {
	for (int i = 0; i < M; i++) {
		A[i] = i;
	}

	do {
		for (int mask = 0; mask < (1<<M); mask++) {
			for (int i = 0; i < M; i++) {
				S[i] = A[i];
				S[N - 1 - i] = N - 1 - A[i];
				if (mask & (1<<i))
					std::swap(S[i], S[N - 1 - i]);
			}
			S[M] = M;

			if (is_inflatable(S)) {
				for (int i = 0; i < N; i++) {
					std::cout << "123456789abcdefghijklmnopqrstuvwxyz"[S[i]];
				}
				std::cout << std::endl;
			}
		}
	} while (std::next_permutation(A, A + M));

	return 0;
}
