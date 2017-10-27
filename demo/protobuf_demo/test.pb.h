// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef PROTOBUF_test_2eproto__INCLUDED
#define PROTOBUF_test_2eproto__INCLUDED

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
void protobuf_AddDesc_test_2eproto();
void protobuf_AssignDesc_test_2eproto();
void protobuf_ShutdownFile_test_2eproto();

class NestedMessage;
class ParallelMessage;

// ===================================================================

class ParallelMessage : public ::google::protobuf::Message {
 public:
  ParallelMessage();
  virtual ~ParallelMessage();

  ParallelMessage(const ParallelMessage& from);

  inline ParallelMessage& operator=(const ParallelMessage& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ParallelMessage& default_instance();

  void Swap(ParallelMessage* other);

  // implements Message ----------------------------------------------

  inline ParallelMessage* New() const { return New(NULL); }

  ParallelMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ParallelMessage& from);
  void MergeFrom(const ParallelMessage& from);
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
  void InternalSwap(ParallelMessage* other);
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

  // optional int32 item1 = 1;
  void clear_item1();
  static const int kItem1FieldNumber = 1;
  ::google::protobuf::int32 item1() const;
  void set_item1(::google::protobuf::int32 value);

  // optional int32 item2 = 2;
  void clear_item2();
  static const int kItem2FieldNumber = 2;
  ::google::protobuf::int32 item2() const;
  void set_item2(::google::protobuf::int32 value);

  // optional int32 item3 = 3;
  void clear_item3();
  static const int kItem3FieldNumber = 3;
  ::google::protobuf::int32 item3() const;
  void set_item3(::google::protobuf::int32 value);

  // optional int32 item4 = 4;
  void clear_item4();
  static const int kItem4FieldNumber = 4;
  ::google::protobuf::int32 item4() const;
  void set_item4(::google::protobuf::int32 value);

  // optional int32 item5 = 5;
  void clear_item5();
  static const int kItem5FieldNumber = 5;
  ::google::protobuf::int32 item5() const;
  void set_item5(::google::protobuf::int32 value);

  // optional string item6 = 6;
  void clear_item6();
  static const int kItem6FieldNumber = 6;
  const ::std::string& item6() const;
  void set_item6(const ::std::string& value);
  void set_item6(const char* value);
  void set_item6(const char* value, size_t size);
  ::std::string* mutable_item6();
  ::std::string* release_item6();
  void set_allocated_item6(::std::string* item6);

  // optional string item7 = 7;
  void clear_item7();
  static const int kItem7FieldNumber = 7;
  const ::std::string& item7() const;
  void set_item7(const ::std::string& value);
  void set_item7(const char* value);
  void set_item7(const char* value, size_t size);
  ::std::string* mutable_item7();
  ::std::string* release_item7();
  void set_allocated_item7(::std::string* item7);

  // optional string item8 = 8;
  void clear_item8();
  static const int kItem8FieldNumber = 8;
  const ::std::string& item8() const;
  void set_item8(const ::std::string& value);
  void set_item8(const char* value);
  void set_item8(const char* value, size_t size);
  ::std::string* mutable_item8();
  ::std::string* release_item8();
  void set_allocated_item8(::std::string* item8);

  // optional string item9 = 9;
  void clear_item9();
  static const int kItem9FieldNumber = 9;
  const ::std::string& item9() const;
  void set_item9(const ::std::string& value);
  void set_item9(const char* value);
  void set_item9(const char* value, size_t size);
  ::std::string* mutable_item9();
  ::std::string* release_item9();
  void set_allocated_item9(::std::string* item9);

  // optional string item10 = 10;
  void clear_item10();
  static const int kItem10FieldNumber = 10;
  const ::std::string& item10() const;
  void set_item10(const ::std::string& value);
  void set_item10(const char* value);
  void set_item10(const char* value, size_t size);
  ::std::string* mutable_item10();
  ::std::string* release_item10();
  void set_allocated_item10(::std::string* item10);

