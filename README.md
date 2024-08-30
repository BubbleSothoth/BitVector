# BitVector
一个比特级的bool数组，理论上它可以比传统的字节级的bool数组节省8倍空间。
一个BitVector实例在内存中需要118Byte空间，所以，在理论上当你需要长度大于118*8+8=952的bool数组时，他会有更好的空间优化。

# API
```C++
	bool Get(size_t index);
```
获取index的值
```C++
	bool Set(size_t index, bool val);
```
将index的值置为val
