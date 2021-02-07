#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
 int map_size;
struct Ship {
    int size;
    int health;
    int x1;
    int y1;
    int x2;
    int y2;
};
struct node {
    int id;
    struct Ship ship;
    struct node *next;
};

struct node *newnode(int id, int size, int x1, int y1, int x2, int y2) {
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->id = id;
    new_node->ship.size = size;
    new_node->ship.health = size;
    new_node->ship.x1 = x1;
    new_node->ship.x2 = x2;
    new_node->ship.y1 = y1;
    new_node->ship.y2 = y2;
    new_node->next = NULL;
    return new_node;
}

void addfront(struct node **head, int id, int size, int x1, int y1, int x2, int y2) {
    struct node *new_node = newnode(id, size, x1, y1, x2, y2);
    new_node->next = *head;
    *head = new_node;
}

bool deletenode(struct node **head, int id) {
    if (*head == NULL) {
        return false;
    }
    if ((*head)->id == id) {
        struct node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return true;
    }
    struct node *current = *head;
    struct node *last = NULL;
    while (current != NULL) {
        if (current->id == id) {
            last->next = current->next;
            free(current);
            return true;
        }
        last = current;
        current = current->next;
        return false;
    }
}

struct node *head1 = NULL;
struct node *head2 = NULL;

void menue(void);
void putship(char map[10][10], int size, struct node **head, int id);
void check(int satr, int sotoon, struct node *head, char choice[10][10], int *point);
void creat_map(char map[10][10], struct node **head);
void nagshe(char choice[10][10]);
void player1(int *point1, int *point2, char map2[10][10], char choice2[10][10], char name1[20], char map1[10][10],
             char choice1[10][10],
             char name2[20], struct node *head11, struct node *head22);
void player2(int *point1, int *point2, char map2[10][10], char choice2[10][10], char name1[20], char map1[10][10],
             char choice1[10][10],
             char name2[20], struct node *head11, struct node *head22);
void bot_craetmap(char bot_map[10][10],struct node **head);
void playwithbot(int *point,int *bot_point, char name[20], char choice[10][10], char map[10][10], char bot_choice[10][10],
                 char bot_map[10][10],struct node*head11,struct node*head22);

void botplay(int *point,int *bot_point, char name[20], char choice[10][10], char map[10][10], char bot_choice[10][10],
             char bot_map[10][10],struct node*head11,struct node*head22);
void chooseuserfromfile(int *point, char name[20]);
void creatnewuser(char name[20], int *point);
void matchscores(char name[20], int point);
void part1();
void part2();
void part5(int * mapsize);
void part6();
void menuework(void);

int main() {
    menue();
    menuework();
    return 0;
}

void menue(void) {

    printf("MENUE\n1.Play with a friend\n2.Play with bot\n3. Load game\n4. Load last game\n5. Settings\n6. Score Board\n7. Exit\n");
}

void menuework(void) {
    int n;
    map_size=10;
    fflush(stdin);
    scanf("%d", &n);
    if (n == 1) {
        part1();
    }
    else if (n == 2) {
        part2();
    }
    else if (n == 3) {

    }
    else if (n == 4) {

    } else if (n == 5) {
        part5(&map_size);

    } else if (n == 6) {
        part6();
    } else if (n == 7) {
        printf("Khodafeziiiiiiii :)))) *__*");
        exit(1);
    } else {
        printf("voroodi eshtebast dobare vared kon");
        menuework();

    }
}

