/*
 * =====================================================================================
 *
 *       Filename:  TitleDAO.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 16时38分54秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */
#ifndef _COMPLETE_USER_EXEPERIENCE_TITLEDAO_H_
#define _COMPLETE_USER_EXEPERIENCE_TITLEDAO_H_

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

class TitleDAO
{
public:
    TitleDAO();
    ~TitleDAO();

    bool create(const char *url, const char *user, const char *passwd);

    /**
     * @brief: 获取用户在[start_time, end_time]时间段的经验值增加数量
     *
     * @param start_time[in] 开始时间
     * @param end_time[in] 结束时间
     * @param map[out] 用户的经验值变化信息
     * 
     * @return 0:成功 其他值失败
     */
    int get_experience_change_info(unsigned int start_time, unsigned int end_time,
            UidExperienceMap &map);

    /**
     * @brief: 补全用户经验值，更新数据库detail表和summary表
     *
     * @param uid[in] 用户ID
     * @param exp[in] 经验值变化量
     * @param time[in] 时间戳
     * 
     * @return 0:成功 其他值失败
     */
    int complete_user_experience(unsigned int uid, unsigned long exp, unsigned int time);

private:
    char _url[64];
    char _user[64];
    char _passwd[64];

    Stt::DB::SttDBPool *_db_pool;
};

} // !namespace complete_user_exp
} // !namespace dy

#endif // _COMPLETE_USER_EXEPERIENCE_TITLEDAO_H_

