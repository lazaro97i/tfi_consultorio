#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>


struct user{
	char userName[10];
	char pass[10];
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
	printf("\n\t\t0. SALIR");
	
	printf("\n\n\tOPCION: ");
	scanf("%d", &opc);
	
	
	return opc;
	
}

void getUsers(FILE *archivo);
void setUser(FILE *archivo);
void setDoc(FILE *archivo);

main(){
	
	//crea un puntero para el archivo
	FILE *archivo;
	int navigation;
	
	printf("\nCargando datos...");
	//abre el archivo en el caso de que exista, si no existe devuelve NULL
	archivo = fopen("usuarios.dat","r+b");
	
	if(archivo == NULL){
		//crea el archivo usuarios.dat
		archivo = fopen("usuarios.dat", "w+b");
		if(archivo == NULL){
			printf("ERROR al crear el archivo usuarios.dat");
		}
		printf("\n\nDatos cargados!!");
	}else{
		printf("\n\nDatos cargados!!");
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
				setDoc(archivo);
				break;
			case 2:
				//carga un nuevo usuario(sin validacion)
				setUser(archivo);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				getUsers(archivo);
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
	
	fclose(archivo);
	
}

void getUsers(FILE *archivo){

	fseek(archivo,0,SEEK_SET);
	user u;
	
	printf("\n\n\n\t\t\tLista de usuarios.\n");
	printf("\t\t\t------------------");
	
	fread(&u,sizeof(user),1,archivo);
	
	while(!feof(archivo)){
		
		printf("\n\n\tNombre: %s", u.fullName);
		printf("\n\tUsuario: %s", u.userName);
		printf("\n\tPassword: %s", u.pass);
		printf("\n\n\t------------");
		
		fread(&u,sizeof(u),1,archivo);
	}
	
}

void setUser(FILE *archivo){

	user u;
	
	//posiciona el puntero al final del archivo para agregar un nuevo usuario
	fseek(archivo,0,SEEK_END);
	
	printf("\n\n\t\tCargar usuario.");
	printf("\n\t\t---------------");
	
	//el flushall borra el bufer de la escritura anterior 
	_flushall();
	printf("\n\nNombre completo: ");
	gets(u.fullName);

	_flushall();
	printf("\nUsuario: ");
	gets(u.userName);

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
	fwrite(&u, sizeof(u), 1, archivo);
	
	printf("\n\n\t\tUsuario cargado correctamente!!");
	
}

void setDoc(FILE *archivo){
	printf("Aca se carga el doctor");
}






