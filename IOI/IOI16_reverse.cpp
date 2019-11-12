#include "reverse.h"
#include <algorithm>

std::vector<long long> reverse(std::vector<long long> a) {
	std::reverse(a.begin(), a.end());
	return a;
}
