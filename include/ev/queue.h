#ifndef __EV_QUEUE_H__
#define __EV_QUEUE_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_UTILS_QUEUE Queue
 * @ingroup EV_UTILS
 * @{
 */

/**
 * @brief Static initializer for #ev_queue_node_t.
 * @note A static initialized queue node is not a valid node.
 */

/**
 * @brief Queue node type.
 */
typedef struct ev_queue_node
{
    struct ev_queue_node* p_prev;
    struct ev_queue_node* p_next;
} ev_queue_node_t;
#define EV_QUEUE_NODE_INVALID  \
    {\
        NULL,\
        NULL,\
    }

/**
 * @brief Initialize circular linked list
 * @param[out] head     List handle
 */
EV_API void ev_queue_init(ev_queue_node_t* head);

/**
 * @brief Insert a node to the tail of the list.
 * @warning the node must not exist in any list.
 * @param[in,out] head  Pointer to list
 * @param[in,out] node  Pointer to a new node
 */
EV_API void ev_queue_push_back(ev_queue_node_t* head, ev_queue_node_t* node);

/**
 * @brief Insert a node to the head of the list.
 * @warning the node must not exist in any list.
 * @param[in,out] head      Pointer to list
 * @param[in,out] node      Pointer to a new node
 */
EV_API void ev_queue_push_front(ev_queue_node_t* head, ev_queue_node_t* node);

/**
 * @brief Delete a exist node
 * @param[in,out] node      The node you want to delete
 */
EV_API void ev_queue_erase(ev_queue_node_t* node);

/**
 * @brief Check whether list is empty
 * @param[in] node          Any node in list
 * @return                  bool
 */
EV_API int ev_queue_empty(const ev_queue_node_t* node);

/**
 * @brief Get the first node and remove it from the list.
 * @param[in,out] head      Pointer to list
 * @return                  The first node
 */
EV_API ev_queue_node_t* ev_queue_pop_front(ev_queue_node_t* head);

/**
 * @brief Get the last node and remove it from the list.
 * @param[in,out] head      Pointer to list
 * @return                  The last node
 */
EV_API ev_queue_node_t* ev_queue_pop_back(ev_queue_node_t* head);

/**
 * @brief Get the first node.
 * @param[in] head      Pointer to list
 * @return              The first node
 */
EV_API ev_queue_node_t* ev_queue_head(ev_queue_node_t* head);

/**
* @brief Get next node.
* @param[in] head   Queue head
* @param[in] node   Current node
* @return           The next node
*/
EV_API ev_queue_node_t* ev_queue_next(ev_queue_node_t* head, ev_queue_node_t* node);

/**
 * @} EV_UTILS_QUEUE
 */

#ifdef __cplusplus
}
#endif
#endif
