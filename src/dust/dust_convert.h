#ifndef _DUST_CONVERT
#define _DUST_CONVERT

#include <stdint.h>

namespace dust
{

/**
 * Converts numbers to 64 bit wide unsigned integer whereby
 * any signedness is ignored. If absolute value of the number
 * is greater or equal than .5, then the result is rounded
 * up and down otherwise.
 */
uint64_t rounduint64(long double);

/**
 * Swaps byte order on little-endian systems and does nothing 
 * otherwise. swapByteOrder cycles on LE systems.
 */
void swapByteOrder16(uint16_t&);
void swapByteOrder32(uint32_t&);
void swapByteOrder64(uint64_t&);

/**
 * Pushes bytes to the end of a vector.
 */
#define PUSH_BACK_BYTES(vector, value)\
    vector.insert(vector.end(), reinterpret_cast<unsigned char *>(&(value)),\
    reinterpret_cast<unsigned char *>(&(value)) + sizeof((value)));

/**
 * Pushes bytes to the end of a vector based on a pointer.
 */
#define PUSH_BACK_BYTES_PTR(vector, ptr, size)\
    vector.insert(vector.end(), reinterpret_cast<unsigned char *>((ptr)),\
    reinterpret_cast<unsigned char *>((ptr)) + (size));
}

#endif // _DUST_CONVERT
