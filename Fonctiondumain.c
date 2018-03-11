#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

int random(int min, int max)
{
    int randVal = min + rand()%max;

    return randVal;
}

void loadSave(int *x, int *y, char * name, int *vie, int *vieMax, int *attack, int *defense, int *exp, int *level, int *inventory)
{
    FILE* saveFile = NULL;
    saveFile = fopen("save.txt","r");
    if (saveFile != NULL)
    {
        fscanf(saveFile, "%d %d", x, y);
        fscanf(saveFile,"%s", name);
        fscanf(saveFile,"%d", vie);
        fscanf(saveFile,"%d", vieMax);
        fscanf(saveFile,"%d", attack);
        fscanf(saveFile,"%d", defense);
        fscanf(saveFile,"%d", exp);
        fscanf(saveFile,"%d", level);
        fscanf(saveFile,"%d %d %d", &inventory[0], &inventory[1], &inventory[2]);
        fclose(saveFile);
    }
    else
    {
        printf("Aucune sauvegarde n'as �t� trouv� .. ");
    }
}

void writeSave(int x, int y, char *name, int vie, int vieMax, int attack, int defense, int exp, int level, int *inventory)
{
    FILE * saveFile = NULL;
    saveFile = fopen("save.txt", "w+");

    if(saveFile != NULL)
    {
        fprintf(saveFile, "%d %d\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d %d %d", x, y, name, vie, vieMax, attack, defense, exp, level, inventory[0], inventory[1], inventory[2]);

        fclose(saveFile);
    }
}

int afficherHelpMenu()
{
    system("cls");
    Color(10,0);
    printf("\t\tCOMMANDS HELPER \n\n");
    printf("- go [direction] | (north, east, west, south)\n");
    printf("- inventaire | Pour afficher le menu inventaire\n");
    printf("- save | Pour sauvegarder\n");
    printf("- pick up (objet) |(potion,Attack Boost, Defense Boost\n");
    printf("- help | Logique c'est pour afficher ce que tu vois!\n\n");
    Color(10,0);
    Color(12,0);
    printf("Pour revenir a la map taper une touche");
    Color(12,0);
    scanf("%*[^\n]");
    clearBuffer();
}

void afficherInventaire(int * inventaire)
{
    system("cls");
    char * itemName[] = {"Potion","Attack boost","Defense boost"};
    int i;
    printf("Inventaire :\n");
    for(i = 0; i< 3; i++)
    {
        printf("%s", itemName[i]);
        if(inventaire[i] > 1)
            printf("s");
        printf(" x %d\n", inventaire[i]);
    }
    printf("\n");
    Color(12,0);
    printf("Pour revenir taper sur n'importe qu'elle touche.");
    Color(12,0);
    scanf("%*[^\n]");
    clearBuffer();
}

int afficherMainMenu()
{
    system("cls");
    int answer = 0;
    Color(11,0);
    printf("\n\n\n\n    MAIN MENU \n\n");
    Color(11,0);
    printf("1. Create New Game\n");
    printf("2. Load Saved Game\n");
    printf("3. About\n");
    printf("4. EXIT\n\n>");

    while ((answer == 0) || (answer > 4))
    {
        int test=scanf("%d[^\n]", &answer);
        clearBuffer();
        if(answer > 4 || test < 1)
        {
            printf("Cette commande n'existe pas ! !\n>");
        }
    }
    return answer;
}

void afficherAboutMenu()
{
    system("cls");
    Color(14,0);
    printf("0100010100010010101");
    Color(14,0);
    Color(12,0);
    printf("\nPour revenir au menu taper n'importe qu'elle touche...");
    scanf("%*[^\n]");
    Color(12,0);
    clearBuffer();
}

int afficherFightMenu()
{
    int answer = 0;
    printf("MENU DE COMBAT : \n");
    printf("1. Attaquer\n");
    printf("2. Inventaire\n");
    printf("3. Fuir\n\n>");

    while ((answer == 0) |(answer > 3))
    {
        scanf("%d[^\n]", &answer);
        clearBuffer();
        if(answer > 3)
        {
            printf("Cette commande n'existe pas ! !\n");
        }
    }
    return answer;
}

