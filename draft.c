#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 32
#define FILENAME "users.txt"

int choice;
void clear_screen();

void dashboard();
int user_exists(const char *username);

int login() {
  printf("Login with credentials down below\n");
  return 1;
}
void signup() {
  printf("This is the signup page\n");
  return;
}

void clear_screen() {
#ifdef _WIN32
  system("cls"); // Windows
#else
  system("clear"); // Linux/macOS
#endif
}

void loadingAnimation() {
  int barLength = 15;
  int delay = 150;
  // ASCII characters for the progress bar
  char emptyChar = 177;  // Unfilled section
  char filledChar = 219; // Filled section

  // Draw the empty progress bar
  printf("\t\t\t\t");
  for (int i = 0; i < barLength; i++) {
    printf("%c", emptyChar);
  }
  printf("\r"); // Return cursor to the start of the line
  printf("\t\t\t\t");

  // Fill the progress bar
  for (int i = 0; i < barLength; i++) {
    printf("%c", filledChar);
    fflush(stdout);       // Ensure each block appears immediately
    usleep(delay * 1000); // Delay in milliseconds
  }

  printf("\n\n");
}

void forgotAcc() {
  printf("Forgot account functionality\n");
  return;
}

void dashboard() {
  printf(BBLU "\tWelcome to GhorerBank\t\n" reset);
  printf(WHT "1. Login\n");
  printf("2. Create new account\n");
  printf("3. Forgot account/password\n");
  printf("4. Exit\n\n" reset);
  printf("Type to select an operation: ");

  scanf("%d", &choice);

  switch (choice) {
  case 1:
    printf("Taking you to the login page!\n");
    loadingAnimation();
    clear_screen();
    login();
    break;

  case 2:
    printf("Taking you to the signup page!\n");
    loadingAnimation();
    clear_screen();
    signup();
    break;

  case 3:
    printf("Have Patience, you'll have your account back!\n");
    loadingAnimation();
    clear_screen();
    forgotAcc();
    break;

  case 4:
    printf("Exiting program. Goodbye!\n");
    sleep(2);
    exit(0);

  default:
    printf("Invalid choice. Please try again.\n");
    break;
  }
}

int main() {
  while (1) {
    clear_screen();
    loadingAnimation();
    clear_screen();
    dashboard();
  }

  return 0;
}
