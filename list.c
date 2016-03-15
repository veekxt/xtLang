#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "list.h"
/**
可变数组，test_Taolist()是一个如何使用的例子
*/
Taolist * init_Taolist_fun(int len,int data_len)
{
    Taolist *s = (Taolist *)malloc(sizeof(Taolist));
    s->len=0;//当前使用的长度
    s->cur=0;//当前位置
    s->state=0;//状态，保留
    s->max_len=len;//最大长度
    s->data=(len<=0 ? NULL:malloc(data_len*len));
    return s;
}

Taolist * Taolist_clone_fun(const Taolist *src,int data_len)
{
    Taolist *s = (Taolist *)malloc(sizeof(Taolist));
    s->len=src->len;
    s->cur=src->cur;
    s->state=src->state;
    s->max_len=src->max_len;
    s->data=malloc(data_len*src->max_len);
    s->data=memcpy(s->data, src->data, src->max_len * data_len);
    return s;
}

void Taolist_kill(Taolist *l)
{
    free(l->data);
    free(l);
}

void test_Taolist()
{
    Taolist *intl = Taolist_init(int,10);
    Taolist_add(int,intl,1);
    Taolist_add(int,intl,2);
    Taolist_add(int,intl,3);
    Taolist_add(int,intl,4);
    Taolist_add(int,intl,5);

    Taolist_update(int,2,intl,99);

    Taolist_del(int,1,intl);
    Taolist_del(int,9,intl);//索引过大无效

    puts("clone:");
    Taolist *e = Taolist_clone(intl,int);

    Taolist_add(int,e,777);
    Taolist_swap(int,0,3,e);

    for(int i=0;i<e->len;i++){
        printf("%d\n",Taolist_get(int,i,e));
    }


    puts("not clone:");
    for(int i=0;i<intl->len;i++){

        printf("%d\n",Taolist_get(int,i,intl));
    }
}
