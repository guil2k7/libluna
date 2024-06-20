#pragma once

#include "DS_List.h"
#include "RakAssert.h"

namespace RakNet::DataStructures
{
	template <class MemoryBlockType>
	class MemoryPool
	{
	public:
		MemoryPool();
		~MemoryPool();
		void Preallocate(unsigned numElements);
		MemoryBlockType *Allocate(void);
		void Release(MemoryBlockType *m);
		void Clear(void);
	protected:
		int blocksOut;
		DataStructures::List<MemoryBlockType*> pool;
	};

	template<class MemoryBlockType>
	MemoryPool<MemoryBlockType>::MemoryPool()
	{
#ifndef NDEBUG
		blocksOut=0;
#endif
	}
	template<class MemoryBlockType>
	MemoryPool<MemoryBlockType>::~MemoryPool()
	{
#ifndef NDEBUG
		RakAssert(blocksOut==0);
#endif
		unsigned i;
		for (i=0; i < pool.Size(); i++)
			delete pool[i];
	}

	template<class MemoryBlockType>
	void MemoryPool<MemoryBlockType>::Preallocate(unsigned numElements)
	{
		unsigned i;
		for (i=pool.Size(); i < numElements; i++)
		{
			pool.Insert(new MemoryBlockType);
		}
	}

	template<class MemoryBlockType>
	MemoryBlockType* MemoryPool<MemoryBlockType>::Allocate(void)
	{
#ifndef NDEBUG
		blocksOut++;
#endif
		if (pool.Size()==0)
			return new MemoryBlockType;
		else
		{
			MemoryBlockType* out;
			out=pool[pool.Size()-1];
			pool.Del();
			return out;
		}
	}
	template<class MemoryBlockType>
	void MemoryPool<MemoryBlockType>::Release(MemoryBlockType *m)
	{
		pool.Insert(m);
#ifndef NDEBUG
		RakAssert(blocksOut>0);
		blocksOut--;
#endif
	}
	template<class MemoryBlockType>
	void MemoryPool<MemoryBlockType>::Clear(void)
	{
#ifndef NDEBUG
		RakAssert(blocksOut==0);
#endif
		unsigned i;
		for (i=0; i < pool.Size(); i++)
			delete pool[i];
		pool.Clear();
	}
}
