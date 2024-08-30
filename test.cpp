#include "BitVector.h"
#include <bits/stdc++.h>

using namespace std;

int main(void) {
	const size_t n = 1024;
	vector<bool> v(n);
	BitVector bv(n);
	bool l[n];
	printf_s("vector\tBitVector\tbool[]\n");
	printf_s("%d\t%d\t%d\n", sizeof(v), sizeof(bv), sizeof(l));
	return 0x00;
}

int main2() {
	bool bv[128];
	bv[0] = true;
	while (true);
	return 0x00;
}