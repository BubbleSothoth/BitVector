# BitVector
一个比特级的bool数组，理论上它可以比传统的字节级的bool数组节省8倍空间。
一个BitVector实例在内存中需要118Byte空间，所以，在理论上当你需要长度大于129的bool数组时，他会有更好的空间优化。

# API
```C++
BitVector(size_t len, size_t alignlen = 1);
```
设置数组长度为len，数据以alignlen Byte为单位对齐（）。例如，当len=9，alignlen=1时，会申请⌈9/(1*8)‌⌉*1 Byte 的内存空间；当len=25,alignlen=4时会申请‌⌈25/(4*8)⌉*4 Byte 的内存空间。
```C++
bool Get(size_t index);
```
获取index的值
```C++
bool Set(size_t index, bool val);
```
将index的值置为val
