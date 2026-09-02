#include "compiler.h"

extern char tac[MAX_TAC][100];
extern int tacCount;

int isNumber(const char *s) {
    for(int i=0;s[i]!='\0';i++)
        if(!isdigit(s[i])) return 0;
    return 1;
}

void optimizeTAC() {
    printf("\n===== OPTIMIZATION =====\n");

    for(int i=0;i<tacCount;i++) {
        char result[50],left[50],right[50],op;
        int matched=sscanf(tac[i],"%s = %s %c %s",
                           result,left,&op,right);

        if(matched==4) {
            if(isNumber(left)&&isNumber(right)) {
                int a=atoi(left),b=atoi(right),value=0;
                switch(op) {
                    case '+':value=a+b;break;
                    case '-':value=a-b;break;
                    case '*':value=a*b;break;
                    case '/':if(b!=0)value=a/b;else continue;
                }
                sprintf(tac[i],"%s = %d",result,value);
                continue;
            }

            if(op=='+'&&strcmp(right,"0")==0)
                sprintf(tac[i],"%s = %s",result,left);
            else if(op=='*'&&strcmp(right,"1")==0)
                sprintf(tac[i],"%s = %s",result,left);
            else if(op=='*'&&strcmp(right,"0")==0)
                sprintf(tac[i],"%s = 0",result);
        }
    }

    printf("Optimization completed.\n");
    printf("\n===== OPTIMIZED TAC =====\n");
    for(int i=0;i<tacCount;i++) printf("%s\n",tac[i]);
}
