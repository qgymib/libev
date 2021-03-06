#include <string.h>
#include "ev/list.h"

static void _list_lite_set_once(ev_list_t* handler, ev_list_node_t* node)
{
	handler->head = node;
	handler->tail = node;
	node->p_after = NULL;
	node->p_before = NULL;
	handler->size = 1;
}

void ev_list_init(ev_list_t* handler)
{
	memset(handler, 0, sizeof(*handler));
}

void ev_list_push_back(ev_list_t* handler, ev_list_node_t* node)
{
	if (handler->head == NULL)
	{
		_list_lite_set_once(handler, node);
		return;
	}

	node->p_after = NULL;
	node->p_before = handler->tail;
	handler->tail->p_after = node;
	handler->tail = node;
	handler->size++;
}

void ev_list_insert_before(ev_list_t* handler, ev_list_node_t* pos, ev_list_node_t* node)
{
	if (handler->head == pos)
	{
		ev_list_push_front(handler, node);
		return;
	}

	node->p_before = pos->p_before;
	node->p_after = pos;
	pos->p_before->p_after = node;
	pos->p_before = node;
	handler->size++;
}

void ev_list_insert_after(ev_list_t* handler,  ev_list_node_t* pos, ev_list_node_t* node)
{
	if (handler->tail == pos)
	{
		ev_list_push_back(handler, node);
		return;
	}

	node->p_before = pos;
	node->p_after = pos->p_after;
	pos->p_after->p_before = node;
	pos->p_after = node;
	handler->size++;
}

void ev_list_push_front(ev_list_t* handler, ev_list_node_t* node)
{
	if (handler->head == NULL)
	{
		_list_lite_set_once(handler, node);
		return;
	}

	node->p_before = NULL;
	node->p_after = handler->head;
	handler->head->p_before = node;
	handler->head = node;
	handler->size++;
}

ev_list_node_t* ev_list_begin(const ev_list_t* handler)
{
	return handler->head;
}

ev_list_node_t* ev_list_end(const ev_list_t* handler)
{
	return handler->tail;
}

ev_list_node_t* ev_list_next(const ev_list_node_t* node)
{
	return node->p_after;
}

ev_list_node_t* ev_list_prev(const ev_list_node_t* node)
{
	return node->p_before;
}

void ev_list_erase(ev_list_t* handler, ev_list_node_t* node)
{
	handler->size--;

	/* Ψһ�ڵ� */
	if (handler->head == node && handler->tail == node)
	{
		handler->head = NULL;
		handler->tail = NULL;
		return;
	}

	if (handler->head == node)
	{
		node->p_after->p_before = NULL;
		handler->head = node->p_after;
		return;
	}

	if (handler->tail == node)
	{
		node->p_before->p_after = NULL;
		handler->tail = node->p_before;
		return;
	}

	node->p_before->p_after = node->p_after;
	node->p_after->p_before = node->p_before;
	return;
}

ev_list_node_t* ev_list_pop_front(ev_list_t* handler)
{
	ev_list_node_t* node = handler->head;
	if (node == NULL)
	{
		return NULL;
	}

	ev_list_erase(handler, node);
	return node;
}

ev_list_node_t* ev_list_pop_back(ev_list_t* handler)
{
	ev_list_node_t* node = handler->tail;
	if (node == NULL)
	{
		return NULL;
	}

	ev_list_erase(handler, node);
	return node;
}

size_t ev_list_size(const ev_list_t* handler)
{
	return handler->size;
}
