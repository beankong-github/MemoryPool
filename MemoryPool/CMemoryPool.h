#pragma once

#include <iostream>
#include <vector>
#include <cassert>

class CMemoryPool
{
private:
	size_t m_blockSize;
	size_t m_blockCount;

	std::vector<char>  m_pool;
	std::vector<void*> m_freeBlocks;	// 할당 가능한 메모리들의 주소

public:
	CMemoryPool(size_t _blockSize, size_t _blockCount)
		: m_blockSize(_blockSize)
		, m_blockCount(_blockCount)
	{
		m_pool.resize(m_blockCount * m_blockSize);

		for (size_t i = 0; i < _blockCount; ++i)
		{
			m_freeBlocks.push_back(&m_pool[i * m_blockSize]);
		}
	}

	void* allocate()
	{
		if (m_freeBlocks.empty())
			return nullptr;

		void* block = m_freeBlocks.back();
		m_freeBlocks.pop_back();

		return block;
	}

	void deallocate(void* _block)
	{
		// _block의 주소가 m_pool의 범위 밖이면 경고
		assert(_block >= m_pool.data() && _block < m_pool.data() + m_pool.size());
		// m_pool의 주소 ~ _block의 주소 크기가 m_blockSize로 나눠떨어지지 않으면 경고
		assert(0 == ((char*)_block - m_pool.data()) % m_blockSize);

		m_freeBlocks.push_back(_block);
	}
};
