/*
	chenzezhong
	2017-5-13 20:27
	contact: chenzzh01@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>

FILE *pFile;
int syn=0;

void block();
void decls();
void stmts();
void stmt();
void boo();
void expr();
void term();
void factor();
void scaner();
void for_loop();
void while_loop();
void do_while_loop();
void fuzhi();
void if_else();


int main()
{
    if((pFile = fopen("output.txt","r"))==NULL)
    {
      printf("文件打开失败\n");
      exit(-1);
    }
    block();
    fclose(pFile);
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
    scaner();
    if(syn==2)
    {
      scaner();
      if(syn==11) {
        scaner();
        if(syn==26) {
            printf("定义语句分析成功.\n");
            decls();
        }
        else if(syn==18){
          boo();
          if(syn==26)   // ;
          {
              printf("定义语句分析成功.\n");
              decls();
          }
        }else {
          printf("定义语句缺少分号.\n");
          exit(-1);
        }
      }
      else {
        printf("定义语句变量错误\n");
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
    scaner();
    if(syn==18)     //=
    {
      boo();
      return;
    }
    else if(syn==17 || syn==29){   //++ --
        scaner();
		    return;
	  }
    else {
      printf("赋值语句错误.\n");
      exit(-1);
    }
}


void if_else()
{
    scaner();
    if(syn==27)         // 27 - '('
    {
        boo();
        if(syn==28)     //28 - ')'
        {
          scaner();
          if(syn==32) {
            scaner();
            stmts();
            if(syn==33) {
              scaner();
              if(syn==4)    //4 - else
              {
                scaner();
                if(syn==32) {
                  scaner();
                  stmts();
                  if(syn==33) {
                    printf("if_else语句分析成功.\n");
                    return;
                  }else {
                    printf("if_else语句else块缺少右花括号.\n");
                    exit(-1);
                  }
                }
                else {
                  printf("if_else语句else块缺少左花括号.\n");
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
              printf("if语句缺少右花括号.\n");
              exit(-1);
            }
          }
          else {
            printf("if语句缺少左花括号.\n");
            exit(-1);
          }
        }
    }
    else{
        printf("if语句条件表达式缺少左括号.\n");
        exit(-1);
    }
}


void do_while_loop()
{
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
                  boo();
                  if(syn==28) {
                    scaner();
                    if(syn==26) {
                      printf("do_while语句分析成功.\n");
  					          return;
                    }
                    else {
                      printf("do_while语句缺少结束分号.\n");
                      exit(-1);
                    }
                  }
                  else {
                    printf("do后面条件表达式缺少右括号.\n");
                    exit(-1);
                  }
                }
                else {
                  printf("do后面条件表达式缺少左括号.\n");
                  exit(-1);
                }
            }
            else {
              printf("do_while语句while错误.\n");
              exit(-1);
            }
        }
        else {
          printf("do_while语句缺少右花括号.\n");
          exit(-1);
        }
    }
    else {
      printf("do_while语句缺少左花括号.\n");
      exit(-1);
    }
}



void while_loop()
{
    scaner();
    if(syn==27)
    {
        boo();
        if(syn==28) {
          scaner();
          if(syn==32) {
            scaner();
            stmts();
            if(syn==33) {
              printf("while语句分析成功.\n");
            }
            else {
              printf("while语句缺少右花括号.\n");
              exit(-1);
            }
          }
          else {
            printf("while语句缺少左花括号.\n");
            exit(-1);
          }
        }
        else {
          printf("while语句缺少右括号.\n");
          exit(-1);
        }
    }
    else {
      printf("while语句缺少左括号.\n");
      exit(-1);
    }
}

void for_loop()
{
    scaner();
    if(syn==27) {
        scaner();
        stmt();
        boo();
        scaner();
        if(syn==11) {
          fuzhi();
        }
        if(syn==28) {
            scaner();
            if(syn==32) {
                stmts();
                if(syn==33) {
                    printf("for循环语句分析成功.\n");
                }else {
                    printf("for循环语句右花括号缺失.\n");
                    exit(-1);
                }
            }
            else {
                printf("for循环语句右花括号缺失.\n");
                exit(-1);
            }
        }else {
            printf("for循环语句缺少右括号.\n");
            exit(-1);
        }

    }else {
        printf("for循环语句缺少左括号.\n");
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
                  printf("赋值语句缺少分号.\n");
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
                  printf("break语句缺少结束分号.\n");
                  exit(-1);
                }
                break;
            }
        case  9: {            //return
            boo();
            if(syn==26) {
                printf("return语句分析成功.\n");
            }
            else {
                printf("return语句缺少结束分号.\n");
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


void boo()
{
  expr();
  if(syn==20||syn==22||syn==23||syn==24||syn==25)
  {
    expr();
  }
  return;
}


void expr()
{
    term();
    while((syn==13)||(syn==14))       //+ -
    {
        term();
    }
    return;
}

void term()
{
    factor();
    while((syn==15)||(syn==16))         // * /
    {
        factor();
    }
    return;
}

void factor()
{
    scaner();
    if((syn==11)||(syn==12))
    {
        scaner();
    }
    else if(syn==27)
    {
        expr();
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
    return;
}


void scaner()
{
  char ch;
  ch=fgetc(pFile);
  while (ch!=EOF)
  {
      if(ch==')')
      {
          fseek(pFile,-4,SEEK_CUR);
          syn=0;
          while(ch<'0'||ch>'9')
          {
              ch=fgetc(pFile);
          }
          while(ch>='0'&&ch<='9')
          {
              syn=syn*10+ch-'0';
              ch=fgetc(pFile);
          }
          fseek(pFile,4,SEEK_CUR);
          ch=fgetc(pFile);
          return;
      }else{
          ch=fgetc(pFile);
      }
  }
}
