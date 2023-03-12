#include <stdio.h>
 #include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
typedef union
{
    float fData;
    char cData;

} Item;
typedef struct
{
    int top;
    Item items[256];
} Stack;

Stack* initialize()
{
    Stack* s=malloc(sizeof(Stack));
    s->top=0;
    return s;
}

Item pop(Stack* s)
{
    Item value;
    s->top--;
    value =s->items[s->top];
    return value;

}
void push(Stack* s,Item val)
{
    s->items[s->top]=val;
    s->top++;
}

Item top (Stack* s)
{
    Item value;
    value=s->items[s->top-1];
    return value;
}
int isEmpty(Stack* s)
{
    if(s->top==0)
        return -1;
    else
        return 0;
}

float evaluate(char x,float operand1,float operand2)
{
    if(x=='*')
        return operand1*operand2;
    if(x=='/')
        return operand1/operand2;
    if(x=='%')
        return (int)operand1%(int)operand2;
    if(x=='+')
        return operand1+operand2;
    if(x=='-')
        return operand1-operand2;

    if(x=='^')
        return pow(operand1,operand2);
}
int isoperator(char *exp)
{
    for(int i=0; i<strlen(exp); i++)
    {
        if(isdigit(exp[i]))
            return 0;

    }
    return 1;

}




float evaluatePostfix(char *postfix)
{
    Stack* s=initialize();
    int i;
    float operand1,operand2,value;
    Item x,y;
    char *token=strtok(postfix," ");
    while(token!=NULL)
    {

        if(isoperator(token)==1)
        {
            operand2=pop(s).fData;
            operand1=pop(s).fData;
            value=evaluate(token[0],operand1,operand2);
            x.fData=value;
            push(s,x);
        }
        else
        {
            y.fData=atof(token);
            push(s,y);
        }


        token=strtok(NULL," ");
    }
    x.fData=pop(s).fData;
    return x.fData;



}
int orderOfOperators(char x)
{

    if(x=='^')
        return 2;
    if(x=='*'||x=='/'||x=='%')
        return 1;
    if(x=='+'||x=='-')
        return 0;
}
void infixTopostfix(char *infix,char *postfix)
{

    Stack*s=initialize();

strcpy(postfix,"");
    Item x;
    char *token=strtok(infix," ");
    while(token!=NULL)

    {

        if(isoperator(token)==0)
        {
            strcat(postfix,token);
            strcat(postfix," ");

        }
        else if(token[0]==')')
        {
            char temp[256]="";
            while(!isEmpty(s)&&top(s).cData!='(')
            {
                temp[0]=pop(s).cData;
                strcat(postfix,temp);
                strcat(postfix," ");

            }
            pop(s).cData;
        }
        else if(isEmpty(s))
        {
            x.cData=token[0];
            push(s,x);

        }
        else
        {
            while(!isEmpty(s)&&orderOfOperators(top(s).cData)>=orderOfOperators(token[0])&&top(s).cData!='(')
            {char temp[256]="";
                temp[0]=pop(s).cData;
                strcat(postfix,temp);
                strcat(postfix," ");

            }
            x.cData=token[0];
            push(s,x);

        }

        token=strtok(NULL," ");

    }
    while(!isEmpty(s))
    {
        char temp[256]="";
        temp[0]=pop(s).cData;
                strcat(postfix,temp);
                strcat(postfix," ");


    }


}


void replaceNewLineBySpace(char *s)
{
    char *s1=s;
    while((s1=strstr(s1,"\n"))!=NULL)
        *s1=' ';
}
int main(int argc,char**argv)
{
    printf("Input (infix):");
    char infixExpr[256]="";
    char postfixExpr[256]="";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit:");
    while(fgets(infixExpr,255,stdin)!=NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixTopostfix(infixExpr,postfixExpr);
        printf("Postfix : %s\n",postfixExpr);
        float result =evaluatePostfix(postfixExpr);
        printf("Result :%f\n\n",result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit:");


    }


    return 0;
}
