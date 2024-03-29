// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rescode.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_rescode_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_rescode_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_rescode_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_rescode_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_rescode_2eproto;
namespace ocean_mprpc {
class ResultCode;
struct ResultCodeDefaultTypeInternal;
extern ResultCodeDefaultTypeInternal _ResultCode_default_instance_;
}  // namespace ocean_mprpc
PROTOBUF_NAMESPACE_OPEN
template<> ::ocean_mprpc::ResultCode* Arena::CreateMaybeMessage<::ocean_mprpc::ResultCode>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace ocean_mprpc {

// ===================================================================

class ResultCode final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ocean_mprpc.ResultCode) */ {
 public:
  inline ResultCode() : ResultCode(nullptr) {}
  ~ResultCode() override;
  explicit PROTOBUF_CONSTEXPR ResultCode(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ResultCode(const ResultCode& from);
  ResultCode(ResultCode&& from) noexcept
    : ResultCode() {
    *this = ::std::move(from);
  }

  inline ResultCode& operator=(const ResultCode& from) {
    CopyFrom(from);
    return *this;
  }
  inline ResultCode& operator=(ResultCode&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ResultCode& default_instance() {
    return *internal_default_instance();
  }
  static inline const ResultCode* internal_default_instance() {
    return reinterpret_cast<const ResultCode*>(
               &_ResultCode_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ResultCode& a, ResultCode& b) {
    a.Swap(&b);
  }
  inline void Swap(ResultCode* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ResultCode* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ResultCode* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ResultCode>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ResultCode& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const ResultCode& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ResultCode* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ocean_mprpc.ResultCode";
  }
  protected:
  explicit ResultCode(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kErrmsgFieldNumber = 2,
    kErrcodeFieldNumber = 1,
  };
  // bytes errmsg = 2;
  void clear_errmsg();
  const std::string& errmsg() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_errmsg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_errmsg();
  PROTOBUF_NODISCARD std::string* release_errmsg();
  void set_allocated_errmsg(std::string* errmsg);
  private:
  const std::string& _internal_errmsg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_errmsg(const std::string& value);
  std::string* _internal_mutable_errmsg();
  public:

  // int32 errcode = 1;
  void clear_errcode();
  int32_t errcode() const;
  void set_errcode(int32_t value);
  private:
  int32_t _internal_errcode() const;
  void _internal_set_errcode(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:ocean_mprpc.ResultCode)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr errmsg_;
  int32_t errcode_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_rescode_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ResultCode

// int32 errcode = 1;
inline void ResultCode::clear_errcode() {
  errcode_ = 0;
}
inline int32_t ResultCode::_internal_errcode() const {
  return errcode_;
}
inline int32_t ResultCode::errcode() const {
  // @@protoc_insertion_point(field_get:ocean_mprpc.ResultCode.errcode)
  return _internal_errcode();
}
inline void ResultCode::_internal_set_errcode(int32_t value) {
  
  errcode_ = value;
}
inline void ResultCode::set_errcode(int32_t value) {
  _internal_set_errcode(value);
  // @@protoc_insertion_point(field_set:ocean_mprpc.ResultCode.errcode)
}

// bytes errmsg = 2;
inline void ResultCode::clear_errmsg() {
  errmsg_.ClearToEmpty();
}
inline const std::string& ResultCode::errmsg() const {
  // @@protoc_insertion_point(field_get:ocean_mprpc.ResultCode.errmsg)
  return _internal_errmsg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void ResultCode::set_errmsg(ArgT0&& arg0, ArgT... args) {
 
 errmsg_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:ocean_mprpc.ResultCode.errmsg)
}
inline std::string* ResultCode::mutable_errmsg() {
  std::string* _s = _internal_mutable_errmsg();
  // @@protoc_insertion_point(field_mutable:ocean_mprpc.ResultCode.errmsg)
  return _s;
}
inline const std::string& ResultCode::_internal_errmsg() const {
  return errmsg_.Get();
}
inline void ResultCode::_internal_set_errmsg(const std::string& value) {
  
  errmsg_.Set(value, GetArenaForAllocation());
}
inline std::string* ResultCode::_internal_mutable_errmsg() {
  
  return errmsg_.Mutable(GetArenaForAllocation());
}
inline std::string* ResultCode::release_errmsg() {
  // @@protoc_insertion_point(field_release:ocean_mprpc.ResultCode.errmsg)
  return errmsg_.Release();
}
inline void ResultCode::set_allocated_errmsg(std::string* errmsg) {
  if (errmsg != nullptr) {
    
  } else {
    
  }
  errmsg_.SetAllocated(errmsg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (errmsg_.IsDefault()) {
    errmsg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ocean_mprpc.ResultCode.errmsg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace ocean_mprpc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_rescode_2eproto
