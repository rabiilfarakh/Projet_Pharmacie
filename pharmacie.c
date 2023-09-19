#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#define T_MAX 100

// structur Produit
typedef struct{
    char code[50];
    char nom[50];
    int quantite;
    double prix;
}produit;

// structur produit acheter
typedef struct{
    char code[50];
    char nom[50];
    int quantite;
    double prix; 
    time_t date;
}produitAcheter;

// fonction qui ajoute un produit au tableau de produit
void ajoutProduit(produit x, produit *tabProduit, int *tailleTabProduit) {

     if (*tailleTabProduit < T_MAX){
        tabProduit[(*tailleTabProduit)++]=x;
        printf("produit ajouter\n\n");
     }else{
        printf("vous pouvez pas ajoutez de produit memoir insuffisante\n");
     }
}

// fonction qui ajoute plusieur produit au tableau
void ajoutPlusieurProduit(int *n,produit *produitAajouter,produit *tabProduit,int *tailleTabProduit){
    int i;

    for(i=0;i<*n;i++){
        ajoutProduit(produitAajouter[i],tabProduit,tailleTabProduit);
    }
}

// fonction qui affiche les produits qui sont stockees dans le tableau
void ListerProduits(produit *tabProduits, int tailleTabProduit) {
    int i;

    printf("\nListe des produits :\n");
    for ( i = 0; i < tailleTabProduit; i++) {
        printf("Produit %d :\n", i + 1);
        printf("Nom: %s\n", tabProduits[i].nom);
        printf("Quantite: %d\n", tabProduits[i].quantite);
        printf("Prix TTC: %.2lf\n", tabProduits[i].prix+(tabProduits[i].prix*15)/100);
        printf("----------------------------------------\n");
    }
}

// fonction qui affiche le tableau de produit en ordre croissant selon leur nom
void listerCroissant(produit *tabProduits, int tailleTabProduit){
    produit x;
    int k=1,i;
    while(k==1){
        k=0;
    for(i=0;i<tailleTabProduit-1;i++){
        if(strcmp(tabProduits[i].nom,tabProduits[i+1].nom)>0){
            x=tabProduits[i];
            tabProduits[i]=tabProduits[i+1];
            tabProduits[i+1]=x;
            k=1;
        } 
    }
    }
    ListerProduits(tabProduits,tailleTabProduit);

}

// fonction qui affiche le tableau de produit en ordre decroissant selon leur prix
void listerDecroissant(produit *tabProduits, int tailleTabProduit){
    produit x;
    int k=1,i;
    while(k==1){
        k=0;
    for(i=0;i<tailleTabProduit-1;i++){
        if(tabProduits[i].prix<tabProduits[i+1].prix){
            x=tabProduits[i];
            tabProduits[i]=tabProduits[i+1];
            tabProduits[i+1]=x;
            k=1;
        } 
    }
    }
    ListerProduits(tabProduits,tailleTabProduit);

}

// fonction qui permet a l'utilisateur d'acheter un produit 
void acheterProduit(int *tailleTabProduit,produit *tabProduits,char *code,produitAcheter *tab,int *tailleTabAchat,int quant){
    int i;
    for(i=0;i<*tailleTabProduit;i++){
        if(strcmp(tabProduits[i].code,code)==0){
            if(tabProduits[i].quantite>quant){
                if (*tailleTabAchat < T_MAX){
                strcpy(tab[*tailleTabAchat].code,tabProduits[i].code);
                strcpy(tab[*tailleTabAchat].nom,tabProduits[i].nom);
                tab[*tailleTabAchat].prix=tabProduits[i].prix+(tabProduits[i].prix*15/100);
                tab[*tailleTabAchat].quantite=quant;
                tab[*tailleTabAchat].date=time(NULL);
                tabProduits[i].quantite-=quant;
                (*tailleTabAchat)++;
                printf("achat fait avec succee\n");
            }
        }else
            printf("quantite insuffisante\n");
    }else
        printf("ona pas ce produit dans le stock \n");
    }
}

// fonction qui affiche les produits acheter 
void afficherProduitAcheter(produitAcheter *tab,int *taille){
    int i;
    printf("liste des produits acheter\n");
    for(i=0;i<*taille;i++){
        printf("Produit %d :\n", i + 1);
        printf("Nom: %s\n", tab[i].nom);
        printf("Quantité: %d\n", tab[i].quantite);
        printf("Prix TTC: %.2lf\n", tab[i].prix);
        printf("Date d achat : %s", ctime(&tab[i].date));
        printf("----------------------------------------\n");
    }
}

