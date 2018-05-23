#include "stdint_suffix.h"

uint8_t operator ""_u8(unsigned long long v) {
    return static_cast<uint8_t>(v);
}

int8_t operator ""_i8(unsigned long long v) {
    return static_cast<int8_t>(v);
}

uint16_t operator ""_u16(unsigned long long v) {
    return static_cast<uint16_t>(v);
}

int16_t operator ""_i16(unsigned long long v) {
    return static_cast<int16_t>(v);
}

uint32_t operator ""_u32(unsigned long long v) {
    return static_cast<uint32_t>(v);
}

int32_t operator ""_i32(unsigned long long v) {
    return static_cast<int32_t>(v);
}

uint64_t operator ""_u64(unsigned long long v) {
    return static_cast<uint64_t>(v);
}

int64_t operator ""_i64(unsigned long long v) {
    return static_cast<int64_t>(v);
}
