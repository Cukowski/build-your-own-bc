#include "my_bc.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        err_set_parse();
        err_print_and_clear();
        return 1;
    }
    (void)argv;

    // vector tokens, vector rpn
    t_vec tokens, rpn;
    vec_init(&tokens, sizeof(t_token));
    vec_init(&rpn, sizeof(t_token));

    // lexer
    lex(argv[1], &tokens);

    // shunting yard -> rpn 

    // evaluate rpn

    // success

    return 0;
}
