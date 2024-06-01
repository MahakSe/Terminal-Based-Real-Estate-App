#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionHeaders.h"

int *ad_count ;
Person *is_login = NULL;

int main() {

    ad_count = (int*) malloc(sizeof(int));
    int cas;
    is_login = (Person*) malloc(sizeof (Person));
    FILE *ads = fopen("ads.txt", "a+");

    int *temp_count ;
    temp_count = (int *) malloc(sizeof (int));
    *ad_count = 0;

    char line[400];
    char lastLine[400];

    while (fgets(line, sizeof(line), ads) != NULL) {
        strcpy(lastLine, line);
        sscanf(lastLine, "%d", temp_count);
        if(*temp_count != -1)
            sscanf(lastLine, "%d", ad_count);
    }
    fclose(ads);
    //printf("%d\n", *ad_count);


    int flag=1;


    while (flag) {
        is_login = (Person*) malloc(sizeof (Person));
        printf("0: View the list of all ads\n");
        printf("1: Signup\n");
        printf("2: Login\n");
        printf("3: Exit\n");
        printf("Enter a number:\n");
        scanf("%d", &cas);
        printf("\n");
        switch (cas) {
            case 0: {
                int filter;
                printf("Enter a number to filter the ads based on that:\n");
                printf("0: Area\n");
                printf("1: Price\n");
                printf("2: Economical\n");
                printf("3: No Filter\n");

                scanf("%d", &filter);

                print(filter);
                break;
            }
            case 1: {
                signup();
                break;
            }



            case 2: {
                login();
                int flag2 = 1;
                if (strstr(is_login->user, "seller") != NULL) {
                    int option;
                    while (flag2) {
                        printf("0: View the list of all ads\n");
                        printf("1: Add an ad\n");
                        printf("2: See your ads\n");
                        printf("3: request to promote your access\n");
                        printf("4: Go back\n");
                        printf("Enter a number:");
                        scanf("%d", &option);
                        printf("\n");
                        switch (option) {
                            case 0:
                                int filter1;
                                printf("Enter a number to filter the ads based on that:\n");
                                printf("0: Area\n");
                                printf("1: Price\n");
                                printf("2: Economical\n");
                                printf("3: No Filter\n");

                                scanf("%d", &filter1);

                                print(filter1);
                                break;
                            case 1:
                                Add_ad();
                                break;
                            case 2:
                                print_personal_ads();
                                break;
                            case 3:
                                request_promot();
                                break;
                            case 4:
                                flag2 = 0;
                                is_login = NULL;
                                break;
                        }
                    }


                } else if (strstr(is_login->user, "agent") != NULL) {
                    printf("Do you choose to log in as a seller(1) or an agent(2)?:");
                    int part;
                    scanf("%d", &part);
                    if (part == 1) {
                        int option;
                        while (flag2) {
                            printf("0: View the list of all ads\n");
                            printf("1: Add an ad\n");
                            printf("2: See your ads\n");
                            printf("3: Go back\n");
                            printf("Enter a number:");
                            scanf("%d", &option);

                            switch (option) {
                                case 0:
                                    int filter1;
                                    printf("Enter a number to filter the ads based on that:\n");
                                    printf("0: Area\n");
                                    printf("1: Price\n");
                                    printf("2: Economical\n");
                                    printf("3: No Filter\n");

                                    scanf("%d", &filter1);

                                    print(filter1);
                                    break;
                                case 1:
                                    Add_ad();
                                    break;
                                case 2:
                                    print_personal_ads();
                                    break;
                                case 3:
                                    is_login = NULL;
                                    flag2 = 0;
                                    break;

                            }
                        }
                    } else //agent
                    {
                        int flag3 = 1;
                        int option;
                        while (flag3) {
                            printf("0: View the list of all requested ads\n");
                            printf("1: Go back\n");
                            printf("Enter a number:");
                            scanf("%d", &option);
                            switch (option) {
                                case 0:
                                    requested_ads();
                                    break;

                                case 1:
                                    flag3 = 0;
                                    is_login = NULL;
                                    break;
                            }
                        }
                    }
                }



                else if(strstr(is_login->user, "admin") != NULL)
                {
                    flag2 = 1;
                    printf("Do you choose to log in as a seller(1), an agent(2) or an admin(3)?:");
                    int part;
                    scanf("%d", &part);

                    while(flag2) {
                        switch (part) {
                            case 1:
                                int option;
                                while (flag2) {
                                    printf("0: View the list of all ads\n");
                                    printf("1: Add an ad\n");
                                    printf("2: See your ads\n");
                                    printf("3: Go back\n");
                                    printf("Enter a number:");
                                    scanf("%d", &option);
                                    printf("\n");
                                    switch (option) {
                                        case 0:
                                            int filter1;
                                            printf("Enter a number to filter the ads based on that:\n");
                                            printf("0: Area\n");
                                            printf("1: Price\n");
                                            printf("2: Economical\n");
                                            printf("3: No Filter\n");

                                            scanf("%d", &filter1);

                                            print(filter1);
                                            break;
                                        case 1:
                                            Add_ad();
                                            break;
                                        case 2:
                                            print_personal_ads();
                                            break;
                                        case 3:
                                            flag2 = 0;
                                            is_login = NULL;
                                            break;
                                    }
                                }

                                break;

                            case 2: {//agent

                                while (flag2) {
                                    printf("0: View the list of all requested ads\n");
                                    printf("1: Go back\n");
                                    printf("Enter a number:");
                                    scanf("%d", &option);
                                    switch (option) {
                                        case 0:
                                            requested_ads();
                                            break;

                                        case 1:
                                            flag2 = 0;
                                            is_login = NULL;
                                            break;
                                    }
                                }
                                break;
                            }
                            case 3://admin
                                while(flag2) {
                                    printf("\n");
                                    printf("0: Enhance an individual's access.\n");
                                    printf("1: Review promotion requests and approve or deny them.\n");
                                    printf("2: View the entire history of posted advertisements.\n");
                                    printf("3: Go back!\n");
                                    int n;
                                    scanf("%d", &n);
                                    switch (n) {
                                        case 0:
                                            printUsers();
                                            break;
                                        case 1:
                                            see_promotion_requests();
                                            break;
                                        case 2:
                                            see_ads_history();
                                            break;
                                        case 3:
                                            is_login = NULL;
                                            flag2 = 0;
                                            break;
                                    }
                                }
                        }
                    }
                }
                break;
            }

            case 3: {
                flag = 0;
                is_login = NULL;
                break;
            }
            default: {
                printf("Invalid choice. Please enter a valid number.\n");
            }
        }
    }

    free(is_login);
    free(ad_count);


    return 0;
}

