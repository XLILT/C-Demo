/*
 * =====================================================================================
 *
 *       Filename:  CompleteServerConfig.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月18日 14时37分09秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#include "CompleteServerConfig.h"
#include <stdio.h>
#include <memory.h>

namespace dy
{
namespace complete_user_exp
{

CompleteServerConfig::CompleteServerConfig():
    _title_dao_url(NULL), _title_dao_user(NULL), _title_dao_passwd(NULL),
    _transact_dao_url(NULL), _transact_dao_user(NULL), _transact_dao_passwd(NULL),
    _yuchi_transact_dao_url(NULL), _yuchi_transact_dao_user(NULL), 
    _yuchi_transact_dao_passwd(NULL), _start_time(0), _end_time(0), _complete_switch(0)
{
}

CompleteServerConfig::~CompleteServerConfig()
{
    if(_title_dao_url != NULL)
    {
        delete _title_dao_url;
    }

    if(_title_dao_user != NULL)
    {
        delete _title_dao_user;
    }

    if(_title_dao_passwd != NULL)
    {
        delete _title_dao_passwd;
    }

    if(_transact_dao_url != NULL)
    {
        delete _transact_dao_url;
    }

    if(_transact_dao_user != NULL)
    {
        delete _transact_dao_user;
    }

    if(_transact_dao_passwd != NULL)
    {
        delete _transact_dao_passwd;
    }

    if(_yuchi_transact_dao_url != NULL)
    {
        delete _yuchi_transact_dao_url;
    }

    if(_yuchi_transact_dao_user != NULL)
    {
        delete _yuchi_transact_dao_user;
    }

    if(_yuchi_transact_dao_passwd != NULL)
    {
        delete _yuchi_transact_dao_passwd;
    }
}

bool CompleteServerConfig::load_config()
{
    FILE* file_json = fopen("config.json", "rb");
    if(NULL != file_json)
    {
        char *data = new char[100 * 1024 + 1];
        memset(data, 0, 100 * 1024 + 1);

        fread(data, 100 * 1024 + 1, 1, file_json);
        fclose(file_json);

        Json::Reader reader;
        if(reader.parse(data, _json_config_root) == false)
        {
            delete[] data;
            printf("config.json format error!!!\n");
            return false;
        }

        if(_json_config_root.isObject())
        {
            _title_dao_url = getItemAsSttString("TITLE_DAO_URL");
            _title_dao_user = getItemAsSttString("TITLE_DAO_USER");
            _title_dao_passwd = getItemAsSttString("TITLE_DAO_PASSWD");

            _transact_dao_url = getItemAsSttString("TRANSACT_DAO_URL");
            _transact_dao_user = getItemAsSttString("TRANSACT_DAO_USER");
            _transact_dao_passwd = getItemAsSttString("TRANSACT_DAO_PASSWD");

            _yuchi_transact_dao_url = getItemAsSttString("YUCHI_TRANSACT_DAO_URL");
            _yuchi_transact_dao_user = getItemAsSttString("YUCHI_TRANSACT_DAO_USER");
            _yuchi_transact_dao_passwd = getItemAsSttString("YUCHI_TRANSACT_DAO_PASSWD");

            _start_time = getItemAsUInt("START_TIME", 1450139400);
            _end_time = getItemAsUInt("END_TIME", 1450168200);

            _complete_switch = getItemAsUInt("COMPLETE_SWITCH", 0);
        }
        else
        {
            printf("config.json root format error!!!\n");
            return false;
        }
    }
    else
    {
        printf("config.json does not exist!!!\n");
        return false;
    }

    return true;
}

const char* CompleteServerConfig::get_title_dao_url()
{
    if(NULL != _title_dao_url)
    {
        return _title_dao_url->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_title_dao_user()
{
    if(NULL != _title_dao_user)
    {
        return _title_dao_user->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_title_dao_passwd()
{
    if(NULL != _title_dao_user)
    {
        return _title_dao_passwd->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_transact_dao_url()
{
    if(NULL != _transact_dao_url)
    {
        return _transact_dao_url->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_transact_dao_user()
{
    if(NULL != _transact_dao_user)
    {
        return _transact_dao_user->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_transact_dao_passwd()
{
    if(NULL != _transact_dao_passwd)
    {
        return _transact_dao_passwd->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_yuchi_transact_dao_url()
{
    if(NULL != _yuchi_transact_dao_url)
    {
        return _yuchi_transact_dao_url->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_yuchi_transact_dao_user ()
{
    if(NULL != _yuchi_transact_dao_user)
    {
        return _yuchi_transact_dao_user->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

const char* CompleteServerConfig::get_yuchi_transact_dao_passwd()
{
    if(NULL != _yuchi_transact_dao_passwd)
    {
        return _yuchi_transact_dao_passwd->c_UTF8();
    }
    else
    {
        return NULL;
    }
}

unsigned int CompleteServerConfig::get_start_time()
{
    return _start_time;
}

unsigned int CompleteServerConfig::get_end_time()
{
    return _end_time;
}

unsigned int CompleteServerConfig::get_complete_switch()
{
    return _complete_switch;
}

SttString* CompleteServerConfig::getItemAsSttString(const char *item)
{
	if (NULL == item)
	{
		return NULL;
	}

	Json::Value &val = _json_config_root[item];
	if (val.isString())
	{
		return new SttString(val.asCString());		
	}
	else
	{
		return NULL;
	}
}

int CompleteServerConfig::getItemAsUInt(const char *item, unsigned int default_value)
{
	if (NULL == item)
	{
		return default_value;
	}

	Json::Value &val = _json_config_root[item];
	if (val.isInt())
	{
		return val.asUInt();
	}
	else
	{
		return default_value;
	}
}

} // !namespace complete_user_exp
} // !namespace dy
