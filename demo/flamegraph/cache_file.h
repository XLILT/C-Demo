/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2015, Douyu Network Technology Co., Ltd. in Guangzhou
 *  All rights reserved.
 *   
 *  @version : 1.0   
 *  @author : mxl
 *  @E-mail：xiaolongicx@gmail.com
 *  @date : 2015/7/1
 *   
 *  Revision Notes : 
 *		Dump memory binary data to file and load from it.
 *      Type T must have the construct without args.
 *      Base on file CacheFile.h code by bluezheng.
*/

#ifndef __FILE_CACHE_H__
#define __FILE_CACHE_H__

#include <fstream>
#include <vector>

#define S_OK 0
#define S_ERR -1

template<typename T>
int dump_data_to_file(const std::string &file_name, std::vector<T> &vec_data, int &total_serialize_count)
{    
    if (file_name.empty())
    {
        return S_ERR;
    }
    
    std::ofstream ofs(file_name.c_str(), std::ofstream::binary);

    // 先写入数据的个数    
    int total_count = vec_data.size(); 
    ofs.write(reinterpret_cast<char*>(&total_count), sizeof(total_count));    
	
	typename std::vector<T>::const_iterator it_v = vec_data.begin();	
    for (; it_v != vec_data.end(); ++it_v)    
    {
        const T &data = *it_v;
        ofs.write(reinterpret_cast<char*>(const_cast<T*>(&data)), sizeof(T));       
    }

    ofs.close();
    return S_OK;
}

template<typename T>
int load_data_from_file(const std::string &file_name, std::vector<T> &vec_data, int &total_load_count)
{
    if (file_name.empty())
    {
        return S_ERR;
    }	

    std::ifstream ifs(file_name.c_str(), std::ifstream::binary);

    int total_count = 0;
    ifs.read(reinterpret_cast<char*>(&total_count), sizeof(total_count));
    if (!ifs)
    {
        return S_ERR;
    }

    vec_data.reserve(total_count);
    for (int i = 0; i < total_count; ++i)
    {
        T data;
        memset(&data, 0, sizeof(T));

        ifs.read(reinterpret_cast<char*>(&data), sizeof(data));
        if (ifs)
        {
            vec_data.push_back(data);
        }
    }

    ifs.close();
    total_load_count = vec_data.size();

    return S_OK;
}

#endif  //#ifndef __FILE_CACHE_H__

