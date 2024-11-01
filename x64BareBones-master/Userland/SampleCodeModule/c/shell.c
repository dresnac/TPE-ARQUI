#include <stdint.h>
#include <shell.h>

#define PROMPT_TEXT "$:>"

void startShell(){

    //misma logica que seguiamos en el kernel main pero pasado al userLand
    //esta bien hacer todo con syscalls?

    while(1){
        syscall(4, 1, PROMPT_TEXT, 3); // imprime el prompt text
        char c = 0;
        int len;
        while(1){
            syscall(3, 1, c, len);   //leo el caracter del teclado
		    if(c == '\n')
	 		{
	 			syscall(6, 1, 1, 1); //borro, que pongo en los otros params?
                syscall(7, 1, 1, 1); //newline
				syscall(4, 1, PROMPT_TEXT, 3); // imprime el prompt text
	 		}
	 		else if(c==8){
	 			syscall(6, 1, 1, 1); //borro, que pongo en los otros params?
	 			syscall(6, 1, 1, 1); //borro, que pongo en los otros params?
	 			syscall(4, 1, "_", 3); // imprime el cursor
	 		}
	 		else{
	 			syscall(6, 1, 1, 1); //borro, que pongo en los otros params?
	 			syscall(4, 1, c, 3); // imprime el caracter
     			syscall(4, 1, "_", 3); // imprime el cursor
	 		}
        }
    }	

    char * ejemplo = "Jorge";
    syscall(4, 1, ejemplo, 5);

}