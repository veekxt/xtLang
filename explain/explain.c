#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/parser.h"
#include "../datastr/list.h"
#include "explain.h"

/*
int print_symbol_table(struct XTlist *symbol_table)
{
    for(int i=0;i<symbol_table->len;i++)
    {
        struct XTlist * list_var=XTlist_get(symbol_table,i,struct XTlist *);
        for(int j=0;j<list_var->len;j++)
        {
            printf("level %d, %d rd variable,%s == %d\n",i,j,XTlist_get(list_var,j,struct xt_symbol *)->name,XTlist_get(list_var,j,struct xt_symbol *)->value.u.int_value);
        }
    }
    return 0;
}

*/

struct xt_value cal_exp(struct XTtree *exp)
{
    struct xt_value tmp;
    tmp.type=XT_V_INT;
    tmp.u.int_value=0;
    switch(exp->tree_type)
    {
        case OP_ADD:
            {
                struct XTtree *exp_l = XTlist_get(exp->child,0,struct XTtree *);
                struct XTtree *exp_r = XTlist_get(exp->child,1,struct XTtree *);
                struct xt_value tmp_l=cal_exp(exp_l);
                struct xt_value tmp_r=cal_exp(exp_r);
                tmp.u.int_value=tmp_l.u.int_value + tmp_r.u.int_value;
                tmp.type=XT_V_INT;
            }
        break;
        case OP_DIVIDE:
            {
                struct XTtree *exp_l = XTlist_get(exp->child,0,struct XTtree *);
                struct XTtree *exp_r = XTlist_get(exp->child,1,struct XTtree *);
                struct xt_value tmp_l=cal_exp(exp_l);
                struct xt_value tmp_r=cal_exp(exp_r);
                tmp.u.int_value=tmp_l.u.int_value / tmp_r.u.int_value;
                tmp.type=XT_V_INT;
            }
        break;
        case OP_MULTIPLY:
            {
                struct XTtree *exp_l = XTlist_get(exp->child,0,struct XTtree *);
                struct XTtree *exp_r = XTlist_get(exp->child,1,struct XTtree *);
                struct xt_value tmp_l=cal_exp(exp_l);
                struct xt_value tmp_r=cal_exp(exp_r);
                tmp.u.int_value=tmp_l.u.int_value * tmp_r.u.int_value;
                tmp.type=XT_V_INT;
            }
        break;
        case OP_REDUCE:
            {
                struct XTtree *exp_l = XTlist_get(exp->child,0,struct XTtree *);
                struct XTtree *exp_r = XTlist_get(exp->child,1,struct XTtree *);
                struct xt_value tmp_l=cal_exp(exp_l);
                struct xt_value tmp_r=cal_exp(exp_r);
                tmp.u.int_value=tmp_l.u.int_value - tmp_r.u.int_value;
                tmp.type=XT_V_INT;
            }
        break;
        case NUMBER:
            {
                tmp.u.int_value=atoi(exp->content);
                tmp.type=XT_V_INT;
            }
        break;
        case IDEN:
            {

            }
            break;
        default:;
    }
    return tmp;
};

int explain(struct XTtree *root,struct XTlist *symbol_table)
{
    struct XTlist *list_var=init_XTlist(0,sizeof(struct xt_symbol *));//当前符号表
    XTlist_add(symbol_table,struct XTlist *,list_var);                  //当前符号表放在栈的最顶层
    //symbol_table->current+=1;                                       // 栈指针+1

    for(int i=0;i<root->child->len;i++)
    {
        struct XTtree *tmp = XTlist_get(root->child,i,struct XTtree *);
        switch(tmp->tree_type)
        {
        case ASSIGN_STMT:
            {
                struct xt_symbol *var = (struct xt_symbol *)malloc(sizeof(struct xt_symbol));
                var->name=(XTlist_get(tmp->child,0,struct XTtree *))->content;
                var->value=cal_exp(XTlist_get(tmp->child,1,struct XTtree *));
                XTlist_add(list_var,struct xt_symbol *,var);
            }
            break;
        case STMT:
            {
                explain(tmp,symbol_table);
            }
            break;
        case NUM_EXP:
        case OP_ADD:
        case OP_DIVIDE:
        case OP_MULTIPLY:
        case OP_REDUCE:
            {
                struct xt_value target = cal_exp(tmp);
                printf("target is %d\n",target.u.int_value);
            }
            break;
        default:;
        }
    }
    XTlist_pop(symbol_table,struct XTlist *);
    return 0;
}
