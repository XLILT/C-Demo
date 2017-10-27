#include "stdafx.h"
#include <netmsg/netmsg_gate.h>
#include <netmsg/netmsg_login.h>
#include <netmsg/netmsg_room.h>
#include <MsgClientLib/MsgClient.h>

void send_msg(MsgClient* msg_client, int i, bool id_debug = false)
{
    MI_TextMessage* tcmsg = NULL;
    int member_id = 0;
    int group_id = 0;

    //发送消息给rediswriter 49001
    /**
    MI_StreamStateReport mi;
    mi.uid = 21290;
    mi.rid = 396;
    mi.empty_count = 3;
    mi.full_count = 10;
    mi.is_p2p = 0;
    strncpy(mi.cdn_id, "ws", sizeof(mi.cdn_id));
    strncpy(mi.surl, "http://hdl3a.douyutv.com/live/tara.flv?wsSecret=5eab0b2a04c75bc027f7247899888fe8&wsTime=1419493446", sizeof(mi.surl));
    strncpy(mi.ip, "192.168.1.131", sizeof(mi.ip));


    MI_ADPromotionStub mi;
    mi.ad_id = 1;
    mi.user_id = 21290;
    mi.room_id = 369;
    mi.position = 1001;
    mi.time = time(NULL);
    strncpy(mi.client_ip, "192.168.1.165", sizeof(mi.client_ip));
    strncpy(mi.device_id, "E55DE360979A27D9CFBBFE671456BFB2", sizeof(mi.device_id));
    */

    //发送消息给security 45001
    /**
    MI_BalefulUserBehaverReport mi;
    mi.err_code = rand() % 2 ? BALEFUL_BEHAVER_BAD_PASSWD : BALEFUL_BEHAVER_BAD_USERNAME;
    mi.ip = 0xC0A80183;
    */

    //发送消息给gate 10003
    /**
    JXLogin::MC_LoginRequest mi;
    mi.m_RoomId = 396;
    mi.m_GateId = 10003;
    mi.m_ClientType = 0;

    strncpy(mi.m_RoomPass, "", sizeof(mi.m_RoomPass));
    strncpy(mi.m_NickName, "auto_y91gJJ6cBh", sizeof(mi.m_NickName));
    strncpy(mi.m_Password, "e10adc3949ba59abbe56e057f20f883e", sizeof(mi.m_Password));
    strncpy(mi.m_ClientIP, "", sizeof(mi.m_ClientIP));
    strncpy(mi.device_id, "E55DE360979A27D9CFBBFE671456BFB2", sizeof(mi.device_id));
    strncpy(mi.reference_time, "1421745252", sizeof(mi.reference_time));
    strncpy(mi.verify_key, "958b86c4a9a57fca575346cb0a5abb8e", sizeof(mi.verify_key));
    */

    /*
    //发送消息给secgate 11001
    MC_AdPosReq mi;
    mi.rid = 396;
    mi.uid = 21290;
    mi.devid.assign("E55DE360979A27D9CFBBFE671456BFB2");
    for(int i = 1; i < 12; i++)
    {
            mi.pos_arr.push_back(i);
    }


    //MI_TextMessage* tcmsg = mi.ToMITextMessage(0);

    SttString strResult;
    mi.ToTextMessage(&strResult);

    MI_TextMessage* tcmsg = MI_TextMessage::Alloc(0, strResult.c_UTF8(), strlen(strResult.c_UTF8()));
    */

    /* 赠送鱼丸 10003
    MC_RoomDonateReq mi;

    SttString strResult;
    mi.ToTextMessage(&strResult);

    MI_TextMessage* tcmsg = MI_TextMessage::Alloc(0, strResult.c_UTF8(), strlen(strResult.c_UTF8()));
    member_id = 10003;
    */

    /*
    //uint64_t start = SttGetUsTickCount();
    char *msg_content = (char *)"type@=mail_new_res";
    tcmsg = MI_TextMessage::Alloc(0, msg_content, strlen(msg_content));
    member_id = 60002;
    group_id = 60;
    */

    /** 鱼翅交易消息 30001 
    JXGate::MI_YuchiTransactResult mi;

    mi.src_id = 29900407;
    mi.dst_id = 26544693;
    mi.room_id = 442836;
    mi.gift_id = 59;
    mi.gift_count = 1;
    snprintf(mi.src_nick_name, sizeof(mi.src_nick_name), "高桥龙零");


    SttString strResult;
    mi.ToTextMessage(&strResult);

    tcmsg = MI_TextMessage::Alloc(0, strResult.c_UTF8(), strlen(strResult.c_UTF8()));
    member_id = 30130;
    group_id = 30000;
    */

    /** ping 20001 */
    JXServer::MI_TextPing *mi_ping = new JXServer::MI_TextPing;
    make_MI_TextPing(*mi_ping);

    tcmsg = reinterpret_cast<MI_TextMessage *>(mi_ping);
    member_id = 20001;
    group_id = 20;

    if(msg_client->GetStatus() == MsgClient::STATUS_LOGIN)
    {
        std::cout << "send to member" << member_id << std::endl;
        msg_client->SendToMember2(member_id, (BYTE*)tcmsg, tcmsg->m_Size);

        //std::cout << "send to group " << group_id << std::endl;
        //msg_client->SendToGroup2(group_id, (BYTE*)tcmsg, tcmsg->m_Size);

        //std::cout << "send to randomly of group " << group_id << std::endl;
        //msg_client->SendToOneRandomlyWithinGroup(group_id, (BYTE*)tcmsg, tcmsg->m_Size);
    }

    delete []tcmsg;

    printf("%d over\n", i);
}

