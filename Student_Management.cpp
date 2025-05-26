#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include<direct.h>
//====Les déclarations=====//
typedef struct module{	
	char  nom_module[20];	
	int coefficient[] ;
	float note[];
}module;
typedef struct adresse{
	char rue[20],ville[20],wilaya[20];
}adresse;
typedef struct etudiant{
	char  nom[] ,email[50];
	char prenom[];
	int id;
	int age ;
	adresse residence ;
	float moyenne;
	module type_module ;
}etudiant;
etudiant e ;
///========procedure ajouter==============
void ajouter(){
	FILE *Fp=fopen("etudiantdatabse/.txt","a");
	int num ; 
	printf("entre le num de cet etudiant:");
    scanf("%d",&num);
    fflush(stdin);
	printf("nom : ");
    scanf("%s",&e.nom);
    printf("prenom : ");
    scanf("%s",&e.prenom);
    //-----informations de cet étudiant -----//
    printf("\n lemail est :");
    scanf("%s",&e.email);
    printf(" id : ");
    scanf("%d",&e.id);
    fflush(stdin);
    printf("lage :");
    scanf("%d",&e.age);
    fflush(stdin);
    printf(" la rue  : ");
    scanf("%s",&e.residence.rue);
    fflush(stdin);
    printf("la ville est :");
    scanf("%s",&e.residence.ville);
    fflush(stdin);
    printf("la wilaya est :");
    scanf("%s",&e.residence.wilaya);
    fprintf(Fp,"%s,%s,%s,%d,%d,%s,%s,%s\n",e.nom,e.prenom,e.email,e.id,e.age,e.residence.rue,e.residence.ville,e.residence.wilaya);
    fclose(Fp);
}

void affichage(){
    FILE *Fp= fopen("etudiant.txt", "r");
    printf("Liste des étudiants :\n"); 
    fscanf(Fp,"%s,%s,%s,%d,%d,%s,%s,%s",e.nom,e.prenom,e.email,&e.id,&e.age,e.residence.rue,e.residence.ville,e.residence.wilaya);
    printf("%s,%s,%s,%d,%d,%s,%s,%s",e.nom,e.prenom,e.email,e.id,e.age,e.residence.rue,e.residence.ville,e.residence.wilaya);
    fclose(Fp);
}
 ///========procedure rechercher par nom==============
void rechercher_par_nom(){
	char nom[20];
	printf("Entrer le nom d'etudiant : ");
	scanf("%s",&nom);
	FILE *Fp=fopen("etudiantdatabase/.txt","r");
    do{
		fscanf(Fp,"%s,%s,%s,%d,%d,%s,%s,%s,%s,%s\n",&e.nom,&e.prenom,&e.email,&e.id,&e.age,&e.residence.rue,&e.residence.ville,&e.residence.wilaya,&e.type_module.nom_module,&e.residence.wilaya);
    	if(strcmp(e.nom,nom)==0){
			printf("informations de (%s)\n",nom);
			printf("prenom :%s\n ",e.prenom);
			printf("lemail est :%s\n",e.email);
			printf("id :%d\n ",e.id);
			printf("lage %d",e.age);
			printf(" la rue  %s",e.residence.rue);
			printf("la ville est %s",e.residence.ville);
    		printf("la wilaya est %s",e.residence.wilaya);}
 	   }
    while(!feof(Fp));
    fclose(Fp);
}

    ///========procedure modifier==============
