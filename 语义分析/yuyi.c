/*
	chenzezhong
	contact: chenzzh01@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>

FILE *pFile,*pFile2;
int syn=0;
int line;
int q=0;
int kk=0;
int pc=1;
char token[8];

void block();
void decls();
void stmts();
void stmt();
char *boo();
void scaner();
void for_loop();
void while_loop();
void do_while_loop();
void fuzhi();
void if_else();
char *expr();
char *term();
char *newtemp();
void emit(char *result,char *arg1,char *op,char *ag2);
char *factor();
char *Myitoa(int num);

struct
{
    char result1[8];
    char ag11[8];
    char op1[8];
    char ag21[8];
} quad[100];



int main()
{
    pFile2 = fopen("yuyishuchu.txt","w");
    fprintf(pFile2," (操作符,\t操作数1,\t操作数2,\t结果\t)\n");
    if((pFile = fopen("output.txt","r"))==NULL)
    {
      printf("文件打开失败\n");
      exit(-1);
    }
    fscanf(pFile,"%s\t\t%s\t\t%s\n",token,token,token);
    block();
    fclose(pFile);
    fclose(pFile2);
    return 0;
}


void block()
{
    scaner();
    if(syn==1){
        decls();
        stmts();
        if(syn==10) {
            printf("success!\n\n");
            return;
        }
        else
        {
          printf("缺少end结束标志.\n");
          exit(-1);
        }
    }
    else{
        printf("缺少begin开始符号.\n");
        exit(-1);
    }
}


void decls()
{
    char tt[8],eplace[8];
    scaner();
    if(syn==2)
    {
      scaner();
      if(syn==11) {
          strcpy(tt,token);
        scaner();
        if(syn==26) {
            printf("定义语句分析成功.\n");
            decls();
        }
        else if(syn==18){
            strcpy(eplace,boo());
          if(syn==26)   // ;
          {
              emit(tt,eplace,"=","");
              printf("定义语句分析成功.\n");
              decls();
          }
        }else {
          printf("第%d行定义语句缺少分号.\n",line);
          exit(-1);
        }
      }
      else {
        printf("第%d行定义语句变量错误\n",line);
        exit(-1);
      }
    }
}

void stmts()
{
    stmt();
    scaner();
    if(syn==10||syn==33)
      return;
    else
      stmts();
}



void fuzhi()
{
    char tt[8],eplace[8],tp[8];
    strcpy(tt,token);
    scaner();
    //printf("%d\t%s\n",syn,token);
    if(syn==18)     //=
    {
        strcpy(eplace,boo());
        emit(tt,eplace,"=","");
        return;
    }
    else if(syn==17 || syn==29){   //++ --
        //emit()
        strcpy(tp,newtemp());
        if(syn==17)
            emit(tp,tt,"+","1");
        if(syn==29)
            emit(tp,tt,"-","1");
        emit(tt,tp,"=","");
        scaner();
		return;
	  }
    else {
        printf("第%d行赋值语句错误.\n",line);
        exit(-1);
    }
}


void if_else()
{
    char eplace[8];
    scaner();
    if(syn==27)         // 27 - '('
    {
        strcpy(eplace,boo());
        if(syn==28)     //28 - ')'
        {
          scaner();
          if(syn==32) {
              char *m = (char *)malloc(8);
              strcpy(m,Myitoa(pc+1));
              emit(m,eplace,"jnz","");
            scaner();
            stmts();
            if(syn==33) {
              scaner();
              if(syn==4)    //4 - else
              {
                  char *n = (char *)malloc(8);
                  strcpy(n,Myitoa(pc+1));
                emit(n,eplace,"jz","");
                scaner();
                if(syn==32) {
                  scaner();
                  stmts();
                  if(syn==33) {
                    printf("if_else语句分析成功.\n");
                    return;
                  }else {
                    printf("第%d行if_else语句else块缺少右花括号.\n",line);
                    exit(-1);
                  }
                }
                else {
                  printf("第%d行if_else语句else块缺少左花括号.\n",line);
                  exit(-1);
                }
              }
              else
              {
                printf("if语句分析成功.\n");
                fseek(pFile,-5,SEEK_CUR);
                return;
              }
            }
            else {
              printf("第%d行if语句缺少右花括号.\n",line);
              exit(-1);
            }
          }
          else {
            printf("第%d行if语句缺少左花括号.\n",line);
            exit(-1);
          }
        }
    }
    else{
        printf("第%d行if语句条件表达式缺少左括号.\n",line);
        exit(-1);
    }
}


void do_while_loop()
{
    char eplace[8];
    int temp = pc;
    scaner();
    if(syn==32)       // "{}"
    {
      scaner();
      stmts();
        if(syn==33)     // "{}"
        {
            scaner();
            if(syn==7)   //while
            {
                scaner();
                if(syn==27)
                {
                    strcpy(eplace,boo());
                    char *m = (char *)malloc(8);
                    strcpy(m,Myitoa(temp));
                    emit(m,eplace,"loop","");
                  if(syn==28) {
                    scaner();
                    if(syn==26) {
                      printf("do_while语句分析成功.\n");
  					          return;
                    }
                    else {
                      printf("第%d行do_while语句缺少结束分号.\n",line);
                      exit(-1);
                    }
                  }
                  else {
                    printf("第%d行do后面条件表达式缺少右括号.\n",line);
                    exit(-1);
                  }
                }
                else {
                  printf("第%d行do后面条件表达式缺少左括号.\n",line);
                  exit(-1);
                }
            }
            else {
              printf("第%d行do_while语句while错误.\n",line);
              exit(-1);
            }
        }
        else {
          printf("第%d行do_while语句缺少右花括号.\n",line);
          exit(-1);
        }
    }
    else {
      printf("第%d行do_while语句缺少左花括号.\n",line);
      exit(-1);
    }
}



void while_loop()
{
    char eplace[8];
    int temp=pc;
    char *m = (char *)malloc(8);
    strcpy(m,Myitoa(temp));
    scaner();
    if(syn==27){
        strcpy(eplace,boo());
        if(syn==28) {
          scaner();
          if(syn==32) {
            scaner();
            stmts();
            if(syn==33) {
                emit(m,eplace,"loop","");
                printf("while语句分析成功.\n");
            }
            else {
                printf("第%d行while语句缺少右花括号.\n",line);
                exit(-1);
            }
          }
          else {
            printf("第%d行while语句缺少左花括号.\n",line);
            exit(-1);
          }
        }
        else {
          printf("第%d行while语句缺少右括号.\n",line);
          exit(-1);
        }
    }
    else {
      printf("第%d行while语句缺少左括号.\n",line);
      exit(-1);
    }
}

void for_loop()
{
    char eplace[8];
    int temp;
    char *m = (char *)malloc(8);
    scaner();
    if(syn==27) {
        scaner();
        stmt();
        temp = pc;
        strcpy(eplace,boo());
        scaner();
        if(syn==11) {
          fuzhi();
        }
        if(syn==28) {
            scaner();
            if(syn==32) {
                stmts();
                strcpy(m,Myitoa(temp));
                emit(m,eplace,"loop","");
                if(syn==33) {
                    printf("for循环语句分析成功.\n");
                }else {
                    printf("for循环语句右花括号缺失.\n");
                    exit(-1);
                }
            }
            else {
                printf("第%d行for循环语句右花括号缺失.\n",line);
                exit(-1);
            }
        }else {
            printf("第%d行for循环语句缺少右括号.\n",line);
            exit(-1);
        }

    }else {
        printf("第%d行for循环语句缺少左括号.\n",line);
        exit(-1);
    }
}

void stmt()
{
    switch(syn)
    {
        case 3:
            {
                if_else();
                break;
            }
        case 5:
            {
                for_loop();
                break;
            }
        case 11:
            {
                fuzhi();
                if(syn==26)   // ;
                {
                    printf("赋值语句分析成功.\n");
                    return;
                }
                else{
                  printf("第%d行赋值语句缺少分号.\n",line);
                  exit(-1);
                }
                break;
            }
        case 7:            //while
            {
                while_loop();
                break;
            }
        case 8:            //do
            {
                do_while_loop();
                break;
            }
        case 36:            //break
            {
                scaner();
                if(syn == 26) {
                  printf("break语句分析成功.\n");
                }
                else {
                  printf("第%d行break语句缺少结束分号.\n",line);
                  exit(-1);
                }
                break;
            }
        case  9: {            //return
            char *eplace;
            eplace=(char *)malloc(12);
            strcpy(eplace,boo());
            if(syn==26) {
                emit(eplace,"","ret","");
                printf("return语句分析成功.\n");
            }
            else {
                printf("第%d行return语句缺少结束分号.\n",line);
                exit(-1);
            }
            return;
        }
        case 26:{
          break;
        }
        default: return;
    }
    return;
}


char *boo()
{
    char *tp,*ep2,*eplace,*tt;
    tp=(char *)malloc(12);
    ep2=(char *)malloc(12);
    eplace=(char *)malloc(12);
    tt=(char *)malloc(12);
    strcpy(eplace,expr());
  if(syn==20||syn==22||syn==23||syn==24||syn==25)
  {
      char *eplace2 = (char *)malloc(12);

      if(syn==20){
          strcpy(tt,"<");
      }else if(syn==22){
          strcpy(tt,"<=");
      }else if(syn==23) {
          strcpy(tt,">");
      }else if(syn==24) {
          strcpy(tt,">=");
      }else {
          strcpy(tt,"==");
      }
      strcpy(eplace2,expr());
      strcpy(tp,newtemp());
      emit(tp,eplace,tt,eplace2);
      strcpy(eplace,tp);
  }
  return eplace;
}


char *expr()
{
    char *tp,*ep2,*eplace,*tt;
    tp=(char *)malloc(12);
    ep2=(char *)malloc(12);
    eplace=(char *)malloc(12);
    tt=(char *)malloc(12);
    strcpy(eplace,term());
    while((syn==13)||(syn==14))       //+ -
    {
        if(syn==13)
            strcpy(tt,"+");
        else
            strcpy(tt,"-");
        strcpy(ep2,term());
        strcpy(tp,newtemp());
        emit(tp,eplace,tt,ep2);
        strcpy(eplace,tp);
    }
    return eplace;
}

char *term()
{
    char *tp,*ep2,*eplace,*tt;
    tp=(char *)malloc(12);
    ep2=(char *)malloc(12);
    eplace=(char *)malloc(12);
    tt=(char *)malloc(12);
    strcpy(eplace,factor());
    while((syn==15)||(syn==16))         // * /
    {
        if (syn==15)strcpy(tt,"*");
        else strcpy(tt,"/");
        strcpy(ep2,factor());
        strcpy(tp,newtemp());
        emit(tp,eplace,tt,ep2);
        strcpy(eplace,tp);
    }
    return eplace;
}

char *factor()
{
    char *fplace;
    fplace=(char *)malloc(12);
    strcpy(fplace,"");
    scaner();
    if((syn==11)||(syn==12))
    {
        strcpy(fplace,token);
        scaner();
    }
    else if(syn==27)
    {
        fplace =expr();
        if(syn==28)
        {
          scaner();
        }
        else
        {
            printf("表达式右括号错误.\n");
            exit(-1);
        }
    }
    else
    {
        printf("表达式右部错误.\n");
        exit(-1);
    }
    return fplace;
}

void scaner()
{

  if(fscanf(pFile,"%s\t\t%d\t\t%d\n",token,&syn,&line) != EOF)
  {
    return;
  }
}


char *newtemp()
{
    char *p;
    p=(char *)malloc(8);
    char *m = (char *)malloc(8);
    kk++;
    strcpy(m,Myitoa(kk));
    strcpy(p+1,m);
    p[0]='t';
    return p;
}


char *Myitoa(int num) //将整数转换成字符串，mac的编译器不支持itoa()
{
    char str[8];
    int temp = num;
    int i = 0;
    while(temp>0)
    {
        str[i] = temp % 10 + '0';
        temp = temp / 10;
        i++;
    }
    str[i] = '\0';

    int j = 0;
    char reverseStr[8];
    i--;
    do
    {
        reverseStr[j] = str[i];
        j++;
        i--;
    }while(i>=0);
    reverseStr[j] = '\0';
    return reverseStr;
}


void emit(char *result,char *ag1,char *op,char *ag2)
{
    strcpy(quad[q].result1,result);
    strcpy(quad[q].ag11,ag1);
    strcpy(quad[q].op1,op);
    strcpy(quad[q].ag21,ag2);
    fprintf(pFile2,"%d:( %-6s,%-6s,%-6s,%-6s)\n",pc,quad[q].op1,quad[q].ag11,quad[q].ag21,quad[q].result1);
    q++;
    pc++;
}
