#include "ev.h"
#include "test.h"

TEST_FIXTURE_SETUP(version)
{
}

TEST_FIXTURE_TEARDOWN(version)
{
}

TEST_F(version, str)
{
    char buffer[64];
#if EV_VERSION_PREREL
    snprintf(buffer, sizeof(buffer), "%d.%d.%d-dev%d", EV_VERSION_MAJOR, EV_VERSION_MINOR, EV_VERSION_PATCH, EV_VERSION_PREREL);
#else
    snprintf(buffer, sizeof(buffer), "%d.%d.%d", EV_VERSION_MAJOR, EV_VERSION_MINOR, EV_VERSION_PATCH);
#endif

    ASSERT_EQ_STR(buffer, ev_version_str());
}

TEST_F(version, code)
{
    ASSERT_EQ_UINT(EV_VERSION_CODE, ev_version_code());
}

TEST_F(version, compare)
{
    /* patch version compare */
    ASSERT_GT_UINT(EV_VERSION(0, 0, 2), EV_VERSION(0, 0, 1));

    /* major version is larger than minor version */
    ASSERT_GT_UINT(EV_VERSION(2, 0, 0), EV_VERSION(1, 2, 0));

    /* version macro should support compare in pre-process stage */
#if EV_VERSION(0, 1, 2) > EV_VERSION(0, 1, 1)
    /* do nothing */
#else
    test_abort("");
#endif
}
