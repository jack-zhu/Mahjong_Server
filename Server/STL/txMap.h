﻿#ifndef _TX_MAP_H_
#define _TX_MAP_H_

#include "txSTLBase.h"

template<typename Key, typename Value>
class txMap : public txSTLBase
{
public:
	typedef typename std::map<Key, Value>::iterator iterator;
	typedef typename std::map<Key, Value>::reverse_iterator reverse_iterator;
public:
	txMap(){}
	virtual ~txMap(){ clear(); }
	reverse_iterator rbegin()
	{
		return mMap.rbegin();
	}
	reverse_iterator rend()
	{
		return mMap.rend();
	}
	iterator begin()
	{
		return mMap.begin();
	}
	iterator end()
	{
		return mMap.end();
	}
	iterator find(const Key& k)
	{
		return mMap.find(k);
	}
	bool contains(const Key& key)
	{
		return mMap.find(key) != mMap.end();
	}
	std::pair<iterator, bool> insert(const Key& k, const Value& v)
	{
		checkLock();
		return mMap.insert(std::make_pair(k, v));
	}
	void erase(const iterator& iter, bool check = true)
	{
		if (check)
		{
			checkLock();
		}
		mMap.erase(iter);
	}
	void erase(const Key& key, bool check = true)
	{
		auto iter = mMap.find(key);
		if (iter != mMap.end())
		{
			erase(iter);
		}
	}
	void clear()
	{
		checkLock();
		mMap.clear();
	}
	int size()
	{
		return (int)mMap.size();
	}
	Value& operator[](const Key& k)
	{
		return mMap[k];
	}
protected:
	std::map<Key, Value> mMap;
};

#endif