void part1() {

    char name1[20], name2[20], map1[map_size][map_size], map2[map_size][map_size];
    int point1, point2;
    printf("player1\n");
    printf("esmeto vared kon az tarigh: 1.karbar ghadimi 2.karbar jadid");
    int n;
    scanf("%d", &n);
    if (n == 1) {
        chooseuserfromfile(&point1, name1);
    }
    if (n == 2) {
        creatnewuser(name1, &point1);
    }
    creat_map(map1, &head1);
    printf("player2\n");
    printf(" az tarigh: 1.karbar ghadimi 2.karbar jadid");
    int m;
    fflush(stdin);
    scanf("%d", &m);
    if (m == 1) {
        chooseuserfromfile(&point2, name2);
    }
    if (m == 2) {
        creatnewuser(name2, &point2);
    }
    creat_map(map2, &head2);
    char choice1[map_size][map_size], choice2[map_size][map_size];
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            choice1[i][j] = ' ';
            choice2[i][j] = ' ';
        }
    }

    player1(&point1, &point2, map2, choice2, name1, map1, choice1, name2, head1, head2);
    matchscores(name1, point1);
    matchscores(name2, point2);


}

void part2() {

    char name1[20], map1[map_size][map_size], map2[map_size][map_size], choice1[map_size][map_size], choice2[map_size][map_size];
    int point1, point2=0;
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            choice1[i][j] = ' ';
            choice2[i][j] = ' ';
        }
    }
    printf("player1\n");
    printf("esmeto vared kon az tarigh: 1.karbar ghadimi 2.karbar jadid");
    int n;
    fflush(stdin);
    scanf("%d", &n);
    if (n == 1) {
        chooseuserfromfile(&point1, name1);
    }
    if (n == 2) {
        creatnewuser(name1, &point1);
    }
    creat_map(map1, &head1);
    bot_craetmap(map2,&head2);
    playwithbot(&point1,&point2, name1, choice1, map1, choice2, map2,head1,head2);
    matchscores(name1, point1);

}
void part5(int * mapsize){
    int y,n;
    fflush(stdin);
    printf("mikahay size map ro taghir bedi? 1.yes 2.no");
    scanf("%d",&n);
    if (n==1){
    printf("size jadid vared kon");
    scanf("%d",&y);
    *mapsize=y;
    menue();
    menuework();}
    if (n!=1){
        menue();
        menuework();}
}
void part6() {
    char buf[20];
    FILE *fp = fopen("scoreboard.txt", "r");
    while (fgets(buf, 20, fp) != NULL) {
        puts(buf);
    }
    fclose(fp);
}

void chooseuserfromfile(int *point, char name[20]) {

    char buf[20];
    int counter,lines,n
    ;

    counter = 0;
    lines=0;
    FILE *fpin = fopen("names.txt", "r");
    FILE *fpin2 = fopen("points.txt", "r");
    while (fgets(buf, 20, fpin) != NULL)  {
        puts(buf);
        lines++;}
    fclose(fpin);
    fflush(stdin);
    printf("esm karbaro vared kon\n");
    gets(name);
    fpin = fopen("names.txt", "r");
        while (fscanf(fpin,"%s",buf) != NULL) {
        counter++;
        if (strcmpi(name, buf) == 0) {fseek(fpin2, counter - 1, SEEK_SET);
            fscanf(fpin2, "%d", point);
            fclose(fpin2); break; }
        if (counter==lines && (strcmpi(name, buf) != 0) ){
            printf("in esm dar list nist chikar mikoni? 1.entekab az list 2.karbar jadid");
            fflush(stdin);
            scanf("%d",&n);
            if (n==1){chooseuserfromfile(point,name);}
            if (n==2){creatnewuser(name,point);}
        }
    }

}

void creatnewuser(char name[20], int *point) {
    *point = 0;
    char buf[20];
    fflush(stdin);
    printf("esmeto vared kon\n");
    gets(name);
    FILE *fpin, *fp;
    while (1) {
        fpin = fopen("names.txt", "r");
        while (fgets(buf, 20, fpin) != NULL) {
            if (strcmp(name, buf) == 0) {
                printf("in esm ghablan vared shode .ye esm dige vared kon\n");
                gets(name);
                fclose(fpin);
            } else
                break;
        }
        if (strcmp(name, buf) != 0)
            break;

    }
   // strcpy(name, buf);
    fp = fopen("names.txt", "a");
    fprintf(fp, "\n%s", name);
    fclose(fp);
    fp = fopen("points.txt", "a");
    fprintf(fp, "\n%d", *point);
    fclose(fp);
    fp = fopen("scoreboard.txt", "a");
    fprintf(fp, "\n%s%d", name, *point);
    fclose(fp);
}

