#include <iostream>
#include <fstream>
#include <string>
#include "stdafx.h"
#include "addressbook.pb.h"
#include "test.pb.h"
#include "test_stt.h"
#include "test_json.h"

using namespace std;

// This function fills in a Person message based on user input.
void PromptForAddress(tutorial::Person* person) {
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while (true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        tutorial::Person::PhoneNumber* phone_number = person->add_phone();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial::Person::MOBILE);
        } else if (type == "home") {
            phone_number->set_type(tutorial::Person::HOME);
        } else if (type == "work") {
            phone_number->set_type(tutorial::Person::WORK);
        } else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}

uint32_t serialize_to_array(uint8_t *buff, int count)
{
    uint32_t buf_size = 0;

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    /*
    tutorial::AddressBook address_book;
    tutorial::Person *new_person = address_book.add_person();
    new_person->set_id(1);
    new_person->set_name("1234567890");
    new_person->set_email("12345678901234567890");

    tutorial::Person::PhoneNumber *new_phone_number = new_person->add_phone();
    new_phone_number->set_number("12345678901");
    new_phone_number->set_type(tutorial::Person::MOBILE);

    string serialize_string;
    printf("address_book bytesize:%d\n", address_book.ByteSize());
    address_book.SerializeToString(&serialize_string);
    printf("serialize_string size: %lu\n", serialize_string.size());
    buf_size = serialize_string.size();

    //char *buff = new char[1024];
    //char *buff = new char[address_book.ByteSize()];
    uint64_t start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        address_book.SerializeToArray(buff, address_book.ByteSize());
    }

    uint64_t stop_tick = SttGetTickCount();
    printf("serialize %d times cost %lu ms\n", count, stop_tick - start_tick);
    */

    ParallelMessage parallel_message;

    parallel_message.set_item1(1);
    parallel_message.set_item2(1);
    parallel_message.set_item3(1);
    parallel_message.set_item4(1);
    parallel_message.set_item5(1);
    parallel_message.set_item5(1);
    parallel_message.set_item6("1");
    parallel_message.set_item7("1");
    parallel_message.set_item8("1");
    parallel_message.set_item9("1");
    parallel_message.set_item10("1");
    
    buf_size = parallel_message.ByteSize();
    std::string str_result;
    uint64_t start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        // parallel_message.SerializeToArray(buff, buf_size);
        parallel_message.SerializeToString(&str_result);
    }

    uint64_t stop_tick = SttGetTickCount();
    printf("serialize parallel_messag %d times cost %lu ms\n", count, stop_tick - start_tick);

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        //parallel_message.ParseFromArray(buff, buf_size);
        parallel_message.ParseFromString(str_result);
        
    }

    stop_tick = SttGetTickCount();
    printf("parse parallel_messag %d times cost %lu ms\n", count, stop_tick - start_tick);

    NestedMessage nested_message;

    nested_message.add_item1(1);
    nested_message.add_item1(1);
    nested_message.add_item1(1);
    nested_message.add_item1(1);
    nested_message.add_item1(1);
    nested_message.add_item2("1");
    nested_message.add_item2("1");
    nested_message.add_item2("1");
    nested_message.add_item2("1");
    nested_message.add_item2("1");

    buf_size = nested_message.ByteSize();
    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        nested_message.SerializeToArray(buff, buf_size);
    }

    stop_tick = SttGetTickCount();
    printf("serialize nested_message %d times cost %lu ms\n", count, stop_tick - start_tick);

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        nested_message.ParseFromArray(buff, buf_size);
    }

    stop_tick = SttGetTickCount();
    printf("parse nested_message %d times cost %lu ms\n\n", count, stop_tick - start_tick);


    google::protobuf::ShutdownProtobufLibrary();

    return buf_size;
}

