#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

// Estructuras para el manejo de elecciones y resultados
typedef struct {
    char nombre[50];
    int votos;
} Resultado;

typedef struct {
    char partido[50];
    char candidato[50]; 
    char cedula[15];
    char vicecandidato[50];
    char campana[50];
} Partido;

// Variables globales para el control del periodo y candidatos activos
char periodo[10] = " ";
Partido candidatosGlobales[5];

// Construye la ruta absoluta para los archivos
void rutaArchivo(char ruta[], char nombre[], int numero)
{
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\%s%d.txt", nombre, numero);
}

// Recupera el último periodo activo para evitar pérdida de progreso al reiniciar
void restaurarPeriodoActivo() {
    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");
    if (archivo != NULL) {
        char periodoGuardado[20];
        int num;
        while (fscanf(archivo, "%s %d", periodoGuardado, &num) == 2) {
            strcpy(periodo, periodoGuardado);
        }
        fclose(archivo);
    }
}

// Busca el siguiente índice disponible para no sobreescribir elecciones anteriores
int obtenerNuevoArchivo()
{
    FILE *archivo;
    char ruta[150];
    int numero = 0;

    while(1)
    {
        sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numero);
        archivo = fopen(ruta, "r");
        if(archivo == NULL)
            return numero; 
        fclose(archivo);
        numero++;
    }
}

// Cuenta la cantidad de procesos electorales registrados históricamente
int contarElecciones()
{
    FILE *archivo;
    char nombreArchivo[250];
    int contador = 0;
    int numero = 0;
    while (1)
    {
        sprintf(nombreArchivo, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numero);
        archivo = fopen(nombreArchivo, "r");
        if (archivo == NULL)
        {
            break; 
        }
        fclose(archivo);
        contador++;
        numero++;
    }
    return contador;
}

// Verifica si un código de periodo ya ha sido registrado previamente
int comprobarPeriodo(char periodoInput[])
{
    FILE *archivo;
    char periodoGuardado[10];
    int numeroArchivo;
    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");

    if(archivo == NULL)
    {
        return 0;
    }
    while(fscanf(archivo, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        if(strcmp(periodoGuardado, periodoInput) == 0)
        {
            fclose(archivo);
            return 1; // El periodo ya existe
        }
    }
    fclose(archivo);
    return 0; 
}

// Módulo para la creación y configuración de un nuevo proceso electoral
int controlarPanel(){
  int cantidad = 0, k = 0;
  char aut[20];
  Partido candidatos[5];
  char nombrar_Archivo[250];
  FILE *archivo;
  FILE *prueba;
  FILE *periodoArchivo;
  
  int cant;
  char periodoGuardado[20];
int numeroArchivo;

  cant = contarElecciones();

  while(1)
  {
    printf("\nIngrese el Periodo de elecciones: ");
    fgets(aut, 20, stdin);
    aut[strcspn(aut, "\n")] = '\0';
    
    // Validación de longitud del código del periodo
    if(strlen(aut) != 6)
    {
        printf("Error: Código de autentificación '%s' no válido. Debe contener 6 caracteres.\n", aut);
        printf("Ejemplo: 2026-A");
        continue;
    }
    if(comprobarPeriodo(aut))
    {
        printf("Error: El periodo '%s' ya se encuentra registrado. Intente con otro código.\n", aut);
        continue;
    }
    sprintf(nombrar_Archivo, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", cant);
    prueba = fopen(nombrar_Archivo, "r");
    if(prueba == NULL)
    {
      printf("\t\t/ / / / / Nueva elección / / / / /\n");
      while(cantidad <= 0 || cantidad > 5)
      {
        printf("Ingrese cuántos partidos quiere ingresar:");
        scanf("%d", &cantidad);
        while(getchar() != '\n');
        
        if(cantidad > 5)
        {
            printf("Error: No puede ingresar %d candidatos, el límite es 5.\n", cantidad);
        }
        else if(cantidad <= 0)
        {
            printf("Error: Debe ingresar al menos un candidato para crear una elección.\n");
        }
        else
        {
            k = cantidad;
            archivo = fopen(nombrar_Archivo, "w");
            if(archivo == NULL)
            {
                printf("Error crítico: No se pudo crear el archivo %s.\n", nombrar_Archivo);
                return 0;
            }
            
            // Captura de datos de partidos y candidatos
            for(int i = 0; i < cantidad; i++)
            {
                printf("Ingrese el nombre del partido #%d: ", i + 1);
                fgets(candidatos[i].partido, 50, stdin);
                candidatos[i].partido[strcspn(candidatos[i].partido, "\n")] = '\0';

                printf("Ingrese el nombre del candidato: ");
                fgets(candidatos[i].candidato, 50, stdin);
                candidatos[i].candidato[strcspn(candidatos[i].candidato, "\n")] = '\0';

                printf("Ingrese el nombre del vice-candidato: ");
                fgets(candidatos[i].vicecandidato, 50, stdin);
                candidatos[i].vicecandidato[strcspn(candidatos[i].vicecandidato, "\n")] = '\0';
            }
            printf("Elecciones creeadas con exito...");
            // Estructuración visual en el archivo de texto de candidatos
            fprintf(archivo, "==========================================================\n");
            fprintf(archivo, "               ELECCIONES ESTUDIANTILES\n");
            fprintf(archivo, "                 PERIODO: %s\n", aut);
            fprintf(archivo, "==========================================================\n\n");

            for(int i = 0; i < cantidad; i++)
            {
                fprintf(archivo, "Partido Político : %s\n", candidatos[i].partido);
                fprintf(archivo, "Número de Lista  : %d\n\n", i + 1);
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "CANDIDATO\n");
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "Nombre: %s\n", candidatos[i].candidato);
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "VICE-CANDIDATO\n");
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "Nombre: %s\n\n", candidatos[i].vicecandidato);
            }
            fclose(archivo);

            // Registro del nuevo periodo en el índice general
            periodoArchivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "a");
            if(periodoArchivo == NULL)
            {
                printf("Error: No se pudo guardar el periodo en periodos.txt.\n");
                return 0;
            } 
            fprintf(periodoArchivo, "%s %d\n", aut, cant);
            fclose(periodoArchivo);
            strcpy(periodo, aut);
            
            printf("Éxito: Elección del periodo '%s' creada. Actualmente hay un total de %d elecciones creadas.\n", periodo, cant + 1);
            
            // Selección de continuidad de flujo
            int opcion;
            printf("\n\nDesea continuar con el periodo actual?");
            printf("\n1. Si");
            printf("\n2. Elegir otro periodo");
            printf("\nOpcion: ");
            scanf("%d", &opcion);
            while(getchar() != '\n');
            if(opcion == 1)
            {
                return k;
            }
            else if(opcion == 2)
{
    FILE *Periodos;
    char periodoGuardado[20];
    int numeroArchivo;
    char nuevoPeriodo[10];

    Periodos = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");

    if(Periodos == NULL)
    {
        printf("No existen periodos registrados.\n");
        break;   // No uses return 0
    }

    printf("\n========================================\n");
    printf("      PERIODOS DISPONIBLES\n");
    printf("========================================\n");

    while(fscanf(Periodos, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        printf("Periodo: %s\n", periodoGuardado);
    }

    fclose(Periodos);

    printf("\nIngrese el periodo que desea utilizar: ");
    fgets(nuevoPeriodo, sizeof(nuevoPeriodo), stdin);
    nuevoPeriodo[strcspn(nuevoPeriodo, "\n")] = '\0';

    if(comprobarPeriodo(nuevoPeriodo))
    {
        strcpy(periodo, nuevoPeriodo);
        printf("Éxito: Periodo cambiado correctamente a '%s'.\n", periodo);
        return k;
    }
                else
                {
                    printf("Error: El periodo ingresado '%s' no existe.\n", nuevoPeriodo);
                    return 0;
                }
            }
            else
            {
                printf("Error: Opción inválida. Saliendo al menú.\n");
                return 0;
            }
        }
      }
    }
    else
    {
        fclose(prueba);
        cant++;
    }
  }
}

