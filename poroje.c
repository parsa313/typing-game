#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <dir.h>
char username[40];
int password;
float totalscore = 0.0;
//calculating score of the user for each word
float calscore(int time1, int time2, int pause_time, int wrongchar, int word_length, int level)
{
	int play_time = (time2 - time1) - pause_time;
	float score = ((float)(word_length *2 - wrongchar) / play_time) *(10 + level) / 10.0;
	return score;

}
void introduction(void) //explaining the game for new user
{
    printf("                                welcome\n");
    SetColor(14);
    printf("this game evaluates your typing speed and you should type shown words as fast as you can\n");
    SetColor(15);
    printf("your total score is compared with others if you want\n");
    printf("during entering the words you can press");
    SetColor(12);
    printf(" P ");
    SetColor(15);
    printf("for pause and unpause and ");
    SetColor(12);
    printf("E ");
    SetColor(15);
    printf("for exiting the game\n");
    printf("you should press");
    SetColor(12);
    printf(" s ");
    SetColor(15);
    printf("for starting the game and ");
    SetColor(12);
    printf("c ");
    SetColor(15);
    printf("for continueing the game\n");
    printf("press y for yes and n for no\n");
    Sleep(15000);
    system("cls");
}
void makelowecase(char* word, int word_length)
{
    int i;
    for( i = 0; i<word_length; i++)
{
  word[i] = tolower(word[i]);
}
}
void countdown(void)//counddown for user that entered wrong user and pass 5 times
{

    int i;
    for(i=300;i>=1;i--)
    {
        printf("try again in ");
        int minute=i/60;
        int second=i%60;
        printf("%d:%d",minute,second);
        Sleep(1000);
        system("cls");
    }
}
void prepare(void) //preperation for start entering the words
{
	int i;
	for (i = 3; i >= 1; i--)
	{
		printf("%d", i);
		Sleep(1000);
		system("cls");
	}

	printf("START");

}

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes &0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}

	return;
}

void compare(void) //comparing user with others and show user rank
{
	int level, pass, i, j;
	float score, a;
	int linenumber = 0;
	char c, nam[30];
	char line[40];
	FILE *fp = fopen("user1.txt", "a+");
	rewind(fp);
	c = getc(fp);
	for (c = getc(fp); c != EOF; c = getc(fp))	//number of lines in file
	{
		if (c == '\n')
			linenumber = linenumber + 1;
	}

	float *scores = malloc(linenumber* sizeof(float));	//dynamicly creating an array
	rewind(fp);
	for (i = 0; i < linenumber; i++)
	{
		fgets(line, 40, fp);
		sscanf(line, "%s %d %d %f", nam, &pass, &level, &score);	//reading scores from file in storing it in array

		scores[i] = score;
	}

	for (i = 0; i < linenumber; ++i)	//sorting scores in decending order
	{
		for (j = i + 1; j < linenumber; ++j)
		{
			if (scores[i] < scores[j])
			{
				a = scores[i];
				scores[i] = scores[j];	//replacing with third variable
				scores[j] = a;

			}
		}
	}

	for (i = 0; i < linenumber; i++)	//showing person rank
	{
		if (scores[i] == totalscore)
		{
			printf("you are %d best player\n", i + 1);
			break;
		}
	}

	free(scores);
	fclose(fp);
}

void save(int level)	//copying old content and current user content into another file then removing old file and renaming new file to old file name
{
	int pass, levels;
	int linenumber = 0;
	float score;
	char nam[30];
	char line[20];
	FILE *fp2 = fopen("user2.txt", "w");	//creating user2 text file
	FILE *fp1 = fopen("user1.txt", "r");
	if (fp1 == NULL)
		printf("file did not open");

	while (fscanf(fp1, "%s %d %d %f", nam, &pass, &levels, &score) == 4)
	{
		if ((strcmp(nam, username) != 0) || (pass != password))	//copying all data except the user data to another file
		{
			fprintf(fp2, "%s %d %d %f\n", nam, pass, levels, score);

		}
	}

	fprintf(fp2, "%s %d %d %f\n", username, password, level, totalscore);	//add current user information to file
	fclose(fp1);
	fclose(fp2);
	int remove_operation_result = remove("user1.txt");	//if succesful returns 0
	int rename_operation_result = rename("user2.txt", "user1.txt");	//if succesful returns 0
	if (remove_operation_result == 0 && rename_operation_result == 0)	//if both rename and remove were succesful so the saving was succesful
		printf("File saved successfully\n");
	else
		printf("unable to save the file\n");
}

