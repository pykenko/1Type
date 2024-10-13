#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#define SIZE 15

#define HEIGHT 6
#define WIDTH 6
int combo_count;
int playerx = 0;
int playery = 0;
int moves = 15;
int candy_run = 1;
int total_score = 0;
char global_username[20];
int user_author = 0;
int real_menuu = 1;
// this code if from renko dont copy!
#define COLOR_A FOREGROUND_RED | FOREGROUND_INTENSITY // ini merah
#define COLOR_B FOREGROUND_GREEN | FOREGROUND_INTENSITY // hijau
#define COLOR_C FOREGROUND_BLUE | FOREGROUND_INTENSITY // biru
#define COLOR_D FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY // kuning jalan jalan beli ketoprak, ketoprak

void fix_candy_that_gone_gone();

char map[6][6] = {
	{' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' '}
};

void candy_map(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i;int j;
	system("cls");
	printf("==============================\n");
	printf(" =         combo %5d      =\n",combo_count);
	printf("==============================\n");
	printf(" =         score %5d      =\n",total_score);
	printf("==============================\n");
	printf(" =         moves %5d      =\n",moves);
	printf("==============================\n");
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			if(i == playerx && j == playery){
				printf(":[%c]:",map[i][j]);
			} else{
				switch(map[i][j]){
					case '1':
                    SetConsoleTextAttribute(hConsole, COLOR_A);
                    break;
                case '2':
                    SetConsoleTextAttribute(hConsole, COLOR_B);
                    break;
                case '3':
                    SetConsoleTextAttribute(hConsole, COLOR_C);
                    break;
                case '4':
                    SetConsoleTextAttribute(hConsole, COLOR_D);
                    break;
				}
				printf(" [%c] ", map[i][j]);
				SetConsoleTextAttribute(hConsole, 7); // supaya user warna putih biar lebih gampang ya ges ya soalny klo putih semua pusing
			}
		}
		printf("\n");
	}
}

void give_candy(){
	int i;int j;
	char can[] = {'1','2','3','4'};
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			if(map[i][j] == ' '){
				int dy = rand() % 4;
				map[i][j] = can[dy];
			}
		}
		candy_map();
		Sleep(100);
		printf("\n");
	}
}

void move_position(char move){
	switch(move){
		case 'w':
			if(playerx > 0) playerx--;break;
		case 's':
			if(playerx < HEIGHT - 1)playerx++;break;
		case 'a':
			if(playery > 0) playery--;break;
		case 'd':
			if(playery < WIDTH - 1) playery++;break;
	}
}

void move_candy(){
	int moved = 0;
	
	int current_x = playerx;
	int current_y = playery;
	char temp_candy = map[current_x][current_y];
//	int restricted = map[playerx - 1][playery - 1];
//	int restricted1 = map[playerx + 1][playery + 1];
//	int restricted2 = map[playerx - 1][playery + 1];
//	int restricted3 = map[playerx + 1][playery - 1];
	while(moved == 0){
		char move = getch();
		switch(move){
			case 'w':
				if(playerx > 0 && (current_x - 1) < playerx)playerx--;
					candy_map();
					break;
			case 's':
				if(playerx < HEIGHT - 1 && (current_x + 1) > playerx)playerx++;
					candy_map();
					break;
			case 'a':
				if(playery > 0 && (current_y - 1) < playery) playery--;
					candy_map();
					break;
			case 'd':
				if(playery < WIDTH - 1 && (current_y + 1) > playery) playery++;
					candy_map();
					break;
			case '\r':
					moved = 1;
					// this code if from renko dont copy!
					map[current_x][current_y] = map[playerx][playery];
					map[playerx][playery] = temp_candy;
					moves--;
					break;
		}
	}
}

void check_candy_explode_boom_tline(){
	int i;int j;
	for(i = 0;i<HEIGHT;i++){
		for(j = 0;j<WIDTH;j++){
			if(map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] == map[i][j-1] && map[i][j] == map[i][j-2] && map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-2] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+2][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 100;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] == map[i][j-1] && map[i][j] == map[i][j-2] && map[i][j] == map[i-1][j] && map[i][j] == map[i-2][j] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-2] = ' ';
				candy_map();
				Sleep(100);
				map[i-1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i-2][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 100;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i+1][j] && map[i][j] == map[i-1][j] && map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i-1][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 100;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i+1][j] && map[i][j] == map[i-1][j] && map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-2] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i-1][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 100;
				fix_candy_that_gone_gone();
				combo_count++;
			}
		}
	}
}

