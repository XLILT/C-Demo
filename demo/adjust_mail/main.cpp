#include "stdafx.h"
#include <SttMongoDB/MongoDBPool.h>
#include <RedisDB/RedisDBPool.h>

static const char *DB_NAME()
{
    return "user_batch_mail";
}

static const char *COLLECTION_NAME()
{
    return "summary";
}

static const char *DB_NAME1()
{
    return "batch_mail";
}

static const char *COLLECTION_NAME1()
{
    return "summary";
}

enum MailStatus
{
    MS_UNREAD   = 0,
    MS_READ     = 1,
    MS_DELETE   = 2,
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

typedef std::vector<UserMailWrap> UserMailWrapArray;

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

bool json_array_to_uid_array(const char *json_doc, std::vector<int32_t> &uid_arr)
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

        uid_arr.push_back(uid);
    }

    return true;
}

bool get_user_mail_array(UserMailArray &user_mail_arr, const char *_host, uint16_t _port)
{
    user_mail_arr.clear_mail();

    MongoDBPool * _db_pool = new MongoDBPool(_host, _port);

    std::string err_info;
    SttMongoDB *mongo = _db_pool->GetConnection(err_info);
    if (!mongo)
    {
        std::cout << "conn error" << std::endl;

        return false;
    }

    bool ret = true;
    do
    {
        std::string ret_str;
        char query_json[1024] = {0};
        snprintf(query_json, sizeof(query_json), "{\"uid\": %d}", user_mail_arr.uid);

        if (!mongo->QueryDoc(ret_str, DB_NAME(), COLLECTION_NAME(), query_json, err_info))
        {
            std::cout << "query by " << query_json << " error " << err_info << std::endl;

            ret = false;
            break;
        }

        MultiUserMailArray multi_arr;
        if(!json_array_to_user_mail_wrap_array(ret_str.c_str(), multi_arr))
        {
            std::cout << "user mail array json " << ret_str << " format error" << std::endl;

            ret = false;
            break;
        }

        BOOST_FOREACH(const UserMailArray &user_mail_arr_loop, multi_arr)
        {
            if (user_mail_arr_loop.uid == user_mail_arr.uid)
            {
                user_mail_arr = user_mail_arr_loop;

                break;
            }
        }
    } while (0);

    _db_pool->ReleaseConnection(mongo);
    delete _db_pool;
    return ret;
}

bool set_user_mail(int32_t uid, const UserMailWrapArray &user_mail_wrap_arr, const char *_host, uint16_t _port)
{
    MongoDBPool * _db_pool = new MongoDBPool(_host, _port);
    std::string err_info;
    SttMongoDB *mongo = _db_pool->GetConnection(err_info);
    if (!mongo)
    {
        std::cout << "conn error" << std::endl;

        return false;
    }

    char condition_json[64] = {0};
    snprintf(condition_json, sizeof(condition_json), "{\"uid\": %d}", uid);

    bool ret = true;
    do
    {
        if(!mongo->Remove(DB_NAME(), COLLECTION_NAME(), condition_json, err_info, true))
        {
            std::cout << "remove error: "  << err_info << std::endl;
            ret = false;
            break;
        }

        if (user_mail_wrap_arr.empty())
        {
            std::string update_json = "{$addToSet: {\"unread_mails\": {$each: []}}, $addToSet: {\"read_mails\": {$each: []}}, $addToSet: {\"del_mails\": {$each: []}}}";

            if (!mongo->UpdateDoc(DB_NAME(), COLLECTION_NAME(), condition_json, update_json.c_str(), err_info, true))
            {
                std::cout << "update " << condition_json << " : " << update_json << " error " << err_info << std::endl;

                ret = false;
                break;
            }
        }
        else
        {
            std::string update_json = "{";

            bool have_unread = false;
            std::string unread_update_json = "$push: {\"unread_mails\": {$each: [";

            bool have_read = false;
            std::string read_update_json = "$push: {\"read_mails\": {$each: [";

            bool is_unread_first = true;
            bool is_read_first = true;
            BOOST_FOREACH(const UserMailWrap &user_mail_wrap, user_mail_wrap_arr)
            {
                if (user_mail_wrap.status == MS_UNREAD)
                {
                    if (!is_unread_first)
                    {
                        unread_update_json += ", ";
                    }
                    else
                    {
                        is_unread_first = false;
                    }

                    bool is_batch = user_mail_wrap.body.empty();

                    unread_update_json += user_mail_wrap.to_json(is_batch);
                    have_unread = true;
                }
                else if (user_mail_wrap.status == MS_READ)
                {
                    if (!is_read_first)
                    {
                        read_update_json += ", ";
                    }
                    else
                    {
                        is_read_first = false;
                    }

                    bool is_batch = user_mail_wrap.body.empty();

                    read_update_json += user_mail_wrap.to_json(is_batch);
                    have_read = true;
                }
            }

            if (have_unread)
            {
                update_json += unread_update_json;
                update_json += "], $sort: {ts: 1}}}";
            }

            if (have_read)
            {
                if (have_unread)
                {
                    update_json += ", ";
                }

                update_json += read_update_json;
                update_json += "], $sort: {ts: 1}}}";
            }

            update_json += "}";

            if (!mongo->UpdateDoc(DB_NAME(), COLLECTION_NAME(), condition_json, update_json.c_str(), err_info, true))
            {
                std::cout << "update " << condition_json << " : " << update_json << " error " << err_info << std::endl;

                ret = false;
                break;
            }
        }
    } while (0);

    _db_pool->ReleaseConnection(mongo);
    delete _db_pool;
    return ret;
}

