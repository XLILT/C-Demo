#include <iostream>
#include <fstream>
#include "rpctester.h"


using namespace std;

void call_rpc(MsgClient* msg_client, int i, bool is_debug)
{
	SttString stt_str;
	SttString parm_str;
	SttEncoder enc;
	int sev_id = 0;
	string rpc_name;

	//printf("please input any key except enter after login OK!!!\n");
	//scanf("%d", &uid);
	//SttSleep(1000);

	//enc.AddItem("rid", 30);
	//enc.AddItem("uid", 21290);
	//enc.AddItem("uid", uid);
	//enc.AddItem("gift_level", lev);
	//enc.AddItem("uid", uid);
	//ip@=59.67.128.195/room_id@=71795/user_id@=0/dev_id@=ACEF60CE4CF7B5AFE04D84BCB390EBA8

	/** 60001 query_ad_list
	enc.AddItem("ip", "59.67.128.195");
	enc.AddItem("ip", 5967128195);
	enc.AddItem("room_id", 396);
	enc.AddItem("user_id", 0);
	enc.AddItem("dev_id", "ACEF60CE4CF7B5AFE04D84BCB390EBA8");
	enc.AddItem("position", 10001);
	*/

	/** 49001  mongo_query
	enc.AddItem("db", "chat_msg_2015_1_31");
	enc.AddItem("coll", "16");
	enc.AddItem("cond", "{}");
	*/

	/** 42001 update_user
	sev_id = 42001;
	rpc_name = "update_user";

	uid = i;
	enc.AddItem("uid", uid);
    */

	/** 42001 login_auth
	sev_id = 42001;
	rpc_name = "login_auth";
	enc.AddItem("nick", "test_mxl");
	enc.AddItem("password", "e10adc3949ba59abbe56e057f20f883a");
	enc.AddItem("ip", "192.168.1.131");
	*/

	/** 42001  get_user_info
	sev_id = 42001;
	rpc_name = "get_user_info";

	enc.AddItem("uid", rand() % 1000000);
	*/

	/** 42001  get_user_info
	sev_id = 42001;
	rpc_name = "query_user_info";

	enc.AddItem(21290);
	*/

	/** 90001 query_member_socre
	enc.AddItem("uid", 1537690);
	*/

	/** 40001 is_signined_room
	enc.AddItem("rid", 64609);
	enc.AddItem("uid", 1537690);
	 */

	/** 40001  get_prize
	enc.AddItem("tid", 17);
	enc.AddItem("uid", 2093118);
	*/

	/** 30003  call_command_line
	enc.AddItem("cmd", "help");
	*/

	/** 48001  send_phone_message
	//enc.AddItem("phone", "15727009221");
	//enc.AddItem("msg", "where is she?");
	enc.AddItem("phone", "15827136314");
	enc.AddItem("msg", "HF");
	*/

	/** 48001  query_foreign_phone_verify_status
	enc.AddItem("phone", "15727009221");
	*/

	/** 60001  query_ad_list_pos
	sev_id = 60001;
	rpc_name = "query_ad_list_pos";
	//enc.AddItem("phone", "15727009221");
	//enc.AddItem("msg", "where is she?");
	enc.AddItem("room_id", "369");
	enc.AddItem("user_id", "21290");
	enc.AddItem("dev_id", "91194F0305393FF9C92F963E18AC9539");
	enc.AddItem("ip", "192.168.1.131");
	enc.AddItem("pos", "1/2/3/4/5/6/7/8/9/10/11/");
	*/

	/** 60001  save_ad_click_record
	sev_id = 60001;
	rpc_name = "save_ad_click_record";
	enc.AddItem("ad_id", 308);
	enc.AddItem("room_id", 369);
	enc.AddItem("user_id", 21290);
	//enc.AddItem("dev_id", "91194F0305393FF9C92F963E18AC9539");
	enc.AddItem("ip", "192.168.1.131");
	enc.AddItem("position", "1001");
	*/

	/** 47001  status_query_user_online_info
	enc.AddItem("uid", "407279");
	*/

	/** 51001  query_mail_count
	enc.AddItem("uid", 21290);
	enc.AddItem("tag", 0);
	*/

	/** 51001  query_mail
    sev_id = 51001;
    rpc_name = "query_mail";

	enc.AddItem("uid", 21290);
	enc.AddItem("tag", 0);
	enc.AddItem("offset", 0);
	enc.AddItem("count", 25);
    */

	/** 51001  send_mail
	enc.AddItem("src_id", 0);
	enc.AddItem("sub", "sub");
	enc.AddItem("body", "body");
	enc.AddItem("dst_grp_id", 0);
	//enc.AddItem("dst_id", "21290@S");
	enc.AddItem("dst_id", "sfasdfg9uafkl");
	*/

    /** 51001  query_mail
    sev_id = 51001;
    rpc_name = "handle_mail";

    enc.AddItem("uid", 21290);
    enc.AddItem("opt", 2);
    enc.AddItem("tag", 0);
    enc.AddItem("mid", "");
    */

	/** 60001  query_ad_list
	enc.AddItem("room_id", 17542);
	enc.AddItem("user_id", 13031563);
	enc.AddItem("dev_id", "91194F0305393FF9C92F963E18AC9539");
	enc.AddItem("ip", "113.57.191.77");
	*/

	/** 49001  mongo_querys
	//sev_id = 49001;
	sev_id = 49721;
	rpc_name = "mongo_querys";
	enc.AddItem("db_name", "innermail");
	enc.AddItem("coll_name", "summary");
	//enc.AddItem("mtype", "query_count");
	enc.AddItem("mtype", "");
	enc.AddItem("json_cond", "{\"dst_id\":21290, status:0}");
	//enc.AddItem("json_obj", "");
	enc.AddItem("limit", 25);
	//enc.AddItem("skip", "");
	*/

	/** 90001  mobile_bind_notify
	sev_id = 90001;
	rpc_name = "mobile_bind_notify";
	uid = i;

	enc.AddItem("uid", uid);
	enc.AddItem("flag", 0);
	*/

    /** 90008 yuchi_gift_donate
    sev_id = 90008;
    rpc_name = "transact_request";

    enc.AddItem("type", "yuchi_gift_donate");
    //enc.AddItem("uid", 21290);
    enc.AddItem("uid", random() % 200000);
    enc.AddItem("rid", 396);
    enc.AddItem("dstid", 21291);
    enc.AddItem("gfid", 65);
    enc.AddItem("client_type", 0);
    enc.AddItem("count", 1);
    enc.AddItem("ncnm", "");
    enc.AddItem("ip", "");
    */

    /** 140001 alipay_chatmsg
    sev_id = 320001;
    rpc_name = "alipay_chatmsg";

    enc.AddItem("rid", 192);
    enc.AddItem("uid", 1);
    enc.AddItem("content", "content");
    enc.AddItem("nick", "nick");
    */

   /**
    * 14001 query_member_money

   sev_id = 14001;
   rpc_name = "query_member_money";

   enc.AddItem("uid", 21290);
   */

   /**
    * 90001  transact_request
    *
    */

   sev_id = 90001;
   rpc_name = "transact_request";

   enc.AddItem("type", "donate_room");
   enc.AddItem("sid", "101951");
   enc.AddItem("sip", " ");
   enc.AddItem("did", "40147");
   enc.AddItem("rid", "271345");
   enc.AddItem("ms", "995700");
   enc.AddItem("ct", "0");
   enc.AddItem("device_id", " ");
   enc.AddItem("ltkid", "70340541");
   enc.AddItem("biz", "1");
   enc.AddItem("stk", "80e5c7178ad5ac45");

	enc.GetResualt(&parm_str);

	if(is_debug)
	{
		printf("rpc args:%s\n", parm_str.c_UTF8());
	}

    MsgClient::RpcRequestInfo rpc_req;
    rpc_req._receiver_id = sev_id;
    rpc_req._timeout_ms = 5000;
    rpc_req._func_name = rpc_name.c_str();
    rpc_req._parameters = parm_str.c_UTF8();
    rpc_req._rpc_global_id = "123";
    rpc_req._password = "123";
    rpc_req._version = 1;


    if(msg_client->call_remote_function(rpc_req, &stt_str))
	//if(msg_client->call_remote_function(sev_id, 5000, &stt_str, rpc_name.c_str(), parm_str.c_UTF8()))
	{
		SttDecoder dec;
		dec.Parse(stt_str.c_UTF8());
		int nResult = dec.GetItemAsInt("result", 0);
		if (0 == nResult)
		{
			if(is_debug)
			{
				printf("call ok ,return:%s\n\n", stt_str.c_UTF8());
			}

			TL_FAST_LOG("ret.log", tlstNoSplit, "call ok :%s, %d", stt_str.c_UTF8(), i);
		}
		else
		{
			if(is_debug)
			{
				printf("@_@!!! Error:%d\n\n", nResult);
			}

			TL_FAST_LOG("ret.log", tlstNoSplit, "err_code:%d, %d", nResult, i);
		}
	}
	else
	{
		printf("time out\r\n");
	}
}

