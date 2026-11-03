#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define INPUT_SIZE 100

int readInteger(const char *prompt, int min, int max)
{
    char input[INPUT_SIZE];
    char *end;
    long value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput ended. Exiting game.\n");
            exit(0);
        }

        errno = 0;
        value = strtol(input, &end, 10);

        if (end == input || errno == ERANGE)
        {
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        while (*end == ' ' || *end == '\t')
            end++;

        if (*end != '\n' && *end != '\0')
        {
            printf("Invalid input! Enter numbers only.\n");
            continue;
        }

        if (value < min || value > max)
        {
            printf("Invalid choice! Enter a number from %d to %d.\n", min, max);
            continue;
        }

        return (int)value;
    }
}

int readYesNo(const char *prompt)
{
    char input[INPUT_SIZE];
    char answer;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
            return 0;

        if (sscanf(input, " %c", &answer) != 1)
        {
            printf("Please enter y or n.\n");
            continue;
        }

        /* Reject extra non-whitespace characters. */
        char *p = input;
        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == answer)
        {
            p++;
            while (*p == ' ' || *p == '\t')
                p++;

            if (*p == '\n' || *p == '\0')
            {
                if (answer == 'y' || answer == 'Y')
                    return 1;
                if (answer == 'n' || answer == 'N')
                    return 0;
            }
        }

        printf("Invalid input! Enter only y or n.\n");
    }
}

void showChoice(int choice)
{
    if (choice == 0)
        printf("Snake");
    else if (choice == 1)
        printf("Water");
    else
        printf("Gun");
}

void showScoreboard(int player, int computer, int draws)
{
    printf("\n========== SCOREBOARD ==========\n");
    printf("Player Wins   : %d\n", player);
    printf("Computer Wins : %d\n", computer);
    printf("Draws         : %d\n", draws);
    printf("================================\n");
}

void playGame(int bestOfFive)
{
    int player = 0;
    int computerScore = 0;
    int draws = 0;
    int rounds = 0;
    int you, computer;

    while (1)
    {
        if (bestOfFive && (player == 3 || computerScore == 3))
            break;

        printf("\n========== ROUND %d ==========\n", rounds + 1);
        printf("0. Snake\n");
        printf("1. Water\n");
        printf("2. Gun\n");

        you = readInteger("\nEnter your choice (0-2): ", 0, 2);
        computer = rand() % 3;

        printf("\nYou chose: ");
        showChoice(you);

        printf("\nComputer chose: ");
        showChoice(computer);
        printf("\n");

        if (you == computer)
        {
            printf("\nIt's a DRAW!\n");
            draws++;
        }
        else if ((you == 0 && computer == 1) ||
                 (you == 1 && computer == 2) ||
                 (you == 2 && computer == 0))
        {
            printf("\nCongratulations! YOU WIN THIS ROUND!\n");
            player++;
        }
        else
        {
            printf("\nCOMPUTER WINS THIS ROUND!\n");
            computerScore++;
        }

        rounds++;
        showScoreboard(player, computerScore, draws);

        if (!bestOfFive && !readYesNo("\nDo you want to play again? (y/n): "))
            break;
    }

    printf("\n========== FINAL RESULT ==========\n");
    printf("Total Rounds  : %d\n", rounds);
    printf("Player Wins   : %d\n", player);
    printf("Computer Wins : %d\n", computerScore);
    printf("Draws         : %d\n", draws);

    if (player > computerScore)
        printf("\nFINAL WINNER: PLAYER!\n");
    else if (computerScore > player)
        printf("\nFINAL WINNER: COMPUTER!\n");
    else
        printf("\nFINAL RESULT: MATCH DRAW!\n");
}

int main(void)
{
    int menu;

    srand((unsigned int)time(NULL));

    while (1)
    {
        printf("\n================================\n");
        printf("       SNAKE WATER GUN GAME\n");
        printf("================================\n");
        printf("1. Normal Mode\n");
        printf("2. Best of 5 Mode\n");
        printf("3. Exit Game\n");

        menu = readInteger("\nEnter your option (1-3): ", 1, 3);

        if (menu == 1)
            playGame(0);
        else if (menu == 2)
            playGame(1);
        else
        {
            printf("\nThank you for playing!\n");
            break;
        }
    }

    return 0;
}
