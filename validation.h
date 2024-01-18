#include <string.h>

bool checkSpace(char text[10]);

bool authUser(char userName[10]){
	
	char simbols[] = {'+','-','/','*','?',168,'!',173};
	
	int cUpr = 0;
	int cNum = 0;
	
	if(strlen(userName) > 10 || strlen(userName) < 6){
		printf("ERROR: *El usuario debe tener entre 6 y 10 caracteres\n*");
		return false;
	}
	
	if(!checkSpace(userName)){
		return false;
	}
	
	if(userName[0]<97 || userName[0]>122){
			printf("\nERROR: *El usuario debe comenzar con una letra minuscula*\n");
			return false;
	}
	
	for(int i=0; i<strlen(userName); i++) {
		bool banSimb=true;
		if(
			(userName[i]>=48 && userName[i]<=57) ||
			(userName[i]>=65 && userName[i]<=90) ||
			(userName[i]>=97 && userName[i]<=122)
		){
			if(userName[i]>=65 && userName[i]<=90){
				cUpr++;
			}
			if(userName[i]>=48 && userName[i]<=57){
				cNum++;
			}	
		}else{
			for(int j=0; j<sizeof(simbols); j++){
				if(userName[i] == simbols[j]){
					cNum++;
					banSimb=true;
					break;
				}else{
					banSimb=false;
				}
			}
		}
		if(!banSimb){
			printf("\nERROR: Caracteres validos a-Z, 0-9 y {+,-,/,*,?,¿,!,¡}\n");
			return false;
		}
	}

	if(cUpr < 2 || cNum > 3){
		printf("\nERROR: El usuario debe tener al menos 2 letras mayusculas y un maximo 3 digitos/simbolos\n");
		return false;
	}
	
	return true;
}

bool checkSpace(char text[10]){
	
	char space[0];
	space[0] = ' ';
	int compare = strstr(text, space)-text;
	
	if(compare >= 0){
		printf("\nERROR: *El usuario no debe contener espacios*\n");
		return false;
	}
	
	return true;
	
}


