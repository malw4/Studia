// #define SCALAR float
#define SCALAR double

// size of small matrix block (for L1, L2, L1+L2)
#define BLOCK_SIZE_S 108
// size of large matrix block - for final performance measurements
// #define BLOCK_SIZE_L (5*BLOCK_SIZE_S)
// (e.g. 540 size of all arrays ~6.7MB, to be used for two level blocking)

// for testing with single level blocking
#define BLOCK_SIZE_L (BLOCK_SIZE_S)

#define ALIGNMENT 64

