#ifndef EV_SEM_WIN_H
#define EV_SEM_WIN_H
#ifdef __cplusplus
extern "C" {
#endif

struct ev_sem_s
{
    ev_os_sem_t r;
};

#ifdef __cplusplus
}
#endif
#endif
