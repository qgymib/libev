#include <errno.h>

EV_LOCAL int ev__translate_sys_error(int syserr)
{
    return ev__translate_posix_sys_error(syserr);
}