void send_msg_concurrently(MsgClient* msg_client, int i)
{
    int j = 1000000;
    while(j--)
    {
        //uint64_t start1 = SttGetUsTickCount();

        send_msg(msg_client, i, false);

        //uint64_t end1 = SttGetUsTickCount();
        //TL_FAST_LOG("tmp.log", tlstNoSplit, "%d : %d cost:%lu", i, j, end1 - start1);
        //SttSleep(20);
    }
}

void aw_on_server_msg(int memberID, int GroupId, int len, BYTE* data)
{
    CSttTransmitData* refdata = new CSttTransmitData(data, len);
    MessageBase* msg = (MessageBase*)refdata->m_buf.GetBuffer();

    if (msg->m_Type == MIT_TextMessage)
    {
        MI_TextMessage* tmsg = (MI_TextMessage*)msg;

        SttDecoder dec;
        dec.Parse(tmsg->m_content);

        SttString* strValue = dec.GetItem("type");
        if (strValue == NULL)
        {
            return;
        }

        const char* strType = strValue->c_UTF8();
        if (strType)
        {
            if (stricmp(strType, "test") == 0)
            {
                //uint64_t end = SttGetUsTickCount();
                //TL_FAST_LOG("tmp.log", tlstNoSplit, "netmsg cost:%lu", tmsg->m_Session);
                //处理推送成功后逻辑
                printf("get %s\n", strValue->c_UTF8());
            }
            else
            {
                TL_FAST_LOG("log/OnServerMsg.log", tlstDay, "event is invalid:%s ", strType);
            }
        }
    }
}

void onRecvServerEvent(CSttTransmitData* data)
{
    MessageBase* pMsg = (MessageBase*)data->m_buf.GetBuffer();
    if (pMsg->m_Type == MST_Error)
    {
        MS_Error* msg = (MS_Error*)pMsg;
        printf("error:%d\r\n", msg->m_ErrorCode);
    }else if (pMsg->m_Type == MST_MsgLoginResp)
    {
        //MS_MsgLoginResp* msg = (MS_MsgLoginResp*)pMsg;
        //printf("Login success, session:%d\r\n", msg->m_SessionId);
        //msg_client->JoinGroup(group_id);
    }else if (pMsg->m_Type == MST_MsgMemberList)
    {
        MS_MsgMemberList* msg = (MS_MsgMemberList*)pMsg;
        printf("GroupList:Group:%d,%d Members\r\n", msg->m_nGroupId, msg->m_nMemberCount);
    }else if (pMsg->m_Type == MST_MsgGroupData)
    {
        MS_MsgGroupData* msg = (MS_MsgGroupData*)pMsg;
        aw_on_server_msg(msg->nSender, msg->nGroupId, msg->m_Size-sizeof(MS_MsgGroupData), msg->bData);

        //if (m_ServerMsgCallback)
        {
            //m_ServerMsgCallback(msg->nSender, msg->nGroupId, msg->m_Size-sizeof(MS_MsgGroupData), msg->bData);

        }


    }
}

int main(int argc, char **argv)
{
    cout << "sizeof(SttMsgBus::MC_MsgLoginReq): " << sizeof(SttMsgBus::MC_MsgLoginReq) << endl;

    SttAsyncQueue* AsyncQueue = new SttAsyncQueue;
    SttTimerTask* timer = new SttTimerTask(*AsyncQueue);
    MsgClient* msg_client = new MsgClient(timer);

    char ip[64] = "119.90.49.111";
    int port = 11044;
    int id = 666666;
    int choice = 0;

    printf("********Welcome to STT msg send Center********\n");
    printf("please choose server ip port and id config:\n");
    printf("***0.default config 119.90.49.111 11044 666666***\n");
    printf("***1.default config 192.168.1.64 11001 666666***\n");
    printf("***2.set manully***\n");
    scanf("%d", &choice);
    if (1 == choice)
    {
        snprintf(ip, sizeof(ip), "%s", "192.168.1.64");
        port = 11001;
    }
    else if(2 == choice)
    {
        printf("please input server ip port and server's id: ");
        scanf("%s%d%d", ip, &port, &id);
    }

    msg_client->SetServer(ip, port);
    msg_client->Login(id, "net_msg_tester", "net_msg_tester");

    MsgClient::ClientCallBack cb = boost::bind(&onRecvServerEvent, _1);
    msg_client->SetEventCallback(cb);

    SttSleep(5000);

    cout<< "please choose the call mode:" <<endl;
    cout<< "*** 1. single call ***" <<endl;
    cout<< "*** 2. concurrent call ***" <<endl;

    cin>>choice;

    if(1 == choice)
    {
        /** 单次调用rpc */
        //new boost::thread(boost::bind(&call_rpc, msg_client, 1));
        //msg_client->reg_RPC_callback("hello", boost::bind(&f, _1, _2, _3));
        printf("********Wait some seconds, handsome sir (@_@)********\n");
        //send_msg(msg_client, 0, true);
        new boost::thread(boost::bind(&send_msg, msg_client, 0, true));
    }
    else if(2 == choice)
    {
        cout<< "********start to send msg after seconds ********" <<endl;

        /** 并发调用rpc */
        int i = 0;
        for (i =0; i < 2000; i++)
        {
            new boost::thread(boost::bind(&send_msg_concurrently, msg_client, i));
        }
    }

    getchar();
    getchar();
    return 0;
}
