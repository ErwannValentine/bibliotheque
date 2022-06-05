#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct{
	int EtudiantOuProf;
	char NomUtilisateur[200];
	char Mdp[200];
	int NombreLivre;
} User;

typedef struct{
	int Dispo;
	char Titre[200];
	char Auteur[200];
	int Categorie;
} Book;



void ecrireFichier(User a) {
	FILE* fichier = NULL;
	fichier = fopen("User.txt", "a");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	else{
		fprintf(fichier, "%d %s %s %d\n", a.EtudiantOuProf, a.NomUtilisateur, a.Mdp, a.NombreLivre);
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
		fscanf(fichier, "%d", &tab[i].NombreLivre);
	}
	
	return tab;
}



void ecrireBook(Book a) {
	FILE* fichier = NULL;
	fichier = fopen("Book.txt", "a");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	else{
		fprintf(fichier, "%d %s %s %d\n", a.Dispo, a.Titre, a.Auteur, a.Categorie);
	}

}



Book* lireBook(int *nmbBook) {
	Book* tab = NULL;
	FILE* fichier = NULL;
	fichier = fopen("Book.txt", "r");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	char ligneBook[1000];
	while(fgets(ligneBook, 999, fichier) != NULL) {
		*nmbBook= *nmbBook+ 1;
	}
	tab = malloc(*nmbBook* sizeof(Book));
	rewind(fichier);
	for(int i = 0; i < *nmbBook ; i++) {
		fscanf(fichier, "%d", &tab[i].Dispo);
		fscanf(fichier, "%s", tab[i].Titre);
		fscanf(fichier, "%s", tab[i].Auteur);
		fscanf(fichier, "%d", &tab[i].Categorie);
	}
	
	return tab;
}



void CreerCompteEtu( User * tabUser, int nmbUser){
	User e;
	e.EtudiantOuProf=1;
	e.NombreLivre=0;
	printf("\nVeuillez saisir un nom d'utilisateur\n\n");
	scanf("%s",e.NomUtilisateur);
	for(int i = 0; i < nmbUser ; i++) {
		if (strcmp(tabUser[i].NomUtilisateur, e.NomUtilisateur)==0) {
			printf("\nErreur nom d'utilisateur deja utilisé, veuillez vous connecter.\n");
			exit(1);
		}
	}
	printf("\nVeuillez saisir un mot de passe\n\n");
	scanf("%s",e.Mdp);
	ecrireFichier(e);
}



void CreerCompteProf( User * tabUser, int nmbUser){
	User p;
	p.EtudiantOuProf=2;
	p.NombreLivre=0;
	printf("\nVeuillez saisir un nom d'utilisateur\n\n");
	scanf("%s",p.NomUtilisateur);
	for(int i = 0; i < nmbUser ; i++) {
		if (strcmp(tabUser[i].NomUtilisateur, p.NomUtilisateur)==0) {
			printf("\nErreur nom d'utilisateur deja utilisé, veuillez vous connecter.\n");
			exit(1);
		}
	}
	printf("\nVeuillez saisir un mot de passe\n\n");
	scanf("%s",p.Mdp);
	ecrireFichier(p);
}



