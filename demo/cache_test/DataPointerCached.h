/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2015, Douyu Network Technology Co., Ltd. in Guangzhou
 *  All rights reserved.
 *   
 *  @version : 1.0   
 *  @author : mxl
 *  @E-mail：xiaolongicx@gmail.com
 *  @date : 2015/5/14
 *   
 *  Revision Notes : 
 *		LRU Cache with shared_ptr.
*/

#pragma once

#include <string>

#ifndef _DATA_POINTER_CACHED_H_
#define _DATA_POINTER_CACHED_H_

template<typename T>
class DataSet
{
public:
	std::string name;			//集合的名字
	uint64_t max_size;		//集合中最多能容纳的数据项个数
	
	struct DataItem
	{
		std::string id;				//数据块id
		uint64_t active_time;	//最后活跃时间戳
		uint64_t size;
		T data;			//数据块指针
		
		static uint64_t	instance_count;		//实例个数

		DataItem(std::string id, T &data)
		{
			this->id.assign(id);			
			this->active_time = time(NULL);
			this->size = sizeof(*data);
			this->data = data;
						
			instance_count++;
		}

		~DataItem()
		{			
			instance_count--;			
		}	
	};

	//using IdDataMap = boost::unordered_map<std::string, DataSet<T>::DataItem *>;
	typedef boost::unordered_map<std::string, DataSet<T>::DataItem*> IdDataMap;
	IdDataMap		datas;

	

public:
	DataSet(const char* set_name, int max_size);
	~DataSet();	
	
	const T* get(std::string id);
	void set(std::string id, T &data);
	void del(std::string id);
			
	uint64_t getKeysSet(std::vector<std::string> &ids);			
	uint64_t getValuesSet(std::vector<const T&> &values);

	uint64_t size();		//返回集合中数据项的个数
	uint64_t clearCold();		//清理冷数据项，返回被删除的数据项个数。
};

template<typename T>
class DataCached
{
private:
	typedef boost::unordered_map<std::string, DataSet<T> *> DataSetMap;
	DataSetMap		sets;

public:
	DataCached();
	~DataCached();

	bool add_set(const char* set_name, uint64_t max_size);
	void del_set(const char* set_name);

	const T* get(const char* set_name, std::string id);
	bool set(const char* set_name, std::string id, T &data);
	void del(const char* set_name, std::string id);
	
	uint64_t getKeysSet(const char* set_name, std::vector<std::string>& ids);
	uint64_t getValuesSet(const char* set_name, std::vector<T&>& values);

	uint64_t getSetSize(const char* set_name);
	
	uint64_t size();
	uint64_t clearCold();
};

template<typename T>
uint64_t DataSet<T>::DataItem::instance_count = 0;

struct ItemActiveTime
{
	int		id;
	int		active_time;

	ItemActiveTime(int id, int active_time):id(id), active_time(active_time){}
};

static bool lessthen(const ItemActiveTime& t1, const ItemActiveTime& t2)
{
	return t1.active_time < t2.active_time;
}

template<typename T>
DataSet<T>::DataSet(const char* set_name, int max_size)
{
	name = set_name;
	this->max_size = max_size;
}

template<typename T>
DataSet<T>::~DataSet()
{
	typename IdDataMap::iterator it = datas.begin();
	while (it != datas.end())
	{
		if (it->second)
		{
			delete it->second;
			it++;
		}		
	}

	datas.clear();
}

template<typename T>
void DataSet<T>::set(std::string id, T &data)
{
	typename IdDataMap::iterator it = datas.find(id);
	if (it != datas.end())
	{
		if (it->second)
		{
			delete it->second;
		}		

		DataItem *item = new DataItem(id, data);
		if (item)
		{
			item->active_time = time(NULL);
			it->second = item;
		}
		else
		{
			datas.erase(it);
		}
	}
	else
	{
		DataItem* item = new DataItem(id, data);
		if (item)
		{
			item->active_time = time(NULL);
			datas[id] = item;
		}
	}
}