void check_candy_explode_boom_Lline(){
	int i;int j;
	for(i = 0;i<HEIGHT;i++){
		for(j = 0;j<WIDTH;j++){
			if(map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+2][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 75;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i][-1] && map[i][j] == map[i][j-2] && map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-2] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+2][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 75;
				// this code if from renko dont copy!
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i][j-1] && map[i][j] == map[i][j-2] && map[i][j] == map[i-1][j] && map[i][j] == map[i-2][j] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j-2] = ' ';
				candy_map();
				Sleep(100);
				map[i-1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i-2][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 75;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] == map[i-1][j] && map[i][j] == map[i-2][j] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				map[i-1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i-2][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 75;
				fix_candy_that_gone_gone();
				combo_count++;
			}
		}
	}
}

void check_candy_explode_boom_5line(){
	int i;int j;
	for(i = 0;i<HEIGHT;i++){
		for(j = 0;j<WIDTH;j++){
			if(map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] == map[i][j+3] && map[i][j] == map[i][j+4] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+3] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+4] = ' ';
				candy_map();
				Sleep(100);
				total_score += 50;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j] && map[i][j] == map[i+3][j] && map[i][j] == map[i+4][j] && map[i][j] != ' ' && i <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+2][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+3] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+4] = ' ';
				candy_map();
				Sleep(100);
				total_score += 50;
				fix_candy_that_gone_gone();
				combo_count++;
			}
		}
	}
}

void check_candy_explode_boom_4line(){
	int i;int j;
	for(i = 0;i<HEIGHT;i++){
		for(j = 0;j<WIDTH;j++){
			if(map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] == map[i][j+3] && map[i][j] != ' ' && j <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+3] = ' ';
				candy_map();
				Sleep(100);
				total_score += 10;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j] && map[i][j] == map[i+3][j] && map[i][j] != ' ' && i <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+2][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+3] = ' ';
				candy_map();
				Sleep(100);
				total_score += 10;
				fix_candy_that_gone_gone();
				combo_count++;
			}
		}
	}
}
// this code if from renko dont copy!
void check_candy_explode_boom_3line(){
	int i;int j;
	for(i = 0;i<HEIGHT;i++){
		for(j = 0;j<WIDTH;j++){
			if(map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2] && map[i][j] != ' ' && j <= 5){
				// this code if from renko dont copy!
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+1] = ' ';
				candy_map();
				Sleep(100);
				map[i][j+2] = ' ';
				candy_map();
				Sleep(100);
				total_score += 5;
				fix_candy_that_gone_gone();
				combo_count++;
			}
			
			if(map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j] && map[i][j] != ' ' && i <= 5){
				map[i][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+1][j] = ' ';
				candy_map();
				Sleep(100);
				map[i+2][j] = ' ';
				candy_map();
				Sleep(100);
				total_score += 5;
				fix_candy_that_gone_gone();
				combo_count++;
			}
		}
	}
	
//	for(i = 0;i<HEIGHT;i++){
//		for(j = 0;j<WIDTH;j++){
//			
//		}
//	}
}

//void fall(char array[ROWS][COLS], int col) {
//    int row;
//    for (row = ROWS - 1; row >= 0; row--) {
//        if (array[row][col] == ' ') {
//            array[row][col] = 'O';
//            break;
//        }
//    }
//}

void fix_candy_that_gone_gone(){
	char can[] = {'1','2','3','4'};
	int i;int j;int ilovecandy;
	for(ilovecandy = 0; ilovecandy < 10; ilovecandy++){
		// this code if from renko dont copy!
//		check_candy_explode_boom_5line();
//		check_candy_explode_boom_4line();
//		check_candy_explode_boom_3line();
		for(i = 0;i<HEIGHT;i++){
			for(j = 0;j<WIDTH;j++){
				if(map[i][j] == ' '){
					int temp;
					for(temp = i;temp > 0;temp--){
						map[temp][j] = map[temp-1][j];
					}
				}
			}
		}
//		check_candy_explode_boom_5line();
//		check_candy_explode_boom_4line();
//		check_candy_explode_boom_3line();
		for(i = 0;i<HEIGHT;i++){
			for(j = 0;j<WIDTH;j++){
				if(map[i][j] == ' '){
					int dy = rand() % 4;
					map[i][j] = can[dy];
				}
			}
		}
	}
}

