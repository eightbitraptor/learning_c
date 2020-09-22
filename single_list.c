#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node * next;
    char data;
} node_t;

node_t *
unlinked_node(char data)
{
    node_t * n = malloc(sizeof(node_t));
    n->next = NULL;
    n->data = data;

    return n;
}

node_t *
get_last_node(node_t * head)
{
    while(head->next != NULL)
    {
        head = head->next;
    }
    return head;
}

node_t *
prepend(node_t * head, char data)
{
    node_t * new_head = unlinked_node(data);
    new_head->next = head;

    return new_head;
}

void
append(node_t * head, char data)
{
    node_t * last = get_last_node(head);
    node_t * new_last = unlinked_node(data);
    last->next = new_last;
}

void
insert_at(node_t * head, int pos, char c)
{
    node_t * new_node = unlinked_node(c);

    for(int i = 0; i < pos; i++)
    {
        head = head->next;

        if(i == (pos - 1))
        {
            node_t * t = head->next;
            head->next = new_node;
            new_node->next = t;
        }
    }
}

void
print_list(node_t * head)
{
    while(1) {
        printf("%c", head->data);
        if(head->next == NULL) break;
        head = head->next;
    }
    printf("\n");

}

int
main()
{
    node_t * list = unlinked_node('a');
    list = prepend(list, 'A');
    append(list, 'b');
    append(list, 'd');
    insert_at(list, 2, 'c');

    print_list(list);
}