bool get_batch_mail_body(UserMailWrap &mail, const char *_host, uint16_t _port)
{
    std::string err_info;
    SttMongoDB mongo;
    if (!mongo.Connect(_host, _port, err_info))
    {
        std::cout << "conn error" << std::endl;

        return false;
    }

    std::string query_json = "{\"mid\": \"";
    query_json += mail.mid;
    query_json += "\"}";

    std::string ret_str;
    if (!mongo.QueryDoc(ret_str, DB_NAME1(), COLLECTION_NAME1(), query_json.c_str(), err_info))
    {
        std::cout << "query by " << query_json << " error " << err_info << std::endl;

        return false;
    }

    UserMailWrapArray mail_arr;
    if(json_array_to_mail_array(ret_str.c_str(), mail_arr))
    {
        if (mail_arr.size() == 1)
        {
            mail = mail_arr.front();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

void filter_dirty_and_get_ts_for_batch(UserMailArray &user_mail_arr, const char *_host, uint16_t _port)
{
    UserMailWrapArray::iterator it = user_mail_arr.unread_mail_arr.begin();
    while(it != user_mail_arr.unread_mail_arr.end())
    {
        //std::cout << it->mid << std::endl;
        if (it->title == "我在鱼吧关注了你")
        {
            it = user_mail_arr.unread_mail_arr.erase(it);
        }
        else
        {
            if (it->ts == 0)
            {
                UserMailWrap mail;
                mail.mid = it->mid;
                if(get_batch_mail_body(mail, _host, _port))
                {
                    it->ts = mail.ts;
                }
                else
                {
                    // error log
                    TL_FAST_LOG("err.log", tlstNoSplit, " get mid %s error", it->mid.c_str());
                }
            }

            ++it;
        }
    }

    UserMailWrapArray::iterator it_read = user_mail_arr.read_mail_arr.begin();
    while(it_read != user_mail_arr.read_mail_arr.end())
    {
        //std::cout << it_read->mid << std::endl;
        if (it_read->title == "我在鱼吧关注了你")
        {
            it_read = user_mail_arr.read_mail_arr.erase(it_read);
        }
        else
        {
            if (it_read->ts == 0)
            {
                UserMailWrap mail;
                mail.mid = it_read->mid;
                if(get_batch_mail_body(mail, _host, _port))
                {
                    it_read->ts = mail.ts;
                }
                else
                {
                    // error log
                    TL_FAST_LOG("err.log", tlstNoSplit, " get mid %s error", it_read->mid.c_str());
                }
            }

            ++it_read;
        }
    }
}

void adjust_by_uid(const char *host, uint16_t port, int32_t uid)
{
    UserMailArray uma;
    uma.uid = uid;
    if(!get_user_mail_array(uma, host, port))
    {
        TL_FAST_LOG("err.log", tlstNoSplit, " get_user_mail_array uid %d error", uid);
        return;
    }

    filter_dirty_and_get_ts_for_batch(uma, host, port);

    UserMailWrapArray umwa = uma.unread_mail_arr;
    umwa.insert(umwa.end(), uma.read_mail_arr.begin(), uma.read_mail_arr.end());

    if (!set_user_mail(uid, umwa, host, port))
    {
        TL_FAST_LOG("err.log", tlstNoSplit, " get_user_mail_array uid %d error", uid);
        return;
    }
}

bool get_uid_arr(const char *host, uint16_t port, int32_t limit, int32_t skip, std::vector<int32_t> &uid_arr)
{
    uid_arr.clear();

    std::string err_info;
    SttMongoDB mongo;
    if (!mongo.Connect(host, port, err_info))
    {
        std::cout << "conn error" << std::endl;

        return false;
    }

    std::string ret_str;
    if (!mongo.QueryDoc(ret_str, DB_NAME(), COLLECTION_NAME(), "{}", err_info, "{uid: 1}", limit, skip, "{uid: 1}"))
    {
        std::cout << "query error " << err_info << std::endl;

        return false;
    }

    //std::cout << ret_str << std::endl;

    if(!json_array_to_uid_array(ret_str.c_str(), uid_arr))
    {
        return false;
    }

    return true;
}

void adjust_all(const char *host, uint16_t port)
{
    const int32_t limit = 1000;
    int32_t skip = 0;

    while(true)
    {
        std::vector<int32_t> uid_arr;
        if(get_uid_arr(host, port, limit, skip, uid_arr))
        {
            if (uid_arr.empty())
            {
                std::cout << "deal over" << std::endl;
                break;
            }

            std::cout << "dealing " << skip << " to " << skip + limit << " ..." << std::endl;

            BOOST_FOREACH(int32_t uid, uid_arr)
            {
                //std::cout << "dealing " << uid << std::endl;
                adjust_by_uid(host, port, uid);
            }

            skip += limit;
        }
        else
        {
            std::cout << "get_uid_arr error" << std::endl;

            break;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: " << std::endl;
        std::cout << "    " << argv[0] << " host port [uid]" << std::endl;
        return -1;
    }

    const char *host = argv[1];
    uint16_t port = atoi(argv[2]);

    if (argc > 3)
    {
        int32_t uid = atoi(argv[3]);

        adjust_by_uid(host, port, uid);
    }
    else
    {
        adjust_all(host ,port);
    }

    TL_SHUTDOWN();
    return 0;
}
