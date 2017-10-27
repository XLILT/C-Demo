/*
 * =====================================================================================
 *
 *       Filename:  CompleteServerConfig.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月18日 14时35分59秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#ifndef _COMPLETE_USER_EXPERIENCE_CONFIG_H_
#define _COMPLETE_USER_EXPERIENCE_CONFIG_H_

#include <CommonBase/String.h>
#include <CommonBase/SttEncoding.h>
#include <Jsoncpp/json.h>

namespace dy
{
namespace complete_user_exp
{

class CompleteServerConfig
{
public:
    CompleteServerConfig();
    ~CompleteServerConfig();

    /**
     * @brief: 加载配置
     *
     * @param item[in] key值
     * 
     * @return false: 失败 true: 成功
     */
    bool load_config();

    // 获取TitleServer 数据库配置
    const char* get_title_dao_url();
    const char* get_title_dao_user();
    const char* get_title_dao_passwd();

    // 获取TransactServer 数据库配置
    const char* get_transact_dao_url();
    const char* get_transact_dao_user();
    const char* get_transact_dao_passwd();

    // 获取YuChiTransactServer 数据库配置
    const char* get_yuchi_transact_dao_url();
    const char* get_yuchi_transact_dao_user();
    const char* get_yuchi_transact_dao_passwd();

    // 获取补全数据的开始时间和截止时间
    unsigned int get_start_time();
    unsigned int get_end_time();

    // 获取补全开关配置
    unsigned int get_complete_switch();

protected:
    /**
     * @brief: 获取key为item的value值，函数内部分配内存，外部释放
     *
     * @param item[in] key值
     * 
     * @return NULL: 失败 其他值成功
     */
    SttString* getItemAsSttString(const char *item);

    /**
     * @brief: 获取key为item的value值
     *
     * @param item[in] key值
     * @param default_value[in] 默认value值
     * 
     * @return 0: 成功 其他值失败
     */
    int getItemAsUInt(const char *item, unsigned int default_value);

private:
    Json::Value _json_config_root;

    SttString *_title_dao_url;
    SttString *_title_dao_user;
    SttString *_title_dao_passwd;

    SttString *_transact_dao_url;
    SttString *_transact_dao_user;
    SttString *_transact_dao_passwd;

    SttString *_yuchi_transact_dao_url;
    SttString *_yuchi_transact_dao_user;
    SttString *_yuchi_transact_dao_passwd;

    unsigned int _start_time;
    unsigned int _end_time;
    unsigned int _complete_switch;
};

} // !namespace complete_user_exp
} // !namespace dy

#endif // _COMPLETE_USER_EXPERIENCE_CONFIG_H_

