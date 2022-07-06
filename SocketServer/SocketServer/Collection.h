#pragma once

template<typename T>
class Collection : public enable_shared_from_this<Collection<T>>
{
public:
	T Find(int32 key);
	Vector<T> GetVector();
	bool KeyExist(int32 key);
	bool Remove(int32 key);
	void Update();
	void Add(int32 key, T t, bool isNewData = true);
	void SetData(MapRef<int32, T> collectoin);
	void AddUpdatedIndex(int32 key);
	int32 GetSize();

private:
	USE_LOCK;
	MapRef<int32, T> _collection = MakeShared<Map<int32, T>>();
	Vector<int32> _updatedKeys;
};

template<typename T>
void Collection<T>::Add(int32 key, T t, bool isNewData)
{
	WRITE_LOCK;
	_collection->insert(std::make_pair(key, t));

	t->GetTableSchema()->SetMarkAsUpdated([self = this->shared_from_this(), key]() {
		self->AddUpdatedIndex(key);
	});

	if (isNewData) {
		t->Insert();
	}
};

template<typename T>
inline void Collection<T>::SetData(MapRef<int32, T> collection)
{
	_collection = collection;
};

template<typename T>
bool Collection<T>::Remove(int32 key)
{
	WRITE_LOCK;
	auto removed = _collection->find(key)->second;
	_collection->erase(key);
	removed->Remove();
	return true;
};

template<typename T>
T Collection<T>::Find(int32 key)
{
	READ_LOCK;
	auto target = _collection->find(key);

	if (target == _collection->end()) {
		return nullptr;
	}

	return target->second;
};

template<typename T>
Vector<T> Collection<T>::GetVector()
{
	READ_LOCK;
	Vector<T> vector;

	for (auto const& [first, second] : *_collection) {
		vector.push_back(second);
	}
	return vector;
};

template<typename T>
bool Collection<T>::KeyExist(int32 key)
{
	READ_LOCK;
	auto target = _collection->find(key);
	return target != _collection->end() ? true : false;
};

template<typename T>
void Collection<T>::Update()
{
	WRITE_LOCK;
	for (auto& key : _updatedKeys) {
		auto target = _collection->find(key)->second;
		target->Update();
	}
	_updatedKeys.clear();
};

template<typename T>
void Collection<T>::AddUpdatedIndex(int32 key)
{
	WRITE_LOCK;
	_updatedKeys.push_back(key);
}

template<typename T>
int32 Collection<T>::GetSize()
{
	return _collection->size();
}

