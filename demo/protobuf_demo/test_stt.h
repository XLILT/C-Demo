/*************************************************************************
    > File Name: test_stt.h
    > Author: mxl2
    > Mail: xiaolongicx@gmail.com
    > Created Time: Tue 29 Mar 2016 02:07:20 PM CST
 ************************************************************************/
#include "stdafx.h"
#include <Common/Tools.h>

struct SttParallelMessage
{
    int32_t item1;
    int32_t item2;
    int32_t item3;
    int32_t item4;
    int32_t item5;
    std::string item6;
    std::string item7;
    std::string item8;
    std::string item9;
    std::string item10;

    SttParallelMessage()
        : item1(0),
        item2(0),
        item3(0),
        item4(0),
        item5(0),
        item6(""),
        item7(""),
        item8(""),
        item9(""),
        item10("")
    {}

    SttString * ToTextMessage(SttString * str)
    {
        SttEncoder enc;

        enc.AddItem("item1", item1);
        enc.AddItem("item2", item2);
        enc.AddItem("item3", item3);
        enc.AddItem("item4", item4);
        enc.AddItem("item5", item5);
        enc.AddItem("item6", item6.c_str());
        enc.AddItem("item7", item7.c_str());
        enc.AddItem("item8", item8.c_str());
        enc.AddItem("item9", item9.c_str());
        enc.AddItem("item10", item10.c_str());

        return enc.GetResualt(str);
    }

    bool FromTextMessage(const char *msg)
    {
        SttDecoder dec;

        dec.Parse(msg);

        item1 = dec.GetItemAsInt("item1");
        item2 = dec.GetItemAsInt("item2");
        item3 = dec.GetItemAsInt("item3");
        item4 = dec.GetItemAsInt("item4");
        item5 = dec.GetItemAsInt("item5");

        char str[1024] = {0};
        get_string_from_decoder(str, sizeof(str), "item6", &dec);
        item6 = str;
        get_string_from_decoder(str, sizeof(str), "item7", &dec);
        item7 = str;
        get_string_from_decoder(str, sizeof(str), "item8", &dec);
        item8 = str;
        get_string_from_decoder(str, sizeof(str), "item9", &dec);
        item9 = str;
        get_string_from_decoder(str, sizeof(str), "item10", &dec);
        item10 = str;

        return true;
    }
};

struct SttNestedMessage
{
    std::vector<int32_t> item1;
    std::vector<std::string> item2;

    SttString *ToTextMessage(SttString *str)
    {
        SttEncoder enc;

        SttEncoder enc_item1;
        SttString str_item1;
        BOOST_FOREACH(int int_val, item1)
        {
            enc_item1.AddItem(int_val);
        }

        SttEncoder enc_item2;
        SttString str_item2;

        BOOST_FOREACH(std::string &string_val, item2)
        {
            enc_item2.AddItem(string_val.c_str());
        }

        enc.AddItem("item1", enc_item1.GetResualt(NULL)->c_UTF8());
        enc.AddItem("item2", enc_item2.GetResualt(NULL)->c_UTF8());

        return enc.GetResualt(str);
    }

    bool FromTextMessage(const char *msg)
    {
        SttDecoder dec;

        dec.Parse(msg);

        char str[1024] = {0};
        get_string_from_decoder(str, sizeof(str), "item1", &dec);
        SttDecoder dec_item;
        dec_item.Parse(str);

        for(int i = 0 ; i < dec_item.m_Count; ++i)
        {
            item1.push_back(dec_item.GetItemAsInt(i));
        }

        get_string_from_decoder(str, sizeof(str), "item2", &dec);
        dec_item.Parse(str);

        for(int i = 0 ; i < dec_item.m_Count; ++i)
        {
            item2.push_back(dec_item.GetItem(i)->c_UTF8());
        }

        return true;
    }
};

