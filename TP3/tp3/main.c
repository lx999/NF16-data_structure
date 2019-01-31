//Xiang LI
//Cédric BARRETEAU
#include "tp3.h"

int main(int argc, char const *argv[]) {

  int choix, col, lignes, i, j, tab[N][M];
  matrice_creuse m, m2;
  int construite=0;
  char *fichier=malloc(MAX*sizeof(char));

  for(i=0; i<N; i++)
    for(j=0; j<M; j++){
      if((i-j)%2==0)
        tab[i][j]=0;
      else
        tab[i][j]=0;
    }

  while(1){
    printf("\n\nMENU\n____\n\nQue voulez-vous faire ?\n");
    printf("1 Transformer une matrice\n"); // m
    printf("2 Lire une matrice à partir d'un fichier\n"); // m
    printf("3 Afficher une matrice creuse\n"); // m
    printf("4 Additionner deux matrices creuses\n"); // m + rentrée
    printf("5 Calculer le gain pour une matrice donnée\n"); // m
    printf("6 Quitter\n\n");

    scanf("%d", &choix);
    switch(choix){
      case 1:
        printf("Combien voulez-vous de lignes ?\n");
        scanf("%d", &lignes);
        printf("Combien voulez-vous de colonnes ?\n");
        scanf("%d", &col);
        if(lignes > N || col > M ){
            printf("vous avez dépassé la taille max\n");
        }else{
            constructMat(&m, tab, lignes, col);
            construite=1;
            printf("\n\nMatrice enregistrée");
        }
        break;

      case 2:
        printf("Quel fichier voulez-vous lire ? ");
        scanf("%s", fichier);
        lireFichier(&m,fichier);
        construite=1;
        break;
      case 3:
        if(construite){
          printf("Affichage de la matrice :\n\n");
          afficherMat(m);
        }
        else
          printf("Vous n'avez pas encore construit de matrice");
        break;
      case 4:
          if(construite){
            printf("Entrez la matrice que vous voulez additionner à celle en mémoire :\n");
            for(i=0;i<m.Nlignes;i++)
                for(j=0;j<m.Ncolonnes;j++){
                    printf("Valeur ligne %d colonne %d : ",i,j);
                    scanf("%d",&tab[i][j]);
                }
            constructMat(&m2, tab, m.Nlignes, m.Ncolonnes);
            printf("\n\nSomme : \n\n");
            addMat(m,m2);
            afficherMat(m);
          }else{
            printf("Vous n'avez pas encore construit la première matrice");
          }
            break;
      case 5:
          if(construite){
                printf("\nGain d'espace : %d octets",nombreOctetsGagnes(m));
          }else{
                printf("Vous n'avez pas encore construit de matrice");
          }
          break;
      case 6:
        printf("Fin du programme\n\n");
        return 0;
    }
  }
}
