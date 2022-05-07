#ifndef __TEST_CONFIG_H__
#define __TEST_CONFIG_H__
#ifdef __cplusplus
extern "C" {
#endif

typedef struct test_config_s
{
    /**
     * @brief Command line argument number.
     */
    int     argc;

    /**
     * @brief Command line argument list.
     */
    char**  argv;

    /**
     * @brief Disable builtin memory leak check.
     */
    int     flag_no_memcheck;

    /**
     * @brief Start as stdio echo server and do not run tests.
     */
    int     flag_as_stdio_echo_server;
} test_config_t;

extern test_config_t test_config;

/**
 * @brief Setup test configuration from command line.
 * @param[in] argc  Command line argument number.
 * @param[in] argv  Command line argument list.
 */
void test_config_setup(int argc, char* argv[]);

/**
 * @brief Cleanup test configuration.
 */
void test_config_cleanup(void);

#ifdef __cplusplus
}
#endif
#endif