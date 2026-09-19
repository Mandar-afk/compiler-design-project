#include "compiler.h"

extern char tac[MAX_TAC][100];
extern int tacCount;

void generateTargetCode() {
    printf("\n===== TARGET CODE =====\n");

    for(int i=0;i<tacCount;i++) {
        char result[50],left[50],right[50],op;
        int matched=sscanf(tac[i],"%s = %s %c %s",
                           result,left,&op,right);

        if(matched==4) {
            printf("LOAD R1, %s\n",left);
            switch(op) {
                case '+':printf("ADD R1, %s\n",right);break;
                case '-':printf("SUB R1, %s\n",right);break;
                case '*':printf("MUL R1, %s\n",right);break;
                case '/':printf("DIV R1, %s\n",right);break;
            }
            printf("STORE %s, R1\n",result);
        }
        else {
            char value[50];
            if(sscanf(tac[i],"%s = %s",result,value)==2) {
                printf("MOV R1, %s\n",value);
                printf("STORE %s, R1\n",result);
            }
        }
    }
}
