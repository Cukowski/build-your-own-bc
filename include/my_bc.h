#ifndef MY_BC_H
#define MY_BC_H

#include <stddef.h>
#include <stdint.h> 

// for tokens and vectors public types

// malloc, free ... 

// error handling
void err_set_parse(void);

void err_print_and_clear(void);

// tiny dynamic array
typedef struct s_vec {
    void *data;  // raw bytes
    size_t size; // element count
    size_t cap;  // allocated capacity in elements
    size_t elem; // size of elements: sizeof(element)
} t_vec;

int  vec_init(t_vec *v, size_t elem_size);
void vec_free(t_vec *v);
int  vec_push(t_vec *v, const void *elem);


// tokens
typedef enum e_toktype {
    TOK_INT,    // int literal
    TOK_OP,     // + - * / % ~ (unary minus) ` (unary plus)
    TOK_LPAREN, // (
    TOK_RPAREN  // )
} t_toktype;

typedef enum e_assoc {
    ASSOC_LEFT,
    ASSOC_RIGHT
} t_assoc;

typedef struct s_token {
    t_toktype type;
    long long ival;     // volid when type == TOK_INT
    char op;            // operator char
    int prec;           // precedence 
    t_assoc assoc; 
} t_token;


// Return 0 on succ, non-zero: error (set parse error)
int lex(const char *s, t_vec *out_tokens);


#endif /* MY_BC_H */
