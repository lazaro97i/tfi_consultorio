#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "validation.h"

struct user{
	char userName[10];
	char pass[32];
	char fullName[60];
};

struct doc{
	char fullName[60];
	int id, dni;
	char phone[25];
};


int Nav(){
	
	int opc;
	
	printf("\n\t\tMODULO ADMINISTRACION");
	printf("\n\t\t---------------------");
	
	printf("\n\n\t\t1. Registrar profecionales");
	printf("\n\t\t2. Registrar usuario recepcionista");
	printf("\n\t\t3. Atenciones por profecional");
	printf("\n\t\t4. Ranking de profecionales por atenciones");
	printf("\n\t\t5. Ver usuarios");
	printf("\n\t\t6. Ver profesionales");
	printf("\n\t\t0. SALIR");
	
	printf("\n\n\tOPCION: ");
	scanf("%d", &opc);
	
	
	return opc;
	
}

void getUsers(FILE *userFile);
void setUser(FILE *userFile);
void setDoc(FILE *docFile);
void getDoc(FILE *docFile);
bool userExists(char userName[10], FILE *userFile);

main(){
	
	
	FILE *userFile; //crea un puntero para el archivo de usuarios
	FILE *docFile; //crea un puntero para el archivo de profesionales
	int navigation;
	user u;
	
	printf("\n\t\tCargando datos...");
	//abre el archivo en el caso de que exista, si no existe devuelve NULL
	userFile = fopen("usuarios.dat","r+b");
	docFile = fopen("profesionales.dat", "r+b");
	
	if(userFile == NULL){
		//crea el archivo usuarios.dat
		userFile = fopen("usuarios.dat", "w+b");
		if(userFile == NULL){
			printf("ERROR al crear el archivo usuarios.dat");
		}
		printf("\n\n\t\tUsuarios cargados!!");
	}else{
		printf("\n\n\t\tUsuarios cargados!!");
	}
	
	if(docFile == NULL){
		//crea el archivo profesionales.dat
		docFile = fopen("profesionales.dat", "w+b");
		if(docFile == NULL){
			printf("ERROR al crear el archivo profesionales.dat");
		}
		printf("\n\n\t\tProfesionales cargados!!");
	}else{
		printf("\n\n\t\tProfesionales cargados!!");
	}
	
	printf("\n\n\n");
	system("pause");
		
	do{
		system("cls");
		navigation = Nav();
		system("cls");
		
		switch(navigation){
			
			case 1:
				//carga doc(sin validacion)
				setDoc(docFile);
				break;
			case 2:
				//carga un nuevo usuario(sin validacion)
				setUser(userFile);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				getUsers(userFile);
				break;
			case 6:
				getDoc(docFile);
				break;
			case 0:
				printf("\n\n\n\t\t\tFin del programa...\n\n\n");
				exit(1);
			default:
				printf("\n\n\n\t\t\tOpcion incorrecta...\n\n");
				break;
			
		}
		
		printf("\n\n\n");
		system("pause");
		
	}while(navigation != 0);
	
	fclose(userFile);
	fclose(docFile);
	
}

void getUsers(FILE *userFile){

	fseek(userFile,0,SEEK_SET);
	user u;
	
	printf("\n\n\n\t\tLista de usuarios.\n");
	printf("\t\t------------------");
	
	fread(&u,sizeof(user),1,userFile);                                
	
	while(!feof(userFile)){
		
		printf("\n\n\tNombre: %s", u.fullName);
		printf("\n\tUsuario: %s", u.userName);
		printf("\n\tPassword: %s", u.pass);
		printf("\n\n\t------------");
		
		fread(&u,sizeof(u),1,userFile);
	}
	
}

void getDoc(FILE *docFile){

	fseek(docFile,0,SEEK_SET);
	doc d;
	
	printf("\n\n\n\t\tLista de profesionales.\n");
	printf("\t\t------------------");
	
	fread(&d,sizeof(doc),1,docFile);                                
	
	while(!feof(docFile)){
		
		printf("\n\n\tApellido y nombre: %s", d.fullName);
		printf("\n\tId: %d", d.id);
		printf("\n\tDni: %d", d.dni);
		printf("\n\tTelefono: %s", d.phone);
		printf("\n\n\t------------");
		
		fread(&d,sizeof(d),1,docFile);
	}
	
}

