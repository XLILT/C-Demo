/*
 * =====================================================================================
 *
 *       Filename:  CompleteServer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月18日 14时27分28秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#include "stdafx.h"
#include "CompleteServer.h"

#include <stdlib.h>
#include "CompleteServerConfig.h"

#include "TitleDAO.h"
#include "TransactDAO.h"
#include "YuChiTransactDAO.h"

namespace dy
{
namespace complete_user_exp
{

CompleteServer::CompleteServer()
{
    _title_dao = NULL;
    _transact_dao = NULL;
    _yuchi_transact_dao = NULL;
    _complete_server_config = NULL;
}

bool CompleteServer::create()
{
    _complete_server_config = new CompleteServerConfig;
    if(_complete_server_config->load_config() == false)
    {
        return false;
    }

    _title_dao = new dy::complete_user_exp::TitleDAO();
    if(false == _title_dao->create(
            _complete_server_config->get_title_dao_url(),
            _complete_server_config->get_title_dao_user(),
            _complete_server_config->get_title_dao_passwd()))
    {
        return false;
    }

    _transact_dao = new dy::complete_user_exp::TransactDAO();
    if(false == _transact_dao->create(
            _complete_server_config->get_transact_dao_url(),
            _complete_server_config->get_transact_dao_user(),
            _complete_server_config->get_transact_dao_passwd()))
    {
        return false;
    }

    _yuchi_transact_dao = new dy::complete_user_exp::YuChiTransactDAO();
    if(false == _yuchi_transact_dao->create(
            _complete_server_config->get_yuchi_transact_dao_url(),
            _complete_server_config->get_yuchi_transact_dao_user(),
            _complete_server_config->get_yuchi_transact_dao_passwd()))
    {
        return false;
    }

    return true;
}

CompleteServer::~CompleteServer()
{
    if(_title_dao != NULL)
    {
        delete _title_dao;
    }

    if(_transact_dao != NULL)
    {
        delete _transact_dao;
    }

    if(_yuchi_transact_dao != NULL)
    {
        delete _yuchi_transact_dao;
    }

    if(_complete_server_config != NULL)
    {
        delete _complete_server_config;
    }
}

int CompleteServer::read_users_exp_change_info()
{
    int result = 0;

    result = _title_dao->get_experience_change_info(
            _complete_server_config->get_start_time(), 
            _complete_server_config->get_end_time(),
            _experience_map);

    UidExperienceMap::iterator it = _experience_map.begin();
    while(it != _experience_map.end())
    {
        TL_FAST_LOG("./log/experience_detail.log", tlstDay, "uid:%d exp:%lu",
                it->first, it->second);
        it++;
    }

    return result;
}

int CompleteServer::read_users_silver_consume_info()
{
    int result = 0;

    result = _transact_dao->get_users_silver_info(
            _complete_server_config->get_start_time(),
            _complete_server_config->get_end_time(),
            _silver_map);

    UidSilverMap::iterator it = _silver_map.begin();
    while(it != _silver_map.end())
    {
        TL_FAST_LOG("./log/silver_consume.log", tlstDay, "uid:%d silver:%d",
                it->first, it->second);
        it++; 
    }
    
    return result;
}

int CompleteServer::read_users_gold_consume_info()
{
    int result = 0;

    result = _yuchi_transact_dao->get_users_gold_info(
            _complete_server_config->get_start_time(),
            _complete_server_config->get_end_time(),
            _gold_map);

    UidGoldMap::iterator it = _gold_map.begin();
    while(it != _gold_map.end())
    {
        TL_FAST_LOG("./log/gold_consume_detail.log", tlstDay, "uid:%d gold:%d",
                it->first, it->second);
        it++;
    }

    return result;
}

int CompleteServer::calc_users_exp_complete_info()
{
    int result = 0;
    
    UidSilverMap::iterator silver_iterator = _silver_map.begin();
    while(silver_iterator != _silver_map.end())
    {
        UidExperienceMap::iterator it = _complete_experience_map.find(silver_iterator->first);
        if(it != _complete_experience_map.end())
        {
            // 100鱼丸一个经验值，数据库中存储的值为 经验值*100
            it->second = (silver_iterator->second + it->second);
        }
        else
        {
            _complete_experience_map[silver_iterator->first] = silver_iterator->second;
        }

        silver_iterator = _silver_map.erase(silver_iterator);
    }

    UidGoldMap::iterator gold_iterator = _gold_map.begin();
    while(gold_iterator != _gold_map.end())
    {
        UidExperienceMap::iterator it = _complete_experience_map.find(gold_iterator->first);
        if(it != _complete_experience_map.end())
        {
            // 0.1个鱼翅一个经验值，数据库中存储的鱼翅值为实际值的100倍
            it->second += gold_iterator->second * 10;
        }
        else
        {
            _complete_experience_map[gold_iterator->first] = gold_iterator->second * 10;
        }

        gold_iterator = _gold_map.erase(gold_iterator);
    }

    UidExperienceMap::iterator exp_iterator = _experience_map.begin();
    while(exp_iterator != _experience_map.end())
    {
        UidExperienceMap::iterator it = _complete_experience_map.find(exp_iterator->first);
        if(it != _complete_experience_map.end())
        {
            // 如果member_experience_detail中的经验记录和大于鱼丸表和鱼翅表的，则不处理
            if(exp_iterator->second < it->second)
            {
                it->second = it->second - exp_iterator->second;
            }
            else
            {
                _complete_experience_map.erase(it);
            }
        }

        exp_iterator = _experience_map.erase(exp_iterator);
    }

    UidExperienceMap::iterator ite = _complete_experience_map.begin();
    while(ite != _complete_experience_map.end())
    {
        TL_FAST_LOG("./log/complete_exp_detail.log", tlstDay, "uid:%d exp:%lu", 
                ite->first, ite->second);
        ite++;
    }

    return result;
}

int CompleteServer::complete_user_experience()
{
    int result = 0;

    if(_complete_server_config->get_complete_switch() == 0)
    {
        return result;
    }

    UidExperienceMap::iterator it = _complete_experience_map.begin();
    while(it != _complete_experience_map.end())
    {
        if(_title_dao->complete_user_experience(it->first, it->second,
                _complete_server_config->get_end_time()) != 0)
        {
            TL_FAST_LOG("./log/complete_experience_error.log", tlstDay, "complete "
                    "error, uid:%d exp:%lu", it->first, it->second);
            result = ET_UNKNOWN;
        }
        else
        {
            TL_FAST_LOG("./log/complete_experience_ok.log", tlstDay, "complete "
                    "ok, uid:%d exp:%lu", it->first, it->second);
        }

        it = _complete_experience_map.erase(it);
    }

    return result;
}

int CompleteServer::execute()
{
    int result = 0;

    result = read_users_exp_change_info();
    if(result != 0)
    {
        printf("Failed to read users's experience change info.\n");
        return result;
    }

    result = read_users_silver_consume_info();
    if(result != 0)
    {
        printf("Failed to read users's silver consume info.\n");
        return result;
    }

    result = read_users_gold_consume_info();
    if(result != 0)
    {
        printf("Failed to read users's gold consume info.\n");
        return result;
    }

    result = calc_users_exp_complete_info();
    if(result != 0)
    {
        printf("Failed to calculate users's experience to complete.\n");
        return result;
    }

    result = complete_user_experience();
    if(result != 0)
    {
        printf("Failed to complete users's experience.\n");
        return result;
    }

    return result;
}

} // !namespace complete_user_exp
} // !namespace dy
