// #define SCALAR float
#define SCALAR double

// size of small matrix block
#define BLOCK_SIZE_S 48
// size of large matrix block - for final performance measurements
//#define BLOCK_SIZE_L (2*BLOCK_SIZE_S)
// for testing with single level blocking
#define BLOCK_SIZE_L (BLOCK_SIZE_S)

#define ALIGNMENT 64

