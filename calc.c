// This uses struct based stack implementation of Stack
// build str: gcc -Wall -Wextra -g -o s s2.c -lm
// TODO: divide by zero detection.
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include "queue.h"
#include "stack.h"
#include "strings.h"
#include "memory.h"

typedef enum {
    V_OP,
    V_VAL,
    V_PAR,
} VType;

// Struct of values
typedef struct _value_ {
    VType type;
    int val;
} Value;

// Struct of expression tree nodes.
typedef struct _node_ {
    Value* val;
    struct _node_* next;
    struct _node_* left;
    struct _node_* right;
} Node;

Node* tree = NULL;

Value* createValue(VType type, int value) {

    Value* val = malloc(sizeof(Value));
    val->type = type;
    val->val = value;

    return val;
}

void print_value(Value* val) {

    assert(val != NULL);

    switch(val->type) {
        case V_OP:
            if(val->val == '_')
                fputc('-', stdout);
            else if(val->val == '#')
                fputc('+', stdout);
            else
                fputc(val->val, stdout);
            break;
        case V_VAL: printf("%d", val->val); break;
        case V_PAR: printf("("); break;
        default: printf("BARF!\n"); break;
    }
}

Node* create_node(Value* val, Node* left, Node* right) {

    assert(val != NULL);

    Node* node = _alloc_obj(Node);
    node->val = val;
    node->next = NULL;
    node->left = left;
    node->right = right;

    return node;
}

void push_node(Node* node) {

    assert(node != NULL);

    node->next = tree;
    tree = node;
}

Node* pop_node() {

    Node* node = tree;
    tree = tree->next;

    return node;
}

void print_node(Node* n) {

    assert(n != NULL);

    fputc('(', stdout);
    print_value(n->val);
    fputc(')', stdout);
}

void postfix_traverse(Node* node) {

    if(node != NULL) {
        postfix_traverse(node->left);
        postfix_traverse(node->right);
        print_value(node->val);
    }
}

void prefix_traverse(Node* node) {

    if(node != NULL) {
        print_value(node->val);
        prefix_traverse(node->right);
        prefix_traverse(node->left);
    }
}

/*
 * This prints the original expression with a lot more parens.
 * Input: 6*(--5+3)*2
 * Output: ( (6) * ( ( (-(-(5)))+(3) ) * (2) ) )
 * Unpacked: (6*((--5+3)*2))
 */
bool is_left_assoc(Value*);
void infix_traverse(Node* node) {

    if(node != NULL) {
        if(node->val->type == V_OP && is_left_assoc(node->val)) {
            fputc('(', stdout);
            infix_traverse(node->left);
            print_value(node->val);
            infix_traverse(node->right);
            fputc(')', stdout);
        }
        else {
            infix_traverse(node->left);
            print_value(node->val);
            infix_traverse(node->right);
        }
    }
}

void printQueue(Queue q) {

    assert(q != NULL);

    if(q == NULL) {
        printf("NULL queue\n");
        return;
    }

    resetQueue(q);

    for(Value* val = iterateQueue(q); val != NULL; val = iterateQueue(q))
        print_value(val);

    fputc('\n', stdout);
}

void printStack(Stack s) {

    assert(s != NULL);

    resetQueue(s);

    fputc('.', stdout);
    for(Value* val = iterateQueue(s); val != NULL; val = iterateQueue(s)) {
        print_value(val);
        fputc('.', stdout);
    }

    fputc('\n', stdout);
}

// A utility function to check if the given character is operand
int checkIfOperand(char ch) {

    return isdigit(ch);
}

bool is_left_assoc(Value* v) {

    assert(v != NULL);

    switch(v->val) {
        case '(':
        case '^':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%': return true;

        case '#':
        case '_': return false;

        default:
            printf("invalid operator assoc '%c' (%d)\n", v->val, v->val);
            exit(1);

    }
}

// Function to compare precedence
// If we return larger value means higher precedence
int precedence(Value* v) {

    assert(v != NULL);

    switch(v->val) {
        case '(': return 0; // lowest precedence

        case '+':
        case '-': return 1;

        case '*':
        case '/':
        case '%': return 2;

        case '#':           // unary plus
        case '_': return 4; // unary minus

        case '^': return 3; // exponent

        default:
            printf("invalid operator precedence '%c' (%d)\n", v->val, v->val);
            exit(1);
    }

    return -1;
}

bool is_unary(Value* v) {

    assert(v != NULL);

    if(v->val == '#' || v->val == '_')
        return true;
    else
        return false;
}

