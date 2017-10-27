#include <utility>
#include <string>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <assert.h>
#include <boost/pool/singleton_pool.hpp>
#include <stdio.h>
#include <boost/regex.hpp>
#include <boost/unordered_map.hpp>
#include <unistd.h>
#include <boost/thread.hpp>
#include <textlog/textlog.h>
#include <boost/lexical_cast.hpp>
#include <Common/Tools.h>
#include "stdafx.h"
#include "A.h"
#include <stdio.h>

//#include "cache_file.h"

using namespace std;

#define STT_BUFFER_BLOCK_SIZE 4096
#define STT_BUFFER_BLOCK_MASK ~0xFFF
#define STT_BASE_BUFFER_SIZE 8192

#ifdef _DEBUG
    #define XXX 1
#else
    #define XXX 0
#endif

//int a = 0;
volatile int a = 0;

static uint32_t seed = 1;

static void hexdump(FILE *f, const char *title, const unsigned char *s, int len)
{
//#define HEXDUMPTYPE

#ifdef HEXDUMPTYPE

    int n = 0;
    fprintf(f, "%s", title);

    for (n = 0; n < len; ++n)
    {
        fprintf(f, "%02x", s[n]);
    }
#else
    int n = 0;
    fprintf(f, "%s", title);

    for (; n < len; ++n)
    {
        if ((n % 16) == 0)
        {
                fprintf(f, "\n%04x", n);
        }

        fprintf(f, " %02x", s[n]);
    }

    fprintf(f, "\n");
#endif
}

int get_local_current_date()
{
    time_t t = time(NULL);  // 获取unix time
    struct tm st_time;

#ifdef _MSC_VER
    localtime_s(&st_time, &t);
#else       //_MSC_VER
    localtime_r(&t, &st_time);
#endif      //_MSC_VER

    char buffer[16];
    memset(buffer, 0, sizeof(buffer));

    snprintf(buffer, sizeof(buffer), "%4d%02d%02d", st_time.tm_year + 1900,
        st_time.tm_mon + 1, st_time.tm_mday);

    return atoi(buffer);
}

void add()
{
    for(int cnt=0; cnt < 1000000; cnt++)
    {
        a += 1;
    }

}

void del()
{
    for(int cnt=0; cnt < 1000000; cnt++)
    {
        a -= 1;
    }

}

void prt()
{
   while(1)
   {
       cout << "ing ***" << a << endl;
   }
}
inline static int ComputeAllocSize(int nSize)
{

        return (nSize + STT_BASE_BUFFER_SIZE - 1) & (~(STT_BASE_BUFFER_SIZE - 1));
}

static const char * const greeting = "hello friend";

std::vector<std::string> split(std::string str,std::string s)
{
    boost::regex reg(s.c_str());
    std::vector<std::string> vec;
    boost::sregex_token_iterator it(str.begin(),str.end(),reg,-1);
    boost::sregex_token_iterator end;
    while(it!=end)
    {
        vec.push_back(*it++);
    }
    return vec;
}

class A
{
private:
    int _x;
public:
    A(int x)
    {
        _x = x;
        cout << "Construct" << endl;
    }

    ~A()
    {
        cout << "Deconstruct" << endl;
    }

    void f()
    {
        //delete this;
        cout << "come on!" << _x << endl;
    }
};

#if 0

template<typename T>
class A
{
public:
    typedef std::map<string, T> my_map;
    my_map map_;

public:
    A(){}
    ~A(){}

    //void put(string id, T data){my_map[id] = data;}
    const T & get(string id)
    {
        typename std::map< string, T >::iterator it = map_.end();
    }
};


template<typename T>
class MyTemplate
{
  class Inner {};
  Inner met();
};

template<typename T>
typename MyTemplate<T>::Inner  MyTemplate<T>::met()
{}

void print(int elem)
{
    cout << elem <<  " ";
}

class Base1
{
public:
    virtual void f()=0;
    //int x;
};

class Base2
{
public:
    virtual void f()=0;
    //int x;
};

class FromTwo : public Base1, public Base2
{
};

#pragma pack(16)
class C1
{
    int a;
    char c;
};
#endif

struct C2
{
    int a;
    char c;
};

#if 0

union C3
{
    int a;
    char c;
};
#pragma pack()


