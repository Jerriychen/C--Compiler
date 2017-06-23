14级计算机一班_陈泽忠


关于：

cifa.c—————词法分析器
词法分析器的输入是source.txt
词法分析器的输出是output.txt

yuyi.c——————语法和语义分析器
语法语义分析器的输入是output.txt
语法语义分析器的输出是yuyishuchu.txt
输出是四元组形式


符号表.txt
符号表给出了词法分析时各数字所代表的含义
比如数字2代表一个int符号


源语言文法如下：

program -> block

block -> begin decls stmts end

decls -> decl decls | NULL

decl  -> int id;

stmts -> stmt stmts | NULL

stmt  ->  id = boo

	| if( boo ) { stmt }
		
	| if( boo ) { stmt } else { stmt }
		
	| while(boo) {stmt}
		
	| do {stmts} while(boo);
		
	| for(stmt;boo;stmt;) {stmts}
		
	| return id;
		
	| break;
		
	| block
		
boo -> expr < expr 

	| expr > expr 
		
	| expr <= expr 
		
	| expr >=expr

expr -> term + term 

	| term - term

term -> factor * factor 
	
	| factor / factor

factor -> (boo) | id 





语法和语义输出如下：
 (操作符,	操作数1,	操作数2,	结果	)
1:( =     ,4     ,      ,x     )———————x=4     
2:( *     ,x     ,4     ,t1    )———————t1=x*4  ——————————-|
3:( +     ,t1    ,5     ,t2    )———————t2=t1+5		  |—————y=x*4+5-(8*2);
4:( *     ,8     ,2     ,t3    )——————-t3=8*2		  |
5:( -     ,t2    ,t3    ,t4    )——————-t4=t2-t3		  |
6:( =     ,t4    ,      ,y     )——————-y=t4    ———————————|
7:( +     ,y     ,z     ,t5    )
8:( *     ,x     ,t5    ,t6    )
9:( =     ,t6    ,      ,z     )
10:( =     ,0     ,      ,sum   )
11:( <     ,x     ,10    ,t7    )
12:( *     ,x     ,3     ,t8    )
13:( =     ,t8    ,      ,sum   )
14:( +     ,x     ,1     ,t9    )
15:( =     ,t9    ,      ,x     )
16:( loop  ,t7    ,      ,11    )—————————若t7位真，则循环跳转到11
17:( =     ,0     ,      ,i     )
18:( <     ,i     ,10    ,t10   )
19:( +     ,i     ,1     ,t11   )
20:( =     ,t11   ,      ,i     )
21:( +     ,sum   ,1     ,t12   )
22:( =     ,t12   ,      ,sum   )
23:( loop  ,t10   ,      ,18    )
24:( ret   ,      ,      ,z     )