  // @@protoc_insertion_point(class_scope:ParallelMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::int32 item1_;
  ::google::protobuf::int32 item2_;
  ::google::protobuf::int32 item3_;
  ::google::protobuf::int32 item4_;
  ::google::protobuf::internal::ArenaStringPtr item6_;
  ::google::protobuf::internal::ArenaStringPtr item7_;
  ::google::protobuf::internal::ArenaStringPtr item8_;
  ::google::protobuf::internal::ArenaStringPtr item9_;
  ::google::protobuf::internal::ArenaStringPtr item10_;
  ::google::protobuf::int32 item5_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static ParallelMessage* default_instance_;
};
// -------------------------------------------------------------------

class NestedMessage : public ::google::protobuf::Message {
 public:
  NestedMessage();
  virtual ~NestedMessage();

  NestedMessage(const NestedMessage& from);

  inline NestedMessage& operator=(const NestedMessage& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const NestedMessage& default_instance();

  void Swap(NestedMessage* other);

  // implements Message ----------------------------------------------

  inline NestedMessage* New() const { return New(NULL); }

  NestedMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NestedMessage& from);
  void MergeFrom(const NestedMessage& from);
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
  void InternalSwap(NestedMessage* other);
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

  // repeated int32 item1 = 1;
  int item1_size() const;
  void clear_item1();
  static const int kItem1FieldNumber = 1;
  ::google::protobuf::int32 item1(int index) const;
  void set_item1(int index, ::google::protobuf::int32 value);
  void add_item1(::google::protobuf::int32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      item1() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_item1();

  // repeated string item2 = 2;
  int item2_size() const;
  void clear_item2();
  static const int kItem2FieldNumber = 2;
  const ::std::string& item2(int index) const;
  ::std::string* mutable_item2(int index);
  void set_item2(int index, const ::std::string& value);
  void set_item2(int index, const char* value);
  void set_item2(int index, const char* value, size_t size);
  ::std::string* add_item2();
  void add_item2(const ::std::string& value);
  void add_item2(const char* value);
  void add_item2(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& item2() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_item2();

  // @@protoc_insertion_point(class_scope:NestedMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > item1_;
  mutable int _item1_cached_byte_size_;
  ::google::protobuf::RepeatedPtrField< ::std::string> item2_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static NestedMessage* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ParallelMessage

// optional int32 item1 = 1;
inline void ParallelMessage::clear_item1() {
  item1_ = 0;
}
inline ::google::protobuf::int32 ParallelMessage::item1() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item1)
  return item1_;
}
inline void ParallelMessage::set_item1(::google::protobuf::int32 value) {
  
  item1_ = value;
  // @@protoc_insertion_point(field_set:ParallelMessage.item1)
}

// optional int32 item2 = 2;
inline void ParallelMessage::clear_item2() {
  item2_ = 0;
}
inline ::google::protobuf::int32 ParallelMessage::item2() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item2)
  return item2_;
}
inline void ParallelMessage::set_item2(::google::protobuf::int32 value) {
  
  item2_ = value;
  // @@protoc_insertion_point(field_set:ParallelMessage.item2)
}

// optional int32 item3 = 3;
inline void ParallelMessage::clear_item3() {
  item3_ = 0;
}
inline ::google::protobuf::int32 ParallelMessage::item3() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item3)
  return item3_;
}
inline void ParallelMessage::set_item3(::google::protobuf::int32 value) {
  
  item3_ = value;
  // @@protoc_insertion_point(field_set:ParallelMessage.item3)
}

// optional int32 item4 = 4;
inline void ParallelMessage::clear_item4() {
  item4_ = 0;
}
inline ::google::protobuf::int32 ParallelMessage::item4() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item4)
  return item4_;
}
inline void ParallelMessage::set_item4(::google::protobuf::int32 value) {
  
  item4_ = value;
  // @@protoc_insertion_point(field_set:ParallelMessage.item4)
}