void candy_boom(){
	combo_count = 0;
	int i;
	for(i = 0; i < 5;i++){
		check_candy_explode_boom_tline();
		check_candy_explode_boom_Lline(); 
		check_candy_explode_boom_5line();
		check_candy_explode_boom_4line();
		check_candy_explode_boom_3line();
	}
	if(10 > combo_count > 7){
		total_score += 200;
	} else if(15 > combo_count > 10){
		total_score += 300;
		moves++;
	} else if(combo_count > 15){
		total_score += 500;
		moves += 3;
	}
}

void update_highscore(int new_score){
	char a[21];char b[21];int score;
	int congrats = 0;
	FILE *ptk = fopen("users.txt", "r");
	if(ptk == NULL){
		printf("failed");
		return;
	}
	
	char temp[1024];
	char data[1024] = "";
	
	while(fscanf(ptk, "%d$%[^$]$%s\n",&score,a,b) == 3) {
		if(strcmp(a, global_username ) == 0){
			if(new_score > score){
				score = new_score;
				congrats = 1;
			}
		}
		sprintf(temp, "%d$%s$%s\n", score, a, b);
		strcat(data, temp);
	}
	fclose(ptk);
	
	ptk = fopen("users.txt", "w");
	if(ptk == NULL){
		printf("failed");
		return;
	}
	
	fputs(data, ptk);
	
	fclose(ptk);
	if(congrats == 1){
		printf("congratulations on a new highscore of %d\n", new_score);
		printf("press any key to continue");
		getch();
	} else {
		printf("better luck next time\n");
		printf("press any key to continue");
		getch();
	}
}











void candy_loop(){
	give_candy();
	while(candy_run = 1 && moves > 0){
		candy_map();
		char a = getch();
		if(a == 'q')break;
		if(a == '\r')move_candy();
		candy_boom();
//		fix_candy_that_gone_gone();
		move_position(a);
	}
	update_highscore(total_score);
	
	real_menuu = 1;
}
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // this code if from renko dont copy!
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set cursor visibility to FALSE
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}



void old_main(){
	hideCursor();
	system("cls");
	srand(time(0));
	printf("project ");
	Sleep(100);
	printf("candy ");
	Sleep(100);
	printf("crush\n");
	Sleep(100);
	candy_loop();
}









struct users{
	char username[21];
	char password[21];
	int score;
	struct users *next;
	struct users *prev;
}*head, *tail;

struct users *createUser(char username[],char password[],int score){
	struct users *User = (struct users*)malloc(sizeof(struct users));
	// this code if from renko dont copy!
	User->next = NULL;
	User->prev = NULL;
	User->score = score;
	strcpy(User->username, username);
	strcpy(User->password, password);
	return User;
}

struct users *players[SIZE];

// this code if from renko dont copy!
int ndex(char user[]){
	int length = strlen(user);
	int i;int total = 0;
	for(i = 0;i < length;i++){
		total += user[i];
	}
	total %= SIZE;
	return total;
}

void insert_hash(char name[], char password[], int score){
	int idx = ndex(name);
	struct users *temp = createUser(name,password,score); 
	int curr = (idx + 1) % SIZE;
	if(players[idx] == NULL){
		players[idx] = temp;
		return;
	}
	while(curr != idx){
		if(players[curr] == NULL){
			players[curr] = temp;
			return;
		}
		curr = (curr+1) % SIZE;
	}
}

