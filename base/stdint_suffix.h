#ifndef CHEMTOOLS_STDINT_SUFFIX_H
#define CHEMTOOLS_STDINT_SUFFIX_H


#include <cstdint>

uint8_t operator""_u8(unsigned long long v);
int8_t operator""_i8(unsigned long long v);
uint16_t operator""_u16(unsigned long long v);
int16_t operator""_i16(unsigned long long v);
uint32_t operator""_u32(unsigned long long v);
int32_t operator""_i32(unsigned long long v);
uint64_t operator""_u64(unsigned long long v);
int64_t operator""_i64(unsigned long long v);

#endif //CHEMTOOLS_STDINT_SUFFIX_H
