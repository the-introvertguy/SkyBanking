#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define FILENAME "users.txt"

// Function prototypes
void clear_screen();
void dashboard();
void signup();
int login();
int user_exists(const char *username);

int main() {
  dashboard();
  return 0;
}

void loadingScreen() {
  printf("\n\n\n\t\t\t\tPlease wait while loading\n\n");
  char a = 177, b = 219;
  printf("\t\t\t\t");
  for (int i = 0; i < 15; i++) {
    printf("%c", a);
  }
  printf("\r"); // Return cursor to the start of the line
  printf("\t\t\t\t");
  for (int i = 0; i < 15; i++) {
    printf("%c", b);
    fflush(stdout);   // Ensure each block appears immediately
    usleep(15000000); // Delay for 150 milliseconds (adjust for speed)
  }
  system("cls");
}

// Clear screen function
void clear_screen() {
#ifdef _WIN32
  system("cls"); // Windows
#else
  system("clear"); // Linux/macOS
#endif
}

// Dashboard function
void dashboard() {
  int choice;

  while (1) {
    clear_screen();
    printf("=== Welcome to the Dashboard ===\n");
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline left by scanf

    switch (choice) {
    case 1:
      clear_screen();
      signup();
      break;
    case 2:
      clear_screen();
      if (login()) {
        printf("Login successful!\n");
      } else {
        printf("Login failed. Incorrect username or password.\n");
      }
      printf("Press Enter to return to the dashboard...");
      getchar();
      break;
    case 3:
      clear_screen();
      printf("Exiting program. Goodbye!\n");
      exit(0);
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
}

// Sign-up function
void signup() {
  char username[MAX_USERNAME];
  char password[MAX_PASSWORD];

  printf("=== Sign Up Page ===\n");
  printf("Enter a username: ");
  fgets(username, MAX_USERNAME, stdin);
  username[strcspn(username, "\n")] = '\0'; // Remove newline

  if (user_exists(username)) {
    printf("Username already exists. Please choose a different username.\n");
    printf("Press Enter to return...");
    getchar();
    return;
  }

  printf("Enter a password: ");
  fgets(password, MAX_PASSWORD, stdin);
  password[strcspn(password, "\n")] = '\0'; // Remove newline

  FILE *file = fopen(FILENAME, "a");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }
  fprintf(file, "%s %s\n", username, password);
  fclose(file);

  printf("Sign-up successful! You can now log in.\n");
  printf("Press Enter to return to the dashboard...");
  getchar();
}

// Login function
int login() {
  char username[MAX_USERNAME];
  char password[MAX_PASSWORD];
  char file_username[MAX_USERNAME];
  char file_password[MAX_PASSWORD];

  printf("=== Login Page ===\n");
  printf("Enter username: ");
  fgets(username, MAX_USERNAME, stdin);
  username[strcspn(username, "\n")] = '\0';

  printf("Enter password: ");
  fgets(password, MAX_PASSWORD, stdin);
  password[strcspn(password, "\n")] = '\0';

  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return 0;
  }

  while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
    if (strcmp(username, file_username) == 0 &&
        strcmp(password, file_password) == 0) {
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  return 0;
}

// Function to check if a user already exists
int user_exists(const char *username) {
  char file_username[MAX_USERNAME];
  char file_password[MAX_PASSWORD];

  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    return 0;
  }

  while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
    if (strcmp(username, file_username) == 0) {
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  return 0;
}
