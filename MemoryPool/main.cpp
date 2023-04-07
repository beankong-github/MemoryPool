#include "CMemoryPool.h"
#include <time.h>

int main()
{
	constexpr size_t blockSize  = 256;
	constexpr size_t blockCount = 100000;
	time_t           start, end;
	double           timer;

	CMemoryPool memoryPool(blockSize, blockCount);

	std::vector<void*> allocatedBlocks;

	/* �޸� Ǯ - �Ҵ� */
	start = clock();
	for (size_t i = 0; i < blockCount; ++i)
	{
		void* block = memoryPool.allocate();
		assert(block != nullptr);
		allocatedBlocks.push_back(block);
	}

	end   = clock();
	timer = (double)(end - start);
	assert(memoryPool.allocate() == nullptr);

	std::cout << "Memory pool allocation time :" << (timer / CLOCKS_PER_SEC) << std::endl;

	/* �޸� Ǯ - ��ȯ */
	start = clock();
	for (void* block : allocatedBlocks)
	{
		memoryPool.deallocate(block);
	}
	end   = clock();
	timer = (double)(end - start);
	std::cout << "Memory pool deallocation time :" << (timer / CLOCKS_PER_SEC) << std::endl;
	allocatedBlocks.clear();

	/* �Ϲ� �Ҵ� (malloc) */
	start = clock();
	for (size_t i = 0; i < blockCount; ++i)
	{
		void* block = malloc(256);
		assert(block != nullptr);
		allocatedBlocks.push_back(block);
	}
	end   = clock();
	timer = (double)(end - start);
	std::cout << "Normal allocation time :" << (timer / CLOCKS_PER_SEC) << std::endl;

	/* �Ϲ� ��ȯ (free) */
	start = clock();
	for (void* block : allocatedBlocks)
	{
		free(block);
	}
	end   = clock();
	timer = (double)(end - start);
	std::cout << "Normal deallocation time :" << (timer / CLOCKS_PER_SEC) << std::endl;

	return 0;
}
