/*
 * =====================================================================================
 *
 *       Filename:  YuChiTransactDAO.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 16时38分37秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#ifndef _COMPLETE_USER_EXPERIENCE_YUCHITRANDACTDAO_H_
#define _COMPLETE_USER_EXPERIENCE_YUCHITRANDACTDAO_H_

#include "data_def.h"

namespace Stt
{
    namespace DB
    {
        class SttDBPool;
    }
}

namespace dy
{
namespace complete_user_exp
{

class YuChiTransactDAO
{
public:
    YuChiTransactDAO();
    ~YuChiTransactDAO();
    
    bool create(const char *url, const char *user, const char *passwd);

    /**
     * @brief: 获取[start_time, end_time]时间段用户的产生经验值鱼翅消费信息
     *
     * @param start_time[in] 开始时间
     * @param end_time[out] 结束时间
     * @param map[out] 产生经验值的用户鱼翅消费信息
     *
     * @return 0:成功 其他值失败
     */
    int get_users_gold_info(unsigned int start_time, unsigned int end_time,
            UidGoldMap &map);

private:
    char _url[64];
    char _user[64];
    char _passwd[64];

    Stt::DB::SttDBPool *_db_pool;
};

} // !namespace complete_user_exp
} // !namespace dy

#endif // _COMPLETE_USER_EXPERIENCE_YUCHITRANDACTDAO_H_

