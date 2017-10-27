/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2016, Wuhan Douyu Network Technology Co., Ltd.
 *  All rights reserved.
 *
 *  @version : 1.0
 *  @author : mxl
 *  @E-mail : xiaolongicx@gmail.com
 *  @date : Thu Feb 28 10:30:20 CST 2017
 *
 *  Revision Notes :
 */

#ifndef __DATA_DEF_H___
#define __DATA_DEF_H___

#include <Common/Tools.h>
#include <time.h>
#include <string>
#include <Jsoncpp/json.h>
#include <stdint.h>
#include <CommonBase/String.h>
#include <CommonBase/SttEncoding.h>
#include <CommonBase/Utility.h>
#include <stdint.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/detail/atomic_count.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/singleton.hpp>

enum MailStatus
{
    MS_UNREAD   = 0,
    MS_READ     = 1,
    MS_DELETE   = 2,
};

enum HandleOperation {
    HO_READ     = 0,    //read
    HO_DELETE   = 1,    //delete
};

struct UserMailWrap
{
    std::string mid;
    MailStatus status;
    std::string title;
    std::string body;
    time_t ts;

    UserMailWrap()
        :mid(),
        status(MS_UNREAD),
        title(),
        body(),
        ts(0)
    {}

    const std::string to_json(bool is_batch = false) const
    {
        Json::Value v_obj(Json::objectValue);
        v_obj["mid"] = mid.c_str();
        v_obj["status"] = status;
        v_obj["ts"] = static_cast<int32_t>(ts);

        // batch send mail do not contain title etc.
        if (!is_batch)
        {
            v_obj["title"] = title;
            v_obj["body"] = body.c_str();
        }

        Json::FastWriter writer;

        std::string ret_str =  writer.write(v_obj);

        if (!ret_str.empty())
        {
            std::string::iterator it = ret_str.end();
            --it;

            if(*it == '\r' || *it == '\n')
            {
                ret_str.erase(it);
            }
        }

        return ret_str;
    }

    const std::string to_batch_json() const
    {
        Json::Value v_obj(Json::objectValue);
        v_obj["mid"] = mid.c_str();
        v_obj["title"] = title;
        v_obj["body"] = body.c_str();
        v_obj["ts"] = static_cast<int32_t>(ts);

        Json::FastWriter writer;

        return writer.write(v_obj);
    }

    bool from_json(const char *json_doc)
    {
        if (!json_doc)
        {
            return false;
        }

        Json::Reader reader;
        Json::Value root;

        bool parse_ret = reader.parse(json_doc, root, false);
        if (!parse_ret)
        {
            return false;
        }

        if (!root.isObject())
        {
            return false;
        }

        if (!root["mid"].isNull() && root["mid"].isString())
        {
            mid = root["mid"].asCString();
        }
        else
        {
            return false;
        }

        if (!root["status"].isNull() && root["status"].isInt())
        {
            status = static_cast<MailStatus>(root["status"].asInt());
        }

        if (root["ts"].isNull())
        {
            return true;
        }
        else
        {
            if (root["ts"].isInt())
            {
                ts = root["ts"].asInt();
            }

            if (!root["title"].isNull() && root["title"].isString())
            {
                title = root["title"].asCString();
            }

            if (!root["body"].isNull() && root["body"].isString())
            {
                body = root["body"].asCString();
            }
        }

        return true;
    }

    void padding_with_batch_mail_info(const UserMailWrap &batch_mail)
    {
        title = batch_mail.title;
        body = batch_mail.body;
        ts = batch_mail.ts;
    }

    static bool sort_ts_more(const UserMailWrap &mail1, const UserMailWrap &mail2)
    {
        return mail1.ts > mail2.ts;
    }
};

inline bool mail_ts_less(const UserMailWrap &m1, const UserMailWrap &m2)
{
    return m1.ts < m1.ts;
}

typedef std::vector<UserMailWrap> UserMailWrapArray;

struct UserMailCount {
    int32_t uid;
    uint32_t all_count;
    uint32_t unread_count;

    UserMailCount()
        :uid(0),
        all_count(0),
        unread_count(0)
    {}

    bool from_json_array(const char *json_doc)
    {
        if (!json_doc)
        {
            return false;
        }

        Json::Reader reader;
        Json::Value root;

        bool parse_ret = reader.parse(json_doc, root, false);
        if (!parse_ret)
        {
            return false;
        }

        if (!root.isArray())
        {
            return false;
        }

        if (root.size() < 1)
        {
            return false;
        }

        int i = 0;
        if (!root[i]["all_count"].isNull() && root[i]["all_count"].isInt())
        {
            all_count = root[i]["all_count"].asInt();
        }
        else
        {
            return false;
        }

        if (!root[i]["unread_count"].isNull() && root[i]["unread_count"].isInt())
        {
            unread_count = root[i]["unread_count"].asInt();
        }
        else
        {
            return false;
        }

        return true;
    }
};

typedef std::vector<UserMailCount> UserMailCountArray;
typedef std::map<int32_t, UserMailCount> UserMailCountMap;