// fonction qui affiche l'etat des produits stockees dans le tableau de produit
void etatStock(produit *tab,int *taille){
    int i;
    for(i=0;i<*taille;i++){
        if(tab[i].quantite<3){
        printf("Produit %d :\n", i + 1);
        printf("Nom: %s\n", tab[i].nom);
        printf("Quantité: %d\n", tab[i].quantite);
        printf("Prix TTC: %.2lf\n", tab[i].prix+(tab[i].prix*15)/100);
        printf("----------------------------------------\n");
    }
    }

}

// fonction qui permet d'alimenter le stock
void alimenterStock(produit *tab,produit produitA_alimenter,int *taille){
    int i,j;

    for(i=0;i<*taille;i++){
        if(strcmp(tab[i].code,produitA_alimenter.code)==0){
            tab[i].quantite+=produitA_alimenter.quantite;
            printf("produit est alimenter\n");
        }
        else
            printf("veuillez entrer un code valide\n");
    }
}

// fonction qui supprime un produit
void supprimeProduit(char *code,produit *tab,int *taille){
    produit tmp;
    int i,j=-1;
    
    for(i=0;i<*taille;i++){
        if(strcmp(tab[i].code,code)==0){
            j=i;
            break;
        }   
    }
    if(j!=-1){
        tmp=tab[j];
        tab[j]=tab[*taille-1];
        tab[*taille-1]=tmp;
        (*taille)--;
        printf("le produit est supprime\n");
    }else
        printf("produit introuvable verifier votre code\n");
    
}


int main(){
    produit *tabProduit=malloc(T_MAX * sizeof(produit)),x,*y;
    produitAcheter *t=malloc(T_MAX*sizeof(produitAcheter));
    int n,i,tailleTabProduit=0,nbr,quant,tailleTabAchat=0;
    char *code=malloc(30);

    while(1){
    printf("Choisire un nombre: \n");
    printf("1.Ajouter un produit\n");
    printf("2.Ajouter plusieurs produits\n");
    printf("3.Lister les produits\n");
    printf("4.Affichage Croissant selon le nom\n");
    printf("5.Affichage Decroissant selon le prix\n");
    printf("6.Acheter produit\n");
    printf("7.Afficher produit acheter\n");
    printf("8.Afficher les produits dans leur quantite inferieur a 3\n");
    printf("9.Alimenter produit\n");
    printf("10.Supprimer produit\n");
    printf("11.Quitter\n");
    scanf("%d",&n);
    switch (n)
    {
        case 1: 
            printf("code: ");
            scanf("%s",x.code);
            printf("nom: ");
            scanf("%s",x.nom);
            printf("prix: ");
            scanf("%lf",&x.prix);
            printf("quantite: ");
            scanf("%d",&x.quantite);
            ajoutProduit(x,tabProduit,&tailleTabProduit);
            break;
        case 2: 
            printf("entrer le nbr de produit a ajouter: ");
            scanf("%d",&nbr);
            y=malloc(nbr*sizeof(produit));
            for(i=0;i<nbr;i++){
            printf("entrer les information du produit %d\n",i+1);
            printf("code: ");
            scanf("%s",x.code);
            printf("nom: ");
            scanf("%s",x.nom);
            printf("prix: ");
            scanf("%lf",&x.prix);
            printf("quantite: ");
            scanf("%d",&x.quantite);
            y[i]=x;
            }
            ajoutPlusieurProduit(&nbr,y,tabProduit,&tailleTabProduit);
            break;
        case 3: 
            ListerProduits(tabProduit,tailleTabProduit);
            break;
        case 4:
            listerCroissant(tabProduit,tailleTabProduit);
            break;
        case 5:
            listerDecroissant(tabProduit,tailleTabProduit);
            break;
        case 6:
            printf("entrer le code de produit: \n");
            scanf("%s",code);
            printf("saisire la quantite: ");
            scanf("%d",&quant);
            acheterProduit(&tailleTabProduit,tabProduit,code,t,&tailleTabAchat,quant);
            break;
        case 7:
            afficherProduitAcheter(t,&tailleTabAchat);
            break;
        case 8:
            etatStock(tabProduit,&tailleTabProduit);
            break;
        case 9:
            printf("entrer le code du produit a alimenter: ");
            scanf("%s",x.code);
            printf("entrer la quantite: ");
            scanf("%d",&x.quantite);
            alimenterStock(tabProduit,x,&tailleTabProduit);
            break;
        case 10:
            printf("entrer le code: ");
            scanf("%s",code);
            supprimeProduit(code,tabProduit,&tailleTabProduit); 
            break;
        case 11:
            exit(0);

    }
    }

}