int afficherMenuInventaire(int * inventaire)
{
    system("cls");
    int answer =0;
    char * itemName[] = {"Potion","Attack boost","Defense boost"};
    int i;
    printf("Inventaire :\n");
    for(i = 0; i< 3; i++)
    {
        printf("%d: %s", i+1,itemName[i]);
        if(inventaire[i] > 1)
            printf("s");
        printf(" x %d\n", inventaire[i]);
    }
    printf("4: Retour\n");
    while ((answer == 0) |(answer > 4))
    {
        scanf("%d[^\n]", &answer);
        clearBuffer();
        if(answer > 4)
        {
            printf("Cette commande n'existe pas ! !\n");
        }
    }
    return answer;
}

void chooseName(char* name)
{
    system("cls");
    printf("Entre un nom: \n>");
    scanf("%s[^\n]", name);
    clearBuffer();
}

void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearReturn(char* str)
{
    char* p = strchr(str, '\n');
    if(p)
    {
        *p = 0;
    }
    else
    {
        clearBuffer();
    }
}

void pickItem(int rand, int* inventory)
{
    char *itemName[] = {"Potion","Attack boost","Defense boost"};
    printf("Vous avez trouve un object : %s\n", itemName[rand-1]);
    char str[30];
    fgets(str, sizeof str, stdin);
    clearReturn(str);
    if(strcmp(str, "pick up potion") == 0 | strcmp(str, "pick up attack boost") == 0 | strcmp(str, "pick up defense boost") == 0 )
    {
        inventory[rand-1] = inventory[rand-1] + 1;
        printf("Vous avez recuperer l'objet : %s !", itemName[rand-1]);
    }
    else
    {
        printf("DOMMMMAGE TA RATER TA CHANCE!!! MOUHAHAHAHAH\n");
    }
    printf("Appuiyez sur une touche...");
    scanf("%*[^\n]");
    clearBuffer();
}

