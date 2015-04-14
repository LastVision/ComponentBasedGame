//	Min/Max
#define MIN(a, b) ( ( (a) < (b) ) ? (a) : (b) ) 
#define MAX(a, b) ( ( (a) > (b) ) ? (a) : (b) ) 

//	SafeDelete
#define SAFE_DELETE(pointer) delete pointer; pointer = nullptr;

//	ForEach's
#define FOR_EACH(i, vector) for (i = 0; i < vector.size(); i++)
#define FOR_EACH2(vector) for (unsigned int __counter = 0; __counter < vector.size(); __counter++)

//	CyclicErase
#define CYCLIC_ERASE(i, vector) vector[i] = vector.back(); vector.pop_back();

//	Own Macros
#define RANDOM(maxNum) rand() % maxNum + 1
#define DIFF(a, b) (a) - (b)
#define POW(a) (a) * (a)
#define ABS(a) ( ( (a) < 0 ) ? (- (a)) : (a) )