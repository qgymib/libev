#include "test.h"
#include "tools/memcheck.h"
#include "utils/config.h"
#include <stdlib.h>
#include <string.h>

static void _start_as_stdio_echo_server(void)
{
    int c;
    while ((c = fgetc(stdin)) != EOF)
    {
        fputc(c, stdout);
    }
    exit(EXIT_SUCCESS);
}

static void _before_all_test(int argc, char* argv[])
{
    test_config_setup(argc, argv);

    if (test_config.flag_as_stdio_echo_server)
    {
        _start_as_stdio_echo_server();
    }

    if (!test_config.flag_no_memcheck)
    {
        setup_memcheck();
    }
}

static void _after_all_test(void)
{
    fflush(NULL);

    if (!test_config.flag_no_memcheck)
    {
        dump_memcheck();
    }
}

static cutest_hook_t test_hook = {
    _before_all_test,   /* .before_all_test */
    _after_all_test,    /* .after_all_test */
    NULL,               /* .before_fixture_setup */
    NULL,               /* .after_fixture_setup */
    NULL,               /* .before_fixture_teardown */
    NULL,               /* .after_fixture_teardown */
    NULL,               /* .before_fixture_test */
    NULL,               /* .after_fixture_test */
    NULL,               /* .before_parameterized_test */
    NULL,               /* .after_parameterized_test */
    NULL,               /* .before_simple_test */
    NULL,               /* .after_simple_test */
};

int main(int argc, char* argv[])
{
    return cutest_run_tests(argc, argv, &test_hook);
}