#pragma pack(1)
struct C4
{
    int m_id;
    //string name;

    C4() : m_id(0){}

    C4(int id) : m_id(id){}

    bool toString(std::string str)
    {
        str.assign("hehe");
        return true;
    }
};
#pragma pack()

struct C5
{
    public:
    uint64_t push_time;    //放入队列的时间
    uint64_t start_time;   //开始执行的时间
    uint64_t exec_time;    //执行时长
    uint64_t alert_wait_time;  //阀值，等待时长超过此值则进行警告
    uint64_t alert_exec_time;  //阀值，执行时长超过此值则进行警告
    char     src_info[1024];   //源代码信息 源文件 行号 函数名
    char     hint_str[1024];   //提示信息
};

///static void f(C4 x)
///{
///    cout << x.m_id << ", ";
///}

//struct pool_tag{};
//typedef boost::singleton_pool<pool_tag, 4096> my_pool;

class Base1
{
public:
    virtual void f(){cout << "Base1" << endl;};
    //int x;
};

class Base2
{
public:
    virtual void f(){cout << "Base2" << endl;};
    //int x;
};

class FromTwo : public Base1, public Base2
{
public:
    void f(){cout << "FromTwo" << endl;};
};

void g(Base1 *p)
{
    p->f();
}

typedef boost::function<void (void)> CB;

struct CB_Struct
{
    CB cb;
};

void run_cb(list<CB_Struct *> &m_list)
{

    list<CB_Struct *> tmp_list;
    tmp_list.swap(m_list);
    //tmp_list.swap(m_list);

    for(list<CB_Struct *>::iterator it_list = tmp_list.begin(); it_list != tmp_list.end(); it_list++)
    {
        (*it_list)->cb();
    }
}

void print_int(int &x)
{
    cout << hex << &x << ", " << x << endl;
}
#endif

#if 0
void* operator new(size_t size)
{
   printf("malloc %lu\r\n", size);
   return malloc(size);
}

void operator delete(void *memblock)
{
   printf("free\r\n");
   return free(memblock);
}
#endif

class abc
{
public:
    abc()
    {
        printf("abc\r\n");
        throw int();
    }

    ~abc()
    {
        printf("~abc\r\n");
    }
};

class abc;
void del(abc *pobj)
{
    delete pobj;
}

void print_str(const char *str, const int i)
{
    cout << str << endl;
}

void test_gdb_str()
{
    const char * const str[] =
    {
        "123",
        "456",
        "789"
    };

    for(unsigned int i = 0; i < sizeof(str) / sizeof(const char *); i++)
    {
        print_str(str[i], i);
    }
}

SttString * MS_SharkPetsToTextMessage(SttString * str)
{
    SttEncoder list_enc;
    SttString list_str;

    // 招财
    SttEncoder zhaocai_enc;
    SttString zhaocai_str;
    zhaocai_enc.AddItem("name", "zc");
    zhaocai_enc.AddItem("ts", 1);
    zhaocai_enc.GetResualt(&zhaocai_str);

    list_enc.AddItem(zhaocai_str.c_UTF8());

    // 祥瑞
    SttEncoder xiangrui_enc;
    SttString xiangrui_str;
    xiangrui_enc.AddItem("name", "xr");
    xiangrui_enc.AddItem("ts", 2);
    xiangrui_enc.GetResualt(&xiangrui_str);

    list_enc.AddItem(xiangrui_str.c_UTF8());

    // 至尊
    SttEncoder zhizun_enc;
    SttString zhizun_str;
    zhizun_enc.AddItem("name", "zz");
    zhizun_enc.AddItem("ts", 3);
    zhizun_enc.GetResualt(&zhizun_str);

    list_enc.AddItem(zhizun_str.c_UTF8());

    // 获取list
    list_enc.GetResualt(&list_str);

    SttEncoder enc;
    enc.AddItem("type", "user_pets");
    enc.AddItem("list", list_str.c_UTF8());

    return enc.GetResualt(str);
}

class TestInheritBase
{
public:
    virtual void f() { printf("this is f of TestInheritBase\n"); }
};

class TestInheritSon : public TestInheritBase
{
public:
    void f() { printf("this is f of TestInheritSon\n"); }
};

