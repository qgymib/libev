#ifndef __EV_ASSERT_INTERNAL_H__
#define __EV_ASSERT_INTERNAL_H__
#ifdef __cplusplus
extern "C" {
#endif

#define EV_ASSERT(x, ...)	EV_JOIN(EV_ASSERT_, EV_BARG(__VA_ARGS__))(x, ##__VA_ARGS__)

#define EV_ASSERT_0(x, ...)	\
	do {\
		int _assert_ret = (x);\
		if (_assert_ret) {\
			break;\
		}\
		ev__assertion_failure(#x, __FILE__, __LINE__, NULL);\
	} while (0)

#define EV_ASSERT_1(x, fmt, ...)	\
	do {\
		int _assert_ret = (x);\
		if (_assert_ret) {\
			break;\
		}\
		ev__assertion_failure(#x, __FILE__, __LINE__, fmt, ##__VA_ARGS__);\
	} while (0)

EV_LOCAL void ev__assertion_failure(const char* exp, const char* file, int line, const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
