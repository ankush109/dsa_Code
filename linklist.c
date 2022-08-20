#include <stdio.h>
#include <stdlib.h>
/* ==DEFINITION OF SELF-REFERENTIAL STRUCTURE ==*/
typedef struct s_linked_list
{
    int data;
    struct s_linked_list *nxt;
} S_LINKED_LIST;
void initialisation(S_LINKED_LIST **aa_head)
{
    *aa_head = NULL;
}
void insertion_sorted_order(S_LINKED_LIST **aa_head, int n)
{
    S_LINKED_LIST *t, *prv, *cur;
    t = (S_LINKED_LIST *)malloc(sizeof(S_LINKED_LIST));
    t->data = n;
    for (cur = *aa_head, prv = NULL; cur && n > cur->data; cur = cur->nxt)
        prv = cur;
    t->nxt = cur;
    if (prv != NULL)
        prv->nxt = t;
    else
        *aa_head = t;
    // The newly created node must be inserted at the beginning as head node./
}
void insertion_serial_order(S_LINKED_LIST **aa_head, int n)
{
    S_LINKED_LIST *t, *prv, *cur;
    t = (S_LINKED_LIST *)malloc(sizeof(S_LINKED_LIST));
    t->data = n;
    for (cur = *aa_head, prv = NULL; cur; cur = cur->nxt)
        prv = cur;
    t->nxt = cur;
    if (prv)
        prv->nxt = t;
    else
        *aa_head = t;
}
void recursive_insertion_serial_order(S_LINKED_LIST **aa_head, int n)
{
    if (*aa_head == NULL)
    {
        *aa_head = (S_LINKED_LIST *)malloc(sizeof(S_LINKED_LIST));
        (*aa_head)->data = n;
        (*aa_head)->nxt = NULL;
    }
    else
        recursive_insertion_serial_order(&(*aa_head)->nxt, n);
}
void recursive_insertion_sorted_order(S_LINKED_LIST **aa_head, int n)
{
    S_LINKED_LIST *t;
    t = (S_LINKED_LIST *)malloc(sizeof(S_LINKED_LIST));
    t->data = n;
    t->nxt = NULL;
    if (*aa_head == NULL)
        *aa_head = t;
    else if (n < (*aa_head)->data)
    {
        /* next part of the new node will point to the existing head nde.*/
        t->nxt = *aa_head;
        *aa_head = t; /* New node will become head node. */
    }
    else
        recursive_insertion_sorted_order(&(*aa_head)->nxt, n);
}
void reverse(S_LINKED_LIST **aa_head)
{
    S_LINKED_LIST *prv, *cur, *t;
    for (cur = *aa_head, prv = NULL; cur; cur = t)
    {
        t = cur->nxt; /*keep the address of the head node at the pointer t */
        cur->nxt = prv;
        prv = cur;
    }
    *aa_head = prv;
}
void recursive_reverse(S_LINKED_LIST *a_head)
{
    if (a_head->nxt)
        recursive_reverse(a_head->nxt);
    printf("\t % d", a_head->data);
}
int count(S_LINKED_LIST *a_head)
{
    int count = 0;
    for (; a_head; a_head = a_head->nxt)
        count++;
    return (count);
}
int recursive_count(S_LINKED_LIST *a_head)
{
    if (a_head == NULL)
        return 0;
    else
        return (recursive_count(a_head->nxt) + 1);
}
void display(S_LINKED_LIST *a_head)
{
    for (; a_head; a_head = a_head->nxt)
        printf("\t % d", a_head->data);
    printf("\n");
}
void recursive_display(S_LINKED_LIST *a_head)
{
    if (a_head)
    {
        printf("\t % d", a_head->data);
        recursive_display(a_head->nxt);
    }
    else
        printf("\t END. ");
    printf("\n");
}
void deletion(S_LINKED_LIST **aa_head, int n)
{
    S_LINKED_LIST *prv, *cur;
    int found = 0;
    for (cur = *aa_head, prv = NULL; cur; cur = cur->nxt)
    {
        if (prv != NULL && n == cur->data)
        {
            found = 1;
            prv->nxt = cur->nxt;
            free(cur);
            return;
        }
        else if (prv == NULL && n == cur->data)
        {
            found = 1;
            *aa_head = cur->nxt;
            free(cur);
            return;
        }
        else
            prv = cur;
    }
    if (!found)
        printf("\n Data not found\n");
}
void split_and_display(S_LINKED_LIST *a_head, S_LINKED_LIST **aa_head_odd, S_LINKED_LIST **aa_head_even)
{
    S_LINKED_LIST *cur;
    initialisation(aa_head_even);
    initialisation(aa_head_odd);
    for (cur = a_head; cur; cur = cur->nxt)
    {
        if (cur->data % 2 == 0)
            insertion_serial_order(aa_head_even, cur->data);
        else
            insertion_serial_order(aa_head_odd, cur->data);
    }
    display(*aa_head_even);
    display(*aa_head_odd);
}
void merge_and_display(S_LINKED_LIST *a_head1, S_LINKED_LIST *a_head2, S_LINKED_LIST **aa_head_m)
{
    S_LINKED_LIST *cur;
    initialisation(aa_head_m);
    for (cur = a_head1; cur; cur = cur->nxt)
        insertion_sorted_order(aa_head_m, cur->data);
    for (cur = a_head2; cur; cur = cur->nxt)
        insertion_sorted_order(aa_head_m, cur->data);
    display(*aa_head_m);
}
void alternative_merge_and_display(S_LINKED_LIST *a_head1, S_LINKED_LIST *a_head2, S_LINKED_LIST **aa_head_m)
{
    S_LINKED_LIST *cur1, *cur2;
    initialisation(aa_head_m);
    for (cur1 = a_head1, cur2 = a_head2; cur1 && cur2;)
    {
        if (cur1->data < cur2->data)
        {
            insertion_serial_order(aa_head_m, cur1->data);
            cur1 = cur1->nxt;
        }
        else
        {
            insertion_serial_order(aa_head_m, cur2->data);
            cur2 = cur2->nxt;
        }
    }
    for (; cur1; cur1 = cur1->nxt)
        insertion_serial_order(aa_head_m, cur1->data);
    for (; cur2; cur2 = cur2->nxt)
        insertion_serial_order(aa_head_m, cur2->data);
    display(*aa_head_m);
}
void search(S_LINKED_LIST *aa_head, int x)
{
    int flag = 0;
    S_LINKED_LIST *cur = aa_head;
    while (cur != NULL)
    {
        if (cur->data == x)
        {
            printf("Element %d is present in the linked list\n", x);
            flag = 1;
        }

        cur = cur->nxt;
    }
    if (flag == 0)
    {
        printf("Element %d is absent in the linked list\n", x);
    }
}
void main()
{
    S_LINKED_LIST *L = NULL;

    recursive_insertion_sorted_order(&L, 1);
    recursive_insertion_sorted_order(&L, 69);
    recursive_insertion_sorted_order(&L, 6);
    recursive_insertion_sorted_order(&L, 3);
    display(L);
}