void printf_rand()
{
    cout << "seed: " << seed << endl;
    cout << rand() << ", " << rand();
    seed = 2;
    srand(seed);
    cout << "seed: " << seed << endl;
    cout << ", " << rand() << ", " << rand() << endl;
}

unsigned int BKDRHash(const char * str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    const char * p = str;

    while (*p)
    {
        hash = hash * seed + (*p++);
    }

    return (hash & 0x7FFFFFFF);
}

void stap_f1()
{
    for(int i = 0; i < 1000000; ++i)
    {

    }
}

void stap_test()
{
    while(1)
    {
        stap_f1();

        //sleep(1);
    }
}

std::string get_const_ref(int x)
{
    char tmp[1024] = {0};
    snprintf(tmp, sizeof(tmp), "%d", x);

    return tmp;
}

int main(int argc, char **argvs)
{
#if 0
    //int a[] = {1, 2, 3};
    //vector<int> v(a, a + 3);
    //list<int> L(a, a + 3);
    //for_each(L.begin(), L.end(), print);
    //boost::function<int (const char*)> f = std::atoi;
    //std::cout << f("1609") << std::endl;
    //f = std::strlen;
    //std::cout << f("1609") << std::endl;

    //B b;
    //void *p = NULL;

    //cout << "size of base1: " << sizeof(Base1) << endl;
    //cout << "size of base2: " << sizeof(Base2) << endl;
    //cout << "size of from two: " << sizeof(FromTwo) << endl;
    //cout << "size of pointer: " << sizeof(p) << endl;
    //cout << "size of C1: " << sizeof(C1) << endl;
    //cout << "size of C2: " << sizeof(C2) << endl;
    //cout << "size of C3: " << sizeof(C3) << endl;
    //cout << sizeof(b) << endl;
    //cout << b.x << endl;

    //int *p = new int[1024 * 1024 * 2];

    //cout << sizeof(p) << endl;
    //memset(p , 0, sizeof(*p) * 1024 * 1024 * 2);

    //string str;
    //cin >>     str;

    //delete []p;

    cout << sizeof(C4) << endl;

    //list<int> m_vect;
    vector<C4> m_vect;
    m_vect.push_back(C4(1));
    m_vect.push_back(C4(2));
    m_vect.push_back(C4(3));

    //int sum = 0;
    //boost::shared_ptr<int> sum(new int(0));
    //std::for_each(m_vect.begin(), m_vect.end(), boost::bind(&f, _1, boost::ref(sum)));

    std::for_each(m_vect.begin(), m_vect.end(), &f);
    cout  << endl;

    int total_serialize_count;
    dump_data_to_file("test.txt", m_vect, total_serialize_count);

    int total_load_count;
    vector<C4> load_vect;
    load_data_from_file("test.txt", load_vect, total_load_count);


    std::for_each(load_vect.begin(), load_vect.end(), &f);
    cout  << endl;


    //string tmp_str;
    char tmp_str[64];
    while(string(tmp_str) != "exit")
    {
        int *p[100000];
        for (int i = 0; i < 100000; i++)
        {
            //p[i] = (int *)my_pool::malloc();
            p[i] = new int[1024];
            //p[i] = (int *)malloc(1024 * 4);
            //usleep(10000);
            //cout << "malloc" << i << endl;
        }


        //getchar();
        //char ch[123];
        //cin >> ch;
        //string s1("123");

        //vector<int> m_v;
        //m_v.push_back(1);
        //{
        //    vector<int> tmp_v;
        //    m_v.swap(tmp_v);
        //}

        //list<int> m_list;
        //m_list.push_back(1);
        //{
        //    list<int> tmp_l;
        //    m_list.swap(tmp_l);
        //}

        //string *s1 = new string("123");
        //s1->append("123");
        //delete s1;
        //s1.append("123");

        //string s2;
        //s1.swap(s2);
        //cin >> s1;
        //sleep(10);
        //cout << "hehe" << endl;
        for (int i = 0; i < 100000; i++)
        {
            //my_pool::free(p[i]);
            delete []p[i];
            //free(p[i]);
            //cout << "free" << i << endl;
        }

        cout << "free all" << endl;
        //cin >> tmp_str;
    }

    //list<int> m_list;
    //m_list.push_back(1);

    //cout << m_list << endl;

    //cout << sizeof(FromTwo) << endl;

#endif  //endof 0
#if 0
    {
        FromTwo ft;
        Base1 b1;
        Base2 b2;
        CB cb = boost::bind(&FromTwo::f, ft);
        CB cb1 = boost::bind(&Base1::f, b1);
        CB cb2 = boost::bind(&Base2::f, b2);


        CB_Struct *tmp_cb1 = new CB_Struct;
        tmp_cb1->cb = cb;

        CB_Struct *tmp_cb2 = new CB_Struct;
        tmp_cb2->cb = cb1;

        CB_Struct *tmp_cb3 = new CB_Struct;
        tmp_cb3->cb = cb2;

        list<CB_Struct *> m_list;
        m_list.push_back(tmp_cb1);
        m_list.push_back(tmp_cb2);
        m_list.push_back(tmp_cb3);

        new boost::thread(boost::bind(&run_cb, m_list));

        //int x = 9;
        //cout <<hex << &x << " here, " << x << endl;
        //new boost::thread(boost::bind(&print_int, x));
    }

    //int *y = new int;
    //cout << "y" << hex << y << endl;

    //abc *pobj = new abc;
    //delete pobj;
    //del(pobj);

    try
    {
        //new abc;
    }
    catch(int& i)
    {
        printf("%d\r\n", i);
    }

    //getchar();

    char obj_str[] = "123\r\nabc\r\nxyz\r\n";
    //char tmp_str[] = "abc,d";
    char *p = obj_str;
    char *token = strsep(&p, "\r\n");
    //char *token = obj_str;

    static int s_tmp;
    int x_tmp;
    int *p_tmp = new int;

    static C2 s_c2;
    C2 stack_c2;
    C2 *heap_c2 = new C2;


    string tmp_str = "123\r\nabc\r\nxyz\r\n";
    vector<string> vector_str = split(tmp_str, "\r\n");

    //printf("%s\n%ld\n", tmp_str.c_str(), vector_str.size());
    //printf("&s_tmp: %p\r\n&x_tmp: %p\np_tmp: %p\n", &s_tmp, &x_tmp, p_tmp);
    //printf("&s_c2: %p\r\n&stack_c2: %p\nheap_c2: %p\n", &s_c2, &stack_c2, heap_c2);

    boost::unordered_map< pair<int, int>, int> m;
    pair<int, int> p1 = make_pair(1, 2);
    pair<int, int> p2 = make_pair(1, 2);
    m[p1] = 3;
    m[p2] = 4;
    m[make_pair(3, 4)] = 7;
    //m[make_pair(3, 4)] = 8;

    //cout << m.size() << endl;
    cout << (p1 != p2) << endl;

    m.clear();

    //while(1)
    //{
    //    cout << "hehe" << endl;
    //    //usleep(10000);
    //}
    //printf("obj_str:%s # %p\ntoken:%s # %p\n", obj_str, obj_str, token, token);

    //cout << "before: " << a << endl;
    //boost::thread t1(boost::bind(&add));
    //boost::thread t2(boost::bind(&del));
    //boost::thread(boost::bind(&prt));

    //t1.join();
    //boost::thread t2(boost::bind(&del));
    //t2.join();

    //cout << "after: " << a << endl;
    //m_lock.unlock();
    //m_lock.unlock();
    //TL_FAST_LOG("tmp.log", tlstNoSplit, "haha");
    //TL_FAST_LOG("./tmp.log", tlstNoSplit, "haha1");
    //cout << "hehe" << endl;
    //TL_SHUTDOWN();

    //test_gdb_str();
    uint32_t ts = -1;
    string str1;
    string str2;

    //cout << MS_SharkPetsToTextMessage(NULL)->c_UTF8() << endl;
    //cout << sizeof(unsigned long) << endl;
    //cout << "get_local_current_date: " << get_local_current_date() << endl;

    //boost::unordered_map<int, int> m;
    //m.reserve(atoi(argvs[1]));
    //std::vector<int> v;
    //v.reserve(atoi(argvs[1]));

    TestInheritBase *ti = new TestInheritSon();

    //ti->f();

    boost::function<void()>  func = boost::bind(&TestInheritBase::f, ti);
    printf("sizeof func:%lu\n", sizeof(func));
    func();

    delete ti;

    cout << atoi("1@S-9999@S") << endl;
    getchar();


    //cout << AAA::x << endl;
    std::set<int> m_set;
    for(int i = 0; i < 10000000; ++i)
    {
        m_set.insert(i);
    }

    uint64_t start_tick = SttGetUsTickCount();
    m_set.clear();

    printf("set clear times cost avg:%luus\n", SttGetUsTickCount() - start_tick);


    AAA *a = new AAA;
    a->x = 1;

    AAA *a1 = a;
    printf("before del: %d\n", a1->x);

    delete a;
    printf("after del: %d\n", a1->x);

    //cout << strlen(NULL) << endl;
    cout << sizeof(std::string) << endl;


    const char * const rpc_send_mail = "send_mail";
    const char * const rpc_query_mail = "query_mail";
    const char * const rpc_handle_mail = "handle_mail";
    const char * const rpc_query_mail_count = "query_mail_count";
    const char * const rpc_handle_mails_list = "handle_mails_list";
    const char * const rpc_del_mails_from_uid = "del_mails_from_uid";


    const char * const rpc_names[] = {
        rpc_send_mail,
        rpc_query_mail,
        rpc_handle_mail,
        rpc_query_mail_count,
        rpc_handle_mails_list,
        rpc_del_mails_from_uid
    };

    cout << sizeof(rpc_names) / sizeof(char *) << endl;
    cout << rpc_names[0] << endl;
    cout << rpc_names[1] << endl;

    printf("%x\n", (char)0x87);
    printf("%x\n", (char)-1);
    char x = 0x87;
    printf("%x\n", x);


    float f = 6.24;
    cout << boost::lexical_cast<string>(f) << endl;

    cout << convertToString(f) << endl;

    printf("%f\n", f);


    const char ** str_arr = NULL;
    //str_arr = new const char *[2];
    char ** tmp_arr = new char *[2];
    str_arr = tmp_arr;

    str_arr[0] = "0";
    str_arr[1] = "1";

    cout << str_arr[0] << endl;
    cout << str_arr[1] << endl;


    char str[8] = {0};

    hexdump(stdout, "str before snprintf", reinterpret_cast<unsigned char *>(str), sizeof(str));

    snprintf(str, sizeof(str), "1234567");

    hexdump(stdout, "str after snprintf", reinterpret_cast<unsigned char *>(str), sizeof(str));

    printf("hello world\n");

    boost::thread_group thread_gp;
    thread_gp.add_thread(new boost::thread(boost::bind(printf_rand)));
    //thread_gp.add_thread(new boost::thread(boost::bind(printf_rand)));

    thread_gp.join_all();



    map<int, int> m;
    m[1] = 1;

    map<int, int>::const_iterator cit = m.end();
    ++cit;
    ++cit;
    ++cit;

    SttEncoder enc_list;

    SttEncoder enc;
    enc.AddItem("eid", 1);
    enc.AddItem("etp", 1);
    enc.AddItem("esc", 1);

    enc_list.AddItem(boost::scoped_ptr<SttString>(enc.GetResualt(NULL))->c_UTF8());

    enc.AddItem("eid", 2);
    enc.AddItem("etp", 2);
    enc.AddItem("esc", 2);

    enc_list.AddItem(boost::scoped_ptr<SttString>(enc.GetResualt(NULL))->c_UTF8());

    SttEncoder enc2;
    enc2.AddItem("el", boost::scoped_ptr<SttString>(enc_list.GetResualt(NULL))->c_UTF8());

    cout << boost::scoped_ptr<SttString>(enc2.GetResualt(NULL))->c_UTF8() << endl;

    cout << sizeof(boost::shared_ptr<int>) << endl;
    cout << sizeof(boost::shared_ptr<char>) << endl;
    cout << sizeof(boost::shared_ptr<std::string>) << endl;

    cout << sizeof(void *) << endl;

    struct AA {
        int x[64];
    };

    int i = 0;
    while(1)
    {
        AA *a = (AA *)(new int);

        if(++i % 100 == 0)
        {
            cout << a << endl;
        }

        AA a2 = *a;
        //delete a;
    }
    #endif

    //cout << BKDRHash("test_mxl") << endl;
    //

    //stap_test();
    //

    std::cout << get_const_ref(1) << std::endl;

    return 0;
}

