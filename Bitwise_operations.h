#define SET(bit, nbit) ((*bit) |= (1 << (nbit)))
#define RESET(bit, nbit) ((*bit) &= ~(1 << (nbit)))
#define TOGGLE(bit, nbit) ((*bit) ^= (1 << (nbit)))
#define GET_BIT(bit, nbit) ((*bit >> (nbit)) & 1)
