#include "rail.h"

rail_node_t *rails = NULL;

int add(int a, int b)
{
    return a+ b;
}

rail_node_t *CreateRails(int length, int node_num)
{
    /**
     * 表示轨道的头节点
     */
    rail_node_t *head = NULL;
    rail_node_t *node = NULL;

    head = (rail_node_t*) malloc(sizeof (rail_node_t));
    head->id = 1;
    head->last_node_distance = length;
    head->next_node_distance = length;

    node = head;
    // 循环创建每一个节点
    for(int i = 2; i <= node_num; i++)
    {
        rail_node_t *p = (rail_node_t*) malloc(sizeof (rail_node_t));

        p->id = i;
        p->last_node_distance = length;
        p->next_node_distance = length;
        p->last_node = node;
        node->next_node = p;
        node = p;
    }

    // 循环结束时node就是最后一个节点
    node->next_node = head;
    head->last_node = node;

    return head;
}

rail_node_t *FindNode(rail_node_t *rails, int id)
{
    rail_node_t *p = NULL;
    if(rails)
    {
        if(rails->id == id)
        {
            return rails;
        }
        if(rails->next_node != NULL)
        {
            p = FindNode(rails->next_node, id);
            if(p) 
            {
                return p;
            }
        }
        
    }
    return NULL;
}

