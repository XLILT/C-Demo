/*************************************************************************
    > File Name: test_json.h
    > Author: mxl2
    > Mail: xiaolongicx@gmail.com
    > Created Time: Tue 29 Mar 2016 04:10:57 PM CST
 ************************************************************************/
#include <Jsoncpp/json.h>

struct JsonParallelMessage
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

    JsonParallelMessage()
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

    SttString *ToTextMessage(SttString *str)
    {
        Json::Value v_item(Json::objectValue);

        v_item["item1"] = item1;
        v_item["item2"] = item2;
        v_item["item3"] = item3;
        v_item["item4"] = item4;
        v_item["item5"] = item5;
        v_item["item6"] = item6.c_str();
        v_item["item7"] = item7.c_str();
        v_item["item8"] = item8.c_str();
        v_item["item9"] = item9.c_str();
        v_item["item10"] = item10.c_str();

        Json::FastWriter j_writer;
        str->CopyFrom(j_writer.write(v_item).c_str());

        return str;
    }

    bool FromTextMessage(const char *msg)
    {
        bool ret = true;

        Json::Value v_item(Json::objectValue);
        Json::Reader j_reader;
        if(j_reader.parse(msg, v_item, false))
        {
            if(v_item.isObject())
            {
                Json::Value i_value = v_item["item1"];
                if(i_value.isInt())
                {
                    item1 = i_value.asInt();
                }

                i_value = v_item["item2"];
                if(i_value.isInt())
                {
                    item2 = i_value.asInt();
                }

                i_value = v_item["item3"];
                if(i_value.isInt())
                {
                    item3 = i_value.asInt();
                }

                i_value = v_item["item4"];
                if(i_value.isInt())
                {
                    item4 = i_value.asInt();
                }

                i_value = v_item["item5"];
                if(i_value.isInt())
                {
                    item5 = i_value.asInt();
                }

                i_value = v_item["item6"];
                if(i_value.isString())
                {
                    item6 = i_value.asString();
                }

                i_value = v_item["item7"];
                if(i_value.isInt())
                {
                    item7 = i_value.asString();
                }

                i_value = v_item["item8"];
                if(i_value.isInt())
                {
                    item8 = i_value.asString();
                }

                i_value = v_item["item9"];
                if(i_value.isInt())
                {
                    item9 = i_value.asString();
                }

                i_value = v_item["item10"];
                if(i_value.isInt())
                {
                    item10 = i_value.asString();
                }
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }
};

struct JsonNestedMessage
{
    std::vector<int32_t> item1;
    std::vector<std::string> item2;

    SttString *ToTextMessage(SttString *str)
    {
        Json::Value v_item(Json::objectValue);
        
        Json::Value arr_item(Json::arrayValue);  
        BOOST_FOREACH(int int_val, item1)
        {
            arr_item.append(int_val);
        }

        v_item["item1"] = arr_item;

        arr_item.clear();
        BOOST_FOREACH(std::string &str_val, item2)
        {
            arr_item.append(str_val.c_str());
        }

        v_item["item2"] = arr_item;
        
        Json::FastWriter j_writer;
        str->CopyFrom(j_writer.write(v_item).c_str());

        return str;
    }

    bool FromTextMessage(const char *msg)
    {
         bool ret = true;

        Json::Value v_item(Json::objectValue);
        Json::Reader j_reader;
        if(j_reader.parse(msg, v_item, false))
        {
            if(v_item.isObject())
            {
                Json::Value i_value = v_item["item1"];
                if(i_value.isArray())
                {
                    for(int i = 0; i < i_value.size(); ++i)
                    {
                        if(i_value[i].isInt())
                        {
                            item1.push_back(i_value[i].asInt());
                        }
                    }
                }

                i_value = v_item["item2"];
                if(i_value.isArray())
                {
                    for(int i = 0; i < i_value.size(); ++i)
                    {
                        if(i_value[i].isString())
                        {
                            item2.push_back(i_value[i].asString());
                        }
                    }
                }
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }


        return ret;
    }
};

