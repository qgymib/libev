#include <assert.h>

/**
 * @brief Set handle as inactive.
 * @param[in] handle    handler
 */
EV_LOCAL void ev__handle_deactive(ev_handle_t* handle)
{
    if (!(handle->data.flags & EV_HANDLE_ACTIVE))
    {
        return;
    }
    handle->data.flags &= ~EV_HANDLE_ACTIVE;

    ev_loop_t* loop = handle->loop;
    ev_list_erase(&loop->handles.active_list, &handle->handle_queue);
    ev_list_push_back(&loop->handles.idle_list, &handle->handle_queue);
}

/**
 * @brief Force set handle as active.
 * @param[in] handle    handler
 */
EV_LOCAL void ev__handle_active(ev_handle_t* handle)
{
    if (handle->data.flags & EV_HANDLE_ACTIVE)
    {
        return;
    }
    handle->data.flags |= EV_HANDLE_ACTIVE;

    ev_loop_t* loop = handle->loop;
    ev_list_erase(&loop->handles.idle_list, &handle->handle_queue);
    ev_list_push_back(&loop->handles.active_list, &handle->handle_queue);
}

static void _ev_to_close_handle(ev_handle_t* handle)
{
    /**
     * Deactive but not reset #ev_handle_t::data::active_events, for debug
     * purpose.
     * The #ev_handle_t::data::active_events should be zero by now.
     */
    ev__handle_deactive(handle);

    handle->data.flags |= EV_HANDLE_CLOSED;
    ev_list_erase(&handle->loop->handles.idle_list, &handle->handle_queue);

    handle->endgame.close_cb(handle);
}

EV_LOCAL void ev__handle_init(ev_loop_t* loop, ev_handle_t* handle, ev_role_t role)
{
    handle->loop = loop;
    ev_list_push_back(&loop->handles.idle_list, &handle->handle_queue);

    handle->data.role = role;
    handle->data.flags = 0;

    handle->backlog.status = EV_ENOENT;
    handle->backlog.cb = NULL;
    handle->backlog.node = (ev_list_node_t)EV_LIST_NODE_INIT;

    handle->endgame.close_cb = NULL;
    handle->endgame.node = (ev_list_node_t)EV_LIST_NODE_INIT;
}

EV_LOCAL void ev__handle_exit(ev_handle_t* handle, ev_handle_cb close_cb)
{
    assert(!ev__handle_is_closing(handle));

    handle->data.flags |= EV_HANDLE_CLOSING;
    handle->endgame.close_cb = close_cb;

    if (close_cb != NULL)
    {
        ev_list_push_back(&handle->loop->endgame_queue, &handle->endgame.node);
    }
    else
    {
        ev__handle_deactive(handle);
        handle->data.flags |= EV_HANDLE_CLOSED;
        ev_list_erase(&handle->loop->handles.idle_list, &handle->handle_queue);
    }
}

EV_LOCAL int ev__handle_is_active(ev_handle_t* handle)
{
    return handle->data.flags & EV_HANDLE_ACTIVE;
}

EV_LOCAL int ev__handle_is_closing(ev_handle_t* handle)
{
    return handle->data.flags & (EV_HANDLE_CLOSING | EV_HANDLE_CLOSED);
}

EV_LOCAL int ev__backlog_submit(ev_handle_t* handle, ev_handle_cb callback)
{
    if (handle->backlog.status != EV_ENOENT)
    {
        return EV_EEXIST;
    }

    handle->backlog.status = EV_EEXIST;
    handle->backlog.cb = callback;

    ev_list_push_back(&handle->loop->backlog_queue, &handle->backlog.node);

    return 0;
}

EV_LOCAL size_t ev__process_backlog(ev_loop_t* loop)
{
    ev_list_node_t* it;
    size_t active_count = 0;

    while ((it = ev_list_pop_front(&loop->backlog_queue)) != NULL)
    {
        ev_handle_t* handle = EV_CONTAINER_OF(it, ev_handle_t, backlog.node);

        handle->backlog.status = EV_ENOENT;

        handle->backlog.cb(handle);
        active_count++;
    }

    return active_count;
}

EV_LOCAL size_t ev__process_endgame(ev_loop_t* loop)
{
    ev_list_node_t* it;
    size_t active_count = 0;

    while ((it = ev_list_pop_front(&loop->endgame_queue)) != NULL)
    {
        ev_handle_t* handle = EV_CONTAINER_OF(it, ev_handle_t, endgame.node);
        _ev_to_close_handle(handle);
        active_count++;
    }

    return active_count;
}
