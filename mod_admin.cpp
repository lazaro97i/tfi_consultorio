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
	
	printf("\n\t\t\t\t\tMODULO ADMINISTRACION");
	printf("\n\t\t\t\t\t---------------------");
	
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

main(){
	
	
	FILE *userFile; //crea un puntero para el archivo de usuarios
	FILE *docFile; //crea un puntero para el archivo de profesionales
	int navigation;
	user u;
	
	printf("\nCargando datos...");
	//abre el archivo en el caso de que exista, si no existe devuelve NULL
	userFile = fopen("usuarios.dat","r+b");
	docFile = fopen("profesionales.dat", "r+b");
	
	if(userFile == NULL){
		//crea el archivo usuarios.dat
		userFile = fopen("usuarios.dat", "w+b");
		if(userFile == NULL){
			printf("ERROR al crear el archivo usuarios.dat");
		}
		printf("\n\nUsuarios cargados!!");
	}else{
		printf("\n\nUsuarios cargados!!");
	}
	
	if(docFile == NULL){
		//crea el archivo profesionales.dat
		docFile = fopen("profesionales.dat", "w+b");
		if(docFile == NULL){
			printf("ERROR al crear el archivo profesionales.dat");
		}
		printf("\n\nProfesionales cargados!!");
	}else{
		printf("\n\nProfesionales cargados!!");
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
	
	printf("\n\n\n\t\t\tLista de usuarios.\n");
	printf("\t\t\t------------------");
	
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
	
	printf("\n\n\n\t\t\tLista de profesionales.\n");
	printf("\t\t\t------------------");
	
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
	printf("\n\nNombre completo: ");
	gets(u.fullName);
	
	//Ingresa un usuario, lo valida y en el caso de no validar vuelve a pedir el ingreso
	do{
		_flushall();
		printf("\nUsuario: ");
		gets(u.userName);
	}while(!authUser(u.userName)); //La funcion authUser() devuelve un bool, si el usuario es valido devuelve el true
	
	_flushall();
	printf("\nContrasenia: ");
	gets(u.pass);
	
	/*
	escribe el archivo guardando un nuevo usuario parametros:
		variable de la estructura
		tamaño del dato(en este caso el mismo tamaaño de la estructura)
		cantidad de veces que se carga el archivo
		puntero del archivo
	*/
	fwrite(&u, sizeof(u), 1, userFile);
	
	printf("\n\n\t\tUsuario cargado correctamente!!");
	
}

void setDoc(FILE *docFile){
	
	doc d;
	
	//posiciona el puntero al final del archivo para agregar un nuevo profesional
	fseek(docFile,0,SEEK_END);
	
	printf("\n\n\t\tCargar profesional.");
	printf("\n\t\t---------------");      
	
	//el flushall borra el bufer de la escritura anterior 
	_flushall();
	printf("\n\nApellido y nombre: ");
	gets(d.fullName);

	printf("\nId Profesional: ");
	scanf("%d", &d.id);

	printf("\nDni: ");
	scanf("%d", &d.dni);
	
	_flushall();
	printf("\nTelefono: ");
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