// Algoritmo matemático para validar la estructura de la cédula ecuatoriana
int validarCedulaEcuatoriana(const char *cedula) {
    if (cedula == NULL || strlen(cedula) == 0) {
        printf("Error: La cédula ingresada es nula o está vacía.\n");
        return 0;
    }
    if (strlen(cedula) != 10) {
        printf("Error: La cédula debe tener exactamente 10 dígitos. Ingresó %llu dígitos.\n", strlen(cedula));
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            printf("Error: La cédula debe contener exclusivamente números.\n");
            return 0;
        }
    }
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if ((provincia < 1 || provincia > 24) && provincia != 30) {
        printf("Error: Código de provincia '%02d' inválido (Debe ser entre 01-24 o 30).\n", provincia);
        return 0;
    }
    return 1;
}

// Comprueba si el estudiante ya cuenta con un registro de voto en el periodo actual
int yaVoto(const char *cedula, int numeroArchivo)
{
    FILE *archivo;
    char ruta[150];
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\cedulas%d.txt", numeroArchivo);
    archivo = fopen(ruta, "r");
    if(archivo == NULL)
    {
        return 0;
    }
    char cedulaGuardada[50];
    while(fscanf(archivo, "%49s", cedulaGuardada) == 1)
    {
        if(strcmp(cedulaGuardada, cedula) == 0)
        {
            fclose(archivo);
            return 1; // Ya votó
        }
    }
    fclose(archivo);
    return 0; 
}

// Obtiene el ID correlativo correspondiente a una cadena de texto de periodo
int obtenerArchivoPeriodo(char periodoInput[])
{
    FILE *archivo;
    char periodoGuardado[20];
    int numeroArchivo;
    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");
    if(archivo == NULL)
        return -1;
    while(fscanf(archivo, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        if(strcmp(periodoGuardado, periodoInput) == 0)
        {
            fclose(archivo);
            return numeroArchivo;
        }
    }
    fclose(archivo);
    return -1;
}

// Cruza la información del usuario con la base de datos de padron.txt
int verificarPadron(const char *cedula, char *nombreOut, int *edadOut) {
    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\padron.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se encontró el archivo base padron.txt.\n");
        return 0;
    }
    char linea[150];
    char cedulaPadron[50];
    char nombrePadron[100];
    int edadPadron;
    
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (sscanf(linea, "%49[^;];%99[^;];%d", cedulaPadron, nombrePadron, &edadPadron) == 3) {
            if (strcmp(cedulaPadron, cedula) == 0) {
                strcpy(nombreOut, nombrePadron);
                *edadOut = edadPadron;
                fclose(archivo);
                return 1; // Encontrado en el padrón
            }
        }
    }
    fclose(archivo);
    return 0; 
}

