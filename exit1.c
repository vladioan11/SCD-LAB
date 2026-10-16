#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

void mesaj_final(void)
{
	printf("Programul s-a incheiat. Resursele au fost eliberate.\n");
	
}
void mesaj_suplimentar(void){
	printf("Execut actiuni suplimentare la terminare.\n");
}
int main(void){
	long max_exit_functions=sysconf(_SC_ATEXIT_MAX);
	printf("Numar maxim functii atexit: %ld\n", max_exit_functions);

	if(atexit(mesaj_final)!=0){
		fprintf(stderr, "Eroare la inregistrarea functiei mesaj_final\n");
		exit(EXIT_FAILURE);
	}
	printf("Programul ruleaza, FUnctiile de exit sunt inregistrate.\n");
	if(getpid()%2==0){
		printf("Iesire normala.\n");
		return EXIT_SUCCESS;
		
	} else {
		printf("Iesire cu eroare.\n");
		exit(EXIT_FAILURE);
	}
}
