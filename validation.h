#include <string.h>

bool checkSpace(char text[10]);

bool authUser(char userName[10]){
	
	char simbols[] = {'+','-','/','*','?',168,'!',173};
	
	int cUpr = 0;
	int cNum = 0;
	
	if(strlen(userName) > 10 || strlen(userName) < 6){
		printf("\nERROR: *El usuario debe tener entre 6 y 10 caracteres.*\n");
		return false;
	}
	
	if(!checkSpace(userName)){
		return false;
	}
	
	if(userName[0]<97 || userName[0]>122){
			printf("\nERROR: *El usuario debe comenzar con una letra minuscula.*\n");
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
		printf("\nERROR: El usuario debe tener al menos 2 letras mayusculas y un maximo 3 digitos/simbolos.\n");
		return false;
	}
	
	return true;
}

bool authPass(char pass[10]){
	
	char aux[10];
	int numConsecutive = 0;
	
	strcpy(aux,pass);
	strupr(aux);
	
	int cUpr = 0;
	int cLwr = 0;
	int cNum = 0;
	
	if(strlen(pass) > 32 || strlen(pass) < 6){
		printf("\nERROR: *La contrasenia debe tener entre 6 y 32 caracteres.*\n");
		return false;
	}
	
	if(!checkSpace(pass)){
		return false;
	}
	
	for(int i=0; i<strlen(pass); i++) {
		bool banSimb=true;
		if(
			(pass[i]>=48 && pass[i]<=57) ||
			(pass[i]>=65 && pass[i]<=90) ||
			(pass[i]>=97 && pass[i]<=122)
		){
			if(pass[i]>=65 && pass[i]<=90){
				cUpr++;
				if((aux[i+1]-aux[i]) == 1){
					printf("\nERROR: *No se permiten caracteres consecutivos.*\n");
					return false;
				}
			}
			if(pass[i]>=48 && pass[i]<=57){
				cNum++;
				if( i != strlen(pass) ){
					numConsecutive++;
				}else if(pass[i] - pass[i-1] == 1){
					numConsecutive++;
				}
			}
			if(pass[i]>=97 && pass[i]<=122){
				cLwr++;
				if((aux[i+1]-aux[i]) == 1){
					printf("\nERROR: *No se permiten caracteres consecutivos.*\n");
					return false;
				}
			}
			
		}else{
			printf("\nERROR: *Solo se permiten caracteres alfanumericos (a-Z y 0-9).*\n");
			return false;
		}
	}
	
	if(numConsecutive>3){
		printf("\nERROR: *No se permiten mas de 3 numeros consecutivos.*\n");
		return false;
	}
	if(cUpr<=0){
		printf("\nERROR: *La contrasenia debe contener al menos una letra mayuscula.*\n");
		return false;
	}
	if(cLwr<=0){
		printf("\nERROR: *La contrasenia debe contener al menos una letra minuscula.*\n");
		return false;
	}
	if(cNum<=0){
		printf("\nERROR: *La contrasenia debe contener al menos un numero.*\n");
		return false;
	}
	
	return true;
	
}

bool checkSpace(char text[10]){
	
	char space[0];
	space[0] = ' ';
	int compare = strstr(text, space)-text;
	
	if(compare >= 0){
		printf("\nERROR: *No debe contener espacios*\n");
		return false;
	}
	
	return true;
	
}