int contarCandidatos(int numeroArchivo);

// Interfaz para el sufragio del estudiante
int panelEstudiantes(int j, int cantidad)
{
    int votacion;
    char ruta[150];
    char cedula[50];
    char nombreEstudiante[100] = "";
    int edad = 18;
    char archivoCandidatos[150];

    int numeroArchivo = obtenerArchivoPeriodo(periodo);

    if(numeroArchivo == -1)
    {
        printf("No existe una elección activa.\n");
        return 1;
    }

    if(contarCandidatos(numeroArchivo) <= 0)
    {
        return 1;
    }

comp:

    sprintf(archivoCandidatos,
    "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt",
    numeroArchivo);

    FILE *archivo = fopen(archivoCandidatos, "r");

    if(archivo == NULL)
    {
        printf("No se encontró el archivo de candidatos.\n");
        return 1;
    }

    printf("\n");
    printf("=========================================================\n");
    printf("           SISTEMA ELECTORAL ESTUDIANTIL\n");
    printf("=========================================================\n");
    printf("                 MODULO DE VOTACION\n");
    printf("=========================================================\n\n");

    do
    {
        printf("Ingrese su numero de cedula: ");
        scanf("%49s", cedula);
        while(getchar()!='\n');

        printf("\n");

        if(validarCedulaEcuatoriana(cedula)==0)
        {
            continue;
        }

        if(verificarPadron(cedula,nombreEstudiante,&edad)==0)
        {
            printf("La cedula %s no consta en el padron electoral.\n\n",cedula);
            continue;
        }

        if(yaVoto(cedula,numeroArchivo))
        {
            printf("El usuario con cedula %s ya registro su voto.\n",cedula);
            fclose(archivo);
            return 2;
        }

        printf("---------------------------------------------------------\n");
        printf(" BIENVENIDO : %s\n",nombreEstudiante);
        printf(" EDAD       : %d años\n",edad);
        printf(" PERIODO    : %s\n",periodo);
        printf("---------------------------------------------------------\n\n");

        break;

    }while(1);

    char linea[100];
    cantidad = 0;

    printf("=============== LISTAS PARTICIPANTES ====================\n\n");

    while(fgets(linea,sizeof(linea),archivo)!=NULL)
    {
        printf("%s",linea);

        if(strncmp(linea,"Número de Lista",15)==0 ||
           strncmp(linea,"Numero de Lista",15)==0)
        {
            cantidad++;
        }
    }

    fclose(archivo);

    if(cantidad==0)
    {
        printf("No existen candidatos registrados.\n");
        return 1;
    }

    printf("\n=========================================================\n");
    printf("                 OPCIONES DE VOTACION\n");
    printf("=========================================================\n");
    printf("Listas disponibles : 1 - %d\n",cantidad);
    printf("Voto en blanco     : 0\n");
    printf("Voto nulo          : -1\n");
    printf("=========================================================\n");

    int resultado;
    int valido = 0;

    do
    {
        printf("Ingrese su voto: ");

        resultado = scanf("%d",&votacion);

        while(getchar()!='\n');

        if(resultado!=1)
        {
            printf("\nError: Debe ingresar únicamente numeros enteros.\n\n");
            continue;
        }

        if(votacion==-1 || votacion==0 || (votacion>=1 && votacion<=cantidad))
        {
            valido=1;
        }
        else
        {
            printf("\nError: Voto invalido.\n");
            printf("Debe ingresar un numero entre 1 y %d.\n",cantidad);
            printf("Tambien puede ingresar:\n");
            printf("0  -> Voto en blanco\n");
            printf("-1 -> Voto nulo\n\n");
        }

    }while(!valido);

    sprintf(ruta,
    "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d_%d.txt",
    numeroArchivo,j);

    FILE *fp = fopen(ruta,"w");

    if(fp==NULL)
    {
        printf("No se pudo registrar el voto.\n");
        return 1;
    }

    fprintf(fp,
    "Edad: %d\nCédula: %s\nVoto: %d\n",
    edad,cedula,votacion);

    fclose(fp);

    printf("\n=========================================================\n");
    printf("        SU VOTO HA SIDO REGISTRADO CON EXITO\n");
    printf("=========================================================\n");

    char rutaCedula[150];

    sprintf(rutaCedula,
    "C:\\Users\\carlo\\Desktop\\votaciones\\cedulas%d.txt",
    numeroArchivo);

    FILE *fc = fopen(rutaCedula,"a");

    if(fc!=NULL)
    {
        fprintf(fc,"%s\n",cedula);
        fclose(fc);
    }

    return 0;
}

// Escanea y cuantifica de manera independiente las transacciones de archivos de votos individuales
void contarResultados(int numeroArchivo, int *cont, int *cont1, int *cont2, int *cont3, int *cont4, int *blanco, int *nulo){
  char ruta[250];
  char votos[150];
  FILE *archivo;
  int voto = 0;
  *cont = 0;
  *cont1 = 0;
  *cont2 = 0;
  *cont3 = 0;
  *cont4 = 0;
  *blanco = 0;
  *nulo = 0;
  
  for (int i = 0; i < 1000; i++) {
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d_%d.txt", numeroArchivo, i);
    archivo = fopen(ruta, "r");
    if (archivo == NULL) {
      continue;
    }
    while (fgets(votos, sizeof(votos), archivo) != NULL){
      if (sscanf(votos, "Voto: %d", &voto) == 1) {
        if (voto == 0) {
          (*blanco)++;
        }
        else if (voto == -1) {
          (*nulo)++;
        }
        else if (voto == 1) {
          (*cont)++;
        }
        else if (voto == 2) {
          (*cont1)++;
        }
        else if (voto == 3) {
          (*cont2)++;
        }
        else if (voto == 4) {
          (*cont3)++;
        }
        else if (voto == 5) {
          (*cont4)++;
        }
      }
    }
    fclose(archivo);
  }
}

