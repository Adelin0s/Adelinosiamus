#ifndef _MALLOC_ALLOCATOR_H_
#define _MALLOC_ALLOCATOR_H_

// Allocator implementation detail based on default CRT malloc/free.
class MallocAllocator {
public:
	MallocAllocator() {}
	~MallocAllocator() {}

	void SetUp() {}
	void TearDown() {}

	void* Alloc(size_t size) {
		return ::malloc(size);
	}
	void Free(void* p) {
		::free(p);
	}
};

#endif // _MALLOC_ALLOCATOR_H_
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8