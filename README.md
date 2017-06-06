文法如下
--

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
		
		| for(stmt;stmt;stmt;) {stmts}
		
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
...