void setUser(FILE *userFile){

	user u;
	
	//posiciona el puntero al final del archivo para agregar un nuevo usuario
	fseek(userFile,0,SEEK_END);
	
	printf("\n\n\t\tCargar usuario.");
	printf("\n\t\t---------------");
	
	//el flushall borra el bufer de la escritura anterior 
	_flushall();
	printf("\n\n\tApellido y nombre: ");
	gets(u.fullName);
	
	while(strlen(u.fullName) < 6){ // verifica que el nombre al menos contenga 6 caracteres
		_flushall();
		printf("\n\tERROR: *Nombre demasiado corto.*");
		printf("\n\n\tIngrese nuevamente...");
		printf("\n\n\tApellido y nombre: ");
		gets(u.fullName);
	}
	
	printf("\n\n\n\n\n");
	system("pause");
	system("cls");
	printf("\n\n\t\tCargar usuario.");
	printf("\n\t\t---------------");
	printf("\n\n\tA TENER EN CUENTA PARA EL NOMBRE DE USUARIO:");
	printf("\n\n\t1- Debe tener entre 6 y 10 caracteres sin espacios.");
	printf("\n\t2- Debe comenzar con una letra minuscula.");
	printf("\n\t3- Debe tener al menos 2 letras mayusculas.");
	printf("\n\t4- Debe tener como maximo 3 numeros/simbolos.\n");
	//Ingresa un usuario, lo valida y en el caso de no validar vuelve a pedir el ingreso
	do{
		_flushall();
		printf("\n\tUsuario: ");
		gets(u.userName);
	}while(!authUser(u.userName) || !userExists(u.userName, userFile)); //La funcion authUser() devuelve un bool, si el usuario es valido devuelve el true
	
	printf("\n\n\n\n\n");
	system("pause");
	system("cls");
	printf("\n\n\t\tCargar usuario.");
	printf("\n\t\t---------------");
	printf("\n\n\tA TENER EN CUENTA PARA LA CONTRASENIA:");
	printf("\n\n\t1- Debe tener entre 6 y 32 caracteres.");
	printf("\n\t2- Debe contener al menos una letra mayuscula, una letra minuscula y un numero.");
	printf("\n\t3- No podra contener ningun caracter de puntuacion, ni acentos, ni espacios. \n\t   Solo caracteres alfanumericos.");
	printf("\n\t4- No debe tener mas de 3 caracteres numericos consecutivos.");
	printf("\n\t5- No debe tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas. \n\t   Este criterio es valido tanto para letras mayusculas, minusculas o combinacion de ambas.\n");
	do{ //Ingresa una contraseña, la valida y en el caso de no validar vuelve a pedir el ingreso
		_flushall();
		printf("\n\tContrasenia: ");
		gets(u.pass);	
	}while(!authPass(u.pass)); //La funcion authPass() devuelve un bool, si el usuario es valido devuelve el true
	
	/*
	escribe el archivo guardando un nuevo usuario parametros:
		variable de la estructura
		tamaño del dato(en este caso el mismo tamaaño de la estructura)
		cantidad de veces que se carga el archivo
		puntero del archivo
	*/
	fwrite(&u, sizeof(u), 1, userFile);
	
	printf("\n\n\t\tUsuario creado correctamente!!");
	
}

void setDoc(FILE *docFile){
	
	doc d;
	
	//posiciona el puntero al final del archivo para agregar un nuevo profesional
	fseek(docFile,0,SEEK_END);
	
	printf("\n\n\t\tCargar profesional.");
	printf("\n\t\t---------------");      
	
	//el flushall borra el bufer de la escritura anterior 
	_flushall();
	printf("\n\n\tApellido y nombre: ");
	gets(d.fullName);

	printf("\n\tId Profesional: ");
	scanf("%d", &d.id);

	printf("\n\tDni: ");
	scanf("%d", &d.dni);
	
	_flushall();
	printf("\n\tTelefono: ");
	gets(d.phone);
	
	/*
	escribe el archivo guardando un nuevo profesional parametros:
		variable de la estructura
		tamaño del dato(en este caso el mismo tamaño de la estructura)
		cantidad de veces que se carga el archivo
		puntero del archivo
	*/
	fwrite(&d, sizeof(d), 1, docFile);
	
	printf("\n\n\t\tProfesional cargado correctamente!!");
	
}

bool userExists(char userName[10], FILE *userFile){
	
	user u;
	
	fseek(userFile,0,SEEK_SET);
	
	fread(&u,sizeof(user),1,userFile);
	
	while(!feof(userFile)){
		if((strcmp(u.userName, userName)) == 0){
			printf("\n\tERROR: *El nombre de usuario ingresado ya pertenece a un usuario registrado!.*");
			printf("\n\tIngrese nuevamente...\n");
			return false;
		}
		fread(&u,sizeof(user),1,userFile);
	}
	
	return true;
}








