//Xiang LI
//Cédric BARRETEAU

#include "tp3.h"

// O(m)
void putValue(matrice_creuse m, int i, int j, int val){
    if(i<=m.Nlignes && j<=m.Ncolonnes){

            if(val!=0){

                    element* nouvelleCase=malloc(sizeof(element));
                    nouvelleCase->colonne=j;
                    nouvelleCase->valeur=val;
                    nouvelleCase->next=NULL; // pas forcément à la fin : cf plus bas
                    if(m.ptr[i]==NULL){ // si premier de la ligne
                      m.ptr[i]=nouvelleCase;
                    }else{ // si déjà des entrées
                        element* courant=m.ptr[i]->next;
                        element* pred=m.ptr[i];

                         if(m.ptr[i]->colonne==j){ //si le premier pointé est celui qu'on cherche
                            m.ptr[i]->valeur = val; // on le saute, puisqu'il vaut 0 maintenant
                            free(pred);
                            free(courant);
                            return;
                        }else if(m.ptr[i]->colonne>j){
                            nouvelleCase->next=m.ptr[i]->next;
                            m.ptr[i]->next=nouvelleCase->next;
                            free(pred);
                            free(courant);
                            return;
                        }else{
                            while(courant!=NULL && courant->colonne<=j){
                                if((courant->colonne)==j){
                                    courant->valeur = val;
                                    free(pred);
                                    free(courant);
                                    return;
                                }
                                pred=courant;
                                courant=courant->next;
                            }
                            nouvelleCase->next=pred->next;
                            pred->next=nouvelleCase;
                        }

                    }
            }else{
                    if(m.ptr[i]==NULL) // s'il n'y a rien sur la ligne et qu'on met un 0
                      return; // sortir (rien à faire)

                    element* courant=m.ptr[i]->next;
                    element* pre=m.ptr[i];

                     // il y a un élément sur la ligne, quelque part
                        if(m.ptr[i]->colonne==j){ //si le premier pointé est celui qu'on cherche
                            m.ptr[i]=m.ptr[i]->next; // on le saute, puisqu'il vaut 0 maintenant
                            free(pre);
                        }else{
                            while(courant!=NULL){
                                if((courant->colonne)==j){
                                    pre->next=courant->next;// on saute courant
                                    free(courant);
                                    return;
                                }
                                pre=courant;
                                courant=courant->next;
                           }
                        }
                        //à la sortie de boucle == pas de i, j dans la matrice, du coup on fait rien

            }
    }else{
        printf("erreur:dépasser la taille de matrice\n");
    }
}


// O(n*m²)
void constructMat(matrice_creuse *m, int t[N][M],int Nlig, int Ncol){
  int i, j;
  m->ptr=malloc(N*sizeof(liste_ligne)); // allocation des N lignes
  m->Nlignes=Nlig;
  m->Ncolonnes=Ncol;
  // mettre les next des premières cases à NULL
  for(i=0 ; i<N ; i++)
    m->ptr[i]=NULL;


    for(i=0 ; i<Nlig ; i++)
        for(j=0 ; j<Ncol ; j++)
          if(t[i][j]) // si !=0
            {
              // 1 création nouvelle case
              element *nouvelleCase=malloc(sizeof(element));

              // 2 initialisation de ses valeurs
                // i car on garde la colonne dans la case
              nouvelleCase->colonne=j;
              nouvelleCase->valeur=t[i][j];
              nouvelleCase->next=NULL;

              // 3 linker la précédente vers la nouvelle
                // cas première insertion pour cette ligne
             if(m->ptr[i]==NULL)
                m->ptr[i]=nouvelleCase;

                // cas déjà une case
              else{
                element* courant = m->ptr[i];
                while(courant->next!=NULL)
                    courant = courant->next;
                courant->next=nouvelleCase;
              }
            }
}

// O(n*m)
void lireFichier(matrice_creuse *m, char nomFichier[MAX]){
  // N lignes et M colonnes
    FILE *fp;
    char str[N+1];
    char* chunk=malloc(100*sizeof(int));
    int i=0, j;
    if( (fp=fopen(nomFichier,"r")) == NULL ){
        printf("Pas de fichier %s\n", nomFichier);
        exit(1);
    }
    // on cherche i et j
    while(fgets(str, N*M*20,fp)!=NULL){
      chunk=strtok(str,";");
      j=0;
      while(chunk!=NULL){
        chunk[sizeof(chunk)-1]='\0';
        chunk=strtok(NULL, ";");
        j++;
      }
      i++;
    }
    // on construit la matrice
    int tab[N][M];
    int x,y;
    for(x=0;x<N;x++)
      for(y=0;y<M;y++)
        tab[x][y]=1 ;

    constructMat(m, tab,i,j);
    //on la remplit
    rewind(fp);
    i=0;
    while(fgets(str, N*M*20,fp)!=NULL){
      chunk=strtok(str,";");
      j=0;
      while(chunk!=NULL){
        chunk[sizeof(chunk)-1]='\0';
        printf("%d ", atoi(chunk));
        putValue(*m, i,j,atoi(chunk));
        chunk=strtok(NULL, ";");
        j++;
      }
      i++;
      printf("\n");
    }
    fclose(fp);
}

// O(m*n)
void afficherMat(matrice_creuse m){
  int i,j;
  for (i=0;i<m.Nlignes;i++){
    element* courant=m.ptr[i];

    for (j=0;j<m.Ncolonnes;j++){
      if(courant!=NULL && courant->colonne==j){ // si valeur
        printf("%3d",courant->valeur);
        if(courant->next!=NULL) // on passe à la suivante s'il y en a une
          courant=courant->next;
      }
      else // si 0
        printf("  0");
    }
    printf("\n");
  }
  printf("\n\n\n");
}

// O(m)
int getValue(matrice_creuse m, int i, int j){
  if(i>m.Nlignes || j>m.Ncolonnes){
    printf("erreur:dépasser la taille de matrice\n");
    return errno;
  }
  element* courant=m.ptr[i];
  while(courant!=NULL && courant->colonne<=j){
  if((courant->colonne)==j)
    return courant->valeur;
  courant=courant->next;
  }
  return 0;
}



// O(n*m)
void addMat(matrice_creuse m1, matrice_creuse m2){
    if(m1.Nlignes == m2.Nlignes && m1.Ncolonnes == m2.Ncolonnes){
        int i,j;
        for(i=0;i<m1.Nlignes;i++)
            for(j=0;j<m1.Ncolonnes;j++){
                putValue(m1,i,j,getValue(m1,i,j)+getValue(m2,i,j));
            }
    }else{
        printf("erreur: ayant la taille differente");
    }
}

// O(n*m)
int nombreOctetsGagnes(matrice_creuse m1){
    // en français on écrit "donné" et "gagné" dans ce cas :) J'ai enlevé l'accent parce
    // que c'est mieux sans dans le code
    int sizePointeur, sizeElem,sizeMatrice,gagne, utilise;
    sizePointeur = sizeof(element*);
    sizeElem = sizeof(element);
    sizeMatrice = sizeof(int)*m1.Ncolonnes*m1.Nlignes;
    int i,j,n=0;
    for(i=0;i<m1.Nlignes;i++)
        for(j=0;j<m1.Ncolonnes;j++){
            if(getValue(m1,i,j))
                n++; // n compte les cases pleines, donc stockées
        }
   utilise = m1.Nlignes*sizePointeur // les pointeurs en début de ligne
            +n*sizeElem              // tous les elements de la matrice
            +2*sizeof(int);          // stockés dans matrice_creuse
   gagne = sizeMatrice - utilise;
   return gagne;
}