inline void calculate_mail_count_within_mail_array(const UserMailWrapArray &arr, UserMailCount &count)
{
    count.all_count = 0;
    count.unread_count = 0;

    BOOST_FOREACH(const UserMailWrap &user_mail_wrap, arr)
    {
        if (user_mail_wrap.status != MS_DELETE)
        {
            ++count.all_count;

            if (user_mail_wrap.status == MS_UNREAD)
            {
                ++count.unread_count;
            }
        }
    }
}

inline bool json_array_to_user_mail_count_map(const char *json_doc, UserMailCountMap &user_mail_count_map)
{
    if (!json_doc)
    {
        return false;
    }

    Json::Reader reader;
    Json::Value root;

    bool parse_ret = reader.parse(json_doc, root, false);
    if (!parse_ret)
    {
        return false;
    }

    if (!root.isArray())
    {
        return false;
    }

    for (int i = 0; i < root.size(); ++i)
    {
        UserMailCount user_mail_count;

        if (!root[i]["uid"].isNull() && root[i]["uid"].isInt())
        {
            user_mail_count.uid = root[i]["uid"].asInt();
        }
        else
        {
            continue;
        }

        if (!root[i]["unread_count"].isNull() && root[i]["unread_count"].isInt())
        {
            user_mail_count.unread_count = root[i]["unread_count"].asInt();
        }
        else
        {
            continue;
        }

        if (!root[i]["read_count"].isNull() && root[i]["read_count"].isInt())
        {
            user_mail_count.all_count = root[i]["read_count"].asInt() + user_mail_count.unread_count;
        }
        else
        {
            continue;
        }

        user_mail_count_map[user_mail_count.uid] = user_mail_count;
    }

    return true;
}

struct UserMailArray {
    int32_t uid;
    UserMailWrapArray unread_mail_arr;
    UserMailWrapArray read_mail_arr;

    UserMailArray()
        :uid(0),
        unread_mail_arr(),
        read_mail_arr()
    {}

    void clear_mail()
    {
        unread_mail_arr.clear();
        read_mail_arr.clear();
    }
};

typedef std::vector<UserMailArray> MultiUserMailArray;

inline bool json_array_to_user_mail_wrap_array(const char *json_doc, MultiUserMailArray &muti_arr)
{
    muti_arr.clear();

    Json::Reader reader;
    Json::Value root;

    bool parse_ret = reader.parse(json_doc, root, false);
    if (!parse_ret)
    {
        return false;
    }

    if (!root.isArray())
    {
        return false;
    }

    for (int i = 0; i < root.size(); i++)
    {
        UserMailArray arr;

        if (!root[i]["uid"].isNull() && root[i]["uid"].isInt())
        {
            arr.uid = root[i]["uid"].asInt();
        }
        else
        {
            continue;
        }

        const Json::Value & unread_mails = root[i]["unread_mails"];
        if (!unread_mails.isNull() && unread_mails.isArray())
        {
            for (int j = 0; j < unread_mails.size(); j++)
            {
                UserMailWrap mail;

                if (!unread_mails[j]["mid"].isNull() && unread_mails[j]["mid"].isString())
                {
                    mail.mid = unread_mails[j]["mid"].asCString();
                }
                else
                {
                    continue;
                }

                mail.status = MS_UNREAD;

                if (!unread_mails[j]["title"].isNull() && unread_mails[j]["title"].isString())
                {
                    mail.title = unread_mails[j]["title"].asCString();
                }

                if (!unread_mails[j]["body"].isNull() && unread_mails[j]["body"].isString())
                {
                    mail.body = unread_mails[j]["body"].asCString();
                }

                if (!unread_mails[j]["ts"].isNull() && unread_mails[j]["ts"].isInt())
                {
                    mail.ts = unread_mails[j]["ts"].asInt();
                }

                arr.unread_mail_arr.push_back(mail);
            }
        }

        const Json::Value &read_mails = root[i]["read_mails"];
        if (!read_mails.isNull() && read_mails.isArray())
        {
            for (int j = 0; j < read_mails.size(); j++)
            {
                UserMailWrap mail;

                if (!read_mails[j]["mid"].isNull() && read_mails[j]["mid"].isString())
                {
                    mail.mid = read_mails[j]["mid"].asCString();
                }
                else
                {
                    continue;
                }

                mail.status = MS_READ;

                if (!read_mails[j]["title"].isNull() && read_mails[j]["title"].isString())
                {
                    mail.title = read_mails[j]["title"].asCString();
                }

                if (!read_mails[j]["body"].isNull() && read_mails[j]["body"].isString())
                {
                    mail.body = read_mails[j]["body"].asCString();
                }

                if (!read_mails[j]["ts"].isNull() && read_mails[j]["ts"].isInt())
                {
                    mail.ts = read_mails[j]["ts"].asInt();
                }

                arr.read_mail_arr.push_back(mail);
            }
        }

        muti_arr.push_back(arr);
    }

    return true;
}