// Aplica el ordenamiento por método de inserción directa para desplegar ganadores
void resultadosFinales(int numeroArchivo,int cantidad,int *cont,int *cont1,int *cont2,int *cont3,int *cont4,int *blanco,int *nulo,int *a,float *total,Resultado acta[])
{
    Resultado res[5];

    FILE *archivo;
    char linea[100];
    char ruta[150];

    int x=0;

    *a=0;

    if(cantidad>5)
        cantidad=5;

    sprintf(ruta,
    "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt",numeroArchivo);

    archivo=fopen(ruta,"r");

    if(archivo==NULL)
    {
        printf("No existe el archivo de candidatos.\n");
        return;
    }

    
    while(x<cantidad && fgets(linea,sizeof(linea),archivo)!=NULL)
    {
      if(strncmp(linea,"Nombre",6)==0)
        {
            char *p=strchr(linea,':');

            if(p!=NULL)
            {
                p++;

                while(*p==' ')
                    p++;

                p[strcspn(p,"\r\n")]='\0';

                strcpy(res[x].nombre,p);

                switch(x)
                {
                    case 0:
                        res[x].votos=*cont;
                        break;

                    case 1:
                        res[x].votos=*cont1;
                        break;

                    case 2:
                        res[x].votos=*cont2;
                        break;

                    case 3:
                        res[x].votos=*cont3;
                        break;

                    case 4:
                        res[x].votos=*cont4;
                        break;
                }

                x++;
            }
        }
    }

    fclose(archivo);

    for(int i=1;i<x;i++)
    {

        Resultado actual=res[i];

        int j=i-1;
        while(j>=0 && res[j].votos<actual.votos)
        {
            res[j+1]=res[j];
            j--;
        }
        res[j+1]=actual;

    }


    printf("\n===== RESULTADOS =====\n");

    for(int i=0;i<x;i++)
    {

        printf("Candidato %d: %s -> %d votos\n",i+1,res[i].nombre,res[i].votos);

        *a += res[i].votos;
        acta[i]=res[i];

    }



    if((*a+*blanco+*nulo)>0)
    {
        *total=(float)res[0].votos/
        (*a+*blanco+*nulo);
    }
    else
    {
        *total=0;
    }



    printf("\nVotos en blanco: %d\n",*blanco);

    printf("Votos nulos: %d\n",*nulo);



    if(x>0)
    {
        printf("El ganador es %s con %d votos\n",res[0].nombre,res[0].votos);
    }


    printf("Margen del ganador: %.2f %%\n",*total*100);
}

// Cuenta la cantidad de líneas dentro del archivo para calcular candidatos reales
int contarCandidatos(int numeroArchivo){
  FILE *archivo;
  char linea[100];
  char ruta[150];
  int contador = 0;
  sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
  archivo = fopen(ruta, "r");
  if (archivo == NULL){
    return 0;
  }
  while (fgets(linea, 100, archivo) != NULL){
    contador++;
  }
  fclose(archivo);
  return contador;
}

