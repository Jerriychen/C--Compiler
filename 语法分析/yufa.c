/*
	chenzezhong
	2017-5-15 20:27
	contact: chenzzh01@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>

FILE *pFile;
int count=1;
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
            printf("success!\n");
            return;
        }
        else
        {
          printf("缺少end结束标志.\n");
          exit(-1);
        }
    }
    else{
      printf("%d\n",syn);
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
            printf("定义语句正确\n");
            decls();
        }
        else if(syn==18){
          boo();
          if(syn==26)   // ;
          {
              printf("定义语句分析成功\n");
              decls();
          }
        }else {
          printf("定义语句错误.\n");
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
    if(syn==18)     //==
    {
      boo();
      if(syn==26)   // ;
      {
          printf("赋值语句分析成功\n");
          return;
      }
      else{
        printf("赋值语句错误.\n");
        exit(-1);
      }
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
                    printf("if else 语句分析结束\n");
                    return;
                  }
                }
              }
              else
              {
                printf("if 语句分析结束\n");
                stmts();
              }
            }
          }
        }
    }
    else{
        printf("if 语句错误\n");
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
                      printf("do while 语句正确\n");
  					          return;
                    }
                    else {
                      printf("do while 语句有错误\n");
                    }
                  }
                  else {
                    printf("do while 语句有错误\n");
                  }
                }
                else {
                  printf("do while 语句有错误\n");
                }
            }
            else {
              printf("do while 语句有错误\n");
            }
        }
        else {
          printf("do while 语句有错误\n");
        }
    }
    else {
      printf("do while 语句有错误\n");
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
              printf("while do 语句分析结束.\n");
            }
            else {
              printf("while do 语句有错误\n");
            }
          }
          else {
            printf("while do 语句有错误\n");
          }
    		}
        else {
          printf("while do 语句有错误\n");
        }
    }
    else {
      printf("while do 语句有错误\n");
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
        case 11:
            {
                fuzhi();
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
                if(syn!=26)
                {
                    printf("分号缺失.\n");
					          exit(-1);
                }
                break;
            }
        case  9: {            //return
            boo();
            if(syn==26)
                printf("return 语句分析结束.\n");
            return;
        }
		    case 10: return;
        default: block();
    }
    return;
}


void boo()
{
  expr();
  if(syn==20||syn==22||syn==23||syn==24)
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
            printf("the error on '('\n");
			      exit(-1);
        }
    }
    else
    {
        printf("the expression error!\n");
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
      }else
          ch=fgetc(pFile);
  }
}
