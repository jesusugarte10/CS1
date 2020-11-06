// Jesus Ugarte
// Written in COP 3502 to illustrate an array implementation of a stack.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> //Has is digits
#include <math.h>

#define SIZE 100
#define EMPTY -1

struct stack {
    int items[SIZE];
    int top;
};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, int value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
int top(struct stack* stackPtr);
void display(struct stack* stackPtr);

int checkBalance(char*);

char *infixToPostfix(char*);
int evaluate(char*);
int isOperator(char);
int isParentheses(char);
int priority(char);

int main() 
{
    char exp[SIZE];
    int valid;
    printf("\n Enter Expression: ");
    scanf("%[^\n]s", exp);
    printf("Your input expression is: %s", exp);
    valid = checkBalance(exp);
    if (valid)
    {
        char *postfix = infixToPostfix(exp);
        printf("The postfix is %s\n", postfix);
        int answer = evaluate(postfix);
        printf("Evaluation: %d", answer);
        free(postfix);
    }
    return 0;
}

int evaluate(char *postfix)
{
    struct stack numbers;
    int answer;

    for(int i = 0 ; i < strlen(postfix); i++)
    {
        if(isdigit(postfix[i]))
        {
            printf("Made it");
            push(&numbers, atoi(&postfix[i]));
        }
        if(isOperator(postfix[i]))
        {
            int A = pop(&numbers);
            int B = pop(&numbers);

            if (postfix[i] == '+')
            {
                answer = A+B;
                push(&numbers, answer);
            }
        }
    }    
    answer = pop(&numbers);
    return answer;
}

char *infixToPostfix(char* infix)
{
    struct stack operators;
    initialize(&operators);

    int count = 0; //Keep track of th epostfix index
    //allocate memory for postfix
    char *postfix = (char*)malloc((strlen(infix)+1) * 2 * sizeof(char)); //it can handle spaces

    for(int i = 0; i< strlen(infix); i++)
    {
        //if the char is a digit, put it in postfix
        if(isdigit(infix[i]))
        {   
            while (isdigit(infix[i])) //Handle multiple digits
            {
                postfix[count] = infix[i]; //456+3
                i++;
                count++;
            }
            i--;
            //adding while space betweeen numbers
            postfix[count] = ' ';
            count++;
        }
        else if (isOperator(infix[i]))
        {
            if (empty(&operators))
            {
                push(&operators, infix[i]);
            }
            //if the priority is highers than the topof the stack, push it on to operators stack
            else if(priority(infix[i]) > priority(top(&operators)))
            {
                push(&operators, infix[i]);
            }
            //If priority is lower or equal, pop into the postfix until it is empty
            else
            {   
                while((!empty(&operators)) && priority(infix[i]) <= priority(top(&operators)) && !isParentheses(top(&operators)))
                {
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;
                }
                push(&operators, infix[i]);
            }
        }
        //check if char is a parentheses
        else if (infix[i] == '(' || infix[i] == ')')
        {
            //if open parentheses, pushes it to the operators
            if(infix[i] == '(')
            {
                push(&operators, infix[i]);
            }
            else
            {
                while(top(&operators) != '(')
                {
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;
                }
                pop(&operators);
            }
        }
       //check if char is a square bracket
        else if (infix[i] == '[' || infix[i] == ']')
        {
            //if open square bracket, pushes it to the operators
            if(infix[i] == '[')
            {
                push(&operators, infix[i]);
            }
            else
            {
                while(top(&operators) != '[')
                {
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;
                }
                pop(&operators);
            }
        }
        //check if char is a bracket
        else if (infix[i] == '{' || infix[i] == '}')
        {
            //if open bracket, pushes it to the operators
            if(infix[i] == '{')
            {
                push(&operators, infix[i]);
            }
            else
            {
                while(top(&operators) != '{')
                {
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;
                }
                pop(&operators);
            }
        }
    }

    for(int i = 0; i< strlen(infix); i++)
    {
        while((!empty(&operators)) && priority(infix[i]) <= priority(top(&operators)) && !isParentheses(top(&operators)))
        {
            postfix[count++] = pop(&operators);
            postfix[count++] = ' ';
        }
    }
    postfix[count] = '\0';

    return postfix;
}

int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || ch == '%')
    {
        return 1;
    }
    return 0;
}

int isParentheses(char ch)
{
    if (ch =='(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
    {
        return 1;
    }
    return 0;
}

int priority(char ch)
{
    if(ch == '(' || ch == '[' || ch == '{')
        return 0;
    if(ch == '+' || ch == '-')
        return 1;
    if(ch == '*' || ch == '/' || ch == '%')
        return 2;
    if(ch == '^')
        return 3;
    return -1;
}

int checkBalance(char* exp)
{
    int valid = 1;
    struct stack mine;
    initialize(&mine);
    printf("\nChecking balance..\n");

    for(int i = 0; exp[i] != '\0'; i++)
    {
        if( exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
        {
            push(&mine, exp[i]);
        }
        else if (exp[i] == ')')
        {
             char a = pop(&mine);
             if( a != '(' || a == 'I')
             {
                valid = 0;
                printf("Invalid for )!\n");
                return valid;
             }
        }
        else if ( exp[i] == '}')
        {
            char a = pop(&mine);
            if (a != '{' || a == 'I')
            {
                valid =0;
                printf("Invalid for }!\n");
                return valid;
            }
        }
        else if (exp[i] == ']')
        {  
            char a = pop(&mine);
            if (a != '[' || a == 'I')
            {
                valid = 0;
                printf("invalid for ]!\n");
                return valid;
            }
        }
    }
    if(pop(&mine) != 'I')//Still have parenthesis in the stack
    {
        valid = 0 ;
        printf("Invalid . You have extra open symbols");
    }

    return valid;
}

void initialize(struct stack* stackPtr) {
     stackPtr->top = -1;
}

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack* stackPtr, int value) {

    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr) {
    return (stackPtr->top == -1);
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack* stackPtr) {

    int retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return 'I';

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int top(struct stack* stackPtr) {

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}

void display(struct stack* stackPtr) {
    printf("\nPrinting the Current stack...");
    for(int i=0; i<=stackPtr->top; i++)
        printf("%d ", stackPtr->items[i]);
}