// optional int32 item5 = 5;
inline void ParallelMessage::clear_item5() {
  item5_ = 0;
}
inline ::google::protobuf::int32 ParallelMessage::item5() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item5)
  return item5_;
}
inline void ParallelMessage::set_item5(::google::protobuf::int32 value) {
  
  item5_ = value;
  // @@protoc_insertion_point(field_set:ParallelMessage.item5)
}

// optional string item6 = 6;
inline void ParallelMessage::clear_item6() {
  item6_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ParallelMessage::item6() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item6)
  return item6_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_item6(const ::std::string& value) {
  
  item6_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ParallelMessage.item6)
}
inline void ParallelMessage::set_item6(const char* value) {
  
  item6_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ParallelMessage.item6)
}
inline void ParallelMessage::set_item6(const char* value, size_t size) {
  
  item6_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ParallelMessage.item6)
}
inline ::std::string* ParallelMessage::mutable_item6() {
  
  // @@protoc_insertion_point(field_mutable:ParallelMessage.item6)
  return item6_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ParallelMessage::release_item6() {
  
  return item6_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_allocated_item6(::std::string* item6) {
  if (item6 != NULL) {
    
  } else {
    
  }
  item6_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), item6);
  // @@protoc_insertion_point(field_set_allocated:ParallelMessage.item6)
}

// optional string item7 = 7;
inline void ParallelMessage::clear_item7() {
  item7_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ParallelMessage::item7() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item7)
  return item7_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_item7(const ::std::string& value) {
  
  item7_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ParallelMessage.item7)
}
inline void ParallelMessage::set_item7(const char* value) {
  
  item7_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ParallelMessage.item7)
}
inline void ParallelMessage::set_item7(const char* value, size_t size) {
  
  item7_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ParallelMessage.item7)
}
inline ::std::string* ParallelMessage::mutable_item7() {
  
  // @@protoc_insertion_point(field_mutable:ParallelMessage.item7)
  return item7_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ParallelMessage::release_item7() {
  
  return item7_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_allocated_item7(::std::string* item7) {
  if (item7 != NULL) {
    
  } else {
    
  }
  item7_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), item7);
  // @@protoc_insertion_point(field_set_allocated:ParallelMessage.item7)
}

// optional string item8 = 8;
inline void ParallelMessage::clear_item8() {
  item8_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ParallelMessage::item8() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item8)
  return item8_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_item8(const ::std::string& value) {
  
  item8_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ParallelMessage.item8)
}
inline void ParallelMessage::set_item8(const char* value) {
  
  item8_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ParallelMessage.item8)
}
inline void ParallelMessage::set_item8(const char* value, size_t size) {
  
  item8_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ParallelMessage.item8)
}
inline ::std::string* ParallelMessage::mutable_item8() {
  
  // @@protoc_insertion_point(field_mutable:ParallelMessage.item8)
  return item8_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ParallelMessage::release_item8() {
  
  return item8_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_allocated_item8(::std::string* item8) {
  if (item8 != NULL) {
    
  } else {
    
  }
  item8_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), item8);
  // @@protoc_insertion_point(field_set_allocated:ParallelMessage.item8)
}

// optional string item9 = 9;
inline void ParallelMessage::clear_item9() {
  item9_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ParallelMessage::item9() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item9)
  return item9_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_item9(const ::std::string& value) {
  
  item9_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ParallelMessage.item9)
}
inline void ParallelMessage::set_item9(const char* value) {
  
  item9_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ParallelMessage.item9)
}
inline void ParallelMessage::set_item9(const char* value, size_t size) {
  
  item9_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ParallelMessage.item9)
}
inline ::std::string* ParallelMessage::mutable_item9() {
  
  // @@protoc_insertion_point(field_mutable:ParallelMessage.item9)
  return item9_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ParallelMessage::release_item9() {
  
  return item9_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_allocated_item9(::std::string* item9) {
  if (item9 != NULL) {
    
  } else {
    
  }
  item9_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), item9);
  // @@protoc_insertion_point(field_set_allocated:ParallelMessage.item9)
}

