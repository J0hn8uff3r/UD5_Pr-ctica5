#include <fcntl.h> //Define los flags para los modos de apertura de un fichero.
#include <stdio.h> //Permite hacer uso de las llamadas al sistema para el tratamiento de ficheros.
#include <string.h> //Para el tratamiento de cadenas.
// #include <dos.h> //Librería para poder utilizar la función delay y poder visualizar el tamaño de buffer de cada string leído

int main(int argc, char **argv) {
    int sourcef,destf;
    static int tam_buffer = 512; //Declaramos el tamaño del buffer que queremos leer cada vez que realicemos un read. El valor de este tamaño tendrás que decidirlo tú.
    const char* buffer[tam_buffer]; // Buffer de tamaño tam_buffer destinado a almacenar los datos leídos/escritos en la operación read/write.
    int bytesLeidos; //Almacena el valor de los bytes leídos en la operación read.

	
    if(argv[1] == NULL || argv[2] == NULL) {
        printf("Error, el número de argumentos es incorrecto\n");
        printf("Usar: %s <fichero passwd> <fichero backup>\n", argv[0]);
    } else {
		/*Debug
        printf("arg[0] es: %s\n", argv[0]);
        printf("arg[1] es: %s\n", argv[1]);
        printf("arg[2] es: %s\n", argv[2]);*/

        sourcef = open (argv[1], O_RDONLY, 666);//Sólo utilizamos O_RDONLY en lugar de O_CREAT|O_WRONLY para evitar crear el fichero origen si no existe
        printf("Descriptor de fichero origen: %d\n", sourcef);//Debug descriptor prueba ruta absoluta en Windows "%cd%\a.txt"

        //Comprobamos la existencia del fichero origen de argv[1]
        if(sourcef == -1) {
            printf("El fichero origen %s no existe y por tanto no puede ser leído\n", argv[1]);
            close(sourcef);
        } else {//El fichero origen existe, creamos el fichero destino
            destf = open (argv[2], O_CREAT|O_WRONLY, 644);//Creamos el fichero destino con permiso de escritura sólo para el propietario y de lectura para el resto
            if(destf == -1) { //Creación de fichero de destino incorrecta
                close(sourcef);
            } else { //Creación de fichero dump correcta y fichero origen existe
			int totalBytes;
			int suma=0;
                while ((bytesLeidos = read(sourcef,buffer,sizeof(buffer)))>0) {//Bucle para leer sourcef línea a línea
                    write (destf, buffer, bytesLeidos);
					printf("El tamaño del bloque leído es: %d\n", bytesLeidos);
					totalBytes+=bytesLeidos;
					suma++;//Número de iteraciones de acceso al fichero sourcef
					// delay(1000);//Delay para poder mostrar el tamaño de bloque leído en cada iteración
                }
				printf("El total de bytes leídos del fichero origen es: %d\nEl número de accesos al fichero origen es de %d\nEnhorabuena, la copia se ha realizado correctamente\n", totalBytes, suma);
				close(sourcef);//Cerramos ambos ficheros después de su uso
				close(destf);
            }
        }

    }
	return 0;
}