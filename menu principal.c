#include <stdio.h>
#include <string.h>
#include <conio.h> // Solo en Windows/Dev-C++

void controlarPanel(){
    printf("\n--- Nueva Eleccion ---\n");
}

int panelAdministrador(char admin[], char pasar[]){
    char nombre[] = "Administrador1";
    char contr[] = "123456";
    int op;

    if(strcmp(admin,nombre)==0 && strcmp(pasar,contr)==0){
        printf("\nAcceso concedido, presione enter para continuar\n");
        printf("\n1.- Eleccion nueva");
        printf("\n2.- Continuar con eleccion previa");
        printf("\n3.- Borrar voto ilegal");
        printf("\n4.- Eliminar Nombre de usuario");
        printf("\n5.- Generar reportes/actas");
        printf("\n6.- Auditoria de archivos");
        printf("\n7.- Administrador de usuarios");
        printf("\n8.- Resultado");
        printf("\n9.- Salir al menu principal\n");

        printf("\nEscoja una opcion: ");
        scanf("%d",&op);

        switch(op){
            case 1: controlarPanel(); break;
            case 2: printf("Continuando...\n"); break;
            case 3: printf("Borrando voto ilegal...\n"); break;
            default: printf("Opcion no valida\n"); break;
        }
        return 1; // acceso correcto
    } else if(strcmp(admin,nombre)!=0 && strcmp(pasar,contr)!=0){
        printf("\nNombre y contrasenia incorrectos\n");
        return 0;
    } else if(strcmp(admin,nombre)!=0){
        printf("\nNombre incorrecto\n");
        return 0;
    } else {
        printf("\nContrasenia incorrecta\n");
        return 0;
    }
}

int main(void){
    char pasar[20];
    char admin[20];
    char c;
    int i, ver;
    int opcion;

    do {
        printf("\n------------------Programa de elecciones---------------\n");
        printf("1.- Modulo de estudiantes\n");
        printf("2.- Modulo de administrador\n");
        printf("3.- Salir\n");
        printf("Escoja su opcion: ");
        scanf("%d",&opcion);
        while(getchar()!='\n'); // limpiar buffer

        switch(opcion){
            case 1:
                printf("Ingrese su edad: ");
                printf("Ingrese su numero de cedula: ");
                break;
            case 2:
                printf("Ingrese su nombre de usuario: ");
                fgets(admin,20,stdin);
                admin[strcspn(admin,"\n")] = '\0';

                printf("Ingrese su contrasenia: ");
                i=0;
                while((c=getch())!=13){ // Enter
                    pasar[i]=c;
                    i++;
                    printf("*");
                }
                pasar[i]='\0';

                ver=panelAdministrador(admin,pasar);
                break;
            case 3:
                printf("Programa finalizado\n");
                return 0;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while(opcion!=3);

    return 0;
}
