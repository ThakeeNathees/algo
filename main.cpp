

#define ALGO_DEBUG  1
#define TEST_COUNT 10
#define USE_UNICODE 0

#include "algo.h"
#include "src/z_function.h"

#define TEST_CLASS(m_func, ...)               \
class Class_##m_func##_Test : public Tester { \
public:                                       \
	virtual void run() override {             \
		m_func(__VA_ARGS__);                  \
	}                                         \
}

#if ALGO_DEBUG
#define RUN_TESTS(m_func, ...) m_func(__VA_ARGS__)
#else
#define RUN_TESTS(m_func, ...)                         \
	TEST_CLASS(m_func, __VA_ARGS__);                   \
	Class_##m_func##_Test().run_tests(#m_func, TEST_COUNT)
#endif


int main() {

#if USE_UNICODE
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
#endif

	RUN_TESTS(z_function, "aaabcxyzaaaabczaaczabbaaaaaabc");

	return 0;
}