// Generación formal y formateada del acta final de escrutinio

  void generarActa()
  {
    FILE *archivoCandidatos;
    char ruta[150];

    int numeroArchivo=obtenerArchivoPeriodo(periodo);

    if(numeroArchivo==-1)
    {
        printf("No existe un periodo seleccionado.\n");
        return;
    }
    int cantidad=0;

    FILE *archivo;
    char rutaCandidatos[150];
    char linea[100];


    sprintf(rutaCandidatos,
    "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt",
    numeroArchivo);


    archivoCandidatos=fopen(rutaCandidatos,"r");


    if(archivoCandidatos==NULL)
    {
        printf("No se encontro el archivo de candidatos.\n");
        return;
    }


    while(fgets(linea,sizeof(linea),archivoCandidatos)!=NULL)
    {
        if(strncmp(linea,"Partido Político :",17)==0)
        {
            cantidad++;
        }
    }


    fclose(archivoCandidatos);

    int cont=0,cont1=0,cont2=0,cont3=0,cont4=0;
    int blanco=0,nulo=0;

    int a=0;
    float total=0;

    Resultado acta[5];

    contarResultados(numeroArchivo,&cont,&cont1,&cont2,&cont3,&cont4,&blanco,&nulo);
    resultadosFinales(numeroArchivo,cantidad,&cont,&cont1,&cont2,&cont3,&cont4,&blanco,&nulo,&a,&total,acta);
    sprintf(ruta,"C:\\Users\\carlo\\Desktop\\votaciones\\acta%d.txt",numeroArchivo);

    archivo=fopen(ruta,"w");

    if(archivo==NULL)
    {
        printf("No se pudo generar el acta.\n");
        return;
    }

    fprintf(archivo,"============================================================\n");
    fprintf(archivo,"              ACTA OFICIAL DE RESULTADOS ELECTORALES\n");
    fprintf(archivo,"============================================================\n\n");
    fprintf(archivo,"INSTITUCION: ELECCIONES ESTUDIANTILES\n");

    fprintf(archivo,"PERIODO ELECTORAL: %s\n",
    periodo);
    fprintf(archivo,"CODIGO DE ELECCION: %d\n\n",numeroArchivo);

    fprintf(archivo,"------------------------------------------------------------\n");
    fprintf(archivo, "                     RESULTADOS\n");
    fprintf(archivo,"------------------------------------------------------------\n\n");


    fprintf(archivo,"%-5s %-35s %-10s\n","N°","CANDIDATO","VOTOS");

    fprintf(archivo,"------------------------------------------------------------\n");

    for(int i=0;i<cantidad;i++)
    {
        fprintf(archivo,"%-5d %-35s %-10d\n",i+1, acta[i].nombre,acta[i].votos);
    }
    fprintf(archivo,"\n------------------------------------------------------------\n");
    fprintf(archivo,"RESUMEN DE VOTACION\n");
    fprintf(archivo,"------------------------------------------------------------\n\n");

    fprintf(archivo,"Votos validos : %d\n",a);
    fprintf(archivo,"Votos blancos : %d\n",blanco);

    fprintf(archivo,"Votos nulos   : %d\n\n",nulo);
    fprintf(archivo,"TOTAL DE VOTOS EMITIDOS: %d\n", a+blanco+nulo);
    fprintf(archivo,"PORCENTAJE DEL GANADOR: %.2f %%\n\n",total*100);
    fprintf(archivo,"------------------------------------------------------------\n");
    fprintf(archivo,"GANADOR DE LA ELECCION\n");
    fprintf(archivo,"------------------------------------------------------------\n\n");
    fprintf(archivo,"Candidato ganador: %s\n",acta[0].nombre);
    fprintf(archivo,"Cantidad de votos: %d\n\n",acta[0].votos);
    fprintf(archivo,"============================================================\n");
    fprintf(archivo,"                  VALIDACION DEL ACTA\n");
    fprintf(archivo,"============================================================\n\n");
    fprintf(archivo,"Periodo verificado: %s\n",periodo);
    fprintf(archivo,"Archivo electoral: candidatos%d.txt\n",numeroArchivo);
    fprintf(archivo,"Estado: ACTA GENERADA CORRECTAMENTE\n\n");

    fprintf(archivo,"\n============================================================\n");

    fclose(archivo);

    printf("\nActa generada correctamente: acta%d.txt\n",numeroArchivo);
}

