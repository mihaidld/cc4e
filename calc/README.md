# Calculator program that provides the operators +, -, \*, and /.

K&R 2nd Chapter 4

Because it is easier to implement, the calculator will use reverse Polish notation instead of infix.

In reverse Polish notation, each operator follows its operands; an infix expression like

```zsh
(1 - 2) * (4 + 5)
```

is entered as

```zsh
1 2 - 4 5 + *
```

Parentheses are not needed; the notation is unambiguous as long as we know how many operands each operator expects.

The implementation is simple. Each operand is pushed onto a stack; when an operator arrives, the proper number of operands (two for binary operators) is popped, the operator is applied to them, and the result is pushed back onto the stack.
In the example above, for instance, 1 and 2 are pushed, then replaced by their difference,-1. Next,4 and 5 are pushed and then replaced by their sum, 9. The product of -1 and 9, which is -9, replaces them on the stack. The value on the top of the stack is popped and printed when the end of the input line is encountered.
The structure of the program is thus a loop that performs the proper operation on each operator and operand as it appears:

```zsh
while (next operator or operand is not end-of-file indicator)
    if (number)
        push it
    else if (operator)
        pop operands
        do operation
        push result
    else if (newline)
        pop and print top of stack
    else
        error
```