// optional string item10 = 10;
inline void ParallelMessage::clear_item10() {
  item10_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ParallelMessage::item10() const {
  // @@protoc_insertion_point(field_get:ParallelMessage.item10)
  return item10_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_item10(const ::std::string& value) {
  
  item10_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ParallelMessage.item10)
}
inline void ParallelMessage::set_item10(const char* value) {
  
  item10_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ParallelMessage.item10)
}
inline void ParallelMessage::set_item10(const char* value, size_t size) {
  
  item10_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ParallelMessage.item10)
}
inline ::std::string* ParallelMessage::mutable_item10() {
  
  // @@protoc_insertion_point(field_mutable:ParallelMessage.item10)
  return item10_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ParallelMessage::release_item10() {
  
  return item10_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ParallelMessage::set_allocated_item10(::std::string* item10) {
  if (item10 != NULL) {
    
  } else {
    
  }
  item10_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), item10);
  // @@protoc_insertion_point(field_set_allocated:ParallelMessage.item10)
}

// -------------------------------------------------------------------

// NestedMessage

// repeated int32 item1 = 1;
inline int NestedMessage::item1_size() const {
  return item1_.size();
}
inline void NestedMessage::clear_item1() {
  item1_.Clear();
}
inline ::google::protobuf::int32 NestedMessage::item1(int index) const {
  // @@protoc_insertion_point(field_get:NestedMessage.item1)
  return item1_.Get(index);
}
inline void NestedMessage::set_item1(int index, ::google::protobuf::int32 value) {
  item1_.Set(index, value);
  // @@protoc_insertion_point(field_set:NestedMessage.item1)
}
inline void NestedMessage::add_item1(::google::protobuf::int32 value) {
  item1_.Add(value);
  // @@protoc_insertion_point(field_add:NestedMessage.item1)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
NestedMessage::item1() const {
  // @@protoc_insertion_point(field_list:NestedMessage.item1)
  return item1_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
NestedMessage::mutable_item1() {
  // @@protoc_insertion_point(field_mutable_list:NestedMessage.item1)
  return &item1_;
}

// repeated string item2 = 2;
inline int NestedMessage::item2_size() const {
  return item2_.size();
}
inline void NestedMessage::clear_item2() {
  item2_.Clear();
}
inline const ::std::string& NestedMessage::item2(int index) const {
  // @@protoc_insertion_point(field_get:NestedMessage.item2)
  return item2_.Get(index);
}
inline ::std::string* NestedMessage::mutable_item2(int index) {
  // @@protoc_insertion_point(field_mutable:NestedMessage.item2)
  return item2_.Mutable(index);
}
inline void NestedMessage::set_item2(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:NestedMessage.item2)
  item2_.Mutable(index)->assign(value);
}
inline void NestedMessage::set_item2(int index, const char* value) {
  item2_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:NestedMessage.item2)
}
inline void NestedMessage::set_item2(int index, const char* value, size_t size) {
  item2_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:NestedMessage.item2)
}
inline ::std::string* NestedMessage::add_item2() {
  return item2_.Add();
}
inline void NestedMessage::add_item2(const ::std::string& value) {
  item2_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:NestedMessage.item2)
}
inline void NestedMessage::add_item2(const char* value) {
  item2_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:NestedMessage.item2)
}
inline void NestedMessage::add_item2(const char* value, size_t size) {
  item2_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:NestedMessage.item2)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
NestedMessage::item2() const {
  // @@protoc_insertion_point(field_list:NestedMessage.item2)
  return item2_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
NestedMessage::mutable_item2() {
  // @@protoc_insertion_point(field_mutable_list:NestedMessage.item2)
  return &item2_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_2eproto__INCLUDED