#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// Constants for game mechanics
#define JADE_PER_WARP 160
#define JADE_PER_10_WARP 1600
#define BASE_5STAR_CHANCE 1.0f  // 1%
#define BASE_4STAR_CHANCE 10.0f // 10%
#define SOFT_PITY_START 75
#define HARD_PITY_5STAR 90
#define HARD_PITY_4STAR 10
#define PITY_INCREMENT 0.2f // 0.2% for every suceeding pull after soft pity
#define RANDOM_SCALE 10000

// Struct to encapsulate player state
typedef struct {
    int balance;
    int pullsSince5star;
    int pullsSince4star;
} Player;

// Enum for pull results
typedef enum{THREE_STAR, FOUR_STAR, FIVE_STAR} PullResult;

// Function prototypes
void checkBalance(Player* player);
int depositJades(Player* player);
int warpOnce(Player* player);
int warpTen(Player* player);
PullResult simulatePull(Player* player);
int getChoice();

int main(){

    // HSR Gacha Warp Simulator
    int choice;
    Player player = {0, 0, 0}; // Initialize player state

    srand(time(NULL));

    do{
        printf("\n+======================================+\n");
        printf("|        HSR WARP SIMULATOR            |\n");
        printf("+======================================+\n");

        printf(" [1] Check Stellar Jades\n");
        printf(" [2] Deposit Jades\n");
        printf(" [3] Warp 1 time (160 Jades)\n");
        printf(" [4] Warp 10 times (1600 Jades)\n");
        printf(" [5] Exit\n");

        printf("+======================================+\n");

        choice = getChoice(); // Safe input handling

        switch(choice){
            case 1: 
                checkBalance(&player);
                break;
            case 2:
                depositJades(&player);
                break;
            case 3:
                if(player.balance >= JADE_PER_WARP){
                    player.balance -= JADE_PER_WARP;
                    warpOnce(&player);
                }
                else{
                    printf("\nNot enough Stellar Jades! (Need 160)\n");
                }
                break;
            case 4:
                if(player.balance >= JADE_PER_10_WARP){
                    player.balance -= JADE_PER_10_WARP;
                    warpTen(&player);
                }
                else{
                    printf("\nNot enough Stellar Jades! (Need 1600)\n");
                }
                break;
            case 5:
                    printf("\n****************************\n");
                    printf("  Thanks for playing!\n");
                    printf("See you on the Astral Express!\n");
                    printf("****************************\n");
                break;
            default:
                Sleep(1000);
                printf("\nINVALID CHOICE! Please select  1 - 5\n");
                break;
        }

        if(choice != 5) {
            printf("\nPress Enter to return to the menu...");
            while(getchar() != '\n');
            getchar();
        }

    } while(choice != 5);

    return 0;
}

void checkBalance(Player* player){
    printf("\n[**************************************]\n");
    printf("[          BALANCE CHECK               ]\n");
    printf("[**************************************]\n\n");

    printf("   Stellar Jades:  %d\n", player->balance);
    printf("   Pulls since 5*:  %d / 90\n", player->pullsSince5star);
    printf("   Pulls since 4*:  %d / 10\n", player->pullsSince4star);

    printf("\n[**************************************]\n");

}

int depositJades(Player* player){

    int amount;

    printf("\n<-------------------------------------->\n");
    printf("         Deposit Stellar Jades\n");
    printf("<-------------------------------------->\n\n");

    printf("Enter amount: ");
    scanf("%d", &amount);

    if(amount < 0){
        printf("Invalid Amount\n");
        return 0;
    } else {
        printf("\n====================\n");
        printf("Deposit successful +%d Jades\n", amount);
        printf("====================\n");
        player->balance += amount;
        return 0;
    }

}

int warpOnce(Player* player) {
    printf("\nWarping...\n");
    Sleep(2000);

    PullResult result = simulatePull(player); // Use modular function

    if (result == FIVE_STAR){
        printf("\nYou got a 5* Character/Light Cone!\n");
    } else if (result == FOUR_STAR) {
        printf("\nYou got a 4* Character/Light Cone!\n");
    } else {
        printf("\nYou got a 3* Light Cone!\n");
    }

    Sleep(1000);
    return 0;
}

int warpTen(Player* player) {
    int i;
    int hasFourOrFive = 0; // Track if any 4* star or 5* was pulled

    printf("\n===================\n");
    printf("Here are your 10-Pull Results:\n");
    Sleep(2000);

    for(i = 0; i < 10; i++) {
        PullResult result = simulatePull(player); // Use modular function

        if (result == FIVE_STAR) {
            printf("\n%02d: 5* Character/Light Cone!\n",i + 1);
            hasFourOrFive = 1;
        } else if (result == FOUR_STAR) {
            printf("\n%02d: 4* Character/Light Cone!\n",i + 1);
            hasFourOrFive = 1;
        } else {
            printf("\n%02d: 3* Light Cone!\n",i + 1);
        }

        Sleep(1000);
    }

    // Fixed if no 4* or 5* in 10 pulls, guarantee the last one is 4*
    if (!hasFourOrFive) {
        printf("\n(Guarantee triggered) Last pull upgraded to 4* Character/Lightcone\n");
        player->pullsSince4star = 0; // Reset the 4* pity as per guarantee
    }

    return 0;
}

// Modular function for simulating one pull
PullResult simulatePull(Player* player) {
    player->pullsSince5star++;
    player->pullsSince4star++;

    // Calculate 5* chance with soft pity
    float chanceFive = BASE_5STAR_CHANCE;
    if (player->pullsSince5star >= SOFT_PITY_START) {
        chanceFive += (player->pullsSince5star - SOFT_PITY_START + 1) * PITY_INCREMENT;
    }
    if (player->pullsSince5star >= HARD_PITY_5STAR) {
        chanceFive = 100.0f;
    }

    int roll = rand() % RANDOM_SCALE;
    float rollPercent = roll / 100.0f;

    if (player->pullsSince5star >= HARD_PITY_5STAR) {
        player->pullsSince5star = 0;
        player->pullsSince4star = 0;
        return FIVE_STAR;
    } else if (player->pullsSince4star >= HARD_PITY_4STAR) {
        player->pullsSince4star = 0;
        return FOUR_STAR;
    } else if (rollPercent < chanceFive) {
        player->pullsSince5star = 0;
        player->pullsSince4star = 0;
        return FIVE_STAR;
    } else if (rollPercent < chanceFive + BASE_4STAR_CHANCE) {
        player->pullsSince4star = 0;
        return FOUR_STAR;
    } else {
        return THREE_STAR;
    }
}

// Safe Input Function
int getChoice() {
    int choice;
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) == 1) {
            while (getchar() != '\n'); // Clear buffer
            return choice;
        } else {
            printf("\n[!] Invalid Choice!. Please enter a number.\n");
            while (getchar() != '\n'); // Flush invalid input
        }
    }
}