inline bool json_array_old_format_to_user_mail_wrap_array(const char *json_doc, MultiUserMailArray &muti_arr)
{
    Json::Reader reader;
    Json::Value root;

    bool parse_ret = reader.parse(json_doc, root, false);
    if (!parse_ret)
    {
        return false;
    }

    if (!root.isArray())
    {
        return false;
    }

    UserMailArray arr;
    if (root.size() >= 1)
    {
        int i = 0;
        if (!root[i]["dst_id"].isNull() && root[i]["dst_id"].isInt())
        {
            arr.uid = root[i]["dst_id"].asInt();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }

    for (int i = 0; i < root.size(); i++)
    {
        UserMailWrap mail;

        if (root[i]["_id"].isString())
        {
            mail.mid = root[i]["_id"].asString();
        }
        else
        {
            continue;
        }

        if (!root[i]["status"].isNull() && root[i]["status"].isInt())
        {
            mail.status = static_cast<MailStatus>(root[i]["status"].asInt());
        }

        if (!root[i]["sub"].isNull() && root[i]["sub"].isString())
        {
            mail.title = root[i]["sub"].asString();
        }
        else
        {
            continue;
        }

        if (!root[i]["body"].isNull() && root[i]["body"].isString())
        {
            mail.body = root[i]["body"].asString();
        }
        else
        {
            continue;
        }

        if (!root[i]["ts"].isNull() && root[i]["ts"].isInt())
        {
            mail.ts = root[i]["ts"].asInt();
        }
        else
        {
            continue;
        }

        if (mail.status == MS_UNREAD)
        {
            arr.unread_mail_arr.push_back(mail);
        }
        else if (mail.status == MS_READ)
        {
            arr.read_mail_arr.push_back(mail);
        }
    }

    muti_arr.push_back(arr);

    return true;
}

inline bool json_array_to_mail_array(const char *json_doc, UserMailWrapArray &mail_arr)
{
    Json::Reader reader;
    Json::Value root;

    bool parse_ret = reader.parse(json_doc, root, false);
    if (!parse_ret)
    {
        return false;
    }

    if (!root.isArray())
    {
        return false;
    }

    for (int i = 0; i < root.size(); i++)
    {
        UserMailWrap mail;

        if (!root[i]["mid"].isNull() && root[i]["mid"].isString())
        {
            mail.mid = root[i]["mid"].asCString();
        }
        else
        {
            continue;
        }

        if (!root[i]["title"].isNull() && root[i]["title"].isString())
        {
            mail.title = root[i]["title"].asCString();
        }
        else
        {
            continue;
        }

        if (!root[i]["body"].isNull() && root[i]["body"].isString())
        {
            mail.body = root[i]["body"].asCString();
        }
        else
        {
            continue;
        }

        if (!root[i]["ts"].isNull() && root[i]["ts"].isInt())
        {
            mail.ts = root[i]["ts"].asInt();
        }
        else
        {
            continue;
        }

        mail_arr.push_back(mail);
    }

    return true;
}

inline bool json_array_to_uid_arr(const char *json_doc, std::set<int32_t> &uid_set)
{
    Json::Reader reader;
    Json::Value root;

    bool parse_ret = reader.parse(json_doc, root, false);
    if (!parse_ret)
    {
        return false;
    }

    if (!root.isArray())
    {
        return false;
    }

    for (int i = 0; i < root.size(); i++)
    {
        int32_t uid = 0;
        if (!root[i]["uid"].isNull() && root[i]["uid"].isInt())
        {
            uid = root[i]["uid"].asInt();
        }
        else
        {
            continue;
        }

        uid_set.insert(uid);
    }

    return true;
}

class GetUUID
{
public:
    GetUUID()
        :ranUUID(boost::uuids::random_generator()()),
        atom_count(0),
        node_id(0)
    {}

    ~GetUUID() {}

    std::string get_uuid()
    {
        uint8_t uuid_tmp[12];
        uint32_t count = ++atom_count;
        char str_result[33];

        uint32_t ts = time(NULL);

        memcpy(uuid_tmp, &count, 4);
        memcpy(uuid_tmp + 4, &node_id, 4);
        memcpy(uuid_tmp + 8, &ts, 4);

        snprintf(str_result, sizeof(str_result), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            uuid_tmp[0], uuid_tmp[1], uuid_tmp[2], uuid_tmp[3],
            uuid_tmp[4], uuid_tmp[5], uuid_tmp[6], uuid_tmp[7],
            uuid_tmp[8], uuid_tmp[9], uuid_tmp[10], uuid_tmp[11]);

        return std::string(str_result);
    }

    void set_node_id(int32_t nid)
    {
        node_id = nid;
    }

private:
    boost::uuids::uuid ranUUID;
    //boost::detail::atomic_count atom_count;
    boost::atomics::atomic_uint32_t atom_count;
    int32_t node_id;
};

typedef boost::serialization::singleton<GetUUID> GetUUIDSingleton;

#endif  //__DATA_DEF_H___
