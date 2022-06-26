#pragma once
template<typename T>
class Collection
{
public:
	T Find(int32 key);
	T Remove(int32 key);
	void Add(int32 key, T t);
	void SetData(MapRef<int32, T> collectoin);
private:
	USE_LOCK;
	MapRef<int32, T> _collection = MakeShared<Map<int32, T>>();
	Vector<int32> _updatedIndices;
	Vector<int32> _addedIndices;
};

template<typename T>
void Collection<T>::Add(int32 key, T t)
{
	WRITE_LOCK;
	_collection->insert(std::make_pair(key, t));
	_addedIndices.push_back(key);
};

template<typename T>
inline void Collection<T>::SetData(MapRef<int32, T> collectoin)
{
	_collection = collectoin;
};

template<typename T>
T Collection<T>::Remove(int32 key)
{
	WRITE_LOCK;
	auto removed = Find(key);
	_collection->erase(key);
	_updatedIndices.push_back(key);
	return removed;
};

template<typename T>
T Collection<T>::Find(int32 key)
{
	return _collection->find(key)->second;
};