void CreerCompte( User * tabUser, int nmbUser){
	printf("\nEtes vous :\n1.Etudiant\n2.Professeur\n\n");
	char a[100];
	scanf("%s",a);
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



void EmprunterLivre(User a, Book * tabBook, int nmbBook){
	Book x;
	char z[100];


	if (a.EtudiantOuProf==1){
		if (a.NombreLivre<3){
			printf("\nQuelle categorie de livre voulez vous emprunter ?\n");
			printf("1.Cuisine\n2.Jeunesse\n3.Histoire\n4.Théatre\n5.Humour\n\n");
			scanf("%s",z);
			while(strlen(z)!=1){
				printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				scanf("%s",z);
			}
			if(z[0]=='1'){
				printf("\nVeuillez choisir un livre de cuisine à emprunter parmi la liste suivante :\n");
				for(int i = 0; i < 5 ; i++){ 
				    printf("%d. %s %s\n", i+1, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[0].Dispo==1){
                        tabBook[0].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[1].Dispo==1){
                        tabBook[1].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[2].Dispo==1){
                        tabBook[2].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[3].Dispo==1){
                        tabBook[3].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[4].Dispo==1){
                        tabBook[4].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[0].Dispo==1){
                                tabBook[0].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[1].Dispo==1){
                                tabBook[1].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[2].Dispo==1){
                                tabBook[2].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[3].Dispo==1){
                                tabBook[3].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[4].Dispo==1){
                                tabBook[4].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='2'){
				printf("Veuillez choisir un livre de jeunesse à emprunter parmi la liste suivante :\n");
                for(int i = 5; i < 10 ; i++){ 
				    printf("%d. %s %s\n", i-4, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[5].Dispo==1){
                        tabBook[5].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[6].Dispo==1){
                        tabBook[6].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[7].Dispo==1){
                        tabBook[7].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[8].Dispo==1){
                        tabBook[8].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[9].Dispo==1){
                        tabBook[9].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[5].Dispo==1){
                                tabBook[5].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[6].Dispo==1){
                                tabBook[6].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[7].Dispo==1){
                                tabBook[7].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[8].Dispo==1){
                                tabBook[8].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[9].Dispo==1){
                                tabBook[9].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='3'){
				printf("Veuillez choisir un livre d'histoire à emprunter parmi la liste suivante :\n");
                for(int i = 10; i < 15 ; i++){ 
				    printf("%d. %s %s\n", i-9, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[10].Dispo==1){
                        tabBook[10].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[11].Dispo==1){
                        tabBook[11].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[12].Dispo==1){
                        tabBook[12].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[13].Dispo==1){
                        tabBook[13].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[14].Dispo==1){
                        tabBook[14].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[10].Dispo==1){
                                tabBook[10].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[11].Dispo==1){
                                tabBook[11].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[12].Dispo==1){
                                tabBook[12].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[13].Dispo==1){
                                tabBook[13].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[14].Dispo==1){
                                tabBook[14].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='4'){
				printf("Veuillez choisir un livre de théatre à emprunter parmi la liste suivante :\n");
                for(int i = 15; i < 20 ; i++){ 
				    printf("%d. %s %s\n", i-14, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[15].Dispo==1){
                        tabBook[15].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[16].Dispo==1){
                        tabBook[16].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[17].Dispo==1){
                        tabBook[17].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[18].Dispo==1){
                        tabBook[18].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[19].Dispo==1){
                        tabBook[19].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[15].Dispo==1){
                                tabBook[15].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[16].Dispo==1){
                                tabBook[16].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[17].Dispo==1){
                                tabBook[17].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[18].Dispo==1){
                                tabBook[18].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[19].Dispo==1){
                                tabBook[19].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='5'){
				printf("Veuillez choisir un livre d'humour à emprunter parmi la liste suivante :\n");
                for(int i = 20; i < 25 ; i++){ 
				    printf("%d. %s %s\n", i-19, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[20].Dispo==1){
                        tabBook[20].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[21].Dispo==1){
                        tabBook[21].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[22].Dispo==1){
                        tabBook[22].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[23].Dispo==1){
                        tabBook[23].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[24].Dispo==1){
                        tabBook[24].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[20].Dispo==1){
                                tabBook[20].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[21].Dispo==1){
                                tabBook[21].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[22].Dispo==1){
                                tabBook[22].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[23].Dispo==1){
                                tabBook[23].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[24].Dispo==1){
                                tabBook[24].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
		}	
		else {
		    printf("\nVous avez deja emprunter 3 livre, veuillez en rendre un pour en emprunter à nouveau\n\n");
		}
	}
	

	else if (a.EtudiantOuProf==2){
		if (a.NombreLivre<5){
			printf("\nQuelle categorie de livre voulez vous emprunter ?\n");
			printf("1.Cuisine\n2.Jeunesse\n3.Histoire\n4.Théatre\n5.Humour\n\n");
			scanf("%s",z);
			while(strlen(z)!=1){
				printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				scanf("%s",z);
			}
			if(z[0]=='1'){
				printf("\nVeuillez choisir un livre de cuisine à emprunter parmi la liste suivante :\n");
				for(int i = 0; i < 5 ; i++){ 
				    printf("%d. %s %s\n", i+1, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[0].Dispo==1){
                        tabBook[0].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[1].Dispo==1){
                        tabBook[1].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[2].Dispo==1){
                        tabBook[2].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[3].Dispo==1){
                        tabBook[3].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[4].Dispo==1){
                        tabBook[4].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[0].Dispo==1){
                                tabBook[0].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[1].Dispo==1){
                                tabBook[1].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[2].Dispo==1){
                                tabBook[2].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[3].Dispo==1){
                                tabBook[3].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[4].Dispo==1){
                                tabBook[4].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='2'){
				printf("Veuillez choisir un livre de jeunesse à emprunter parmi la liste suivante :\n");
                for(int i = 5; i < 10 ; i++){ 
				    printf("%d. %s %s\n", i-4, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[5].Dispo==1){
                        tabBook[5].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[6].Dispo==1){
                        tabBook[6].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[7].Dispo==1){
                        tabBook[7].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[8].Dispo==1){
                        tabBook[8].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[9].Dispo==1){
                        tabBook[9].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[5].Dispo==1){
                                tabBook[5].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[6].Dispo==1){
                                tabBook[6].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[7].Dispo==1){
                                tabBook[7].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[8].Dispo==1){
                                tabBook[8].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[9].Dispo==1){
                                tabBook[9].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='3'){
				printf("Veuillez choisir un livre d'histoire à emprunter parmi la liste suivante :\n");
                for(int i = 10; i < 15 ; i++){ 
				    printf("%d. %s %s\n", i-9, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[10].Dispo==1){
                        tabBook[10].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[11].Dispo==1){
                        tabBook[11].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[12].Dispo==1){
                        tabBook[12].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[13].Dispo==1){
                        tabBook[13].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[14].Dispo==1){
                        tabBook[14].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[10].Dispo==1){
                                tabBook[10].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[11].Dispo==1){
                                tabBook[11].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[12].Dispo==1){
                                tabBook[12].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[13].Dispo==1){
                                tabBook[13].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[14].Dispo==1){
                                tabBook[14].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='4'){
				printf("Veuillez choisir un livre de théatre à emprunter parmi la liste suivante :\n");
                for(int i = 15; i < 20 ; i++){ 
				    printf("%d. %s %s\n", i-14, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[15].Dispo==1){
                        tabBook[15].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[16].Dispo==1){
                        tabBook[16].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[17].Dispo==1){
                        tabBook[17].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[18].Dispo==1){
                        tabBook[18].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[19].Dispo==1){
                        tabBook[19].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[15].Dispo==1){
                                tabBook[15].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[16].Dispo==1){
                                tabBook[16].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[17].Dispo==1){
                                tabBook[17].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[18].Dispo==1){
                                tabBook[18].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[19].Dispo==1){
                                tabBook[19].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
			else if(z[0]=='5'){
				printf("Veuillez choisir un livre d'humour à emprunter parmi la liste suivante :\n");
                for(int i = 20; i < 25 ; i++){ 
				    printf("%d. %s %s\n", i-19, tabBook[i].Titre, tabBook[i].Auteur);
				}
                printf("\n");
                scanf("%s",z);
			    while(strlen(z)!=1){
				    printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
				    scanf("%s",z);
			    }
                if(z[0]=='1'){
	                if(tabBook[20].Dispo==1){
                        tabBook[20].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='2'){
                    if(tabBook[21].Dispo==1){
                        tabBook[21].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else if(z[0]=='3'){
                    if(tabBook[22].Dispo==1){
                        tabBook[22].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='4'){
                    if(tabBook[23].Dispo==1){
                        tabBook[23].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    }
                }
                else if(z[0]=='5'){
	               if(tabBook[24].Dispo==1){
                        tabBook[24].Dispo=0;
                        a.NombreLivre=a.NombreLivre+1;
                        printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                    }
                    else{
                        printf("\nDésolé ce livre n'est pas disponible\n");
                    } 
                }
                else{
	                printf("\nErreur veuillez saisir 1 ou 2\n\n");
	                while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		                scanf("%s",z);
		                if(z[0]=='1'){
			                if(tabBook[20].Dispo==1){
                                tabBook[20].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            }
			                exit(1);
		                }
		                else if(z[0]=='2'){
		                	if(tabBook[21].Dispo==1){
                                tabBook[21].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                                printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='3'){
		                	if(tabBook[22].Dispo==1){
                                tabBook[22].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='4'){
		                	if(tabBook[23].Dispo==1){
                                tabBook[23].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
                        else if(z[0]=='5'){
                            if(tabBook[24].Dispo==1){
                                tabBook[24].Dispo=0;
                                a.NombreLivre=a.NombreLivre+1;
                            printf("\nVous venez bien d'emprunter le livre, merci :)\n");
                            }
                            else{
                                printf("\nDésolé ce livre n'est pas disponible\n");
                            } 
			                exit(1);
		                }
	                }
                }
			}
		}	
		else {
		printf("Vous avez deja emprunter 5 livre, veuillez en rendre un  pour en emprunter à nouveau\n");
		}
	}
}



void RendreLivre(User a, Book * tabBook, int nmbBook){
    Book x;
	char z[100];

    printf("\nQuelle est la categorie du livre que vous voulez rendre ?\n");
    printf("1.Cuisine\n2.Jeunesse\n3.Histoire\n4.Théatre\n5.Humour\n\n");
    scanf("%s",z);
	while(strlen(z)!=1){
		printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
		scanf("%s",z);
	}
	if(z[0]=='1'){
		printf("\nVeuillez choisir un livre de cuisine à rendre parmi la liste suivante :\n");
		for(int i = 0; i < 5 ; i++){ 
		    printf("%d. %s %s\n", i+1, tabBook[i].Titre, tabBook[i].Auteur);
		}
        printf("\n");
        scanf("%s",z);
		while(strlen(z)!=1){
			printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
			scanf("%s",z);
		}
        if(z[0]=='1'){
            tabBook[0].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='2'){
            tabBook[1].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='3'){
            tabBook[2].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='4'){
            tabBook[3].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='5'){
            tabBook[4].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else{
	        printf("\nErreur veuillez saisir 1 ou 2\n\n");
	        while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		        scanf("%s",z);
		        if(z[0]=='1'){
                    tabBook[0].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
                }
		        else if(z[0]=='2'){
                    tabBook[1].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
                else if(z[0]=='3'){
                    tabBook[2].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n"); 
			        exit(1);
		        }
                else if(z[0]=='4'){
                    tabBook[3].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
               else if(z[0]=='5'){
                    tabBook[4].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
	        }
        }
	}
    if(z[0]=='2'){
		printf("\nVeuillez choisir un livre de jeunesse à rendre parmi la liste suivante :\n");
		for(int i = 5; i < 10 ; i++){ 
		    printf("%d. %s %s\n", i-4, tabBook[i].Titre, tabBook[i].Auteur);
		}
        printf("\n");
        scanf("%s",z);
		while(strlen(z)!=1){
			printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
			scanf("%s",z);
		}
        if(z[0]=='1'){
            tabBook[5].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='2'){
            tabBook[6].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='3'){
            tabBook[7].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='4'){
            tabBook[8].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='5'){
            tabBook[9].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else{
	        printf("\nErreur veuillez saisir 1 ou 2\n\n");
	        while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		        scanf("%s",z);
		        if(z[0]=='1'){
                    tabBook[5].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
                }
		        else if(z[0]=='2'){
                    tabBook[6].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
                else if(z[0]=='3'){
                    tabBook[7].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n"); 
			        exit(1);
		        }
                else if(z[0]=='4'){
                    tabBook[8].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
               else if(z[0]=='5'){
                    tabBook[9].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
	        }
        }
    }
    if(z[0]=='3'){
		printf("\nVeuillez choisir un livre d'histoire à rendre parmi la liste suivante :\n");
		for(int i = 10; i < 15 ; i++){ 
		    printf("%d. %s %s\n", i-9, tabBook[i].Titre, tabBook[i].Auteur);
		}
        printf("\n");
        scanf("%s",z);
		while(strlen(z)!=1){
			printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
			scanf("%s",z);
		}
        if(z[0]=='1'){
            tabBook[10].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='2'){
            tabBook[11].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='3'){
            tabBook[12].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='4'){
            tabBook[13].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='5'){
            tabBook[14].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else{
	        printf("\nErreur veuillez saisir 1 ou 2\n\n");
	        while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		        scanf("%s",z);
		        if(z[0]=='1'){
                    tabBook[10].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
                }
		        else if(z[0]=='2'){
                    tabBook[11].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
                else if(z[0]=='3'){
                    tabBook[12].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n"); 
			        exit(1);
		        }
                else if(z[0]=='4'){
                    tabBook[13].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
               else if(z[0]=='5'){
                    tabBook[14].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
	        }
        }
	}
    if(z[0]=='4'){
		printf("\nVeuillez choisir un livre de théatre à rendre parmi la liste suivante :\n");
		for(int i = 15; i < 20 ; i++){ 
		    printf("%d. %s %s\n", i-14, tabBook[i].Titre, tabBook[i].Auteur);
		}
        printf("\n");
        scanf("%s",z);
		while(strlen(z)!=1){
			printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
			scanf("%s",z);
		}
        if(z[0]=='1'){
            tabBook[15].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='2'){
            tabBook[16].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='3'){
            tabBook[17].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='4'){
            tabBook[18].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='5'){
            tabBook[19].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else{
	        printf("\nErreur veuillez saisir 1 ou 2\n\n");
	        while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		        scanf("%s",z);
		        if(z[0]=='1'){
                    tabBook[15].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
                }
		        else if(z[0]=='2'){
                    tabBook[16].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
                else if(z[0]=='3'){
                    tabBook[17].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n"); 
			        exit(1);
		        }
                else if(z[0]=='4'){
                    tabBook[18].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
               else if(z[0]=='5'){
                    tabBook[19].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
	        }
        }
	}
    if(z[0]=='5'){
		printf("\nVeuillez choisir un livre d'humour à rendre parmi la liste suivante :\n");
		for(int i = 20; i < 25 ; i++){ 
		    printf("%d. %s %s\n", i-19, tabBook[i].Titre, tabBook[i].Auteur);
		}
        printf("\n");
        scanf("%s",z);
		while(strlen(z)!=1){
			printf("\nErreur veuillez saisir 1, 2, 3, 4 ou 5\n\n");
			scanf("%s",z);
		}
        if(z[0]=='1'){
            tabBook[20].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='2'){
            tabBook[21].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='3'){
            tabBook[22].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='4'){
            tabBook[23].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else if(z[0]=='5'){
            tabBook[24].Dispo=1;
            a.NombreLivre=a.NombreLivre-1;
            printf("\nVous venez bien de rendre le livre, merci :)\n");
        }
        else{
	        printf("\nErreur veuillez saisir 1 ou 2\n\n");
	        while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4' || z[0]!='5'){
		        scanf("%s",z);
		        if(z[0]=='1'){
                    tabBook[20].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
                }
		        else if(z[0]=='2'){
                    tabBook[21].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
                else if(z[0]=='3'){
                    tabBook[22].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n"); 
			        exit(1);
		        }
                else if(z[0]=='4'){
                    tabBook[23].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
               else if(z[0]=='5'){
                    tabBook[24].Dispo=1;
                    a.NombreLivre=a.NombreLivre-1;
                    printf("\nVous venez bien de rendre le livre, merci :)\n");
			        exit(1);
		        }
	        }
        }
	}
}



void AjouterLivre(User a){
	if (a.EtudiantOuProf==1){
		printf("\nVous êtes étudiant, vous ne pouvez pas ajouter de livre.\n");
	}
	else if (a.EtudiantOuProf==2){
        printf("\nDésolé, cette fonctionalité n'est pas encore disponible.\n");
	}
}



void InterfaceBiblio(User a){
	
	int nmbBook=0;
	Book * tabBook= lireBook(&nmbBook);

	char z[100];
	printf("\nVoulez vous :\n1.Emprunter un livre\n2.Rendre un livre\n3.Ajouter un livre à la bibliotèque (prof)\n4.Se deconnecter\n\n");
	scanf("%s",z);

	while(strlen(z)!=1){
		printf("\nErreur veuillez saisir 1, 2, 3 ou 4\n\n");
		scanf("%s",z);
	} 

	if(z[0]=='1'){
		EmprunterLivre(a, tabBook, nmbBook);
	}
	else if(z[0]=='2'){
		RendreLivre(a, tabBook, nmbBook);
	}
	else if(z[0]=='3'){
		AjouterLivre(a);
	}
	else if(z[0]=='4'){
		printf("\nMerci à bientot :)\n");
		exit(1);
	}
	else{
		printf("\nErreur veuillez saisir 1, 2, 3 ou 4\n\n");
		while(z[0]!='1' || z[0]!='2' || z[0]!='3' || z[0]!='4'){
			scanf("%s",z);
			if(z[0]=='1'){
				EmprunterLivre(a, tabBook, nmbBook);
				exit(1);
			}
			else if(z[0]=='2'){
				RendreLivre(a, tabBook, nmbBook);
				exit(1);
			}
			else if(z[0]=='3'){
				AjouterLivre(a);
				exit(1);
			}
			else if(z[0]=='4'){
				printf("\nMerci à bientot :)\n");
				exit(1);
			}
		}
	}
}



void SeConnecter(User * tabUser, int nmbUser){
	User x;
	int trouve=0;
	int ind=-1;
	printf("\nVeuillez saisir votre nom d'utilisateur\n\n");
	scanf("%s",x.NomUtilisateur);
	for(int i = 0; i < nmbUser ; i++) {
		if (strcmp(tabUser[i].NomUtilisateur, x.NomUtilisateur)==0) {
			trouve=1;
			ind=i;
		}
	}
	if(trouve==1){
		printf("\nVeuillez saisir votre mot de passe\n\n");
		scanf("%s",x.Mdp);
		if (strcmp(tabUser[ind].Mdp, x.Mdp)==0) {
			printf("\nBonjour %s bienvenue dans le menu principal de l'application Cy Bibliotech.\n",x.NomUtilisateur);
			InterfaceBiblio(tabUser[ind]);
		}
		else {
			printf("Mot de passe incorrect\n");
		}
	}
	else{
		printf("Votre identifiant n'existe pas, veuillez creer un compte.\n");
	}
}



int main(){

//Interface application//

printf("\n****************************************************************************\n");
printf("                        Application Cy BiblioTech                           \n");
printf("****************************************************************************\n");

int nmbUser=0;
User * tabUser=lireFichier(&nmbUser);

char a[100];
printf("\n1.Se connecter \n2.Creer un compte \n\n");
scanf("%s",a);

while(strlen(a)!=1){
	printf("\nErreur veuillez saisir 1 ou 2\n\n");
	scanf("%s",a);
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
		scanf("%s",a);
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