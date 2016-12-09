#include <string.h> //Para el tratamiento de cadenas.

int main(int argc, char **argv) {
	char comando[] = "ls -li ";
	
    if(argv[1] == NULL) {
        printf("Error, escribe la ruta.\n");
        printf("Ejemplo: %s /etc\n", argv[0]);
    } else {
		strcat(comando, argv[1]);//strcat concatena el valor de comando con el argumento del path que le pasamos al programa
		system(comando);//Hace una llamada al sistema, en este caso pedimos listar (-ls) los índices (-i) de los ficheros del path que le pasamos como argumento
    }
	return 0;
}
