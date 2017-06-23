#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define  MAX_LINE 30

char prog[MAX_LINE],token[10],ch;
int syn,p,m,n,sum,line;
char *keywords[10]={"begin","int","if","else","for","printf","while","do","return","end"};
char *BREAK = "break";
void scaner();
void convert(int num,char *result);
char result[8];

int main()
{
    FILE *pFile1 = fopen("source.txt","r");
    FILE *pFile2 = fopen("output.txt","w");
    fprintf(pFile2, "字符\t\t标志符\t\t行号\n");
    while (!feof(pFile1))
    {
        p=0;
        for(m=0;m<MAX_LINE;m++)
            prog[m]= '\0';

        fgets(prog,MAX_LINE,pFile1);
        line++;
        printf("%s",prog);
        char result1[3];
        do{
            scaner();
            switch(syn)
            {
                case 12:
                    convert(sum,result1);
                    fprintf(pFile2,"%s\t\t%d\t\t%d\n",result1,syn,line);break;
                //case -1:
                    //fprintf(pFile2,"you have a error input.\n");break;
                case 0:
                    break;
                default:
                    fprintf(pFile2,"%s\t\t%d\t\t%d\n",token,syn,line);break;
            }
        }while(syn!=0);
    }
    fclose(pFile1);
    fclose(pFile2);
    return 0;
 }


void  convert(int num,char *result)
{
  if(num>=10) {
    result[0]=num/10+'0';
    result[1] = num%10+'0';
    result[2] = '\0';
  }else if(num<10) {
    result[0] = num+'0';
    result[1] = '\0';
  }
}

void scaner()
{
    sum=0;

    for(m=0;m<10;m++)
        token[m]= '\0';

    ch=prog[p++];
    m=0;

    while(ch==' '||ch=='\t')
        ch=prog[p++];

    if(((ch<='z')&&(ch>='a'))||((ch<='Z')&&(ch>='A')))
    {
        while(((ch<='z')&&(ch>='a'))||((ch<='Z')&&(ch>='A'))||((ch>='0')&&(ch<='9')))
        {
            token[m++]=ch;
            ch=prog[p++];
        }
        p--;
        syn=11;
        for(n=0;n<10;n++)
        {
          if(strcmp(token,keywords[n])==0)
          {
              syn=n+1;
              break;
          }
        }


        //底下这几行是临时加的，为了处理break；
        if(strcmp(token,BREAK)==0) {
          syn = 36;
        }
    }

     else if((ch>='0')&&(ch<='9'))
     {
        while((ch>='0')&&(ch<='9'))
        {
            sum=sum*10+ch-'0';
            ch=prog[p++];
        }
        p--;
        syn=12;
    }

    else
    {
        switch(ch)
        {
        case '<':
            token[m++]=ch;
            ch=prog[p++];
            if(ch=='=')
            {
                syn=22;
                token[m++]=ch;
            }
            else
            {
                syn=20;
                p--;
            }
            break;

        case '>':
            token[m++]=ch;
            ch=prog[p++];
            if(ch=='=')
            {
                syn=24;
                token[m++]=ch;
            }
            else
            {
                syn=23;
                p--;
            }
            break;

        case '+':
            token[m++]=ch;
            ch=prog[p++];
            if(ch=='+')
            {
                syn=17;
                token[m++]=ch;
            }
            else
            {
                syn=13;
                p--;
            }
            break;

        case '-':
            token[m++]=ch;
            ch=prog[p++];
            if(ch=='-')
            {
                syn=29;
                token[m++]=ch;
            }
            else
            {
                syn=14;
                p--;
            }
            break;

        case '!':
            ch=prog[p++];
            if(ch=='=')
            {
                syn=21;
                token[m++]=ch;
            }
            else
            {
                syn=31;
                p--;
            }
            break;

        case '=':
            token[m++]=ch;
            ch=prog[p++];
            if(ch=='=')
            {
                syn=25;
                token[m++]=ch;
            }
            else
            {
                syn=18;
                p--;
            }
            break;

        case '*':
            syn=15;
            token[m++]=ch;
            break;

        case '/':
            syn=16;
            token[m++]=ch;
            break;

        case '(':
            syn=27;
            token[m++]=ch;
            break;

        case ')':
            syn=28;
            token[m++]=ch;
            break;

        case '{':
            syn=32;
            token[m++]=ch;
            break;

        case '}':
            syn=33;
            token[m++]=ch;
            break;

        case ';':
            syn=26;
            token[m++]=ch;
            break;

        case ',':
            syn=19;
            token[m++]=ch;
            break;

        case '\"':
            syn=30;
            token[m++]=ch;
            break;

        case ':':
            syn=17;
            token[m++]=ch;
            break;

        case '\n':
        case '\0':
        case '\r':
            syn=0;
            break;

        //default:
          //  syn=-1;
            //break;
        }
    }
}