void matchscores(char name[20], int point) {
    char buf[20];
    int counter, line;
    line = 0;
    counter = 0;
    FILE *fpin = fopen("names.txt", "r");
    fflush(stdin);
    while (fgets(buf, 20, fpin) != NULL) {
        line++;
        if (strcmp(name, buf) == 0) { break; }
    }
    fclose(fpin);
    FILE *fPtr, *fTemp;
    fPtr = fopen("points.txt", "r");
    fTemp = fopen("temp.txt", "W+");
    while ((fgets(buf, 20, fPtr)) != NULL) {
        counter++;
        if (counter == line)
            //fputs(point, fTemp);
        fprintf(fTemp,"%d",point);
        else
            fputs(buf, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove("points.txt");
    rename("temp.txt", "points.txt");
    fPtr = fopen("scoreboard.txt", "r");
    fTemp = fopen("temp.txt", "W+");
    fflush(stdin);
    while ((fgets(buf, 20, fPtr)) != NULL) {
        counter++;
        if (counter == line)
            fprintf(fTemp, "\n%s %d", name, point);
        else
            fputs(buf, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove("scoreboard.txt");
    rename("temp.txt", "scoreboard.txt");

}

void putship(char map[map_size][map_size], int size, struct node **head, int id) {

    int tool1, arz1, tool2, arz2;
    printf(" keshti ba tool %d\n", size);
    if (size == 1) {
        printf("khooneh  ro vared kon:");
        scanf("%d%d", &tool1, &arz1);
        tool1--;
        arz1--;
        while (1) {
            if (map[tool1 ][arz1] == 's' || map[tool1 ][arz1 ] == 'w' || tool1 > map_size-1 || tool1 < 0 ||
                arz1 > map_size-1 || arz1 < 0 ) {
                printf("voroodi eshtebast dobare vared kon");
                scanf("%d%d", &tool1, &arz1);
                tool1--;
                arz1--;
            } else { break; }
        }

        map[tool1][arz1] = 's';
        if (arz1+1!=10){
            map[tool1][arz1+1]='w';
        }
        if (arz1-1!=-1){
            map[tool1][arz1-1]='w';
        }
        if (tool1+1!=10){
            map[tool1+1][arz1]='w';
        }
        if (tool1-1!=-1){
            map[tool1-1][arz1]='w';
        }
       addfront(head,id,size,tool1,arz1,tool1,arz1);
    }
    if (size != 1) {
        printf("khooneh ebteda ro vared kon:");
        scanf("%d%d", &tool1, &arz1);
        tool1--;
        arz1--;
        while (1) {
            int flag;
            flag=0;
            if (tool1+1<size){flag++;}
            else{
                int i=0;
                while (i!=size){
                    if (map[tool1][arz1]=='s' || map[tool1][arz1]=='w'){flag++;}
                    i++;
                    tool1--;
                }
            }
            if (9-tool1+1<size){flag++;}
            else{
                int i=0;
                while (i!=size){
                    if (map[tool1][arz1]=='s' || map[tool1][arz1]=='w'){flag++;}
                    i++;
                    tool1++;
                }
            }
            if (arz1+1<size){flag++;}
            else{
                int i=0;
                while (i!=size){
                    if (map[tool1][arz1]=='s' || map[tool1][arz1]=='w'){flag++;}
                    i++;
                    arz1--;
                }
            }
            if (map_size-arz1<size){flag++;}
            else{
                int i=0;
                while (i!=size){
                    if (map[tool1][arz1]=='s' || map[tool1][arz1]=='w'){flag++;}
                    i++;
                    arz1++;
                }
            }
            if (map[tool1 ][arz1] == 's' || map[tool1][arz1] == 'w'||tool1 > map_size-1 || tool1 < 0 ||
                                            arz1 > map_size-1 || arz1 < 0 || flag==4) {
                printf("voroodi eshtebast dobare vared kon");
                scanf("%d%d", &tool1, &arz1);
                tool1--;
                arz1--;
            } else { break; }
        }
        printf("khooneh enteda ro vared kon:");
        scanf("%d%d", &tool2, &arz2);
        tool2--;
        arz2--;
        while (1) {
            if ((tool1 == tool2 && fabs((float)(arz2 - arz1 +1) )!= ((float)(size))) ||
                (arz1 == arz2 && fabs((double )(tool2 - tool1+1)) != ((double )(size)) ) || map[tool2][arz2] == 'w' ||
                 map[tool2][arz2] == 's') {
                printf("voroodi eshtebast dobare vared kon");
                scanf("%d%d", &tool2, &arz2);
                tool2--;
                arz2--;
            } else
                break;
        }
        int tempx,tempy;
        if ((tool1 == tool2 && arz1 > arz2) || (arz1 == arz2 && tool1 > tool2)){
            tempx=tool2;
            tool2=tool1;
            tool1=tempx;
            tempy=arz2;
            arz2=arz1;
            arz1=tempy;
        }
        addfront(head,id,size,tool1,arz1,tool2,arz2);
        for (int i = tool1; i <=tool2 ; ++i) {
            for (int j = arz1; j <= arz2; ++j) {
                map[i][j]='s';
            }
        }
      /*  if ((tool1 == tool2) && (arz2 > arz1)) {
            for (int i = arz1 ; i <= arz2; ++i) {
                map[tool1][i] = 's';
            }
        } else if ((tool1 == tool2) && (arz1 > arz2)) {
            for (int i = arz2 ; i <= arz1; ++i) {
                map[tool1 - 1][i] = 's';
            }
        } else if ((arz2 == arz1) && (tool2 > tool1)) {
            for (int i = tool1; i <= tool2; ++i) {
                map[i][arz1 - 1] = 's';
            }
        } else if ((arz2 == arz1) && (tool1 > tool2)) {
            for (int i = tool2 ; i <= tool1; ++i) {
                map[i][arz1 - 1] = 's';
            }
        }*/
        if (tool2 == tool1) {
            if (arz1 - 1  != -1) {
                map[tool1][arz1 - 1] = 'w';
            }
            if (arz2+1 != map_size) {
                map[tool1 ][arz2+1] = 'w'; }
            for (int i = arz1 ; i <= arz2; ++i) {
                if (tool1+1!=map_size){
                map[tool1+1][i] = 'w';}
                if (tool1-1!=-1){
                map[tool1 - 1][i] = 'w';}
            }
        }

        if (arz2 == arz1) {
            if (tool1 - 1 != -1) {
                map[tool1 - 1][arz1] = 'w'; }
            if (tool2+1 != map_size) {
                map[tool2][arz1 - 1] = 'w'; }
            for (int i = tool1 ; i <= tool2; ++i) {
                if (arz2+1!=map_size){
                map[i][arz2+1] = 'w';}
                if (arz1-1!=-1){
                map[i][arz1 - 1] = 'w';}
            }
        }

    }

}

void creat_map(char map[map_size][map_size], struct node **head) {
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            map[i][j] = ' ';
        }
    }
    printf("shoma chand ta keshti darin. 1 keshti ba tool 5,2 keshti ba tool 3,3 keshti ba tool 2,4 keshti ba tool 1\n");
    printf(" bayad khoone ebteda va enthaye har keshti ro maloom koni/nmasal: '6 5' yani koone dar khat 6 va sotoon 5\n");
    putship(map, 5, head, 1);
    putship(map, 3, head, 2);
    putship(map, 3, head, 3);
    putship(map, 2, head, 4);
    putship(map, 2, head, 5);
    putship(map, 2, head, 6);
    putship(map, 1, head, 7);
    putship(map, 1, head, 8);
    putship(map, 1, head, 9);
    putship(map, 1, head, 10);

}

void nagshe(char choice[map_size][map_size]) {
    int row, col;
    for (int i = 1; i <=map_size ; ++i) {
        printf("%d",i);
    }
    printf("\n");
    for (int i = 1; i <=2*map_size ; ++i) {
        printf("-");
    }
    printf("\n");
    for (row = 0; row < map_size; row++) {
        printf("|");
        for (col = 0; col < map_size; col++) {
            printf("%c", choice[row][col]);
            printf("|");
        }
        printf("%d", row + 1);
        printf("\n");
        for (int i = 1; i <=2*map_size ; ++i) {
            printf("-");
        }
        printf("\n");
    }
    getchar();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


void player1(int *point1, int *point2, char map2[map_size][map_size], char choice2[map_size][map_size], char name1[20], char map1[map_size][map_size],
             char choice1[map_size][map_size],
             char name2[20], struct node *head11, struct node *head22) {

    int satr, sotoon;
    printf("nobete %s ast\n", name1);
    nagshe(choice2);
    printf("kodoom khooneh?\n");
    scanf("%d%d", &satr, &sotoon);
    sotoon--;
    sotoon--;
    while (1) {
        if (choice2[satr][sotoon] == 'w' || choice2[satr][sotoon] == 's' || choice2[satr][sotoon] == 'b') {
            printf("voroodi ghalate.dobare entekhab kon.\n");
            scanf("%d%d", &satr, &sotoon);
            sotoon--;
            satr--;
        } else { break; }
    }
    if (map2[satr][sotoon] == 'w' || map2[satr][sotoon] == ' ') {
        choice2[satr][sotoon] = 'w';
        nagshe(choice2);
        player2(point1, point2, map2, choice2, name1, map1, choice1, name2, head1, head2);
    } else if (map2[satr][sotoon] == 's') {
        choice2[satr][sotoon] = 's';
        (*point1)++;
        check(satr, sotoon, head22, choice2, point1);
        if (head22 == NULL) {
            printf("%s win!", name1);
            exit(1);
        }
        nagshe(choice2);
        player1(point1, point2, map2, choice2, name1, map1, choice1, name2, head1, head2);
    }

}

void player2(int *point1, int *point2, char map2[map_size][map_size], char choice2[map_size][map_size], char name1[20], char map1[map_size][map_size],
             char choice1[map_size][map_size],
             char name2[20], struct node *head11, struct node *head22) {
    int satr, sotoon;
    printf("nobete %s ast\n", name2);
    nagshe(choice1);
    printf("kodoom khooneh?\n");
    scanf("%d%d", &satr, &sotoon);
    satr--;
    sotoon--;
    while (1) {
        if (choice1[satr][sotoon] == 'w' || choice1[satr][sotoon] == 's' || choice1[satr][sotoon] == 'b') {
            printf("voroodi ghalate.dobare entekhab kon.\n");
            scanf("%d%d", &satr, &sotoon);
            satr--;
            sotoon--;
        } else { break; }
    }
    if (map1[satr][sotoon] == 'w' || map1[satr][sotoon] == ' ') {
        choice1[satr][sotoon] ='w';
        nagshe(choice1);
        player1(point1, point2, map2, choice2, name1, map1, choice1, name2, head1, head2);
    } else if (map1[satr][sotoon] == 's') {
        choice1[satr][sotoon] ='s';
        (*point2)++;
        check(satr, sotoon, head11, choice1, point2);
        if (head11 == NULL) {
            printf("%s win!", name2);
            exit(1);
        }
        nagshe(choice1);
        player1(point1, point2, map2, choice2, name1, map1, choice1, name2, head1, head2);

    }

}

void bot_craetmap(char bot_map[map_size][map_size],struct node **head) {
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            bot_map[i][j] = ' ';
        }
    }
    addfront(head,1,5,0,4,0,8);
    addfront(head,2,3,3,9,5,9);
    addfront(head,3,3,9,6,9,8);
    addfront(head,4,2,0,1,0,2);
    addfront(head,5,2,1,0,2,0);
    addfront(head,6,2,9,2,9,3);
    addfront(head,7,1,3,4,3,4);
    addfront(head,8,1,5,5,5,5);
    addfront(head,9,1,1,9,1,9);
    addfront(head,10,1,7,9,7,9);

    bot_map[1][0] = 's';
    bot_map[2][0] = 's';
    bot_map[0][1] = 's';
    bot_map[0][2] = 's';
    bot_map[0][4] = 's';
    bot_map[0][5] = 's';
    bot_map[0][6] = 's';
    bot_map[0][7] = 's';
    bot_map[0][8] = 's';
    bot_map[3][4] = 's';
    bot_map[5][5] = 's';
    bot_map[1][9] = 's';
    bot_map[3][9] = 's';
    bot_map[4][9] = 's';
    bot_map[5][9] = 's';
    bot_map[9][2] = 's';
    bot_map[9][3] = 's';
    bot_map[9][6] = 's';
    bot_map[9][7] = 's';
    bot_map[7][9] = 's';
    bot_map[9][8] = 's';
    bot_map[0][0] = 'w';
    bot_map[0][0] = 'w';
    bot_map[0][3] = 'w';
    bot_map[0][9] = 'w';
    bot_map[8][9] = 'w';
    bot_map[7][8] = 'w';
    bot_map[1][1] = 'w';
    bot_map[1][2] = 'w';
    bot_map[2][1] = 'w';
    bot_map[3][0] = 'w';
    bot_map[3][3] = 'w';
    bot_map[3][5] = 'w';
    bot_map[3][8] = 'w';
    bot_map[1][4] = 'w';
    bot_map[1][5] = 'w';
    bot_map[1][6] = 'w';
    bot_map[1][7] = 'w';
    bot_map[1][8] = 'w';
    bot_map[2][4] = 'w';
    bot_map[2][9] = 'w';
    bot_map[4][0] = 'w';
    bot_map[4][5] = 'w';
    bot_map[4][4] = 'w';
    bot_map[4][8] = 'w';
    bot_map[5][1] = 'w';
    bot_map[5][4] = 'w';
    bot_map[5][6] = 'w';
    bot_map[5][8] = 'w';
    bot_map[6][0] = 'w';
    bot_map[6][5] = 'w';
    bot_map[6][9] = 'w';
    bot_map[8][2] = 'w';
    bot_map[8][3] = 'w';
    bot_map[8][6] = 'w';
    bot_map[8][7] = 'w';
    bot_map[8][8] = 'w';
    bot_map[9][1] = 'w';
    bot_map[9][4] = 'w';
    bot_map[9][5] = 'w';
    bot_map[9][9] = 'w';

}

void playwithbot(int *point,int *bot_point, char name[20], char choice[map_size][map_size], char map[map_size][map_size], char bot_choice[map_size][map_size],
                 char bot_map[map_size][map_size],
                 struct node *head11,struct node *head22) {
int satr, sotoon;
printf("nobete %s ast\n", name);
printf("kodoom khooneh?\n");
scanf("%d%d", &satr, &sotoon);
satr--;
sotoon--;
while (1) {
if (bot_choice[satr][sotoon] == 'w' || bot_choice[satr][sotoon] == 's' || bot_choice[satr][sotoon] == 'b') {
printf("voroodi ghalate.dobare entekhab kon.\n");
scanf("%d%d", &satr, &sotoon);
satr--;
sotoon--;
} else {
break; }
}
if (bot_map[satr][sotoon] == 'w' || bot_map[satr][sotoon] == ' ') {
bot_choice[satr][sotoon] ='w';
nagshe(bot_choice);
botplay(point,bot_point, name, choice, map, bot_choice, bot_map,head11,head22
);
} else if (bot_map[satr][sotoon] == 's') {
bot_choice[satr][sotoon] = 's';
    (*point)++;
check(satr,sotoon,head22,bot_choice,point);
    if (head22 == NULL) {
        printf("%s win!", name);
        exit(1);
    }
nagshe(bot_choice);
playwithbot(point,bot_point,name, choice, map, bot_choice, bot_map,head11,head22);
}

}

void botplay(int *point,int *bot_point,char name[20], char choice[map_size][map_size], char map[map_size][map_size], char bot_choice[map_size][map_size],
             char bot_map[map_size][map_size],struct node*head11,struct node*head22) {
    int satr, sotoon;
    time_t t = time(NULL);
    srand(t);
    satr = rand() % map_size;

    sotoon = rand() % map_size;
    while (1) {
        if (choice[satr][sotoon] == 'w' || choice[satr][sotoon] == 's' || choice[satr][sotoon] == 'b') {

            satr = rand() % map_size;

            sotoon = rand() % map_size;
        } else { break; }
    }
    if (map[satr][sotoon] == 's') {
        choice[satr][sotoon] = 's';
        bot_point++;
        check(satr,sotoon,head11,choice,bot_point);
        if (head11 == NULL) {
            printf("bot win!");
            exit(1);
        }
        nagshe(choice);
        botplay(point,bot_point, name, choice, map, bot_choice, bot_map,head11,head22);
    } else if (map[satr][sotoon] == 'w' || map[satr][sotoon] == ' ') {
        choice[satr][sotoon] = 'w';
        nagshe(choice);
        playwithbot(point,bot_point, name, choice, map, bot_choice, bot_map,head11,head22);
    }
}

void check(int satr, int sotoon, struct node *head, char choice[map_size][map_size], int *point) {
    struct node *current = head;
    while (current != NULL) {
        if (satr >= current->ship.x1 && satr <= current->ship.x2 && sotoon >= current->ship.y1 &&
            sotoon <= current->ship.y2) {
            int id = current->id;
            current->ship.health = (current->ship.health) - 1;
            if (current->ship.health == 0) {
                for (int i = current->ship.x1; i <= current->ship.x2; ++i) {
                    for (int j = current->ship.y1; j <= current->ship.y2; ++j) {
                        choice[i][j] = 'E';
                        *point += ((5 * 5) / current->ship.size);
                    }
                }
                if (current->ship.size==1){
                    if (current->ship.y1+1!=map_size){
                        choice[current->ship.x1][current->ship.y1+1]='w';
                    }
                    if (current->ship.y1 -1!=-1){
                        choice[current->ship.x1][current->ship.y1-1]='w';
                    }
                    if (current->ship.x1 +1!=map_size){
                        choice[current->ship.x1+1][current->ship.y1]='w';
                    }
                    if (current->ship.x1 -1!=-1){
                        choice[current->ship.x1-1][current->ship.y1]='w';
                    }
                }
                if (current->ship.size!=1){
                    if (current->ship.x1 == current->ship.x2) {
                        if (current->ship.y1 - 1  != -1) {
                            choice[current->ship.x1][current->ship.y1 - 1] = 'w';
                        }
                        if (current->ship.y2+1 != map_size) {
                            choice[current->ship.x1 ][current->ship.y2+1] = 'w'; }
                        for (int i = current->ship.y1 ; i <= current->ship.y2; ++i) {
                            if (current->ship.x1+1!=map_size){
                                choice[current->ship.x1+1][i] = 'w';}
                            if (current->ship.x1-1!=-1){
                                choice[current->ship.x1 - 1][i] = 'w';}
                        }
                    }

                    if (current->ship.y1 == current->ship.y2) {
                        if (current->ship.x1 - 1 != -1) {
                            choice[current->ship.x1 - 1][current->ship.y1] = 'w'; }
                        if (current->ship.x2+1 != map_size) {
                            choice[current->ship.x2][current->ship.y1 - 1] = 'w'; }
                        for (int i = current->ship.x1 ; i <= current->ship.x2; ++i) {
                            if (current->ship.y2+1!=map_size){
                                choice[i][current->ship.y2+1] = 'w';}
                            if (current->ship.y1-1!=-1){
                                choice[i][current->ship.y1 - 1] = 'w';}
                        }
                    }

                }

                deletenode(&head, id);
            }
        }
        current = current->next;
    }
}