void afficherMap(int x, int y)
{
    system("cls");
    printf("\t\t\t\tSYNOPSIS\n\n");
    printf("Vous reveillez au milieu d'une foret de tour eiffel avec un sac contenant Rien du tout.");// Verification
    printf("Vous devez gagnez de l'XP\n");
    printf("Devenir plus fort et battre le BOSS (VENDEUR DE TOUR EIFFEL)\npour sortir de la foret de tour eiffel.\n\n");
    printf("ATTENTION! Vous pouvez tomber sur des touriste zombie,\nils sont minuent de CANON 600D qui vous envoie des flash dans la gueule.\t\n\n");
    Color(15,0);
    char map[10][10] = {{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.','B'}};
    Color(15,0);
    map[y][x] = 'X';
    int i;
    int j;
    for(i = 0; i<10; i++)
    {
        for (j = 0; j < 10; j ++)
        {
            printf("%c   ", map[i][j]);
        }
        printf("\n\n");
    }
    Color(11,0);
    printf("Vous pouvez allez a l'est l'ouest au nord et au sud\n");
    printf("en tapant: -go east- -go north- -go west- -go south-.\n");
    printf("\t   B indique le place du BOSS.\n");
    printf("Vous pouvez taper inventaire pour voir votre.\n\n");
    Color(11,0);
    Color(12,0);
    printf("Taper help pour afficher les commandes\n>");
    Color(12,0);
}

int action(int * x, int * y)
{
    char str[30];
    fgets(str, 30, stdin);
    clearReturn(str);

    if(strcmp(str, "help") == 0)
    {
        return -1;
    }
    if(strcmp(str, "inventaire") == 0)
    {
        return -2;
    }
    if(strcmp(str, "save") == 0)
    {
        return -3;
    }
    if(strcmp(str, "exit") == 0)
    {
        return -4;
    }
    if(strcmp(str, "go east") == 0)
    {
        *x = *x +1;
    }
    else if(strcmp(str,"go west") == 0)
    {
        *x = *x -1;
    }
    else if(strcmp(str,"go north") == 0)
    {
        *y = *y -1;
    }
    else if(strcmp(str,"go south") == 0)
    {
        *y = *y +1;
    }
    else
    {
        return 0;
    }
    if(*x < 0)
    {
        *x= 0;
        return 0;
    }
    if(*x >9)
    {
        *x = 9;
        return 0;
    }
    if(*y < 0)
    {
        *y = 0;
        return 0;
    }
    if(*y > 9)
    {
        *y = 9;
        return 0;
    }
    return 1;
}

int launchFight(int* inventaire, char * name, int level, int vieMax, int * vie, int * attack, int*  defense, int isBoss)
{
    int defenseModifier = 1;
    int attackModifier = 1;
    int choice2;
    char * monsterName;
    int monsterLevel;
    int monsterVie;
    int monsterAttack;
    int monsterDefense;
    if(isBoss == 0)
    {
        monsterName = "Touriste";
        monsterLevel = level;
        monsterVie = 0 + 50 * level;
        monsterAttack = 0 + 15 * level;
        monsterDefense = 0 + 7 * level;
    }
    else
    {
        monsterName = "BOSS LOIC";
        monsterLevel = 2*level;
        monsterVie = 0 + 70 * level;
        monsterAttack = 0 + 25 * level;
        monsterDefense = 0 + 15 * level;
    }
    Color(12,0);
    printf("Pour debuter le combat taper sur une touche ...");
    Color(12,0);
    scanf("%*[^\n]");
    clearBuffer();
    system("cls");
    Color(15,0);
    printf("COMBAT ! \n\n");
    printf("%s Lvl : %d\n", name, level);
    printf("Vie :%d/%d\n", *vie, vieMax);
    printf("Attack : %d/ Defense : %d\n\n", *attack * attackModifier, *defense * defenseModifier);
    printf("VS\n\n");
    printf("%s Lvl : %d\n", monsterName, monsterLevel);
    printf("Vie :%d\n", monsterVie);
    printf("Attack : %d/ Defense : %d\n\n", monsterAttack, monsterDefense);
    Color(15,0);

    while(*vie > 0 && monsterVie > 0)
    {
        int choice = afficherFightMenu();
        switch(choice)
        {
            case 1:
                monsterVie -= (*attack * attackModifier) - monsterDefense/2;
                if(monsterVie >0)
                {
                    *vie = *vie - monsterAttack + (*defense/2 * defenseModifier);
                    if(*vie <0)
                        *vie = 0;
                }
                else
                    monsterVie = 0;
                break;
            case 2 :
                choice2 = afficherMenuInventaire(inventaire);
                switch(choice2)
                {
                    case 1:
                        if(*vie < vieMax && inventaire[0] >0)
                        {
                            inventaire[0] = inventaire[0]-1;
                            *vie += 50;
                            if(*vie > vieMax)
                                *vie = vieMax;
                        }
                        break;
                    case 2:
                        if(inventaire[1] >0)
                        {
                            inventaire[1] = inventaire[1] -1;
                            attackModifier ++;
                        }
                        break;
                    case 3:
                        if(inventaire[2] >0)
                        {
                            inventaire[2] = inventaire[2] -1;
                            defenseModifier ++;
                        }
                        break;
                }
                break;
        case 3:
            if(isBoss == 0)
            {
                if(random(1,3) == 1)
                {
                    printf("Vous avez reussi a fuir ");
                    return 0;
                }
                else
                {
                    printf("Vous n'avez pas reussi a fuir");
                    *vie = *vie - monsterAttack + *defense/2 * defenseModifier;
                    if(*vie < 0)
                        *vie = 0;
                }
            }
            else
            {
                printf("Vous ne pouvez pas fuir !");
            }
            break;
        }
        system("cls");
        printf("COMBAT ! \n\n");
        printf("%s Lvl : %d\n", name, level);
        printf("Vie :%d/%d\n", *vie, vieMax);
        printf("Attack : %d/ Defense : %d\n\n", *attack * attackModifier, *defense * defenseModifier);
        printf("VS\n\n");
        printf("%s Lvl : %d\n", monsterName, monsterLevel);
        printf("Vie :%d\n", monsterVie);
        printf("Attack : %d/ Defense : %d\n\n", monsterAttack, monsterDefense);
    }
    if(*vie <= 0)
    {
        printf("Vous etes mort Le touriste vous a flasher...");
    }
    else
    {
        printf("YEAH!! T'a gagner. Tape sur une touche pour continuer.");
        scanf("%*[^\n]");
        clearBuffer();
    }

    return monsterLevel *10;
}

void launchGame(int isSaved)
{
    int xBoss = 9;
    int yBoss = 9;
    int x = 0;
    int y = 0;
    char name[30];
    int vie = 300;
    int vieMax = 300;
    int attack = 50;
    int defense = 15;
    int expRequire = 20;
    int exp = 0;
    int level = 1;
    int inventory[3] = {0};
    if(isSaved == TRUE)
    {
        loadSave(&x, &y, name, &vie, &vieMax, &attack, &defense, &exp, &level, inventory);
    }
    else
    {
        system("cls");
        chooseName(name);
    }
    int fin = FALSE;
    while (fin == FALSE)
    {
        if(vie <= 0)
            fin = TRUE;
        afficherMap(x,y);
        int tmpFlag = action(&x,&y);
        if(tmpFlag == -1)
        {
            afficherHelpMenu();
        }
        else if(tmpFlag == -2)
        {
            afficherInventaire(inventory);
        }
        else if(tmpFlag == -3)
        {
            writeSave(x, y, name, vie, vieMax, attack, defense, exp, level, inventory);
        }
        else if(tmpFlag == -4)
        {
            break;
        }
        else if (tmpFlag == 1)
        {
            afficherMap(x, y);
            srand((unsigned int)time(NULL));
            int rand2 = random(1, 2);
            if(x == xBoss && y == yBoss)
            {
                launchFight(inventory,name, level,vieMax,&vie,&attack,&defense, 1);
                fin = TRUE;
            }
            else
            {
                if(rand2 == 1)
                {
                    printf("Vous etes attaque par un touriste sauvage!\n");
                    int expe = launchFight(inventory,name, level,vieMax,&vie,&attack,&defense, 0);
                    if(vie < 0)
                    {
                        fin = TRUE;
                        break;
                    }
                    exp += expe;
                    if(exp >= expRequire)
                    {
                        int tmpExp = exp - expRequire;
                        exp = tmpExp;
                        expRequire = level * 30;

                        printf("LEVEL UP !!!\n\n");
                        printf("stats Update : \n");
                        printf("Lvl %d -> ", level);
                        level ++;
                        printf("%d\n", level);
                        printf("Vie %d -> ", vieMax);
                        vie += 50;
                        vieMax += 50;
                        printf("%d\n", vieMax);
                        printf("Attack %d -> ", attack);
                        attack +=15;
                        printf("%d\n", attack);
                        printf("Defense %d -> ", defense);
                        defense += 10;
                        printf("%d\n", defense);
                        printf("BRAVO !\n\nPour contunier");
                        scanf("%*[^\n]");
                        clearBuffer();
                    }
                }
                else
                {
                    int rand4 = random(1,4);
                    printf("%d", rand4);
                    if(rand4 == 2)
                    {
                        printf("Vous avez trouve quelque chose !\n");
                        int rand3 = random(1,3);
                        pickItem(rand3, inventory);
                    }
                }
            }
        }
    }
    if(fin == TRUE)
    {
        if(vie > 0)
        {
            printf("BRAVO ! Tu as vaincu le terrible vendeur de tour eiffeil, tu es notre heros !\n");
        }
        else
        {
            printf("Vous avez perdu ... Quel dommage Le Vendeur de tour eiffeil vous a vendue toute ses tour...\n");
        }
        printf("Pour revenir au menu taper sur une touche...");
        scanf("%*[^\n]");
        clearBuffer();
    }
}
