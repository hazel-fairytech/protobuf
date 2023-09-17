// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google LLC nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef UPB_PROTOS_PROTOS_EXTENSION_LOCK_H_
#define UPB_PROTOS_PROTOS_EXTENSION_LOCK_H_

#include <atomic>

#include "upb/upb/mem/arena.h"

namespace protos::internal {

// TODO(b/295355754): Temporary locking api for cross-language
// concurrency issue around extension api that uses lazy promotion
// from unknown data to upb_MiniTableExtension. Will be replaced by
// a core runtime solution in the future.
//
// Any api(s) using unknown or extension data (GetOrPromoteExtension,
// Serialize and others) call lock/unlock to provide a way for
// mixed language implementations to avoid race conditions)
using UpbExtensionUnlocker = void (*)(const void*);
using UpbExtensionLocker = UpbExtensionUnlocker (*)(const void*);

// TODO(b/295355754): Expose as function instead of global.
extern std::atomic<UpbExtensionLocker> upb_extension_locker_global;

/**
 * MessageLock(arena) acquires lock on an arena when constructed and releases it
 * when destroyed.
 */
class MessageLock {
 public:
  explicit MessageLock(const upb_Arena* arena);
  MessageLock(const MessageLock&) = delete;
  void operator=(const MessageLock&) = delete;
  ~MessageLock();

 private:
  const upb_Arena* root_arena_;
  internal::UpbExtensionUnlocker unlocker_;
};

}  // namespace protos::internal

#endif  // UPB_PROTOS_PROTOS_EXTENSION_LOCK_H_
