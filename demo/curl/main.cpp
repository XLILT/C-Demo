#include <CurLib/CSttCurLib.h>

/*
#pragma comment(lib, "CurLib.lib")
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "CommonBase.lib")
*/

int main(int argc, char* argv[])
{
    std::string str_post = "city=异地&cnt=1040&time=1448627004&tp=1&uid=21539&auth=797e17fc86c083bd26b66749855ecdd4";
    std::string str_ret;

    curl_global_init(CURL_GLOBAL_ALL);
    //CSttCurLib::GetInstance()->CreateDownFile("http://ffmpeg.zeranoe.com/builds/win64/static/ffmpeg-20140626-git-7e8fdf0-win64-static.7z","./ffmpeg.7z",30,1);
    //int code = CSttCurLib::GetInstance()->Get("www.douyutv1.com", str1);
    //int code = CSttCurLib::GetInstance()->Get("http://192.168.91.132/", str1);
    //int code = CSttCurLib::GetInstance()->Posts("http://192.168.91.132/", str_post, str_ret, NULL);
    //int code = CSttCurLib::GetInstance()->Posts("http://live.dz11.com/api/cppSms/yw_consume_sms", str_post, str_ret, NULL);
    int code = CSttCurLib::GetInstance()->Posts("http://live.dz11.com/api/cppSms/yw_consume_sms", str_post, str_ret, NULL, 3, 1);
    //int code = CSttCurLib::GetInstance()->CreateDownFile("www.baidu.com","./douyu2.txt",30,1);

    printf("code:%d\n", code);
    //while(1)
    //if (200 == code)
    if(0 == code)
    {
        FILE *f = fopen("./douyu3.txt", "w+");
        fwrite(str_ret.data(), 1, str_ret.size(), f);

        fclose(f);
    }

    getchar();
    return 0;
}