void test_stt_serialize_parse(int count)
{
    SttParallelMessage stt_parallel_message;

    SttString stt_str;

    uint64_t start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        stt_parallel_message.ToTextMessage(&stt_str);
    }

    printf("%s\n", stt_str.c_UTF8());
    uint64_t stop_tick = SttGetTickCount();
    printf("serialize stt_parallel_message %d cost %lu ms\n", count, stop_tick - start_tick);

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        stt_parallel_message.FromTextMessage(stt_str.c_UTF8());
    }

    stop_tick = SttGetTickCount();
    printf("parse stt_parallel_message %d cost %lu ms\n", count, stop_tick - start_tick);


    SttNestedMessage stt_nested_message;

    stt_nested_message.item1.push_back(0);
    stt_nested_message.item1.push_back(0);
    stt_nested_message.item1.push_back(0);
    stt_nested_message.item1.push_back(0);
    stt_nested_message.item1.push_back(0);
    stt_nested_message.item2.push_back("0");
    stt_nested_message.item2.push_back("0");
    stt_nested_message.item2.push_back("0");
    stt_nested_message.item2.push_back("0");
    stt_nested_message.item2.push_back("0");

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        stt_nested_message.ToTextMessage(&stt_str);
    }

    stop_tick = SttGetTickCount();
    printf("%s\n", stt_str.c_UTF8());
    printf("serialize stt_nested_message %d cost %lu ms\n", count, stop_tick - start_tick);

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        stt_nested_message.FromTextMessage(stt_str.c_UTF8());
    }

    stop_tick = SttGetTickCount();
    printf("parse stt_nested_message %d cost %lu ms\n\n", count, stop_tick - start_tick);
}

void test_json_serialize_parse(int count)
{
    JsonParallelMessage json_parallel_message;
    
    SttString stt_str;

    uint64_t start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        json_parallel_message.ToTextMessage(&stt_str);
    }

    printf("%s", stt_str.c_UTF8());
    uint64_t stop_tick = SttGetTickCount();
    printf("serialize json_parallel_message %d cost %lu ms\n", count, stop_tick - start_tick);

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        json_parallel_message.FromTextMessage(stt_str.c_UTF8());
    }

    stop_tick = SttGetTickCount();
    printf("parse json_parallel_message %d cost %lu ms\n", count, stop_tick - start_tick);

    JsonNestedMessage json_nested_message;

    json_nested_message.item1.push_back(0);
    json_nested_message.item1.push_back(0);
    json_nested_message.item1.push_back(0);
    json_nested_message.item1.push_back(0);
    json_nested_message.item1.push_back(0);
    json_nested_message.item2.push_back("0");
    json_nested_message.item2.push_back("0");
    json_nested_message.item2.push_back("0");
    json_nested_message.item2.push_back("0");
    json_nested_message.item2.push_back("0");

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        json_nested_message.ToTextMessage(&stt_str);
    }

    stop_tick = SttGetTickCount();
    printf("%s", stt_str.c_UTF8());
    printf("serialize json_nested_message %d cost %lu ms\n", count, stop_tick - start_tick);

    start_tick = SttGetTickCount();
    for(int i = 0; i < count; ++i)
    {
        json_nested_message.FromTextMessage(stt_str.c_UTF8());
    }

    stop_tick = SttGetTickCount();
    printf("parse json_nested_message %d cost %lu ms\n\n", count, stop_tick - start_tick);

}

void parse_from_array(uint8_t *buff, uint32_t buf_size, int count)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    tutorial::AddressBook address_book;

    address_book.ParseFromArray(buff, buf_size);
    printf("address_book size: %d\n", address_book.ByteSize());

    for(int i = 0; i < address_book.person_size(); ++i)
    {
        printf("%d %s %s ", address_book.person(i).id(), address_book.person(i).name().c_str(), address_book.person(i).email().c_str());

        for(int j = 0; j < address_book.person(i).phone_size(); ++j)
        {
            printf("%d %s\n", address_book.person(i).phone(i).type(), address_book.person(i).phone(i).number().c_str());
        }


    }

    uint64_t start_tick = SttGetTickCount();
    for(int k = 0; k < count; ++k)
    {
        address_book.ParseFromArray(buff, buf_size);
    }

    uint64_t stop_tick = SttGetTickCount();
    printf("parse %d times cost %lu ms\n", count, stop_tick - start_tick);

}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    /*
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        // Read the existing address book.
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout << argv[1] << ": File not found.  Creating a new file." << endl;
        } else if (!address_book.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    // Add an address.
    PromptForAddress(address_book.add_person());

    {
        // Write the new address book back to disk.
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    */
    uint8_t *buf = new uint8_t[1024];
    int count = argc > 1 ? atoi(argv[1]) : 1;

    serialize_to_array(buf, count);

    test_stt_serialize_parse(count);

    test_json_serialize_parse(count);

    //parse_from_array(buf, sizeof(uint8_t) * 1024, count);

    return 0;
}

