// Optimized C++ code for finding inflatable permutations through random search.
// Only checks centrally symmetric permutations
// Usage: ./inflatable_search 17 1000000 > output.txt
// (Proven that length % 144 must be one of 0, 1, 17, 64, 80, or 81)

#include <algorithm>
#include <iostream>
#include <string>
#include <random>

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

inline bool is_inflatable(int N, int* P, int val1, int val2) {
	int inversions = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			inversions += P[i] > P[j];
		}
	}

	// Must be 2-inflatable to be 3-inflatable
	if (inversions * 2 != N * (N - 1) / 2)
		return false;

	int cnt[6] = {0};
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			for (int k = j + 1; k < N; k++) {
				++cnt[perm_id(P[i], P[j], P[k])];
			}
		}
	}

	return (cnt[0] == val1 && cnt[5] == val1
		&& cnt[1] == val2 && cnt[2] == val2
		&& cnt[3] == val2 && cnt[4] == val2);
}

int main(int argc, char* argv[]) {
	// Check input
	if (argc != 3) {
		std::cerr << "Usage: ./inflatable_search LENGTH LIMIT > output.txt" << std::endl;
		return 1;
	}

	// Parse input
	int N = std::stoi(argv[1]);
	int M = N / 2;
	long long limit = std::stoll(argv[2]);

	int* S = new int[N];
	int* A = new int[M];

	// Initialize
	for (int i = 0; i < M; i++) {
		A[i] = i;
	}

	std::random_device rd;
	std::mt19937 g(rd());

	int val1 = (2 * N - 7) * (N * (N - 1) * (N - 2)) / 6;
	int val2 = (4 * N - 5) * (N * (N - 1) * (N - 2)) / 6;
	if (val1 % (12 * (N - 2)) || val2 % (24 * (N - 2))) {
		std::cerr << "Length of " << N << " does not satisfy divisibility requirements for 3-inflatable permutations to exist." << std::endl;
		return 1;
	}
	val1 /= 12 * (N - 2);
	val2 /= 24 * (N - 2);

	// Search
	long long cnt = 0;
	long long found = 0;
	while (cnt++ < limit) {
		std::shuffle(A, A + M, g);
		for (int i = 0; i < M; i++) {
			S[i] = A[i];
			S[N - 1 - i] = N - 1 - A[i];
			if (g() % 2)
				std::swap(S[i], S[N - 1 - i]);
		}

		if (N % 2)
			S[M] = M;

		if (is_inflatable(N, S, val1, val2)) {
			++found;
			std::cout << '#' << cnt << ": ";
			for (int i = 0; i < N; i++) {
				std::cout << S[i] + 1;
				if (i != N - 1)
					std::cout << ',';
			}
			std::cout << std::endl;
		}
	}

	std::cout << "Done. Generated " << limit << " centrally symmetric permutations of length " << N << ", found " << found << " total 3-inflatable permutation(s)." << std::endl;
	return 0;
}
