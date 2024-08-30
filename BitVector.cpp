#include "BitVector.h"
#include <cstdlib>

#define GetUpInteger(val) (double)val-(int)val==0?val:(double)((int)val+1)

BitVector::BitVector(void):
	vector(nullptr), length(0), alignlen(1), size(0)
{
	std::unique_lock<std::mutex> _(this->mtx);
}

BitVector::BitVector(size_t len, size_t alignlen):
	length(len),alignlen(alignlen)
{
	std::unique_lock<std::mutex> _(this->mtx);
	this->size = GetUpInteger(len / (alignlen * 8));
	vector = (BYTE*)malloc(this->size);
	if (vector == nullptr)
		exit(1);
	ZeroMemory(vector, size);
	if (vector == nullptr)
		exit(1);
	return;
}

BitVector::~BitVector(void)
{
	std::unique_lock<std::mutex> _(this->mtx);
	if (this->vector != nullptr)
		free(this->vector);
	return;
}

bool BitVector::Get(size_t index)
{
	if (index >= this->length)
		return false;
	OFFSET offset=getOffset(index);
	BYTE mask = getMaskCode(offset);
	this->mtx.lock();
	BYTE vec = this->vector[offset.ByteOffset] & mask;
	this->mtx.unlock();
	return vec == 0x00 ? false : true;
}

bool BitVector::Set(size_t index, bool val)
{
	if (index >= this->length)
		return false;
	pair<OFFSET, bool> buffer;
	buffer.first = getOffset(index);
	buffer.second = val;
	if (buffer.first.Offset == ULLONG_MAX)	//buffer无需被写入
		return false;
	if (Get(buffer.first.Offset) == buffer.second)
		return true;
	BYTE byte = getMaskCode(buffer.first);
	this->mtx.lock();
	if (buffer.second)
		this->vector[buffer.first.ByteOffset] = this->vector[buffer.first.ByteOffset] + byte;
	else
		this->vector[buffer.first.ByteOffset] = this->vector[buffer.first.ByteOffset] - byte;
	this->mtx.unlock();
	buffer.first.Offset = ULLONG_MAX;
	return true;
}

BYTE BitVector::getMaskCode(OFFSET offset)
{
	BYTE mask = 0x80;
	mask = mask >> offset.BitOffset;
	return mask;
}

OFFSET BitVector::getOffset(size_t index)
{
	return { index,index / (8 * this->alignlen), index % (8 * this->alignlen) };
}

void BitVector::TestShow(void) {
	printf_s("length:%u\nsize:%u\n", (unsigned)this->length, (unsigned)this->size);
	for (int i = 0; i < this->size; i++) {
		printf_s("%0.2X ", vector[i]);
	}
	printf_s("\n");
}