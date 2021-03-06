// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Player.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Player_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Player_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021001 < PROTOBUF_MIN_PROTOC_VERSION
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
#include "EquipItem.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Player_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Player_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Player_2eproto;
namespace Protocol {
class Player;
struct PlayerDefaultTypeInternal;
extern PlayerDefaultTypeInternal _Player_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::Player* Arena::CreateMaybeMessage<::Protocol::Player>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class Player final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Player) */ {
 public:
  inline Player() : Player(nullptr) {}
  ~Player() override;
  explicit PROTOBUF_CONSTEXPR Player(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Player(const Player& from);
  Player(Player&& from) noexcept
    : Player() {
    *this = ::std::move(from);
  }

  inline Player& operator=(const Player& from) {
    CopyFrom(from);
    return *this;
  }
  inline Player& operator=(Player&& from) noexcept {
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
  static const Player& default_instance() {
    return *internal_default_instance();
  }
  static inline const Player* internal_default_instance() {
    return reinterpret_cast<const Player*>(
               &_Player_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Player& a, Player& b) {
    a.Swap(&b);
  }
  inline void Swap(Player* other) {
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
  void UnsafeArenaSwap(Player* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Player* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Player>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Player& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Player& from) {
    Player::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Player* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Player";
  }
  protected:
  explicit Player(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEquipItemsFieldNumber = 3,
    kUsernameFieldNumber = 2,
    kAccountIdFieldNumber = 1,
  };
  // repeated .Protocol.EquipItem EquipItems = 3;
  int equipitems_size() const;
  private:
  int _internal_equipitems_size() const;
  public:
  void clear_equipitems();
  ::Protocol::EquipItem* mutable_equipitems(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::EquipItem >*
      mutable_equipitems();
  private:
  const ::Protocol::EquipItem& _internal_equipitems(int index) const;
  ::Protocol::EquipItem* _internal_add_equipitems();
  public:
  const ::Protocol::EquipItem& equipitems(int index) const;
  ::Protocol::EquipItem* add_equipitems();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::EquipItem >&
      equipitems() const;

  // string Username = 2;
  void clear_username();
  const std::string& username() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_username(ArgT0&& arg0, ArgT... args);
  std::string* mutable_username();
  PROTOBUF_NODISCARD std::string* release_username();
  void set_allocated_username(std::string* username);
  private:
  const std::string& _internal_username() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_username(const std::string& value);
  std::string* _internal_mutable_username();
  public:

  // uint64 AccountId = 1;
  void clear_accountid();
  uint64_t accountid() const;
  void set_accountid(uint64_t value);
  private:
  uint64_t _internal_accountid() const;
  void _internal_set_accountid(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Player)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::EquipItem > equipitems_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr username_;
    uint64_t accountid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Player_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Player

// uint64 AccountId = 1;
inline void Player::clear_accountid() {
  _impl_.accountid_ = uint64_t{0u};
}
inline uint64_t Player::_internal_accountid() const {
  return _impl_.accountid_;
}
inline uint64_t Player::accountid() const {
  // @@protoc_insertion_point(field_get:Protocol.Player.AccountId)
  return _internal_accountid();
}
inline void Player::_internal_set_accountid(uint64_t value) {
  
  _impl_.accountid_ = value;
}
inline void Player::set_accountid(uint64_t value) {
  _internal_set_accountid(value);
  // @@protoc_insertion_point(field_set:Protocol.Player.AccountId)
}

// string Username = 2;
inline void Player::clear_username() {
  _impl_.username_.ClearToEmpty();
}
inline const std::string& Player::username() const {
  // @@protoc_insertion_point(field_get:Protocol.Player.Username)
  return _internal_username();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Player::set_username(ArgT0&& arg0, ArgT... args) {
 
 _impl_.username_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Protocol.Player.Username)
}
inline std::string* Player::mutable_username() {
  std::string* _s = _internal_mutable_username();
  // @@protoc_insertion_point(field_mutable:Protocol.Player.Username)
  return _s;
}
inline const std::string& Player::_internal_username() const {
  return _impl_.username_.Get();
}
inline void Player::_internal_set_username(const std::string& value) {
  
  _impl_.username_.Set(value, GetArenaForAllocation());
}
inline std::string* Player::_internal_mutable_username() {
  
  return _impl_.username_.Mutable(GetArenaForAllocation());
}
inline std::string* Player::release_username() {
  // @@protoc_insertion_point(field_release:Protocol.Player.Username)
  return _impl_.username_.Release();
}
inline void Player::set_allocated_username(std::string* username) {
  if (username != nullptr) {
    
  } else {
    
  }
  _impl_.username_.SetAllocated(username, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.username_.IsDefault()) {
    _impl_.username_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Protocol.Player.Username)
}

// repeated .Protocol.EquipItem EquipItems = 3;
inline int Player::_internal_equipitems_size() const {
  return _impl_.equipitems_.size();
}
inline int Player::equipitems_size() const {
  return _internal_equipitems_size();
}
inline ::Protocol::EquipItem* Player::mutable_equipitems(int index) {
  // @@protoc_insertion_point(field_mutable:Protocol.Player.EquipItems)
  return _impl_.equipitems_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::EquipItem >*
Player::mutable_equipitems() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.Player.EquipItems)
  return &_impl_.equipitems_;
}
inline const ::Protocol::EquipItem& Player::_internal_equipitems(int index) const {
  return _impl_.equipitems_.Get(index);
}
inline const ::Protocol::EquipItem& Player::equipitems(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.Player.EquipItems)
  return _internal_equipitems(index);
}
inline ::Protocol::EquipItem* Player::_internal_add_equipitems() {
  return _impl_.equipitems_.Add();
}
inline ::Protocol::EquipItem* Player::add_equipitems() {
  ::Protocol::EquipItem* _add = _internal_add_equipitems();
  // @@protoc_insertion_point(field_add:Protocol.Player.EquipItems)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::EquipItem >&
Player::equipitems() const {
  // @@protoc_insertion_point(field_list:Protocol.Player.EquipItems)
  return _impl_.equipitems_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Player_2eproto
