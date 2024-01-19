#include <string.h>

bool checkSpace(char text[10]);

bool authUser(char userName[10]){
	
	// Array con los simbolos permitidos para la creacion del usuario
	char simbols[] = {'+','-','/','*','?',168,'!',173};
	
	int cUpr = 0; //contador de letras mayusculas
	int cNum = 0; //contador de numero/simbolos
	
	// verifica que el usuario no tenga menos de 6 caracteres ni mas de 10
	if(strlen(userName) > 10 || strlen(userName) < 6){
		printf("\n\tERROR: *El usuario debe tener entre 6 y 10 caracteres.*\n");
		return false;
	}
	
	// verifica que el usuario no contenga espacios
	if(!checkSpace(userName)){
		return false;
	}
	
	// verifica que el usuario comience con una letra minuscula
	if(userName[0]<97 || userName[0]>122){
			printf("\n\tERROR: *El usuario debe comenzar con una letra minuscula.*\n");
			return false;
	}
	
	for(int i=0; i<strlen(userName); i++) {
		bool flagSimb=true; // declara una bandera para saber si hay un simbolo que no esta permitido
		if( // Verifica que el usuario ingresado contenga solo caracteres y numeros
			(userName[i]>=48 && userName[i]<=57) || 
			(userName[i]>=65 && userName[i]<=90) ||
			(userName[i]>=97 && userName[i]<=122)
		){
			if(userName[i]>=65 && userName[i]<=90){
				cUpr++; //cuenta las letras mayusculas que contiene para su validacion
			}
			if(userName[i]>=48 && userName[i]<=57){
				cNum++; // cuenta la cantidad de numeros para su validacion
			}	
		}else{ // en el caso de que el usuario contenga un simbolo, verifica que ese simbolo pertenezca al array de simbolos permitidos declarado anteriormente al inicio del metodo
			for(int j=0; j<sizeof(simbols); j++){
				if(userName[i] == simbols[j]){
					cNum++; // si el simbolo pertenece al array, lo suma al contador de numeros/simbolos
					flagSimb=true;
					break; //sale del for a la primera coincidencia y pasa a la siguiente iteracion
				}else{
					flagSimb=false; // en el caso de que el simbolo no perteneza al array de permitidos, cambia la bandera a false
				}
			}
		}
		if(!flagSimb){ // en el caso de que la bandera se encuentre en false, es porque el usuario contiene un caracter no valido y el metodo termina retornando false al programa principal
			printf("\n\tERROR: *Caracteres validos a-Z, 0-9 y {+,-,/,*,?,¿,!,¡}.*\n");
			return false;
		}
	}

	if(cUpr < 2 || cNum > 3){ // si el contador de mayusculas y numeros/simbolos no corresponde a la validacion pedida en la documentacion retorna el error y un false al programa principal
		printf("\n\tERROR: *El usuario debe tener al menos 2 letras mayusculas y un maximo 3 digitos/simbolos.*\n");
		return false;
	}
	
	return true;
}

bool authPass(char pass[10]){ //metodo para validar password
	
	char aux[10]; // creo un auxiliar
	int numConsecutive = 0; // contador de numeros consecutivos 1,2,3,4... etc
	
	strcpy(aux,pass); // copio la pass ingresada por el usuario a la variable auxiliar
	strupr(aux); // transforma la variable auxiliar a mayusucula
	
	int cUpr = 0; // contador de mayusuclas
	int cLwr = 0; // contador de minusculas
	int cNum = 0; // contador de numeros
	
	// valida q la contraseña no tenga menos de 6 caracteres ni mas de 32
	if(strlen(pass) > 32 || strlen(pass) < 6){
		printf("\n\tERROR: *La contrasenia debe tener entre 6 y 32 caracteres.*\n");
		return false;
	}
	
	// valida q la contraseña no contenga espacios
	if(!checkSpace(pass)){
		return false;
	}
	
	for(int i=0; i<strlen(pass); i++) {
		
		if( // verifica que la contraseña solo contenga caracteres y numeros
			(pass[i]>=48 && pass[i]<=57) ||
			(pass[i]>=65 && pass[i]<=90) ||
			(pass[i]>=97 && pass[i]<=122)
		){
			if(pass[i]>=65 && pass[i]<=90){ 
				cUpr++; // si la contraseña es una letra mayuscula suma uno al contador
				if((aux[i+1]-aux[i]) == 1){ // verifica que los caracteres no sean consecutivos, de lo contrario muestra el error y retorna un false
					printf("\n\tERROR: *No se permiten caracteres consecutivos.*\n");
					return false;
				}
			}
			if(pass[i]>=48 && pass[i]<=57){
				cNum++; // si la contraseña contiene un numero incrementa en uno el contador
				if( i != strlen(pass) ){ // verifica que los numeros no sean consecutivos, de lo contrario muestra el error y retorna un false
					numConsecutive++;
				}else if(pass[i] - pass[i-1] == 1){
					numConsecutive++;
				}
			}
			if(pass[i]>=97 && pass[i]<=122){
				cLwr++; // si la contraseña es una letra minuscula suma uno al contador
				if((aux[i+1]-aux[i]) == 1){ // verifica que los caracteres no sean consecutivos, de lo contrario muestra el error y retorna un false
					printf("\n\tERROR: *No se permiten caracteres consecutivos.*\n");
					return false;
				}
			}
			
		}else{ // en el caso de que la contraseña ingresada no sea alfanumerica devuelve el error y retorna un false (no se permiten simbolos)
			printf("\n\tERROR: *Solo se permiten caracteres alfanumericos (a-Z y 0-9).*\n");
			return false;
		}
	}
	
	if(numConsecutive>3){ // con el contador verifica que la contraseña no contenga mas de 3 numeros consecutivos
		printf("\n\tERROR: *No se permiten mas de 3 numeros consecutivos.*\n");
		return false;
	}
	if(cUpr<=0){ // verifica con el contador que la contraseña tenga al menos una mayuscula
		printf("\n\tERROR: *La contrasenia debe contener al menos una letra mayuscula.*\n");
		return false;
	}
	if(cLwr<=0){ // verifica con el contador que la contraseña tenga al menos una minuscula
		printf("\n\tERROR: *La contrasenia debe contener al menos una letra minuscula.*\n");
		return false;
	}
	if(cNum<=0){ // verifica con el contador que la contraseña tenga al menos un numero
		printf("\n\tERROR: *La contrasenia debe contener al menos un numero.*\n");
		return false;
	}
	
	return true;
	
}

bool checkSpace(char text[10]){
	
	char space[0];
	space[0] = ' ';
	int compare = strstr(text, space)-text;
	
	if(compare >= 0){
		printf("\n\tERROR: *No debe contener espacios.*\n");
		return false;
	}
	
	return true;
	
}