/*
 * Convert a RPN expression in a queue to a Binary Expression Tree.
 *
 * The binary expression tree, when traversed in order gives the infix version
 * of the expression, and when traversed post order, it gives the prefix
 * version of the expression. Binary operators have 2 children and unary
 * operators have 1 child. Operands are always leafs on the tree and have no
 * children.
 *
 * Reading the queue one item at a time, when an operand is encountered, push
 * it on the stack of tree nodes. When a binary operator is encountered, then
 * create an operator node. Pop 2 operands from the stack and make the left and
 * right children of the new operator. Push it back on the stack. When a unary
 * operator is seen, then pop only one item, assign it and push the unary
 * operator. When the queue runs out of elements, then there should be exactly
 * one item on the expression tree stack. That item is the completed tree.
 *
 * See:
 * https://en.wikipedia.org/wiki/Binary_expression_tree
 *
 */
void postToTree(Queue* q) {

    assert(q != NULL);

    resetQueue(q);
    for(Value* val = iterateQueue(q); val != NULL; val = iterateQueue(q)) {
        if(val->type == V_VAL) {
            Node* node = create_node(val, NULL, NULL);
            push_node(node);
        }
        else {
            if(is_unary(val)) {
                Node* right = pop_node();
                Node* node = create_node(val, NULL, right);
                push_node(node);
            }
            else {
                Node* right = pop_node();
                Node* left = pop_node();
                Node* node = create_node(val, left, right);
                push_node(node);
            }
        }
    }
}

void tree_to_c_value(String s, Value* v) {

    assert(v != NULL);

    switch(v->type) {
        case V_OP:
            if(v->val == '_')
                appendStringChar(s, '-');
            else if(v->val == '#')
                appendStringChar(s, '+');
            else
                appendStringChar(s, v->val);
            break;
        case V_VAL: appendStringFormat(s, "%d", v->val); break;
        case V_PAR: appendStringChar(s, '('); break;
        default: printf("BARF!\n"); break;
    }
}

void tree_to_c_traverse(String s, Node* node) {

    if(node != NULL) {
        if(node->val->type == V_OP && is_left_assoc(node->val)) {
            appendStringChar(s, '(');
            tree_to_c_traverse(s, node->left);
            tree_to_c_value(s, node->val);
            tree_to_c_traverse(s, node->right);
            appendStringChar(s, ')');
        }
        else {
            tree_to_c_traverse(s, node->left);
            tree_to_c_value(s, node->val);
            tree_to_c_traverse(s, node->right);
        }
    }
}

/*
 * The only function is pow(), which replaces the '^' operator.
 */
void subs_functions(String s) {

    //int idx = findStringChar(s, 0, '^');
    //if(idx > 0) { // note that a '^' cannot be the first character.
    for(int idx = findStringChar(s, 0, '^'); idx > 0; idx = findStringChar(s, 0, '^')) {
        replaceStringChar(s, idx, ',');
        int tmp = findStringRevChar(s, idx, '(');
        insertStringFormat(s, tmp, "pow");
    }

    // else do nothing
}

/*
 * This is just like infix_traverse() but it writes a string instead of just
 * printing the expression to stdout.
 */
String treeToCExpr() {

    String s = createString(NULL);
    tree_to_c_traverse(s, tree);
    subs_functions(s);
    return s;
}

// Convert infix to postfix.
Queue* convItoP(Queue* inp) {

    assert(inp != NULL);

    Stack stk = createStack();
    Queue outp = createQueue();

    resetQueue(inp);
    for(Value* val = iterateQueue(inp); val != NULL; val = iterateQueue(inp)) {
        //printStack(stk);
        if(val->type == V_VAL)
            addQueue(outp, val);
        else if(val->val == '(')
            pushStack(stk, val);
        else if(val->val == ')') { // it must be a v_OP
            while(!stackIsEmpty(stk) && peekStack(stk)->val != '(')
                addQueue(outp, popStack(stk));
            if(!stackIsEmpty(stk) && peekStack(stk)->val != '(') {
                fprintf(stderr, "imbalanced parens\n");
                exit(1);
            }
            else
                popStack(stk);
        }
        else {
            while(!stackIsEmpty(stk) &&
                        ((precedence(val) < precedence(peekStack(stk)) ||
                        (precedence(val) == precedence(peekStack(stk)) &&
                            is_left_assoc(val))))) {
                addQueue(outp, popStack(stk));
            }

            pushStack(stk, val);
        }
    }

    for(Value* tmp = popStack(stk); tmp != NULL; tmp = popStack(stk))
        addQueue(outp, tmp);

    return outp;
}