// Verifica la consistencia lógica de los archivos del periodo electoral activo
int controlArchivos()
{
    FILE *archivo;
    char periodoGuardado[20];
    int numeroArchivo;
    char ruta[150];

    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");
    if(archivo == NULL)
    {
        printf("Aviso: No existen elecciones registradas en el sistema.\n");
        return 0;
    }
    while(fscanf(archivo, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
        FILE *candidatos = fopen(ruta, "r");
        if(candidatos == NULL)
        {
            printf("Error: falta archivo de candidatos del periodo %s\n", periodoGuardado);
            fclose(archivo);
            return 0;
        }
        fclose(candidatos);
    }
    fclose(archivo);
    return 1;
}

// Búsqueda binaria iterativa y recursiva para encontrar cédulas
int busquedaBinariaRecursiva(char arr[][50], int inicio, int fin, const char *objetivo) {
    if (inicio > fin) {
        return -1; 
    }
    int medio = inicio + (fin - inicio) / 2;
    int comparacion = strcmp(arr[medio], objetivo);
    
    if (comparacion == 0) {
        return medio; 
    }
    if (comparacion > 0) {
        return busquedaBinariaRecursiva(arr, inicio, medio - 1, objetivo);
    }
    return busquedaBinariaRecursiva(arr, medio + 1, fin, objetivo);
}

// Interfaz administrativa para desbloquear o visualizar usuarios infractores/votantes
void administrarUsuarios() {
    int opcion_admin;
    int numeroArchivo = obtenerArchivoPeriodo(periodo);
    if(numeroArchivo == -1)
    {
        printf("Error: No existe un periodo seleccionado para administrar.\n");
        return;
    }
    char ruta[150];
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\cedulas%d.txt", numeroArchivo);
    do {
        printf("\t\t1.- Ver lista de usuarios que ya votaron\n");
        printf("\t\t2.- Buscar y banear usuario\n");
        printf("\t\t3.- Regresar al panel principal\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion_admin);
        while(getchar() != '\n');
        
        if (opcion_admin == 1) {
            FILE *archivo = fopen(ruta, "r");
            if (!archivo) {
                printf("\nAviso: Aún no hay registros de usuarios que hayan votado.\n");
            } else {
                char cedulaGuardada[50];
                int count = 0;
                printf("\n--- Lista de Cédulas Registradas ---\n");
                while (fscanf(archivo, "%49s", cedulaGuardada) == 1) {
                    count++;
                    printf("%d. %s\n", count, cedulaGuardada);
                }
                if (count == 0) {
                    printf("La lista está vacía.\n");
                }
                fclose(archivo);
            }
        } 
        else if (opcion_admin == 2) {
            FILE *archivo = fopen(ruta, "r");
            if (!archivo) {
                printf("\n Error: No hay registros de usuarios.\n");
                continue;
            }
            char arregloCedulas[200][50];
            int n = 0;
            while (fscanf(archivo, "%49s", arregloCedulas[n]) == 1) {
                n++;
            }
            fclose(archivo);
            if (n == 0) {
                printf("\n -> La lista de votantes está vacía.\n");
                continue;
            }
            
            char temporal[50];
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp(arregloCedulas[j], arregloCedulas[j+1]) > 0) {
                        strcpy(temporal, arregloCedulas[j]);
                        strcpy(arregloCedulas[j], arregloCedulas[j+1]);
                        strcpy(arregloCedulas[j+1], temporal);
                    }
                }
            }
            char cedulaEliminar[50];
            printf("\nIngrese la cédula del usuario que desea desbanear: ");
            scanf("%49s", cedulaEliminar);
            while(getchar() != '\n');
            int indice = busquedaBinariaRecursiva(arregloCedulas, 0, n - 1, cedulaEliminar);
            if (indice != -1) {
                for (int i = indice; i < n - 1; i++) {
                    strcpy(arregloCedulas[i], arregloCedulas[i+1]);
                }
                n--;
                archivo = fopen(ruta, "w");
                if (archivo) {
                  for (int i = 0; i < n; i++) {
                        fprintf(archivo, "%s\n", arregloCedulas[i]);
                    }
                    fclose(archivo);
                }
                printf("Éxito: El usuario con cédula %s fue eliminado de la lista negra y puede votar.\n", cedulaEliminar);
            } 
            else {
                printf("Error: La cédula %s no se encontró en los registros de votación.\n", cedulaEliminar);
            }
        }
        else if (opcion_admin != 3) {
            printf("\nError: Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion_admin != 3);
}

// Cuenta la cantidad transaccional física de archivos *.txt de votos para calcular j
int contarVotosExistentes(int numeroArchivo) {
    char ruta[200];
    int i = 0;
    FILE *archivo;
    while (1) {
        snprintf(ruta, sizeof(ruta), "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d_%d.txt", numeroArchivo, i);
        archivo = fopen(ruta, "r");
        if (archivo == NULL) {
            return i; 
        }
        fclose(archivo);
        i++;
    }
}

// Suma el valor ASCII de los caracteres para la firma criptográfica base de integridad
void integridadArchivos(int *suma)
{
    FILE *archivo;
    int linea;
    char ruta[150];
    int numeroArchivo = obtenerArchivoPeriodo(periodo);
    *suma = 0;
    if(numeroArchivo == -1)
    {
        printf("Error: No existe un periodo seleccionado.\n");
        return;
    }
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
    archivo = fopen(ruta, "r");
    if(archivo == NULL)
    {
        printf("Error: No se encontró el archivo de candidatos.\n");
        return;
    }
    while((linea = fgetc(archivo)) != EOF) {
        *suma += linea;
    }
    fclose(archivo);
}

// Módulo de control que valida si los archivos han sufrido alteraciones externas maliciosas
void verificarIntegridad()
{
    FILE *archivo;
    FILE *integridad;
    char nombre[50];
    char rutaIntegridad[150];
    char rutaAuditoria[150];
    int integr1 = 0;
    int integr2 = 0;
    time_t tiempo;
    struct tm *fechaHora;
    char fecha[50];
    char aud[50];

    int numeroArchivo = obtenerArchivoPeriodo(periodo);
    if(numeroArchivo == -1)
    {
        printf("Error: No existe un periodo seleccionado.\n");
        return;
    }

    sprintf(nombre, "candidatos%d.txt", numeroArchivo);
    sprintf(rutaIntegridad, "C:\\Users\\carlo\\Desktop\\votaciones\\integridad%d.txt", numeroArchivo);
    sprintf(rutaAuditoria, "C:\\Users\\carlo\\Desktop\\votaciones\\auditoria%d.txt", numeroArchivo);

    integridad = fopen(rutaIntegridad, "r");
    if(integridad == NULL)
    {
        integridadArchivos(&integr1);
        tiempo = time(NULL);
        fechaHora = localtime(&tiempo);
        strftime(aud, sizeof(aud), "%d/%m/%Y %H:%M:%S", fechaHora);
        integridad = fopen(rutaIntegridad, "w");

        if(integridad == NULL)
        {
            printf("Error crítico: No se pudo crear el archivo de integridad.\n");
            return;
        }
        fprintf(integridad, "%d\n%s", integr1, aud);
        fclose(integridad);
        printf("Éxito: Archivo de integridad creado.\n");
        return;
    }

    fscanf(integridad, "%d", &integr1);
    fgetc(integridad); 
    fgets(aud, sizeof(aud), integridad);
    fclose(integridad);

    integridadArchivos(&integr2);
    archivo = fopen(rutaAuditoria, "w");
    if(archivo == NULL){
        printf("Error crítico: No se pudo crear el archivo de auditoria.\n");
        return;
    }
    fprintf(archivo, "--- AUDITORIA DE CANDIDATOS ---\n");
    fprintf(archivo, "Archivo revisado: %s\n", nombre);
    fprintf(archivo, "Fecha de integridad inicial: %s\n", aud);
    fprintf(archivo, "Integridad inicial: %d\n", integr1);
    fprintf(archivo, "Integridad actual: %d\n", integr2);
    
    printf("--- AUDITORIA DE CANDIDATOS ---\n");
    printf("Archivo revisado: %s\n", nombre);
    printf("Fecha de integridad inicial: %s", aud);
    printf("Integridad inicial: %d\n", integr1);
    printf("Integridad actual: %d\n", integr2);
    
    if(integr1 == integr2){
        fprintf(archivo, "Estado: Archivo de candidatos íntegro.\n");
        printf("Estado: Archivo de candidatos íntegro.\n");
    }
    else {
        fprintf(archivo, "Estado: ALERTA. Archivo modificado externamente.\n");
        printf("Estado: ALERTA. Archivo modificado externamente.\n");
    }
    tiempo = time(NULL);
    fechaHora = localtime(&tiempo);
    strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", fechaHora);
    fprintf(archivo, "Fecha y hora de auditoria: %s\n", fecha);
    printf("Fecha y hora de auditoria: %s\n", fecha);
    fprintf(archivo, "-----------------------------\n");
    fclose(archivo);
}

// Menú y enrutamiento interno de privilegios
int panelAdministrador(char admin[], char pasar[]){
  char nombre[] = "Administrador1";
  char contr[] = "123456";
  char supNombre[] = "Supervisor1";
  char supContr[] = "654321";
  char elec;
  int op, comp = 0;
  int cont = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, a = 0, var = 0;
  float total = 0;
  Resultado acta[5];
  int blanco = 0;
  int nulo = 0;
  int numeroArchivo = obtenerArchivoPeriodo(periodo);
  int dif = 0;
  int var1;
  int resultado = 0;
  if(numeroArchivo != -1)
  {
      dif = contarCandidatos(numeroArchivo);
  }

  if(strcmp(admin, nombre) == 0 && strcmp(pasar, contr) == 0){
      printf("\nAcceso concedido, presione enter para continuar...\n");
      do {
          printf("\n\t\t\tPANEL DE ADMINISTRADOR");
          printf("\n\v\t\t1.-Elección nueva");
          printf("\n\t\t2.-Generar reportes/actas");
          printf("\n\t\t3.-Auditoría de archivos");
          printf("\n\t\t4.-Administrador de usuarios");
          printf("\n\t\t5.-Resultado");
          printf("\n\t\t6.-Salir al menú principal");
          printf("\n\nIngrese su opción:");
          scanf("%d", &op);
          while(getchar() != '\n'); 
          
          switch(op)
          {
            case 1:
              comp = controlArchivos();
if (comp == 1) {
    printf("Aviso: Ya existe una eleccion activa, no se puede crear una nueva\n");
    
    char elec;
    int entrada_valida = 0;

    do {
        printf("¿Quiere crear una nueva eleccion si (s), no(n)?\n");
        printf("Ingrese su eleccion s o n: ");
        
        // Leemos el caracter (el espacio antes de %c ayuda a ignorar espacios/saltos previos)
        int resultado_scanf = scanf(" %c", &elec);
        
        // Limpiamos el búfer inmediatamente después del scanf
        while (getchar() != '\n');

        if (resultado_scanf == 1) {
            // Comprobamos si es una de las opciones válidas
            if (elec == 's' || elec == 'S' || elec == 'n' || elec == 'N') {
                entrada_valida = 1; // Entrada correcta, salimos del ciclo
            } else {
                printf("\n[Error] El caracter '%c' no es valido. Solo se permite 's' o 'n'.\n\n", elec);
            }
        } else {
            printf("\n[Error] Entrada no valida. Intente de nuevo.\n\n");
        }

    } while (!entrada_valida);

    // Evaluamos la opción seleccionada por el usuario
    if (elec == 's' || elec == 'S') {
        controlarPanel();
    } else if (elec == 'n' || elec == 'N') {
        printf("Accion cancelada. No se creara una nueva eleccion.\n");
    }

} else {
    controlarPanel();
}
              break;
            case 2:
             {
    FILE *archivo;
    char periodoGuardado[20];
    int numeroArchivo;
    char periodoIngresado[10];

    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");

    if (archivo == NULL)
    {
        printf("No existen periodos registrados.\n");
        break;
    }

    printf("\n===== PERIODOS DISPONIBLES =====\n");

    while (fscanf(archivo, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        printf("Periodo: %s\n", periodoGuardado);
    }

    fclose(archivo);

    printf("\nIngrese el periodo del cual desea generar el acta: ");
    fgets(periodoIngresado, sizeof(periodoIngresado), stdin);
    periodoIngresado[strcspn(periodoIngresado, "\n")] = '\0';

    if (comprobarPeriodo(periodoIngresado))
    {
        strcpy(periodo, periodoIngresado);
        generarActa();
    }
    else
    {
        printf("Error: El periodo '%s' no existe.\n", periodoIngresado);
    }

    break;
}

            case 3:
            
              do {
    printf("¿Desea realizar la auditoria del archivo de registros de campaña?\n");
    printf("1. Si\n");
    printf("0. No\n");
    printf("Ingrese una opcion: ");

    resultado = scanf("%d", &var1);

    while (getchar() != '\n');

    if (resultado != 1) {
        printf("\n[Error] Debe ingresar solo numeros.\n\n");
    } else if (var1 != 0 && var1 != 1) {
        printf("\n[Error] Solo se permite ingresar 0 o 1.\n\n");
    }

} while (resultado != 1 || (var1 != 0 && var1 != 1));

if (var1 == 1) {
    verificarIntegridad();
} else {
    printf("Auditoria omitida. Continuando con el programa...\n");
}
        
              break;
            case 4:
              administrarUsuarios();
              break;
            case 5:
              numeroArchivo = obtenerArchivoPeriodo(periodo);
              if(numeroArchivo != -1) {
                  dif = contarCandidatos(numeroArchivo);
              }
              contarResultados(numeroArchivo, &cont, &cont1, &cont2, &cont3, &cont4, &blanco, &nulo);
              resultadosFinales(numeroArchivo, dif, &cont, &cont1, &cont2, &cont3, &cont4, &blanco, &nulo, &a, &total, acta);
              break;
            case 6:
              break;
            default:
              printf("Error: Opción %d no válida\n", op);
              break;
          }
      } while(op != 6);
      return 0;
      
  } else if(strcmp(admin, supNombre) == 0 && strcmp(pasar, supContr) == 0){
      printf("\nAcceso concedido...\n");
      do {
          printf("\n\t\t\tPANEL DE SUPERVISOR");
          printf("\n\v\t\t1.-Generar reportes/actas");
          printf("\n\t\t2.-Auditoría de archivos");
          printf("\n\t\t3.-Salir al menú principal");
          printf("\n\nIngrese su opción:");
          scanf("%d", &op);
          while(getchar() != '\n'); 
          
          switch(op)
          {
            case 1:
              generarActa();
              break;
            case 2:
              verificarIntegridad();
              break;
            case 3:
              break;
            default:
              printf("Error: Opción %d no válida\n", op);
              break;
          }
      } while(op != 3);
      return 0;
      
  } else if(strcmp(admin, nombre) != 0 && strcmp(admin, supNombre) != 0 && strcmp(pasar, contr) != 0){
    printf("\nError: Nombre y contraseña incorrectos\n");
    return 0;
  } else if(strcmp(admin, nombre) != 0 && strcmp(admin, supNombre) != 0) {
    printf("\nError: Nombre de usuario incorrecto\n");
    return 0;
  } else {
    printf("\nError: Contraseña incorrecta\n");
    return 0;
  } 
}

// Crea la carpeta contenedora e inicializa el padrón electoral en su ruta original
void inicializarPadronAutomatico() {
    CreateDirectory("C:\\Users\\carlo\\Desktop\\votaciones", NULL);
    
    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\padron.txt", "r");
    if (archivo == NULL) {
        archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\padron.txt", "w");
        if (archivo != NULL) {
            fprintf(archivo, "1713575974;Juan Perez;19\n");
            fprintf(archivo, "0926574136;Maria Flores;21\n");
            fprintf(archivo, "1003463121;Carlos Andrade;20\n");
            fprintf(archivo, "0104104279;Ana Belen Cueva;22\n");
            fprintf(archivo, "1104323281;Luis Miguel Toapanta;18\n");
            fprintf(archivo, "1804253164;Diana Carolina Ortiz;23\n");
            fprintf(archivo, "0704025178;Kevin Alejandro Rios;20\n");
            fprintf(archivo, "1311746244;Estefania Nicole Mendoza;24\n");
            fprintf(archivo, "2400124474;Christian David Torres;19\n");
            fprintf(archivo, "3050123456;Sofia Valentina Ruiz;22\n");
            fclose(archivo);
        }
    } else {
        fclose(archivo);
    }
}

int main(void){
  SetConsoleOutputCP(65001);
   char pasar[20];
   char admin[20];
   char c;
   int i = 0, ver, dif = 0;
   
   inicializarPadronAutomatico();
   restaurarPeriodoActivo(); // Función clave añadida para solucionar la pérdida de memoria en reinicios

   int numeroArchivo = obtenerArchivoPeriodo(periodo);
   int j = contarVotosExistentes(numeroArchivo); 
   int opcion = 0;

 while(opcion != 3){
   printf("\n\v\t------------------Programa de elecciones---------------\n");
   printf("Ingrese su solicitud\n");
   printf("\v\t\t1.- Módulo de estudiantes\n");
   printf("\t\t2.- Gestión\n");
   printf("\t\t3.- Salir\n\n");
   printf("Escoja su opcion: ");
   scanf("%d", &opcion);
   while(getchar() != '\n');
   
   switch (opcion){ 
   case 2:
     printf("Ingrese: (Administrador1) o (Supervisor1) dependiendo del rol que le sea asignado\n");
     printf("Ingrese su nombre de usuario: ");
     fgets(admin, 20, stdin);
     admin[strcspn(admin, "\n")] = '\0';
     printf("Ingrese su contraseña: ");
     i = 0;
     
     while((c = getch()) != 13)  {
        pasar[i] = c;
        i++;
        printf("*");
     }
     pasar[i] = '\0';
     ver = panelAdministrador(admin, pasar);
     if (ver > 0) {
        dif = ver;
     } else {
        dif = 0;
     }
     break;

   case 1:
     numeroArchivo = obtenerArchivoPeriodo(periodo);
     j = contarVotosExistentes(numeroArchivo);
     ver = panelEstudiantes(j, dif);
     if(ver == 0){
       j++; 
     }
     else if(ver == 1){
       printf("Error: No existe una elección activa, reinicie el programa en Gestión.\n");
     }
     break;
   case 3:
     printf("--------------------\n");
     printf("Programa finalizado con éxito.\n");
     return 1;
     break;
   default:
     printf("Error: Opcion %d no valida\n", opcion);
     break;
   } 
  }
   return 0; 
}
