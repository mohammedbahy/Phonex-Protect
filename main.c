#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void displayWelcomePage()
{
    printf("============================================\n");
    printf("|                                          |\n");
    printf("|      Welcome to Insurance Management     |\n");
    printf("|                                          |\n");
    printf("|              1. Register                 |\n");
    printf("|              2. Login                    |\n");
    printf("|              3. Exit                     |\n");
    printf("|                                          |\n");
    printf("============================================\n");
}

// User structure
struct User
{
    char username[100];
    char password[100];
    char accessLevel[20];
    char id[20];
};

struct Policy
{
    char policyNumber[20];
    char policyType[50];
    char coverageDetails[100];
    char premiumAmount[20];
    char startDate[20];
    char endDate[20];
    char beneficiary[50];
};

struct Customer
{
    char name[50];
    char address[100];
    char contactInfo[50];
    char policyHistory[200];
};

struct Claim
{
    char claimID[20];
    char policyNumber[20];
    char claimType[50];
    char date[20];
    char description[200];
    char status[20];
};

void registerUser()
{
    FILE *log = fopen("users.txt", "a");
    if (log == NULL) {
        printf("Error opening file!\n");
        return;
    }
    struct User user;
    printf("\n********** Register **********\n");
    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    int i = 0;
    char ch;
    while ((ch = _getch()) != 13) {
        user.password[i] = ch;
        i++;
        printf("*");
    }
    user.password[i] = '\0';
    printf("\nEnter access level (admin/agent/customer): ");
    scanf("%s", user.accessLevel);

    if (strcmp(user.accessLevel, "admin") == 0 || strcmp(user.accessLevel, "agent") == 0) {
        printf("Enter ID: ");
        scanf("%s", user.id);
    } else {
        strcpy(user.id, "");
    }

    fwrite(&user, sizeof(user), 1, log);
    fclose(log);

    printf("\nRegistration successful. Now you can log in with your credentials.\n");
}