void apply_op(Stack* s, Value* v) {

    assert(s != NULL);
    assert(v != NULL);

    switch(v->val) {
        case '+': {
                Value* right = popStack(s);
                Value* left = popStack(s);
                Value* r = createValue(V_VAL, (left->val + right->val));
                printf("value: %d = %d + %d\n", r->val, left->val, right->val);
                pushStack(s, r);
            }
            break;
        case '-': {
                Value* right = popStack(s);
                Value* left = popStack(s);
                Value* r = createValue(V_VAL, (left->val - right->val));
                printf("value: %d = %d - %d\n", r->val, left->val, right->val);
                pushStack(s, r);
            }
            break;
        case '*': {
                Value* right = popStack(s);
                Value* left = popStack(s);
                Value* r = createValue(V_VAL, (left->val * right->val));
                printf("value: %d = %d * %d\n", r->val, left->val, right->val);
                pushStack(s, r);
            }
            break;
        case '/': {
                Value* right = popStack(s);
                Value* left = popStack(s);
                Value* r = createValue(V_VAL, (left->val / right->val));
                printf("value: %d = %d / %d\n", r->val, left->val, right->val);
                pushStack(s, r);
            }
            break;
        case '%': {
                Value* right = popStack(s);
                Value* left = popStack(s);
                Value* r = createValue(V_VAL, (left->val % right->val));
                printf("value: %d = %d %% %d\n", r->val, left->val, right->val);
                pushStack(s, r);
            }
            break;
        case '^': {
                Value* right = popStack(s);
                Value* left = popStack(s);
                Value* r = createValue(V_VAL, (int)pow((double)left->val, (double)right->val));
                printf("value: %d = pow(%d, %d)\n", r->val, left->val, right->val);
                pushStack(s, r);
            }
            break;
        case '_': {
                Value* val = popStack(s);
                Value*r = createValue(V_VAL, (-val->val));
                printf("value: %d = - %d\n", r->val, val->val);
                pushStack(s, r);
            }
            break;
        case '#': {
                Value* val = popStack(s);
                Value* r = createValue(V_VAL, abs(val->val));
                printf("value: %d = abs(%d)\n", r->val, val->val);
                pushStack(s, r);
            }
            break;
        default:
            printf("BARF! '%c' (%d)", v->val, v->val);
            break;
    }
}

// solve a postfix expression and return the result.
int solve_postfix(Queue q) {

    assert(q != NULL);

    printf("postfix solve: "); printQueue(q);
    Stack s = createStack();

    resetQueue(q);
    for(Value* val = iterateQueue(q); val != NULL; val = iterateQueue(q)) {
        switch(val->type) {
            case V_OP:
                apply_op(s, val);
                break;
            case V_VAL:
                pushStack(s, val);
                break;
            default:
                printf("BARF!! '%c', (%d)\n", val->val, val->val);
                break;
        }
    }

    //printf("stack top: %d\n", lenList(s));
    if(lenList(s) != 1) {
        printf("invalid expression: "); printQueue(q);
        printStack(s);
        return 0;
    }

    return ((Value*)getList(s, 0))->val; //s->array[0]->val;
}

/*
 * Convert string to a queue, translate the unary operators, and count
 * the parens.
 */
Queue* parse(String expr) {

    assert(expr != NULL);

    Queue q = createQueue();
    int unary = 1;
    int parens = 0;

    resetString(expr);
    for(int ch = iterateString(expr); ch != 0; ch = iterateString(expr)) {
        if(checkIfOperand(ch)) {
            char s[2] = {ch, 0};
            addQueue(q, createValue(V_VAL, (int)strtol(s, NULL, 10)));
            unary = 0;
        }
        else if(ch == '(') {
            unary = 1;
            addQueue(q, createValue(V_PAR, ch));
            parens++;
        }
        else if(ch == ')') {
            unary = 0;
            addQueue(q, createValue(V_OP, ch));
            parens--;
        }
        else {
            if(unary) {
                if(ch == '-')
                    addQueue(q, createValue(V_OP, '_'));
                else if(ch == '+')
                    addQueue(q, createValue(V_OP, '#'));
                else
                    addQueue(q, createValue(V_OP, ch));
            }
            else
                addQueue(q, createValue(V_OP, ch));
            unary = 1;
        }
    }

    if(parens > 0) {
        printf("unbalanced parens '('\n");
        return NULL;
    }
    else if(parens < 0) {
        printf("unbalanced parens ')'\n");
        return NULL;
    }

    return q;
}

int main() {

    //char expression[] = "-((3+(7*8))-5)^2";
    //char* expr = "-(2*(3+2))^2";
    //char* expr = "6*(--5^4+3)^2";
    //String expr = createString("6*(--5^4+3)^2");
    String expr = createString("6*(--5^2+3)/2");

    printf("raw expr: %s\n", rawString(expr));

    Queue inp = parse(expr);
    printf("parsed expr: ");
    printQueue(inp);

    Queue q = convItoP(inp); //covertInfixToPostfix(expr);
    printf("solution: %d\n", solve_postfix(q));

    postToTree(q);
    printf("postfix: "); postfix_traverse(tree); fputc('\n', stdout);
    printf("prefix:  "); prefix_traverse(tree); fputc('\n', stdout);
    printf("infix:   "); infix_traverse(tree); fputc('\n', stdout);
    //String s = convPtoI(q);
    //printf("p to i expr: %s\n", rawString(s));
    printf("c string:%s\n", rawString(treeToCExpr()));

    return 0;
}
