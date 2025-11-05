/*
SHUNTUNG YARD ( infix -> RPN tokens )

Rules:
- Numbers go straight to output
- Operators: stack by presedence/ associatvity
- ( push to op stack, ) pop until (
- ( ) mismatch, parse error

Presedence:
 3: unary, ` ~ (right assoc)
 2: * / %      (left-assoc)
 1: + -        (left-assoc)

*/
#include "my_bc.h"

static int is_op_token(const t_token *t) {
    return t->type == TOK_OP;
}

int to_rpn(const t_vec *tokens, t_vec *out_rpn) {
    t_vec stack;
    vec_init(&stack, sizeof(t_token));

    for (size_t i = 0; i < tokens->size; i++) {
        t_token tk = *(t_token*)((char*)tokens->data + i * tokens->elem);

        if (tk.type == TOK_INT) {
            // output append
            if (vec_push(out_rpn, &tk) != 0) {
                err_set_parse();
                vec_free(&stack);
                return -1;
            }
        } else if (tk.type == TOK_OP) {
            // pop while top has higher prec, or same prec and current is left-assoc
            t_token *top;

            while ((top = vec_back(&stack)) && is_op_token(top) && 
                    ((tk.assoc == ASSOC_LEFT && top->prec >= tk.prec) ||
                    (tk.assoc == ASSOC_RIGHT && top->prec > tk.prec))) {
                        if (vec_push(out_rpn, top) != 0) {
                            err_set_parse();
                            vec_free(&stack);
                            return -1;
                        }
                        vec_pop(&stack);
            } 
            if (vec_push(&stack, &tk) != 0) {
                err_set_parse();
                vec_free(&stack);
                return -1;
            }
            
        } else if (tk.type == TOK_LPAREN) {
            if (vec_push(&stack, &tk) != 0) {
                err_set_parse();
                vec_free(&stack);
                return -1;
            }

        } else if (tk.type == TOK_RPAREN) {
            // pop until matching (
            t_token *top = vec_back(&stack);
            int matched = 0;
            while (top) {
                if (top->type == TOK_LPAREN) {
                    matched = 1; 
                    vec_pop(&stack);
                    break;
                }
                if (vec_push(out_rpn, top) != 0) {
                    err_set_parse();
                    vec_free(&stack);
                    return -1;
                }
                vec_pop(&stack);
                top = vec_back(&stack);
            }
            if (!matched) {
                err_set_parse();
                vec_free(&stack);
                return -1;
            }
        }
    }

    // pop remaning operators. any paren? -> mismatch
    while (stack.size) {
        t_token *top = vec_back(&stack);
        if (top->type == TOK_LPAREN || top->type == TOK_RPAREN) {
            err_set_parse();
            vec_free(&stack);
            return -1;
        }
        if (vec_push(out_rpn, top) != 0) {
            err_set_parse();
            vec_free(&stack);
            return -1;
        }
        vec_pop(&stack);
    }

    vec_free(&stack);
    return 0;    
}
