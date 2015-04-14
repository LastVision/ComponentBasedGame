#include "DL_Debug.h"

int main(void)
{
	DL_Debug::Debug::Create();

	DL_PRINT("TEST");

	int x = 10;
	int y = 5;

	DL_DEBUG("X: %i Y: %i", y, x);

	float fX = 50.342f;
	double dY = 21.43920;

	DL_DEBUG("fX: %f dY: %d", fX, dY);

	DL_ASSERT_EX(true, "This assert did not fail");

	DL_ASSERT_EX(false, "This assert did fail");

	DL_Debug::Debug::Destroy();

	return 0;
}