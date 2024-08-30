#pragma once
#include <utility>
#include <windows.h>
#include <cstdio>
#include <mutex>

using std::pair;
using std::mutex;

struct Offset {
	size_t Offset;
	size_t ByteOffset;
	size_t BitOffset;
};

typedef struct Offset OFFSET;

class BitVector
{
private:
	BYTE* vector;
	size_t length = 0;
	size_t size = 0;
	unsigned short alignlen = 1;
	mutex mtx;	//负责vector和buffer的线程锁

public:
	BitVector(void);
	BitVector(size_t len, size_t alignlen = 1);
	~BitVector(void);
	bool Get(size_t index);
	bool Set(size_t index, bool val);
	bool& operator[](size_t size) = delete;
	void TestShow(void);
private:
	BYTE getMaskCode(OFFSET offset);
	OFFSET getOffset(size_t index);
};