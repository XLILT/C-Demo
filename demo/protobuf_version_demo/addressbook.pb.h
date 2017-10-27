// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: addressbook.proto

#ifndef PROTOBUF_addressbook_2eproto__INCLUDED
#define PROTOBUF_addressbook_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_addressbook_2eproto();
void protobuf_AssignDesc_addressbook_2eproto();
void protobuf_ShutdownFile_addressbook_2eproto();

class Person;

// ===================================================================

class Person : public ::google::protobuf::Message {
 public:
  Person();
  virtual ~Person();

  Person(const Person& from);

  inline Person& operator=(const Person& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Person& default_instance();

  void Swap(Person* other);

  // implements Message ----------------------------------------------

  inline Person* New() const { return New(NULL); }

  Person* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Person& from);
  void MergeFrom(const Person& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Person* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string age = 1;
  void clear_age();
  static const int kAgeFieldNumber = 1;
  const ::std::string& age() const;
  void set_age(const ::std::string& value);
  void set_age(const char* value);
  void set_age(const char* value, size_t size);
  ::std::string* mutable_age();
  ::std::string* release_age();
  void set_allocated_age(::std::string* age);

  // optional string sex = 2;
  void clear_sex();
  static const int kSexFieldNumber = 2;
  const ::std::string& sex() const;
  void set_sex(const ::std::string& value);
  void set_sex(const char* value);
  void set_sex(const char* value, size_t size);
  ::std::string* mutable_sex();
  ::std::string* release_sex();
  void set_allocated_sex(::std::string* sex);

  // optional string sex1 = 33;
  void clear_sex1();
  static const int kSex1FieldNumber = 33;
  const ::std::string& sex1() const;
  void set_sex1(const ::std::string& value);
  void set_sex1(const char* value);
  void set_sex1(const char* value, size_t size);
  ::std::string* mutable_sex1();
  ::std::string* release_sex1();
  void set_allocated_sex1(::std::string* sex1);

  // @@protoc_insertion_point(class_scope:Person)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr age_;
  ::google::protobuf::internal::ArenaStringPtr sex_;
  ::google::protobuf::internal::ArenaStringPtr sex1_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_addressbook_2eproto();
  friend void protobuf_AssignDesc_addressbook_2eproto();
  friend void protobuf_ShutdownFile_addressbook_2eproto();

  void InitAsDefaultInstance();
  static Person* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Person

// optional string age = 1;
inline void Person::clear_age() {
  age_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Person::age() const {
  // @@protoc_insertion_point(field_get:Person.age)
  return age_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_age(const ::std::string& value) {
  
  age_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Person.age)
}
inline void Person::set_age(const char* value) {
  
  age_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Person.age)
}
inline void Person::set_age(const char* value, size_t size) {
  
  age_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Person.age)
}
inline ::std::string* Person::mutable_age() {
  
  // @@protoc_insertion_point(field_mutable:Person.age)
  return age_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_age() {
  
  return age_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_age(::std::string* age) {
  if (age != NULL) {
    
  } else {
    
  }
  age_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), age);
  // @@protoc_insertion_point(field_set_allocated:Person.age)
}

// optional string sex = 2;
inline void Person::clear_sex() {
  sex_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Person::sex() const {
  // @@protoc_insertion_point(field_get:Person.sex)
  return sex_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_sex(const ::std::string& value) {
  
  sex_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Person.sex)
}
inline void Person::set_sex(const char* value) {
  
  sex_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Person.sex)
}
inline void Person::set_sex(const char* value, size_t size) {
  
  sex_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Person.sex)
}
inline ::std::string* Person::mutable_sex() {
  
  // @@protoc_insertion_point(field_mutable:Person.sex)
  return sex_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_sex() {
  
  return sex_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_sex(::std::string* sex) {
  if (sex != NULL) {
    
  } else {
    
  }
  sex_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sex);
  // @@protoc_insertion_point(field_set_allocated:Person.sex)
}

// optional string sex1 = 33;
inline void Person::clear_sex1() {
  sex1_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Person::sex1() const {
  // @@protoc_insertion_point(field_get:Person.sex1)
  return sex1_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_sex1(const ::std::string& value) {
  
  sex1_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Person.sex1)
}
inline void Person::set_sex1(const char* value) {
  
  sex1_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Person.sex1)
}
inline void Person::set_sex1(const char* value, size_t size) {
  
  sex1_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Person.sex1)
}
inline ::std::string* Person::mutable_sex1() {
  
  // @@protoc_insertion_point(field_mutable:Person.sex1)
  return sex1_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_sex1() {
  
  return sex1_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_sex1(::std::string* sex1) {
  if (sex1 != NULL) {
    
  } else {
    
  }
  sex1_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sex1);
  // @@protoc_insertion_point(field_set_allocated:Person.sex1)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_addressbook_2eproto__INCLUDED
