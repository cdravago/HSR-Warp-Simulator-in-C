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

int pullsSince5star = 0;
int pullsSince4star = 0;

void checkBalance(int balance);
int depositJades();
int warpOnce();
int warpTen();

int main(){

    // HSR Gacha Warp Simulator

    int choice;
    int balance = 0;


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
        
        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1) {
            printf("\n[!] Invalid Option. Please enter a number.\n");
            while (getchar() != '\n')
            Sleep(1000);
            continue;
        }

        switch(choice){
            case 1: 
                checkBalance(balance);
                break;
            case 2:
                balance += depositJades();
                break;
            case 3:
                if(balance >= 160){
                    balance -= 160;
                    warpOnce();
                }
                else{
                    printf("\nNot enough Stellar Jades! (Need 160)\n");
                }
                break;
            case 4:
                if(balance >= 1600){
                    balance -= 1600;
                    warpTen();
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

void checkBalance(int balance){
    printf("\n[**************************************]\n");
    printf("[          BALANCE CHECK               ]\n");
    printf("[**************************************]\n\n");

    printf("   Stellar Jades:  %d\n", balance);
    printf("   Pulls since 5*:  %d / 90\n", pullsSince5star);
    printf("   Pulls since 4*:  %d / 10\n", pullsSince4star);

    printf("\n[**************************************]\n");

}

int depositJades(){

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
        return amount; 
    }


}

int warpOnce(){

    int roll = rand() % 10000; // 0 - 9999 random number na'tin and more precise compared kung 0 - 99
    float rollPercent = roll / 100.0f;

    printf("\nWarping...\n");
    Sleep(2000);

    pullsSince5star++;
    pullsSince4star++;

    // Soft Pity System

    float chanceFive;
    if(pullsSince5star < 75){
        chanceFive = 1; // 1% pa rin
    } 
    else{
        chanceFive = 1.0 + (pullsSince5star - 74) * 0.2f;
    }
    if(pullsSince5star >= 90){
        chanceFive = 100.0;
    }       

    //

    if(pullsSince5star >= 90){
        printf("\n*PITY* You got a guaranteed 5* Character!\n");
        pullsSince5star = 0;
        pullsSince4star = 0;
    }
    else if(pullsSince4star >= 10){
        printf("\n*PITY* You got a guaranteed 4* Character/Light Cone!\n");
        pullsSince4star = 0;
    }
    else if(rollPercent < chanceFive){
        printf("\nYou got a 5* Character/Light Cone!\n");
        pullsSince5star = 0;
        pullsSince4star = 0;
    }
    else if(rollPercent < chanceFive + 10.0){
        printf("\nYou got a 4* Character/Light Cone!\n");
        pullsSince4star = 0;
    }
    else{
        printf("\nYou got a 3* Light Cone.\n");
    }

    Sleep(1000);
    return 0;
}

int warpTen(){
    int i;
    int fourOrfive = 0;

    printf("\n===================\n");
    printf("Here are your 10-Pull Results:\n");
    Sleep(2000);

    for(i = 0; i < 10; i++){
        pullsSince5star++;
        pullsSince4star++;

        // Soft Pity System
        float chanceFive;
        if(pullsSince5star < 75){
            chanceFive = 1.0;
        }
        else{
            chanceFive = 1.0 + (pullsSince5star - 74) * 0.2f;
        }
        if(pullsSince5star >= 90){
            chanceFive = 100.0;
        }

        //

        int roll = rand() % 10000; // same thing earlier 0 - 99 chance
        float rollPercent = roll / 100.0f;

        if(pullsSince5star >= 90){
            printf("\n%02d: *PITY* Guaranteed 5* Character\n", i + 1);
            pullsSince5star = 0;
            pullsSince4star = 0;
            fourOrfive = 1;
        }
        else if(pullsSince4star >= 10){
            printf("\n%02d: *PITY* Guaranteed 4* Character/Light Cone\n", i + 1);
            pullsSince4star = 0;
            fourOrfive = 1;
        }
        else if(rollPercent < chanceFive){
            printf("\n%02d: 5* Character/Light Cone\n", i + 1);
            pullsSince5star = 0;
            pullsSince4star = 0;
            fourOrfive = 1;
        }
        else if(rollPercent < chanceFive + 10.0){
            printf("\n%02d: 4* Character/Light Cone\n", i + 1);
            pullsSince4star = 0;
            fourOrfive = 1;
        }
        else{
            printf("\n%02d: 3* Light Cone\n", i + 1);
        }

        Sleep(1000);
    }

    if(!fourOrfive){
        printf("\n(Guarantee triggered!) Last pull upgraded to 4* Character/Light Cone\n");
        pullsSince4star = 0;
    }

}
