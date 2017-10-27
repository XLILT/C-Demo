#include "stdafx.h"
#include <fstream>
#include <MsgClientLib/MsgClient.h>

const int MAX_SEND_COUNTS_PER_REQUEST = 1000;

std::string msgsev_ip;
uint16_t msgsev_port = 0;
int32_t client_id = 0;
std::string official_name;

bool load_config(const char *file_name, std::string &sub, std::string &body)
{
    bool ret = true;
    try
    {
        std::ifstream ifs(file_name);
        std::string str((std::istreambuf_iterator<char>(ifs)),
                 std::istreambuf_iterator<char>());

        //cout << str << endl;

        Json::Value jroot;
        Json::Reader reader;
        if (reader.parse(str.c_str(), jroot))
        {
            if (jroot.isObject())
            {
                Json::Value &val = jroot["sub"];
                if (val.isString())
                {
                    sub = val.asCString();
                }
                else
                {
                    cout << file_name << " \"sub\" is not founded" << endl;
                    ret = false;
                }

                val = jroot["body"];
                if (val.isString())
                {
                    body = val.asCString();
                }
                else
                {
                    cout << file_name << " \"body\" is not founded" << endl;
                    ret = false;
                }

                val = jroot["ip"];
                if (val.isString())
                {
                    msgsev_ip = val.asCString();
                }
                else
                {
                    cout << file_name << " \"ip\" is not founded" << endl;
                    ret = false;
                }

                val = jroot["port"];
                if (val.isInt())
                {
                    msgsev_port = val.asInt();
                }
                else
                {
                    cout << file_name << " \"port\" is not founded" << endl;
                    ret = false;
                }

                val = jroot["id"];
                if (val.isInt())
                {
                    client_id = val.asInt();
                }
                else
                {
                    cout << file_name << " \"id\" is not founded" << endl;
                    ret = false;
                }

                val = jroot["official"];
                if (val.isString())
                {
                    official_name = val.asCString();
                }
                else
                {
                    cout << file_name << " \"official\" is not founded" << endl;
                    ret = false;
                }
            }
            else
            {
                cout << file_name << " root is not a json object" << endl;
                ret = false;
            }
        }
        else
        {
            cout << file_name << " is not a json format file" << endl;
            ret = false;
        }
    }
    catch(std::exception &e)
    {
        cout << e.what() << endl;
        ret = false;
    }

    return ret;
}

bool load_uids(const char *file_name, std::vector<int> &uid_vec)
{
    bool ret = true;

    try
    {
        std::ifstream ifs(file_name);

        while(ifs)
        {
            char buf[64] = {0};
            ifs.getline(buf, sizeof(buf));

            int uid = atoi(buf);

            //cout << buf << ", " << uid << endl;

            if (uid > 0)
            {
                uid_vec.push_back(atoi(buf));
            }
        }
    }
    catch(std::exception &e)
    {
        cout << e.what() << endl;
        ret = false;
    }

    return ret;
}

bool stt_rpc_send_mails(MsgClient *msg_client, const std::string &sub, const std::string &body, const std::vector<int> &uid_vec)
{
    bool ret = true;
    int sev_id = 51001;
    const std::string rpc_name = "send_mail";

    SttEncoder uid_enc;
    BOOST_FOREACH(const int &uid, uid_vec)
    {
        uid_enc.AddItem(uid);
    }

    SttString uid_str;
    uid_enc.GetResualt(&uid_str);

    SttEncoder enc;
    enc.AddItem("src_id", 0);
    //enc.AddItem("src_nick", official_name.c_str());
    //enc.AddItem("dst_grp_id", 0);
    enc.AddItem("dst_id_list", uid_str.c_UTF8());
    //enc.AddItem("dst_nick_list", "");
    enc.AddItem("sub", sub.c_str());
    enc.AddItem("body", body.c_str());

    SttString parm_str;
    enc.GetResualt(&parm_str);

    uint64_t start_tick = SttGetTickCount();

    SttString stt_str;
    if(msg_client->call_remote_function(sev_id, 15000, &stt_str, rpc_name.c_str(), parm_str.c_UTF8()))
    {
        SttDecoder dec;
        dec.Parse(stt_str.c_UTF8());
        int nResult = dec.GetItemAsInt("result", 0);
        if (0 == nResult)
        {
            //TL_FAST_LOG("ret.log", tlstNoSplit, "call ok :%s, %d", stt_str.c_UTF8(), i);
        }
        else
        {
            TL_FAST_LOG("err.log", tlstNoSplit, "err_code:%d", nResult);
        }

        //TL_FAST_LOG("cost.log", tlstNoSplit, "send to %lu users cost %lums", uid_vec.size(), SttGetTickCount() - start_tick);
    }
    else
    {
        ret = false;
        TL_FAST_LOG("timeout.log", tlstNoSplit, "send to %lu users timeout", uid_vec.size());
    }

    return ret;
}

bool send_mails(const std::string &sub, const std::string &body, const std::vector<int> &uid_vec)
{
    SttAsyncQueue* AsyncQueue = new SttAsyncQueue;
    SttTimerTask* timer = new SttTimerTask(*AsyncQueue);
    MsgClient* msg_client = new MsgClient(timer);

    msg_client->SetServer(msgsev_ip.c_str(), msgsev_port);
    msg_client->Login(client_id, "net_msg_tester", "net_msg_tester");

    SttSleep(3000);

    int succ_cnt = 0;
    int fail_cnt = 0;

    size_t start = 0;
    size_t cnt = 0;
    while(start < uid_vec.size())
    {
        size_t left_cnt = uid_vec.size() - start;
        if (left_cnt >= MAX_SEND_COUNTS_PER_REQUEST)
        {
            cnt = MAX_SEND_COUNTS_PER_REQUEST;
        }
        else
        {
            cnt = left_cnt;
        }

        if(stt_rpc_send_mails(msg_client, sub, body, std::vector<int>(uid_vec.begin() + start, uid_vec.begin() + start + cnt)))
        {
            succ_cnt += cnt;
        }
        else
        {
            fail_cnt += cnt;
        }

        start += cnt;

        //SttSleep(10);
    }

    cout << "succ_cnt: " << succ_cnt << ", fail_cnt: " << fail_cnt << endl;
    return true;
}

int main(int argc, char **argv)
{
    //uint64_t start_tick = SttGetTickCount();

    do
    {
        std::string sub;
        std::string body;

        if(!load_config("config.json", sub, body))
        {
            cout << "load mail failed" << endl;
            break;
        }

        std::vector<int> uid_vec;
        if (!load_uids("uid.txt", uid_vec))
        {
            cout << "load uid failed" << endl;
            break;
        }

        send_mails(sub, body, uid_vec);

        //cout << "send to " << uid_vec.size() << " users cost " << SttGetTickCount() - start_tick << "ms" << endl;
    }while(0);

    TL_SHUTDOWN();
    return 0;
}
