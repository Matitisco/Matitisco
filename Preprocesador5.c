#include<stdio.h>
#include <stdlib.h>

typedef enum {
    In,  // en comentario
    Out, //fuera de comentario
    Numeral
}state;

typedef enum{
    dobleBarra,
    multiRenglon
}comentario;




struct nlist { /* entrada de la tabla: */
    struct nlist *next; /* siguiente entrada en la cadena */
    char *name; /* nombre definido */
    char *defn; /* texto de reemplazo */
};


#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* tabla de apuntadores */  

unsigned hash(char *s)                                                              //Es un unsigned int la funcion 
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)                                                 // recorre el array y termina cuando el array llega a su ultima posicion '\0', con el ++ pasa de posicion el puntero
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)                                                               //duda: por que se declara como puntero pero despues no se pone el * para sacar el dato en strcmp
{
    struct nlist *np;
    for (np=hashtab[hash(s)]; np!=NULL; np=np->next)
    if (strcmp(s, np->name) == 0)                                                               //stcmp devuelve 0 si las 2 cadenas son iguales(strcmp compara todas las letras)
        return np; /* se encontró */                                                            //que la funcion retorne np
    return NULL; /* no se encontró */                                                           //que la funcion retorne NULL
}

struct nlist *lookup(char *);
char *strdup(char *);
/* install: coloca (name, defn) dentro de hashtab */

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* no fue encontrado */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab [hashval] = np;
    }  else /* ya está allí */
        free((void *) np->defn); /* libera la anterior defn */
    if (np->defn = strdup(defn) == NULL)
        return NULL;
    return np;
}


int main(){
    int aux;
    int c;
    struct nlist nodo;
    state s= Out;
    state palabra=Out;
    comentario z;
    while((c=getchar())!=EOF){
        switch(s){
            case Out:
                switch(c){
                    case '/':
                        c=getchar();
                        switch(c){
                            case '/':
                                s=In;
                                z=dobleBarra;
                                break;
                            case '*':
                                s=In;
                                z=multiRenglon;
                                break;
                            default:
                                putchar(c);
                                break;
                        }
                        break;

                    default:                    // no es comentario
                        if (c=='#'){
                            s = Numeral;
                        }
                        int i=0;
                        char arreglo[100];

                        switch(palabra){ //maquina de estados tp anterior
                            case In:   //en palabra
                                switch(c) {
                                    case ' ':
                                    case '\n':
                                    case '\t':
                                        s=Out;
                                        //nodo=lookup(*arreglo);
                                        i=0;
                                        break;
                                    default:
			                            arreglo[i]=c;
                                        i++;
                                }
                            case Out:  //fuera de palabra
                                switch(c){
                                    case ' ':
                                    case '\n':
                                    case '\t':
                                        break;
                                    default:
                                        s=In;
                                }
                            default:
                                break;

                        }


                        putchar(c);
                        break;
                }

                break;
                
            case In:
                switch(z){
                    case dobleBarra:
                        switch(c){
                            case '\n':
                                putchar(c);
                                s=Out;
                                break;
                            default:
                                break;
                        }
                        break;
                    case multiRenglon:
                        switch(c){
                            case '*':
                                c=getchar();
                                switch(c){
                                    case '/':
                                        s=Out;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                                }
                    default:
                        break;    
                }
                break;




            case Numeral: //Hubo un # antes. //Con esto ya se agrega un nombre y un valor a la tabla
                aux=c;
                if((aux=getchar()) == 'd' && (aux=getchar()) == 'e' && (aux=getchar()) == 'f' && (aux=getchar()) == 'i' && (aux=getchar()) == 'n' && (aux=getchar()) == 'e' && (aux=getchar()) == ' ' ){
                    int i;
                    char nombre[100];
                    char valor[100];
                    while(aux=getchar()!=' '){
                        nombre[i] =aux;
                        i++;
                    }
                    i=0;
                    while(aux=getchar()!=' '){
                        valor[i] =aux;
                        i++;
                    }
                    install(nombre,valor); //carga la info en la tabla
                }
                break;

            default:
                break;
        }
    }

    



    return 0;
}
