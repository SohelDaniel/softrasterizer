#ifndef TEST_H
#define TEST_H

#include <cmath>
#include <iostream>

// Minimal assertion harness: no dependencies, one binary, non-zero exit on
// failure so `make test` fails the build.
namespace test {

inline int checks = 0;
inline int failures = 0;

inline void report(bool ok, const char* expr, const char* file, int line) {
	checks++;
	if (ok) return;
	failures++;
	std::cerr << file << ':' << line << ": FAILED  " << expr << '\n';
}

inline bool near(double a, double b, double eps = 1e-5) {
	return std::fabs(a - b) <= eps;
}

inline int summary() {
	std::cout << checks - failures << '/' << checks << " checks passed\n";
	return failures == 0 ? 0 : 1;
}

}  // namespace test

#define CHECK(expr)         ::test::report((expr), #expr, __FILE__, __LINE__)
#define CHECK_NEAR(a, b)    ::test::report(::test::near((a), (b)), #a " ~= " #b, __FILE__, __LINE__)

#endif