void bubble_hash(struct users *arr[], int n){
	int i; int j;
	struct users *temp;
	for(i=0;i < n - 1 ;i++){
		for(j = 0;j < n - 1;j++){
			if(arr[j]->score < arr[j + 1]->score){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

void hall_of_sigma(){
	struct users *temp[SIZE];
	int count = 0;int i;
	
	for(i=0;i<SIZE;i++){
		if(players[i] != NULL){
			temp[count] = players[i];
			count++;
		}
	}
	bubble_hash(temp, count); 
	int j;
	for(j=0;j<10;j++){
		printf("%2d |users : %10s | %d\n",(j+1), temp[j]->username, temp[j]->score );
	}
}

void list_hash(){
	hall_of_sigma(); 
}

void color_text(int color){
    if(color == -1)
    {
        printf("\x1B[0;39m");
        return;
    }
    printf("\x1B[1;%dm", 30 + color);
}

/////////////////////   hashing logic
char *hash(char name[]){
	int length = strlen(name);
	static char hashed[123];
	int i;
	for(i = 0;i<length;i++){
		if((name[i] + 10) < 123){
			hashed[i] = name[i] + 10; 
		} else {
			hashed[i] = name[i] + 10 - 26;
		}
	}
	hashed[i] = '\0';
	return hashed;
}



////////////////////////////////////
/////////FILE
////////////////////////////////////
void registering(char name[], char password[]){
	FILE *ptk = fopen("users.txt", "a");
	if(ptk == NULL)printf("error");
	fprintf(ptk,"0$%s$%s\n", name, password);
	fclose(ptk);
	printf("success!");
}

void user_true(){
	char a[21]; char b[21]; int score;
	FILE *ptk = fopen("users.txt", "r");
	if(ptk == NULL)printf("no one in the file");
	while(ptk != NULL){
		fscanf(ptk, "%d$%[^$]$%s\n",&score,a,b);
		insert_hash(a,b,score);
		if(feof(ptk)){
			break;
		}
	}
	fclose(ptk);
}

void logining(char name[], char password[]){
	int i;
	char *temp = hash(password);
	for(i=0;i<SIZE;i++){
		if(players[i] != NULL){
			if(strcmp(name, players[i]->username ) == 0 && strcmp(temp, players[i]->password) == 0){
				user_author = 1;
				break;
			}
		}
		printf("not authorized");
	}
}
// this code if from renko dont copy!
//void logining(char name[], char password[]){
//	char a[101];char b[101];
//	char *temp = hash(password);
//	FILE *ptk = fopen("users.txt", "r");
//	if(ptk == NULL)printf("error");
//	while(ptk != NULL){
//		fscanf(ptk, "%[^$]$%s\n",a,b);
//		if(strcmp(a,name) == 0 && strcmp(b,temp) == 0){
//			user_author = 1;
//			return;
//		} else if(feof(ptk)){
//			printf("didnt find");
//			break;
//		}
//	}
//	fclose(ptk);
//}



////////////////////////   first menu
int menu_choice = 0;
void print_menu(){
	system("cls");
//	printf("%d\n\n", menu_choice);
	color_text(7);
	printf("Welcome 2 1type\n");
	if(menu_choice == 0){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("login\n");// 0
	if(menu_choice == 1){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("register\n");// 1
	if(menu_choice == 2){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("Hall of fame\n");// 2
	if(menu_choice == 3){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("Exit game\n");// 3
}

////////////////////////   calling to use
void login_page();
void register_page();
void hall_of_fame_page();

///////////////////////   menu movement and logic
int menu = 1;
void main_menu(){
	hideCursor();
	user_true();
	while(menu){
		print_menu();
//		list_hash();
//		if(_kbhit()){
			char type = getch();
			switch(type){
				case 's':
					if(menu_choice < 3){
						menu_choice++;
					}
					break;
				case 'w':
					if(menu_choice > 0){
						menu_choice--;
					}
					break;
				case '\r':
					menu = 0;
					switch(menu_choice){
						case 0:
							login_page();
							break;
						case 1:
							register_page();
							break;
						case 2:
							hall_of_fame_page();
							break;
						case 3:
							color_text(7);
							printf("exiting...");
							break;
					}
				default:
					continue;
			}
//		}
	}
}

//////////////////////////////////
//////////////////game menu
//////////////////////////////////
int real_hall = 0;
int real_menu_choice = 0;
void print_real_menu(){
	system("cls");
//	printf("%d\n\n", menu_choice);
	color_text(7);
	printf("Welcome 2 1type, ");
	color_text(5);
	printf("%s\n", global_username);
	if(real_menu_choice == 0){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("Play game\n");// 0
	if(real_menu_choice == 1){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("Hall of fame\n");// 1
	if(real_menu_choice == 2){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("Log out\n");// 2
	if(real_menu_choice == 3){
		color_text(2); 
	} else {
		color_text(7);	
	}
	printf("Exit game\n");// 3
}
// this code if from renko dont copy!

void real_menu(){
	hideCursor();
	while(real_menuu){
//		user_true();
		print_real_menu();
//		if(_kbhit()){
			char type = getch();
			switch(type){
				case 's':
					if(real_menu_choice < 3){
						real_menu_choice++;
					}
					break;
				case 'w':
					if(real_menu_choice > 0){
						real_menu_choice--;
					}
					break;
				case '\r':
					real_menuu = 0;
					switch(real_menu_choice){
						case 0:
							//play
							old_main();
							break;
						case 1:
							real_hall = 1;
							hall_of_fame_page();
//							printf("%d", real_hall);
//							getch();
							break;
						case 2:
							//log out
							system("cls");
							printf("press any key to continue\n\n\n\n\n\n\n\n\n\n\n");
							getch();
							real_menuu = 0;
							menu = 1;
							global_username[0] = '\0';
							user_author = 0;
							break;
							}
						case 3:
							color_text(7);
							printf("exiting...");
							break;

				default:
					continue;
			}
//		}
	}
}


/////////////////////////////login
void login_page(){
	hideCursor();
	int loginn = 1;
	char username[21];
	char password[21];
	while(loginn){
	system("cls");
	// this code if from renko dont copy!
	printf("Hello how are you this is my login page and i dont know what to write\n\n");
	printf("username : <enter to start typing 'q' to go back> ");
	char a = getch();
	switch(a){
		case '\r':
			// username
			do{
				system("cls");
				printf("Hello how are you this is my login page and i dont know what to write\n\n");
				printf("username : ");
				scanf("%s", username);
				if(strlen(username) < 5)printf("username must be atleast 5 characters!\n");
				if(strlen(username) > 10)printf("username cannot be more than 10 characters!\n");
			} while(strlen(username) < 5 || strlen(username) > 10);
			// password
			do{
				printf("password : ");
				scanf("%s", password);
				if(strlen(password) < 3)printf("password must be atleast 3 characters!\n");
				// this code if from renko dont copy!
				if(strlen(password) > 10)printf("password cannot be more than 10 characters!\n");
			} while(strlen(password) < 3 || strlen(password) > 10);
			logining(username, password);
			if(user_author == 1){
				real_menuu = 1;
				strcpy(global_username, username);
				real_menu();
			}
			loginn= 0;
			break;
		case 'q':
			loginn = 0;
			menu = 1;
			break;
		default:
			printf("\nstop holding the wrong key!");
			break;
	}
	}
}

int username_taken(char user[]){
	int i;
	for(i=0;i<SIZE;i++){
		if(players[i] != NULL){
			if(strcmp(user, players[i]->username) == 0){
				return 1;
			}
		}
	}
	return 0;
}

/////////////////////////////register
void register_page(){
//	user_true();
	hideCursor();
	char username[21];
	char password[21];
	int regis = 1;
	while(regis){
	system("cls");
	printf("register?\n\n");
	printf("pick a username [5-20] : <enter to start typing 'q' to go back> ");
	char a = getch();
	switch(a){
		case '\r':
			// username
			do{
				system("cls");
				printf("regregregister\n\n");
				printf("pick a username [5-10] : ");
				scanf("%s", username);
				if(strlen(username) < 5)printf("username must be atleast 5 characters!\n");
				// this code if from renko dont copy!
				if(strlen(username) > 10)printf("username cannot be more than 10 characters!\n");
				if(username_taken(username) == 1){
					printf("username taken!\n");
					getch();
				}
			} while(strlen(username) < 5 || strlen(username) > 10 || username_taken(username) == 1);
			// password
			do{
				printf("password [3-10] : ");
				scanf("%s", password);
				if(strlen(password) < 3)printf("password must be atleast 3 characters!\n");
				if(strlen(password) > 10)printf("password cannot be more than 10 characters!\n");
			} while(strlen(password) < 3 || strlen(password) > 10);
			char *hashed_pass = hash(password);
			registering(username, hashed_pass);
			printf("\n\npress any key to return");
			getch();
			regis = 0;
			menu = 1;
			break;
		case 'q':
			regis = 0;
			menu = 1;
			break;
		default:
			break;
	}
	}
}


////////////////////////////////   hall of fame
void hall_of_fame_page(){
	hideCursor();
	system("cls");
	printf("hall of fame\n");
	printf("bro thinks he is in the hall of fame\n");
	printf("===================================================\n");
	list_hash();
	printf("\npress any key to go back");
//	printf("\n\n\n\n\n\n\nps, im still working on the score");
//	getch();
	if(real_hall == 1){
//		printf("huh");
		real_menuu = 1;
		getch();
	} else {
//		printf("hahaha");
		menu = 1;
		getch();
	}
}

int main(){
	main_menu();
}