int verifyUserID(char *id)
{
    FILE *file = fopen("ID_verification.txt", "r");
    if (file == NULL) {
        printf("Error opening ID verification file!\n");
        return 0;
    }

    char fileID[20];
    while (fscanf(file, "%s", fileID) != EOF) {
        if (strcmp(fileID, id) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int loginUser(struct User *loggedInUser)
{
    char username[100], password[100], id[20];
    FILE *log = fopen("users.txt", "r");
    if (log == NULL) {
        printf("Error opening file!\n");
        return 0;
    }
    struct User user;
    printf("\n********** Login **********\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    int i = 0;
    char ch;
    while ((ch = _getch()) != 13) {
        password[i] = ch;
        i++;
        printf("*");
    }
    password[i] = '\0';

    int loginSuccess = 0;
    while (fread(&user, sizeof(user), 1, log)) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            if (strcmp(user.accessLevel, "admin") == 0 || strcmp(user.accessLevel, "agent") == 0) {
                printf("\nEnter ID: ");
                scanf("%s", id);
                if (verifyUserID(id)) {
                    printf("\nID verified.\n");
                } else {
                    printf("\nID verification failed.\n");
                    fclose(log);
                    return 0;
                }
            }
            printf("\nLogin successful\n");
            strcpy(loggedInUser->username, user.username);
            strcpy(loggedInUser->password, user.password);
            strcpy(loggedInUser->accessLevel, user.accessLevel);
            strcpy(loggedInUser->id, user.id);
            loginSuccess = 1;
            break;
        }
    }

    if (!loginSuccess) {
        printf("\nIncorrect username or password. Please try again.\n");
    }

    fclose(log);
    return loginSuccess;
}

void createPolicy()
{
    FILE *file = fopen("policies.txt", "a");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Policy p;

    printf("Enter Policy Number: ");
    scanf("%s", p.policyNumber);
    printf("Enter Policy Type: ");
    scanf("%s", p.policyType);
    printf("Enter Coverage Details: ");
    scanf("%s", p.coverageDetails);
    printf("Enter Premium Amount: ");
    scanf("%s", p.premiumAmount);
    printf("Enter Start Date (YYYY-MM-DD): ");
    scanf("%s", p.startDate);
    printf("Enter End Date (YYYY-MM-DD): ");
    scanf("%s", p.endDate);
    printf("Enter Beneficiary: ");
    scanf("%s", p.beneficiary);

    fwrite(&p, sizeof(p), 1, file);
    fclose(file);

    printf("Policy created successfully.\n");
}

void viewPolicies()
{
    FILE *file = fopen("policies.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    struct Policy p;

    while (fread(&p, sizeof(p), 1, file))
        {
        printf("\nPolicy Number: %s\n", p.policyNumber);
        printf("Policy Type: %s\n", p.policyType);
        printf("Coverage Details: %s\n", p.coverageDetails);
        printf("Premium Amount: %s\n", p.premiumAmount);
        printf("Start Date: %s\n", p.startDate);
        printf("End Date: %s\n", p.endDate);
        printf("Beneficiary: %s\n", p.beneficiary);
    }
    fclose(file);
}

void searchPolicy()
{
    char policyNumber[20];
    printf("Enter Policy Number to search: ");
    scanf("%s", policyNumber);

    FILE *file = fopen("policies.txt", "r");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Policy p;
    int found = 0;

    while (fread(&p, sizeof(p), 1, file))
    {
        if (strcmp(p.policyNumber, policyNumber) == 0)
            {
            printf("\nPolicy Number: %s\n", p.policyNumber);
            printf("Policy Type: %s\n", p.policyType);
            printf("Coverage Details: %s\n", p.coverageDetails);
            printf("Premium Amount: %s\n", p.premiumAmount);
            printf("Start Date: %s\n", p.startDate);
            printf("End Date: %s\n", p.endDate);
            printf("Beneficiary: %s\n", p.beneficiary);
            found = 1;
            break;
            }
    }
    if (!found)
        {
        printf("Policy not found.\n");
    }
    fclose(file);
}

void updatePolicy()
{
    char policyNumber[20];
    printf("Enter Policy Number to update: ");
    scanf("%s", policyNumber);

    FILE *file = fopen("policies.txt", "r+");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Policy p;
    int found = 0;
    long pos;

    while (fread(&p, sizeof(p), 1, file))
    {
        if (strcmp(p.policyNumber, policyNumber) == 0)
            {
            found = 1;
            pos = ftell(file) - sizeof(struct Policy);
            fseek(file, pos, SEEK_SET);

            printf("Enter new Policy Type: ");
            scanf("%s", p.policyType);
            printf("Enter new Coverage Details: ");
            scanf("%s", p.coverageDetails);
            printf("Enter new Premium Amount: ");
            scanf("%s", p.premiumAmount);
            printf("Enter new Start Date (YYYY-MM-DD): ");
            scanf("%s", p.startDate);
            printf("Enter new End Date (YYYY-MM-DD): ");
            scanf("%s", p.endDate);
            printf("Enter new Beneficiary: ");
            scanf("%s", p.beneficiary);

            fwrite(&p, sizeof(p), 1, file);
            printf("Policy updated successfully.\n");
            break;
        }
    }
    if (!found)
        {
        printf("Policy not found.\n");
    }
    fclose(file);
}

void removePolicy() {
    char policyNumber[20];
    printf("Enter Policy Number to remove: ");
    scanf("%s", policyNumber);

    FILE *file = fopen("policies.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Policy p;
    int found = 0;

    while (fread(&p, sizeof(p), 1, file)) {
        if (strcmp(p.policyNumber, policyNumber) != 0) {
            fwrite(&p, sizeof(p), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("policies.txt");
        rename("temp.txt", "policies.txt");
        printf("Policy removed successfully.\n");
    } else {
        remove("temp.txt");
        printf("Policy not found.\n");
    }
}

void addCustomer()
{
    FILE *file = fopen("customers.txt", "a");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Customer c;

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter Address: ");
    scanf(" %[^\n]", c.address);
    printf("Enter Contact Information: ");
    scanf(" %[^\n]", c.contactInfo);
    printf("Enter Policy History: ");
    scanf(" %[^\n]", c.policyHistory);

    fwrite(&c, sizeof(c), 1, file);
    fclose(file);

    printf("Customer added successfully.\n");
}

void viewCustomers()
{
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    struct Customer c;

    while (fread(&c, sizeof(c), 1, file))
        {
        printf("\nCustomer Name: %s\n", c.name);
        printf("Address: %s\n", c.address);
        printf("Contact Information: %s\n", c.contactInfo);
        printf("Policy History: %s\n", c.policyHistory);
    }
    fclose(file);
}

void updateCustomer()
{
    char name[50];
    printf("Enter Customer Name to update: ");
    scanf(" %[^\n]", name);

    FILE *file = fopen("customers.txt", "r+");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Customer c;
    int found = 0;
    long pos;

    while (fread(&c, sizeof(c), 1, file))
    {
        if (strcmp(c.name, name) == 0)
            {
            found = 1;
            pos = ftell(file) - sizeof(struct Customer);
            fseek(file, pos, SEEK_SET);

            printf("Enter new Address: ");
            scanf(" %[^\n]", c.address);
            printf("Enter new Contact Information: ");
            scanf(" %[^\n]", c.contactInfo);
            printf("Enter new Policy History: ");
            scanf(" %[^\n]", c.policyHistory);

            fwrite(&c, sizeof(c), 1, file);
            printf("Customer updated successfully.\n");
            break;
        }
    }
    if (!found)
        {
        printf("Customer not found.\n");
    }
    fclose(file);
}

void removeCustomer() {
    char customerName[50];
    printf("Enter Customer Name to remove: ");
    scanf(" %[^\n]", customerName);

    FILE *file = fopen("customers.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Customer c;
    int found = 0;

    while (fread(&c, sizeof(c), 1, file)) {
        if (strcmp(c.name, customerName) != 0) {
            fwrite(&c, sizeof(c), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("customers.txt");
        rename("temp.txt", "customers.txt");
        printf("Customer removed successfully.\n");
    } else {
        remove("temp.txt");
        printf("Customer not found.\n");
    }
}

void initiateClaim()
{
    FILE *file = fopen("claims.txt", "a");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Claim c;

    printf("Enter Claim ID: ");
    scanf("%s", c.claimID);
    printf("Enter Policy Number: ");
    scanf("%s", c.policyNumber);
    printf("Enter Claim Type: ");
    scanf("%s", c.claimType);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", c.date);
    printf("Enter Description: ");
    scanf(" %[^\n]", c.description);
    printf("Enter Status: ");
    scanf("%s", c.status);

    fwrite(&c, sizeof(c), 1, file);
    fclose(file);

    printf("Claim initiated successfully.\n");
}

void viewClaims()
{
    FILE *file = fopen("claims.txt", "r");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Claim c;

    while (fread(&c, sizeof(c), 1, file))
        {
        printf("\nClaim ID: %s\n", c.claimID);
        printf("Policy Number: %s\n", c.policyNumber);
        printf("Claim Type: %s\n", c.claimType);
        printf("Date: %s\n", c.date);
        printf("Description: %s\n", c.description);
        printf("Status: %s\n", c.status);
    }
    fclose(file);
}

void updateClaimStatus()
{
    char claimID[20];
    printf("Enter Claim ID to update: ");
    scanf("%s", claimID);

    FILE *file = fopen("claims.txt", "r+");
    if (file == NULL)
        {
        printf("Error opening file!\n");
        return;
    }
    struct Claim c;
    int found = 0;
    long pos;

    while (fread(&c, sizeof(c), 1, file))
        {
        if (strcmp(c.claimID, claimID) == 0)
        {
            found = 1;
            pos = ftell(file) - sizeof(struct Claim);
            fseek(file, pos, SEEK_SET);

            printf("Enter new Status: ");
            scanf("%s", c.status);

            fwrite(&c, sizeof(c), 1, file);
            printf("Claim status updated successfully.\n");
            break;
        }
    }
    if (!found)
        {
        printf("Claim not found.\n");
    }
    fclose(file);
}

void adminMenu()
{
    int choice = 0;
    while (choice != 4)
    {
        printf("\nAdmin Menu:\n");
        printf("1. Policy Management\n");
        printf("2. Customer Management\n");
        printf("3. Claims Processing\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int ch;

        switch (choice) {
            case 1:
                while (ch != 6) {
                    printf("\nPolicy Management:\n");
                    printf("1.Create Policy\n2.View Policies\n3.Search Policy\n4.Update Policy\n5.Remove Policy\n6.Back\nEnter Choice: ");
                    scanf("%d",&ch);
                    switch(ch)
                    {
                        case 1:
                            createPolicy();
                            break;
                        case 2:
                            viewPolicies();
                            break;
                        case 3:
                            searchPolicy();
                            break;
                        case 4:
                            updatePolicy();
                            break;
                        case 5:
                            removePolicy();
                            break;
                        case 6:
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                }
                break;
            case 2:
               while (ch != 5) {
                    printf("\nCustomer Management:\n");
                    printf("1.Add Customer\n2.View Customers\n3.Update Customer\n4.Remove Customer\n5.Back\nEnter Choice: ");
                    scanf("%d",&ch);
                    switch(ch)
                    {
                        case 1:
                            addCustomer();
                            break;
                        case 2:
                            viewCustomers();
                            break;
                        case 3:
                            updateCustomer();
                            break;
                        case 4:
                            removeCustomer();
                            break;
                        case 5:
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                }
                break;
            case 3:
                while (ch != 3) {
                    printf("\nClaims Processing:\n");
                    printf("1.View Claims\n2.Update Claim Status\n3.Back\nEnter Choice: ");
                    scanf("%d",&ch);
                    switch(ch)
                    {
                        case 1:
                            viewClaims();
                            break;
                        case 2:
                            updateClaimStatus();
                            break;
                        case 3:
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                }
                break;
            case 4:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void generatePolicySalesReport()
{
    FILE *file = fopen("policies.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Policy p;
    int totalPolicies = 0;
    double totalPremium = 0.0;

    while (fread(&p, sizeof(p), 1, file)) {
        totalPolicies++;
        totalPremium += atof(p.premiumAmount);
    }

    fclose(file);

    printf("\nPolicy Sales Report:\n");
    printf("Total Policies Sold: %d\n", totalPolicies);
    printf("Total Premium Amount: %.2f\n", totalPremium);
}

void generateClaimStatisticsReport()
{
    FILE *file = fopen("claims.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Claim c;
    int totalClaims = 0;
    int pending = 0, reviewed = 0, approved = 0, rejected = 0;

    while (fread(&c, sizeof(c), 1, file))
        {
        totalClaims++;
        if (strcmp(c.status, "pending") == 0) pending++;
        else if (strcmp(c.status, "reviewed") == 0) reviewed++;
        else if (strcmp(c.status, "approved") == 0) approved++;
        else if (strcmp(c.status, "rejected") == 0) rejected++;
    }

    fclose(file);

    printf("\nClaim Statistics Report:\n");
    printf("Total Claims: %d\n", totalClaims);
    printf("Pending: %d\n", pending);
    printf("Reviewed: %d\n", reviewed);
    printf("Approved: %d\n", approved);
    printf("Rejected: %d\n", rejected);
}

void agentMenu()
{
    int choice;
    while (choice != 11)
        {
        printf("\nAgent Menu:\n");
        printf("1. Create Policy\n");
        printf("2. View Policies\n");
        printf("3. Search Policy\n");
        printf("4. Update Policy\n");
        printf("5. Add Customer\n");
        printf("6. View Customers\n");
        printf("7. Update Customer\n");
        printf("8. Initiate Claim\n");
        printf("9. View Claims\n");
        printf("10.Reporting and Analytics\n");
        printf("11. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int ch;

        switch (choice)
        {
            case 1:
                createPolicy();
                break;
            case 2:
                viewPolicies();
                break;
            case 3:
                searchPolicy();
                break;
            case 4:
                updatePolicy();
                break;
            case 5:
                addCustomer();
                break;
            case 6:
                viewCustomers();
                break;
            case 7:
                updateCustomer();
                break;
            case 8:
                initiateClaim();
                break;
            case 9:
                viewClaims();
                break;
            case 10:
                    printf("1. Generate Policy Sales Report\n");
                    printf("2. Generate Claim Statistics Report\n");
                    printf("3. Back\n");
                    printf("Enter your choice: ");
                    scanf("%d", &ch);
                    switch (ch) {
                    case 1:
                        generatePolicySalesReport();
                        break;
                    case 2:
                        generateClaimStatisticsReport();
                        break;
                    case 3:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            case 11:
                printf("Logging out...\n");
                break;
            default:
                    printf("Invalid choice. Please try again.\n");
        }
    }
}

void clientMenu()
{
    int choice;
    while (choice != 2){
        printf("\nClient Menu:\n");
        printf("1. View Policies\n");
        printf("2. Log Out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchPolicy();
                break;
            case 2:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main()
{
    struct User loggedInUser;
    int choice;

    while (choice != 3)
        {
        displayWelcomePage();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(&loggedInUser))
                    {
                    if (strcmp(loggedInUser.accessLevel, "admin") == 0)
                        {
                        adminMenu();
                    }
                    else if (strcmp(loggedInUser.accessLevel, "agent") == 0)
                        {
                        agentMenu();
                    }
                    else if (strcmp(loggedInUser.accessLevel, "customer") == 0)
                        {
                        clientMenu();
                    }
                    else
                        {
                        printf("Unknown access level.\n");
                    }
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
