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

#ifndef UPB_MESSAGE_ACCESSORS_SPLIT64_H_
#define UPB_MESSAGE_ACCESSORS_SPLIT64_H_

#include "upb/upb/message/accessors.h"

// Must be last.
#include "upb/upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// JavaScript doesn't directly support 64-bit ints so we must split them.

UPB_API_INLINE uint32_t upb_Message_GetInt64Hi(const upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t default_value) {
  return (uint32_t)(upb_Message_GetInt64(msg, field, default_value) >> 32);
}

UPB_API_INLINE uint32_t upb_Message_GetInt64Lo(const upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t default_value) {
  return (uint32_t)upb_Message_GetInt64(msg, field, default_value);
}

UPB_API_INLINE bool upb_Message_SetInt64Split(upb_Message* msg,
                                              const upb_MiniTableField* field,
                                              uint32_t hi, uint32_t lo,
                                              upb_Arena* arena) {
  return upb_Message_SetInt64(msg, field, ((int64_t)hi << 32) | lo, arena);
}

UPB_API_INLINE uint32_t upb_Message_GetUInt64Hi(const upb_Message* msg,
                                                const upb_MiniTableField* field,
                                                uint32_t default_value) {
  return (uint32_t)(upb_Message_GetUInt64(msg, field, default_value) >> 32);
}

UPB_API_INLINE uint32_t upb_Message_GetUInt64Lo(const upb_Message* msg,
                                                const upb_MiniTableField* field,
                                                uint32_t default_value) {
  return (uint32_t)upb_Message_GetUInt64(msg, field, default_value);
}

UPB_API_INLINE bool upb_Message_SetUInt64Split(upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t hi, uint32_t lo,
                                               upb_Arena* arena) {
  return upb_Message_SetUInt64(msg, field, ((uint64_t)hi << 32) | lo, arena);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#include "upb/upb/port/undef.inc"

#endif  // UPB_MESSAGE_ACCESSORS_SPLIT64_H_
