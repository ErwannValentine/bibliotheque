#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct{
	int EtudiantOuProf;
	char NomUtilisateur[200];
	char Mdp[200];
} User;

void ecrireFichier(User a) {
	FILE* fichier = NULL;
	fichier = fopen("User.txt", "a");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	else{
		fprintf(fichier, "%d %s %s \n", a.EtudiantOuProf, a.NomUtilisateur, a.Mdp);
	}

}

User* lireFichier(int *nmbUser) {
	User* tab = NULL;
	FILE* fichier = NULL;
	fichier = fopen("User.txt", "r");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	char ligneUser[1000];
	while(fgets(ligneUser, 999, fichier) != NULL) {
		*nmbUser= *nmbUser+ 1;
	}
	tab = malloc(*nmbUser* sizeof(User));
	rewind(fichier);
	for(int i = 0; i < *nmbUser ; i++) {
		fscanf(fichier, "%d", &tab[i].EtudiantOuProf);
		fscanf(fichier, "%s", tab[i].NomUtilisateur);
		fscanf(fichier, "%s", tab[i].Mdp);
	}
	
	return tab;
}

void CreerCompteEtu( User * tabUser, int nmbUser){
	User e;
	e.EtudiantOuProf=1;
	printf("\nVeuillez saisir un nom d'utilisateur\n\n");
	scanf("%s",&e.NomUtilisateur);
	for(int i = 0; i < nmbUser ; i++) {
		if (strcmp(tabUser[i].NomUtilisateur, e.NomUtilisateur)==0) {
			printf("\nErreur nom d'utilisateur deja utilisé, veuillez vous connecter.\n");
			exit(1);
		}
	}
	printf("\nVeuillez saisir un mot de passe\n\n");
	scanf("%s",&e.Mdp);
	ecrireFichier(e);
}

void CreerCompteProf( User * tabUser, int nmbUser){
	User p;
	p.EtudiantOuProf=2;
	printf("\nVeuillez saisir un nom d'utilisateur\n\n");
	scanf("%s",&p.NomUtilisateur);
	for(int i = 0; i < nmbUser ; i++) {
		if (strcmp(tabUser[i].NomUtilisateur, p.NomUtilisateur)==0) {
			printf("\nErreur nom d'utilisateur deja utilisé, veuillez vous connecter.\n");
			exit(1);
		}
	}
	printf("\nVeuillez saisir un mot de passe\n\n");
	scanf("%s",&p.Mdp);
	ecrireFichier(p);
}


void CreerCompte( User * tabUser, int nmbUser){
	printf("\nEtes vous :\n1.Etudiant\n2.Professeur\n\n");
	char a[100];
	scanf("%s",&a);
	if(strlen(a)!=1){
	printf("\nErreur veuillez saisir 1 ou 2\n");
	CreerCompte(tabUser, nmbUser);
	}
	if(a[0]=='1'){
	CreerCompteEtu(tabUser, nmbUser);
	}
	else if(a[0]=='2'){
		CreerCompteProf(tabUser, nmbUser);
	}
	else{
		printf("\nErreur veuillez saisir 1 ou 2\n");
		CreerCompte(tabUser, nmbUser);
	}
}

void SeConnecter(User * tabUser, int nmbUser){
	User x;
	int trouve=0;
	int ind=-1;
	printf("\nVeuillez saisir votre nom d'utilisateur\n\n");
	scanf("%s",&x.NomUtilisateur);
	for(int i = 0; i < nmbUser ; i++) {
		if (strcmp(tabUser[i].NomUtilisateur, x.NomUtilisateur)==0) {
			trouve=1;
			ind=i;
		}
	}
	printf("trouve=%d ind=%d \n", trouve, ind);
	if(trouve==1){
		printf("\nVeuillez saisir votre mot de passe\n\n");
		scanf("%s",&x.Mdp);
		if (strcmp(tabUser[ind].Mdp, x.Mdp)==0) {
			printf("\nBonjour %s \n",x.NomUtilisateur);
		}
		else {
			printf("Mot de passe incorrect\n");
		}
	}
	else{
		printf("Votre identifiant n'existe pas, veuillez vous connecter.\n");
	}
}


int main(){

//Interface application//

printf("\n****************************************************************************\n");
printf("                        Application Cy BiblioTech                           \n");
printf("****************************************************************************\n");

int nmbUser=0;
User * tabUser= lireFichier(&nmbUser);

char a[100];
printf("\n1.Se connecter \n2.Creer un compte \n\n");
scanf("%s",&a);

while(strlen(a)!=1){
	printf("\nErreur veuillez saisir 1 ou 2\n\n");
	scanf("%s",&a);
}

if(a[0]=='1'){
	SeConnecter(tabUser, nmbUser);
}
else if(a[0]=='2'){
	CreerCompte(tabUser, nmbUser);
}
else{
	printf("\nErreur veuillez saisir 1 ou 2\n\n");
	while(a[0]!='1' || a[0]!='2'){
		scanf("%s",&a);
		if(a[0]=='1'){
			SeConnecter(tabUser, nmbUser);
			exit(1);
		}
		else if(a[0]=='2'){
			CreerCompte(tabUser, nmbUser);
			exit(1);
		}
	}
}



return (0);
}
