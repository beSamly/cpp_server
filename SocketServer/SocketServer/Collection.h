#pragma once
template<typename T>
class Collection
{
public:
	T Find(int32 key);
	T Remove(int32 key);
	T Add(int32 key, T& t);
	void SetData(MapRef<int32, T> collectoin);
private:
	MapRef<int32, T> _collection;
	Vector<int32> _updatedIndices;
	Vector<int32> _addedIndices;
};

template<typename T>
T Collection<T>::Add(int32 key,T& t)
{
	_collection.insert(key, t);
	_addedIndices.push_back(key);
	return;
}

template<typename T>
inline void Collection<T>::SetData(MapRef<int32, T> collectoin)
{
	_collection = collectoin;
}

template<typename T>
T Collection<T>::Remove(int32 key)
{
	_collection.erase(key);
	_updatedIndices.push_back(key);
	return;
}

template<typename T>
T Collection<T>::Find(int32 key)
{
	return _collection.find(key);
}