void modifier( ){
  //verifier si le fichier est bien ouvert
  FILE  *Fp2=fopen("etudiant2database/.txt","r+");
    if(Fp2==NULL){
    	printf("fichier non ouvert !");
		return  ;
    }

     char nom[20];
     printf("Entrer le nom d'etudiant a modifier : ");
     scanf("%s",nom);
     int found=0;
    while(fread(&e,sizeof( etudiant),1,Fp2)==1){
        if(strcmp(e.nom,nom)==0){
            found=1;
            break;
        }
    }
  //mise a jour des informations
  if(found){
    printf( " le nouvel email est: ");
    scanf("%s", &e.email);
    printf(" nv id: ");
    scanf("%d", &e.id);
    printf(" nv age: ");
    scanf("%d", &e.age);
    printf("nv  Rue: ");
    scanf("%s", &e.residence.rue);
    printf(" nv Ville: ");
    scanf("%s", &e.residence.ville);
    printf("nv  Wilaya: ");
    scanf("%s",&e.residence.wilaya);
    fseek(Fp2, -sizeof(struct etudiant), SEEK_CUR);
    fwrite(&e, sizeof( struct etudiant), 1, Fp2);
    printf("Les informations de l'etudiant ont ete modifiees.\n");
    } else {
    printf("Aucun etudiant trouve avec ce nom.\n");
    }
    fclose(Fp2);
return ;
}
void calculer_moyenne(){
   FILE *fp2=fopen("etudiant2database/.txt","w");
   char NomRech[10];
   int nbrmod;
   float moy=0;
   float scoeff=0;
   printf("Entrez Le nombre des modules :");
   scanf("%d",&nbrmod);
   printf("Entrez Le nom d'etudiant  :");
   scanf("%s",&NomRech);
   fflush(stdin);
	if (NomRech==e.nom ){
		for(int i=1;i<nbrmod+1;i++){
			printf("entrer le nom du module %d:",i);
			scanf("%d",&e.type_module.nom_module[i]);
   		
			printf("entrer le coefficient du module %d:",i);
			scanf("%d",&e.type_module.coefficient[i]);
   		
			printf("entrer la note de l etudiant %d:",i);
        	scanf("%d",&e.type_module.note[i]);
		}
		for(int i=1;i<nbrmod+1;i++){
			moy+=e.type_module.note[i]*e.type_module.coefficient[i];
    		scoeff+=e.type_module.coefficient[i];
		}
		moy/=scoeff;
		printf("la moyenne de l etudiant %s est de %.2f\n",e.nom,moy);
	}
}
 ///========fonction supprimer==============
void supprimer(){
	char rep ; 
	char nom[20];
	FILE *fp2=fopen("etudiant2database/.txt","r");
	FILE *fp3=fopen("etudiant3database/.txt","a");
	printf("nom d`etudiant a supprimer: ");
	scanf("%s",nom);
	fflush(stdin);
	if(strcmp(e.nom,nom)==0){
		printf("entrer o ou n si vous voulez supprimer : ");
		scanf("%c",&rep);
	}
	fflush(stdin);
	if(rep =='o'|| rep == 'O'){
		FILE *fp=fopen("etudiantdatabase/.txt","r");
		FILE *fp2=fopen("Tempdatabase/.txt","a");
	}
	do{
		fscanf(fp2,"%s,%s,%s,%d,%d,%s,%s,%s,%s\n",&e.nom,&e.prenom,&e.email,&e.id,e.age,&e.residence.rue,&e.residence.ville,&e.residence.wilaya);
		if(nom!=e.nom){
			fprintf(fp3,"%s,%s,%s,%d,%d,%s,%s,%s,%s\n",e.nom,e.prenom,e.email,e.id,e.age,e.residence.rue,e.residence.ville,e.residence.wilaya);
		}else{
		printf("l`etudiant nexiste pas dans la liste !!");
	}	
	}
	while(!feof(fp2));
	fclose(fp3);
	fclose(fp2);
	remove("etudiantdatabase/.txt");
	rename("Tempetudiantdatabase/.txt","etudiant2.txt");
	printf("suppression effectuee avec succe");
}
void quitter(){
	system("cls");
	printf("\n\n        \t------------FIN-----------\n\n\n");
	printf("\n\n       \t------------MERCI-----------\n\n\n");
 }
int main(int argc, char *argv[]){
	int  n ;
	char* path = "C:\\database"; // chemin du répertoire à créer
	int status = mkdir(path); // création du répertoire
	if (status == 0) { // vérification de la création réussie
		printf("Répertoire créé avec succès\n");
	}
	else {
		printf("Erreur lors de la création du répertoire\n");
	}


	int choix ; 
		system("color 1B");
	do{
		
			printf("\n        ****      Gestion des etudiants    **** \n\n");
			printf("         ============================================= \n\n");
			printf("  Totale des etudints : %d\n\n",n);
			printf("      <1.  Ajouter  des etudiants------------------ \n");
			printf("      <2.  afficher les informations--------------- \n");
			printf("      <3.  Rechercher un etudiant par nom------------------ \n");
			printf("      <4.  modifier -------------- \n");
			printf("      <5.  supprimer un etudiant -------- \n");
			printf("      <6.  calculer la moyenne d`un etudiant---------------------------- \n");
			printf("      <7.  quitter--------- \n");
			printf("          ============================================== \n\n");
			printf("Entrez votre choix : ");
			scanf("%d",&choix);
			printf("\n\n");
			switch(choix){
				case 1: system("cls");ajouter();break;
				case 2: system("cls");affichage();break;
				case 3: system("cls");rechercher_par_nom();break;
				case 4: system("cls");modifier();break;
				case 5: system("cls");supprimer();break;
				case 6: system("cls");calculer_moyenne();break;
				case 7: system("cls");quitter();break;
				default:system("cls");printf("rechoisissez \n");
			}
    }while(choix!=8);
	system("PAUSE>null");
	return 0;
	
}