float game(int level)
{
	int i, j, time1, time2, pause1, pause2;
	int flag = 0;
	char stop_pause;
	float level_score = 0.0;
	char c, entered_char, choose;
	int linenumber = 0;
	FILE * fp;
	switch (level)	//opening right file based on level the player is
	{
		case 1:
			{
				fp = fopen("LO1.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 2:
			{
				fp = fopen("level2.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 3:
			{
				fp = fopen("level3.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 4:
			{
				fp = fopen("level4.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 5:
			{
				fp = fopen("level5.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 6:
			{
				fp = fopen("level6.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 7:
			{
				fp = fopen("level7.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 8:
			{
				fp = fopen("level8.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 9:
			{
				fp = fopen("level9.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;
		case 10:
			{
				fp = fopen("level10.txt", "a+");
				if (fp == NULL)
					printf("file did not open\n");
			}

			break;

	}

	c = getc(fp);
	for (c = getc(fp); c != EOF; c = getc(fp))	//number of lines in file
	{
		if (c == '\n')
			linenumber = linenumber + 1;
	}

	rewind(fp);

	char **words;	//array of strings
	words = malloc(sizeof(char*) *linenumber);	//dynamicly allocating array of strings
	for (i = 0; i < linenumber; i++)
	{
		words[i] = malloc(sizeof(char) *20);	//20 is maximum character in each line
		fgets(words[i], 20, fp);

	}


	system("cls");
	prepare();
	Sleep(900);
	for (i = 1; i <= 25; i++)	//in each level 25 words should be showed
	{
		int wrongchar = 0;
		int pause_time = 0;
		srand(time(NULL));
		int num = rand();
		int accidentnumber = num % linenumber;
		system("cls");
        makelowecase(words[accidentnumber],strlen(words[accidentnumber]));
		printf("%s\n", words[accidentnumber]);
		time1 = time(NULL);

		for (j = 0; j < strlen(words[accidentnumber]) - 1; j++)	//strlen returns one more than string length
		{
			entered_char = getch();
			if (entered_char == 'P')
			{
				pause1 = time(NULL);
				flag = 1;
				while (1)
				{
					stop_pause = getch();
					if (stop_pause == 'P')
						break;
				}

				pause2 = time(NULL);
				pause_time += pause2 - pause1;
			}

			if (entered_char == 'E')
			{
				pause1 = time(NULL);
				flag = 2;
				while(1)
                {
				printf("\nare you sure you want to exit? press y for yes n for no\n");
				choose = getch();
				if (choose == 'y')
				{
				    system("cls");
				    while(1)
                    {
					fclose(fp);
					printf("do you want your game to be saved?\n");
					choose = getch();
					if (choose == 'y')
					{
						save(level);
						printf("come back soon");
						exit(0);
					}

					else if (choose == 'n')
					{
						printf("game not saved come back soon");
						exit(0);
					}

                    else
				{
					system("cls");
					SetColor(12);
					printf("please enter right characater to choose\n");
					Sleep(2000);
					system("cls");
					SetColor(15);
					continue;
				}

                    }
				}

				else if (choose == 'n')
				{
				    pause2 = time(NULL);
					printf("continue game\n");
					break;
				}

                else
				{
					SetColor(12);
					printf("please enter right characater to choose\n");
					Sleep(2000);
					SetColor(15);
					continue;
				}

                }

				pause_time += pause2 - pause1;
			}

			if (flag == 1 || flag == 2)	//if user wanted to exit or paused the game get another character for continuing the game
				entered_char = getch();
			if (entered_char == words[accidentnumber][j])
			{
				entered_char = entered_char - 32;
				SetColor(10);
				printf("%c", entered_char);
				SetColor(15);
			}
			else
			{
				SetColor(12);
				Beep(750, 50);
				printf("%c", entered_char);
				wrongchar++;
				SetColor(15);

			}

			flag = 0;	//if flag has changed for this word re initialize
		}

		time2 = time(NULL);
		Sleep(300);	//for seeing the last character of the word
		fclose(fp);

		float score = calscore(time1, time2, pause_time, wrongchar, strlen(words[accidentnumber]) - 1, level);
		level_score += score;	//updating amount of totalscore and level score after each word
		totalscore += score;
	}

	return level_score;
}

int login(void)
{
	char choose;
	char saved_name[40];
	char entered_username[40];
	int entered_password;
	int wrongpassword = 1;
	int saved_password, i;	//nam and pass are username and password stored in text file
	int flag = 0;
	int level;
	float score;
	char a;
	char stringpass[4];
	printf("type username :");
	gets(entered_username);
	printf("\n");
	printf("type password :");
	for (i = 0; i < 4; i++)
	{
		a = getch();
		stringpass[i] = a;
		printf("*");
	}

	entered_password = atoi(stringpass);
	Sleep(500);
	system("cls");
	FILE * fp;
	fp = fopen("user1.txt", "r");
	rewind(fp);
	if (fp == NULL)
		printf("file did not open");
	while (fscanf(fp, "%s %d %d %f", saved_name, &saved_password, &level, &score)==4)//checking username and password entered with user and pass saved in file
	{

		if ((strcmp(saved_name, entered_username) == 0) && (saved_password == entered_password))
		{
			flag = 1;
			strcpy(username, entered_username);
			password = entered_password;
			//user_score = score;
			totalscore = score;
			SetColor(10);
			printf("right username and password\n");
			Sleep(2000);
			SetColor(15);
			system("cls");
			while (1)
			{
				printf("do you want to see your rank among other players?\n");
				choose = getch();
				if (choose == 'y')
				{
					compare();
					Sleep(2000);
					system("cls");
					break;
				}
				else if (choose == 'n')
					break;
				else
				{
					system("cls");
					SetColor(12);
					printf("please enter right characater to choose\n");
					Sleep(2000);
					system("cls");
					SetColor(15);
					continue;
				}
			}

			while (1)
			{
				system("cls");
				printf("do you want to continue previous game or start new one\n");
				choose = getch();
				system("cls");
				if (choose == 's')
				{
					fclose(fp);
					return 1;
				}
				else if (choose == 'c')
				{
					fclose(fp);
					return level;
				}
				else
				{
					system("cls");
					SetColor(12);
					printf("please enter right characater to choose\n");
					Sleep(2000);
					system("cls");
					SetColor(15);
					continue;
				}
			}

			break;	//if the information matched break and stop checking information

		}
	}

	fclose(fp);
	if (flag != 1)
	{
		while (1)
		{
			SetColor(12);
			printf("wrong username and password please retry\n");
			Sleep(2000);
			SetColor(15);
			system("cls");
			printf("type username :");
			gets(entered_username);
			printf("\n");
			printf("type password :");
			for (i = 0; i < 4; i++)
			{
				a = getch();
				stringpass[i] = a;
				printf("*");
			}

			entered_password = atoi(stringpass);	//converting string to integer
			Sleep(500);
			system("cls");
			FILE * fp1;
			fp1 = fopen("user1.txt", "r");
			if (fp1 == NULL)
				printf("file did not open");
			while (fscanf(fp1, "%s %d %d %f", saved_name, &saved_password, &level, &score)==4)	//end of file condition
			{

				if ((strcmp(saved_name, entered_username) == 0) && (saved_password == entered_password))	//checking username and password entered with user and pass saved in file
				{
					flag = 1;
					strcpy(username, entered_username);
					password = entered_password;
					totalscore = score;
					SetColor(10);
					printf("right username and password\n");
					Sleep(2000);
					SetColor(15);

					while (1)
					{
						system("cls");
						printf("do you want to see your rank among other players?\n");
						choose = getch();
						if (choose == 'y')
						{
							compare();
							Sleep(2000);
							system("cls");
							break;
						}
						else if (choose == 'n')
							break;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}

					while (1)
					{
						system("cls");
						printf("do you want to continue previous game or start new one\n");
						choose = getch();
						system("cls");
						if (choose == 's')
						{
							fclose(fp1);
							return 1;
						}
						else if (choose == 'c')
						{
							fclose(fp1);
							return level;
						}
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}

					break;	//if the information matched break and stop checking information

				}
			}

			fclose(fp1);

			if (flag == 0)
			{
				wrongpassword++;
				if (wrongpassword != 0 && wrongpassword % 5 == 0)//every 5 time of wrong user and password cant try for 5 minutes
				{
					countdown();
				}
			}
		}
	}
}

int signup(void)
{
    introduction();
	char a;
	char entered_username[20];
	char saved_username[20];
	int entered_password,saved_password;
	int i,level,score;
	int flag=0;
	char pass[4];
	while(1)
    {
	printf("type username :");
	scanf("%s", entered_username);
	printf("\n");
	printf("type 4 digits for password :");
	for (i = 0; i < 4; i++)
	{
		a = getch();
		pass[i] = a;
		printf("*");
	}

	entered_password = atoi(pass);
	system("cls");
	FILE * fp;
	fp = fopen("user1.txt", "r");
	while (fscanf(fp, "%s %d %d %d", saved_username, &saved_password,&level,&score) == 4)
	{
		if ((strcmp(saved_username,entered_username) == 0) && (saved_password == entered_password))	//copying all data except the user data to another file
		{
		    flag=1;
		    fclose(fp);
			break;

		}
	}
	if(flag==1)   //it means username and password already existed so user should try diffrent user and password
        {
            system("cls");
            SetColor(12);
            printf("this username nad password already exists try diffrent username and password \n");
            Sleep(3000);
            system("cls");
            SetColor(15);
            continue;
        }
    else
        {
         strcpy(username,entered_username);
         password=entered_password;
         FILE *fp1=fopen("user1.txt","a+");
         fprintf(fp1, "%s %d 1 0\n", username, password); //1 and 0 are for level and score respectievly
         fclose(fp1);
         return 1;

        }

    }


}
int enter(void) //login and sign up for enterance of the user
{
    int level;
	int i;
	char choose;
	while (1)
	{
		printf("welcome press a for sign up and b for log in\n");
		choose = getch();

		if (choose == 'a')
		{
			system("cls");
			level = signup();
			break;
		}
		else if (choose == 'b')
		{
			system("cls");
			level = login();
			break;
		}
		else
		{
			system("cls");
			SetColor(12);
			printf("please enter right character to choose\n");
			Sleep(2000);
			system("cls");
			SetColor(15);
			continue;

		}
	}
	return level;
}
int prepareForGame(int level)
{
    char choose;

		switch (level)
		{
			case 1:
				{
					while (1)
					{
						printf("ready for start? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 2:
				{
					while (1)
					{
						printf("ready for starting level 2? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;

			case 3:
				{
					while (1)
					{
						printf("ready for starting level 3? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 4:
				{
					while (1)
					{
						printf("ready for starting level 4? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 5:
				{
					while (1)
					{
						printf("ready for starting level 5? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 6:
				{
					while (1)
					{
						printf("ready for starting level 6? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 7:
				{
					while (1)
					{
						printf("ready for starting level 7? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 8:
				{
					while (1)
					{
						printf("ready for starting level 8? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 9:
				{
					while (1)
					{
						printf("ready for starting level 9? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;
			case 10:
				{
					while (1)
					{
						printf("ready for starting level 10? y for yes no for exit\n");
						choose = getch();
						if (choose == 'n')
						{
							system("cls");
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else if (choose == 'y')
							return level;
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

				break;

			default:
				{
					system("cls");
					printf("you finished the game\n");
					Sleep(2000);

					while (1)
					{
						system("cls");
						printf("do you want to start from begining?/n");
						choose = getch();
						if (choose == 'y')
                        {
                            totalscore=0.0; //for saving in the future total score should be reset
                            return 1;
                        }

						else if (choose == 'n')
						{
							printf("do you want your level to be saved?\n");
							choose = getch();
							if (choose == 'y')
							{
								save(level);
								printf("come back soon");
								exit(0);
							}

							if (choose == 'n')
							{
								printf("game not saved come back ");
								exit(0);

							}
						}
						else
						{
							system("cls");
							SetColor(12);
							printf("please enter right characater to choose\n");
							Sleep(2000);
							system("cls");
							SetColor(15);
							continue;
						}
					}
				}

}
}
int main()
{
    SetColor(15);   //better white color than default
    int level=enter();
    while(1)//loop of the game
    {
	     level=prepareForGame(level);
		float level_score = game(level);
		system("cls");
		printf("your score in this level is %4.2f\n", level_score);
		level++;
    }
	return 0;
}
