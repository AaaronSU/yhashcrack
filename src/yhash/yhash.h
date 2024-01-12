//
#pragma once

//
#include "common.h"

//
extern void md5hash(const u8 *restrict msg, const u64 len, u8 *restrict hash);
extern void sha1hash(const u8 *restrict msg, const u64 len, u8 *restrict hash);
extern void sha224hash(const u8 *restrict msg, const u64 len, u8 *restrict hash);
extern void sha256hash(const u8 *restrict msg, const u64 len, u8 *restrict hash);
extern void sha512hash(const u8 *restrict msg, const u64 len, u8 *restrict hash);
