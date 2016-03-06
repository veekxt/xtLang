#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser/tokenizer.h"
#include "parser/parser.h"
#include "explain/explain.h"

int main(void)
{
    struct token_list *tl=init_token_list();
    file_to_token_to_array("test/exp.xt",tl);
    /*
    puts("Token Stream:");
    for(int i=0; i<tl->t->len; i++)
    {
        print_token(XTlist_get(tl->t,i,struct token));
    }
    */
    struct XTtree *s=do_stmt(tl);
    puts("Tree:");
    print_XTtree_V(s,0);
    tl->n=0;
    printf("\n");
    puts("explain: ");
    struct XTlist *symbol_table=init_XTlist(0,sizeof(struct XTlist *));//符号表栈
    explain(s,symbol_table);
    print_symbol_table(symbol_table);//输出符号表
    return 0;
}