template<typename T>
const T* DataSet<T>::get(std::string id)
{
	typename IdDataMap::iterator it = datas.find(id);
	if (it != datas.end())
	{
		if (it->second)
		{
			it->second->active_time = time(NULL);
			return &(it->second->data);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

template<typename T>
void DataSet<T>::del(std::string id)
{
	typename IdDataMap::iterator it = datas.find(id);
	if (it != datas.end())
	{
		if (it->second)
		{
			delete(it->second);
		}

		datas.erase(it);
	}
}

template<typename T>
uint64_t DataSet<T>::getKeysSet(std::vector<std::string>& ids)
{
	typename IdDataMap::iterator it = datas.begin();
	while (it != datas.end())
	{
		ids.push_back(it->first);
		it++;
	}

	return ids.size();
}

template<typename T>
uint64_t DataSet<T>::getValuesSet(std::vector<const T&> &values)
{
	typename IdDataMap::iterator it = datas.begin();
	while (it != datas.end())
	{
		if (it->second)
		{
			values.push_back(it->second);
		}

		it++;
	}

	return values.size();
}

template<typename T>
uint64_t DataSet<T>::size()
{
	return datas.size();
}

template<typename T>
uint64_t DataSet<T>::clearCold()
{
	if (datas.size() <= max_size)
	{
		return 0;
	}

	std::vector<ItemActiveTime> activeTimeArray;
	activeTimeArray.reserve(datas.size());

	typename IdDataMap::iterator it = datas.begin();
	while (it != datas.end())
	{
		if (it->second)
		{
			activeTimeArray.push_back(ItemActiveTime(it->second->id, it->second->active_time));
		}

		it++;
	}

	sort(activeTimeArray.begin(), activeTimeArray.end(), lessthen);

	int del_count = 0;
	int excess_count = activeTimeArray.size() - max_size * 2 / 3;		//保留2/3的容量

	for (int i = 0; i < (int)activeTimeArray.size(); i++)
	{
		typename IdDataMap::iterator itD = datas.find(activeTimeArray[i].id);
		if (itD != datas.end())
		{
			if (itD->second)
			{
				delete itD->second;
				datas.erase(itD);
				del_count++;
			}
		}

		if (del_count >= excess_count)
		{
			break;
		}
	}

	return del_count;
}

template<typename T>
DataCached<T>::DataCached()
{
}

template<typename T>
DataCached<T>::~DataCached()
{
	typename DataSetMap::iterator it = sets.begin();
	while (it != sets.end())
	{
		if (it->second)
		{
			delete it->second;
		}

		it++;
	}

	sets.clear();
}

template<typename T>
bool DataCached<T>::add_set(const char* set_name, uint64_t max_size)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it == sets.end())
	{
		sets[set_name] = new DataSet<T>(set_name, max_size);
	}
	else
	{
		if (it->second)
		{
			it->second->max_size = max_size;
		}		
	}

	return true;
}

template<typename T>
void DataCached<T>::del_set(const char* set_name)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it != sets.end())
	{
		if (it->second)
		{
			delete it->second;
		}

		sets.erase(it);
	}
}

template<typename T>
bool DataCached<T>::set(const char* set_name, std::string id, T &data)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it == sets.end())
	{
		return false;
	}
	else
	{
		if (it->second)
		{
			it->second->set(id, data);
			return true;
		}		
		else
		{
			return false;
		}		
	}
}

template<typename T>
const T* DataCached<T>::get(const char* set_name, std::string id)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it == sets.end())
	{
		return NULL;
	}
	else
	{
		if (it->second)
		{			
			return it->second->get(id);
		}
		else
		{
			return NULL;
		}		
	}
}

template<typename T>
void DataCached<T>::del(const char* set_name, std::string id)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it != sets.end())
	{
		if (it->second)
		{
			it->second->del(id);
		}		
	}
}

template<typename T>
uint64_t DataCached<T>::getKeysSet(const char* set_name, std::vector<std::string> &ids)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it != sets.end())
	{
		if (it->second)
		{
			return it->second->getKeysSet(ids);
		}		
	}
	else
	{
		return 0;
	}
}

template<typename T>
uint64_t DataCached<T>::getValuesSet(const char* set_name, std::vector<T&>& values)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it != sets.end())
	{
		if (it->second)
		{
			return it->second->getValuesSet(values);
		}		
	}
	else
	{
		return 0;
	}
}

template<typename T>
uint64_t DataCached<T>::getSetSize(const char* set_name)
{
	typename DataSetMap::iterator it = sets.find(set_name);
	if (it != sets.end())
	{
		if (it->second)
		{
			return it->second->size();
		}		
	}
	return 0;
}

template<typename T>
uint64_t DataCached<T>::size()
{
	return sets.size();
}

template<typename T>
uint64_t DataCached<T>::clearCold()
{
	int del_count = 0;
	typename DataSetMap::iterator it = sets.begin();
	while (it != sets.end())
	{
		if (it->second)
		{
			if (it->second)
			{
				del_count += it->second->clearCold();
			}			
		}

		it++;
	}

	return del_count;
}

#endif