void call_rpc_concurrently(MsgClient* msg_client, int i)
{
	//uint64_t start = SttGetUsTickCount();

	int j = 1000000;
	while(j--)
	{
		//uint64_t start1 = SttGetUsTickCount();

		call_rpc(msg_client, i, false);

		//uint64_t end1 = SttGetUsTickCount();
		//TL_FAST_LOG("tmp.log", tlstNoSplit, "%d : %d cost:%lu", i, j, end1 - start1);
		//SttSleep(20);
	}

	//uint64_t end = SttGetUsTickCount();
	//TL_FAST_LOG("tmp.log", tlstNoSplit, ">>>> %d cost:%lu", i, end - start);


	//ifstream ifs("uid.txt", ios::nocreate);

    /*
	ifstream ifs("uid.txt");

	string uid_str;
	int j = 0;
	while(ifs>>uid_str)
	{
		cout << j++ << " --> " << uid_str << endl;
		call_rpc(msg_client, atoi(uid_str.c_str()), true);
		SttSleep(500);
	}
    */
}

void f(int invoker_id, int taken_id, const char* args)
{
	printf("enter!");
	return;
}

int main(int argc, char **argv)
{
	SttAsyncQueue* AsyncQueue = new SttAsyncQueue;
	SttTimerTask* timer = new SttTimerTask(*AsyncQueue);
	MsgClient* msg_client = new MsgClient(timer);

	char ip[64] = "10.1.51.9";

	int port = 11001;
	int id = 666666;
	int choice = 0;
	printf("********Welcome to STT RPC Call Center********\n");
	printf("please choose server ip port and id config\n");
	printf("***0.set manully***\n");
    printf("***1.default config 10.1.51.9 11001 666666***\n");
    printf("***2.default config 192.168.1.64 11001 666666***\n");
    printf("***3.default config 192.168.5.14 11001 666666***\n");
    printf("***4.default config 192.168.5.4 11001 666666***\n");
    printf("***5.default config 192.168.6.24 11001 666666***\n");

    scanf("%d", &choice);
    if (0 == choice)
    {
        printf("please input server ip port and server's id: ");
        scanf("%s%d%d", ip, &port, &id);
    }
    if (1 == choice)
    {

    }
    else if(2 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.1.64");
        port = 11001;
    }
    else if(3 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.5.14");
        port = 11001;
    }
    else if(4 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.5.4");
        port = 11001;
    }
    else if(5 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.6.24");
        port = 11001;
    }

	msg_client->SetServer(ip, port);
	msg_client->Login(id, "rpc_tester", "rpc_tester");
    msg_client->set_server_init_done();


	SttSleep(1000);

	cout<< "please choose the call mode:" <<endl;
	cout<< "*** 1. single call test ***" <<endl;
	cout<< "*** 2. concurrent call test ***" <<endl;
	cin>>choice;

	if(1 == choice)
	{
		/** 单次调用rpc */
		//new boost::thread(boost::bind(&call_rpc, msg_client, 1));
		//msg_client->reg_RPC_callback("hello", boost::bind(&f, _1, _2, _3));
		printf("********Wait some seconds, handsome sir (@_@)********\n");
		call_rpc(msg_client, 0, true);
	}
	else if(2 == choice)
	{
		cout<< "********start to call rpc after seconds ********" <<endl;

		/** 并发调用rpc */
		int i = 0;
		for (i =0; i < 400; i++)
		{
			new boost::thread(boost::bind(&call_rpc_concurrently, msg_client, i));
		}
	}


    TL_SHUTDOWN();
	return 0;
}
