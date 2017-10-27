/*
 * =====================================================================================
 *
 *       Filename:  CompleteServer.h
 *
 *    Description:  补全新用户等级一期发布时TitleServer出现问题期间的用户经验不一致
 *
 *        Version:  1.0
 *        Created:  2015年12月18日 14时20分17秒
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  wangfei (wangfei@douyu.tv)
 *		  Company:  武汉斗鱼网络科技有限公司
 *
 * =====================================================================================
 */

#include "data_def.h"

namespace dy
{
namespace complete_user_exp
{

class TitleDAO;
class TransactDAO;
class YuChiTransactDAO;
class CompleteServerConfig;

class CompleteServer
{
public:
    CompleteServer();
    ~CompleteServer();

    bool create();

    /**
     * @brief: 获取用户在规定时间段的鱼丸消耗信息，
     *         存入_user_silver_consume_info_map中
     *
     * @return 0:成功 其他值失败
     */
    int read_users_silver_consume_info();

    /**
     * @brief: 获取用户在规定时间段的鱼翅消耗信息，
     *         存入_user_gold_consume_info_map中
     *
     * @return 0:成功 其他值失败
     */
    int read_users_gold_consume_info();

    /**
     * @brief: 获取用户在规定时间段的经验值增加信息，
     *         存入_user_exp_change_info_map中
     *
     * @return 0:成功 其他值失败
     */
    int read_users_exp_change_info();

    /**
     * @brief: 计算用户在规定时间段的需要补全的经验值信息，
     *         存入_user_exp_change_info_map中
     *
     * @return 0:成功 其他值失败
     */
    int calc_users_exp_complete_info();

    /**
     * @brief: 依据_user_exp_change_info_map补全用户经验值信息
     *         修改数据库记录
     *
     * @return 0:成功 其他值失败
     */
    int complete_user_experience();

    /**
     * @brief: 执行补全操作
     *
     * @return 空
     */
    int execute();

private:
    UidExperienceMap    _experience_map;
    UidExperienceMap    _complete_experience_map;
    UidSilverMap        _silver_map;
    UidGoldMap          _gold_map;
   
    TitleDAO            *_title_dao;
    TransactDAO         *_transact_dao;
    YuChiTransactDAO    *_yuchi_transact_dao;
    CompleteServerConfig    *_complete_server_config;
};

} // !namespace complete_user_exp
} // !namespace dy

