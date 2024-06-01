#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "functionHeaders.h"

void print(int filter)
{
    FILE *ads = fopen("ads.txt", "r");
    fseek(ads, 0, SEEK_SET);

    int count = 0;
    int page = 1;

    int res, id;
    char title[50];
    long long int price;
    long long area;
    int district;
    char description[500];
    long long int recommendedprice;
    int state;
    char username[50];



    if (filter == 3) {
        printf("page %d:\n", page);
        res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                     description, &recommendedprice, &state, username) > 0;
        while (res) {
            if(state != -1) {
                printf("Number: %d, Title: %s ,Price: %lld\n", id, title, price);
                count++;
            }
            if (count == 10) {
                count = 0;
                int next = -1;
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go to the next page of ads\n");
                printf("Enter 2 to go back to the main menu\n");
                scanf("%d", &next);
                while (1) {
                    //scanf("%i", &next);
                    if (next == 1) {
                        page++;
                        printf("page %d:\n", page);
                        break;
                    } else if (next == 0) {
                        printf("Enter the number of ad :");
                        int num;
                        scanf("%d", &num);
                        printAd(num);
                    } else {
                        fclose(ads);
                        return;
                    }
                    printf("\n");
                    printf("Enter 0 to check an ad with specific information.\n");
                    printf("Enter 1 to go to the next page of ads\n");
                    printf("Enter 2 to go back to the main menu\n");
                    scanf("%d", &next);

                }
            }
            res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                         description, &recommendedprice, &state, username)> 0;
        }
        if (count != 0) {
            while (1) {
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go back to the main menu\n");

                int next;
                scanf("%i", &next);
                if (next == 0) {
                    printf("Enter the number of ad: ");
                    int num;
                    scanf("%d", &num);
                    printAd(num);
                } else
                    break;
            }
        }
        fclose(ads);
        return;
    }

    Ads ad_arr[2000];
    int i = 0;

    res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &ad_arr[i].ID, ad_arr[i].Title, &ad_arr[i].Area, &ad_arr[i].District, &ad_arr[i].Price, ad_arr[i].Description,
                 &ad_arr[i].recommendedPrice, &ad_arr[i].State, ad_arr[i].Username) > 0;
    if(!res) {
        printf("No Ads To Display!\n");
        fclose(ads);
        return;
    }

    while(res)
    {
        i++;
        res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &ad_arr[i].ID, ad_arr[i].Title, &ad_arr[i].Area, &ad_arr[i].District, &ad_arr[i].Price, ad_arr[i].Description,
                     &ad_arr[i].recommendedPrice, &ad_arr[i].State, ad_arr[i].Username)> 0;
    }


    if(filter == 0)
    {
        printf("Do you have a preferred house size range in mind? Yes(0), NO(1)\n");
        int range;
        scanf("%d", &range);
        long long int min, max;
        if(!range)
        {
            printf("Please enter the minimum.\n");
            scanf("%lld", &min);
            printf("Please enter the maximum.\n");
            scanf("%lld", &max);
        }

        printf("Do you want to view ads in ascending(0) or descending(1) order?\n");
        int order;
        scanf("%d", &order);

        if(!order)
            qsort(ad_arr,i,sizeof (Ads),sort0);
        else
            qsort(ad_arr,i,sizeof (Ads),sort01);

        printf("page %d:\n", page);
        for(int j = 0; j < i; j++)
        {
            if(ad_arr[j].ID != -1) {
                if(!range)
                {
                    if(min < ad_arr[j].Area &&  ad_arr[j].Area < max)
                    {
                        printf("Number: %d, Title: %s ,Price: %lld\n", ad_arr[j].ID, ad_arr[j].Title, ad_arr[j].Price);
                        count++;
                    }
                }
                else {
                    printf("Number: %d, Title: %s ,Price: %lld\n", ad_arr[j].ID, ad_arr[j].Title, ad_arr[j].Price);
                    count++;
                }
            }
            if(count == 10)
            {
                count = 0;
                int next = -1;
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go to the next page of ads\n");
                printf("Enter 2 to go back to the main menu\n");
                scanf("%d", &next);
                while(1) {
                    if (next == 1) {
                        page++;
                        printf("page %d:\n", page);
                        break;
                    } else if (next == 0) {
                        printf("Enter the number of ad :");
                        int num;
                        scanf("%d", &num);
                        printAd(num);
                    }
                    else {
                        fclose(ads);
                        return;
                    }
                    printf("\n");
                    printf("Enter 0 to check an ad with specific information.\n");
                    printf("Enter 1 to go to the next page of ads\n");
                    printf("Enter 2 to go back to the main menu\n");
                    scanf("%i", &next);

                }
            }
        }
        if (count != 0) {
            while (1) {
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go back to the main menu\n");

                int next;
                scanf("%i", &next);
                if (next == 0) {
                    printf("Enter the number of ad :");
                    int num;
                    scanf("%d", &num);
                    printAd(num);
                } else {
                    break;
                }
            }
        }
        fclose(ads);
        return;
    }

    if(filter == 1)
    {
        printf("Do you have a preferred house price range in mind? Yes(0), NO(1)\n");
        int range;
        scanf("%d", &range);
        long long int min, max;
        if(!range)
        {
            printf("Please enter the minimum.\n");
            scanf("%lld", &min);
            printf("Please enter the maximum.\n");
            scanf("%lld", &max);
        }

        printf("Do you want to view ads in ascending(0) or descending(1) order?\n");
        int order;
        scanf("%d", &order);

        if(!order)
            qsort(ad_arr,i,sizeof (Ads),sort1);
        else
            qsort(ad_arr,i,sizeof (Ads),sort11);

        printf("page %d:\n", page);
        for(int j = 0; j < i; j++)
        {
            if(ad_arr[j].ID != -1) {
                if(!range)
                {
                    if(min < ad_arr[j].Price &&  ad_arr[j].Price < max)
                    {
                        printf("Number: %d, Title: %s ,Price: %lld\n", ad_arr[j].ID, ad_arr[j].Title, ad_arr[j].Price);
                        count++;
                    }
                }
                else {
                    printf("Number: %d, Title: %s ,Price: %lld\n", ad_arr[j].ID, ad_arr[j].Title, ad_arr[j].Price);
                    count++;
                }
            }
            if(count == 10)
            {
                count = 0;
                int next = -1;
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go to the next page of ads\n");
                printf("Enter 2 to go back to the main menu\n");
                scanf("%d", &next);
                while(1) {
                    if (next == 1) {
                        page++;
                        printf("page %d:\n", page);
                        break;
                    } else if (next == 0) {
                        printf("Enter the number of ad :");
                        int num;
                        scanf("%d", &num);
                        printAd(num);
                    }
                    else {
                        fclose(ads);
                        return;
                    }
                    printf("\n");
                    printf("Enter 0 to check an ad with specific information.\n");
                    printf("Enter 1 to go to the next page of ads\n");
                    printf("Enter 2 to go back to the main menu\n");
                    scanf("%i", &next);

                }
            }
        }
        if (count != 0) {
            while (1) {
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go back to the main menu\n");

                int next;
                scanf("%i", &next);
                if (next == 0) {
                    printf("Enter the number of ad :");
                    int num;
                    scanf("%d", &num);
                    printAd(num);
                } else
                    break;
            }
        }
        fclose(ads);
        return;
    }


    if(filter == 2)
    {
        printf("Do you have a preferred house price range in mind? Yes(0), NO(1)\n");
        int range;
        scanf("%d", &range);
        long long int min, max;
        if(!range)
        {
            printf("Please enter the minimum.\n");
            scanf("%lld", &min);
            printf("Please enter the maximum.\n");
            scanf("%lld", &max);
        }

        printf("Do you want to view ads in ascending(0) or descending(1) order?\n");
        int order;
        scanf("%d", &order);

        if(!order)
            qsort(ad_arr,i,sizeof (Ads),sort2);
        else
            qsort(ad_arr,i,sizeof (Ads),sort21);

        printf("page %d:\n", page);
        for(int j = 0; j < i; j++)
        {
            if(ad_arr[j].ID != -1) {
                if(!range)
                {
                    if(min < ad_arr[j].Price && ad_arr[j].Price < max)
                    {
                        printf("Number: %d, Title: %s ,Price: %lld\n", ad_arr[j].ID, ad_arr[j].Title, ad_arr[j].Price);
                        count++;
                    }
                }
                else {
                    printf("Number: %d, Title: %s ,Price: %lld\n", ad_arr[j].ID, ad_arr[j].Title, ad_arr[j].Price);
                    count++;
                }
            }
            if(count == 10)
            {
                count = 0;
                int next = -1;
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go to the next page of ads\n");
                printf("Enter 2 to go back to the main menu\n");
                scanf("%d", &next);
                while(1) {
                    if (next == 1) {
                        page++;
                        printf("page %d:", page);
                        break;
                    } else if (next == 0) {
                        printf("Enter the number of ad :");
                        int num;
                        scanf("%d", &num);
                        printAd(num);
                    }
                    else {
                        fclose(ads);
                        return;
                    }
                    printf("\n");
                    printf("Enter 0 to check an ad with specific information.\n");
                    printf("Enter 1 to go to the next page of ads\n");
                    printf("Enter 2 to go back to the main menu\n");
                    scanf("%i", &next);

                }
            }
        }
        if (count != 0) {
            while (1) {
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go back to the main menu\n");

                int next;
                scanf("%i", &next);
                if (next == 0) {
                    printf("Enter the number of ad :");
                    int num;
                    scanf("%d", &num);
                    printAd(num);
                } else {
                    break;
                }
            }
        }
        fclose(ads);
        return;
    }



}

void login()
{
    FILE *users = fopen("users.txt", "r");
    char user[50];
    char pass[50];
    printf("Please Enter Your Username:\n");
    char c = getchar();
    int t = 0;
    while(c == ' ' || c == '\t' || c == '\n')
        c = getchar();
    while(c != '\n')
    {
        user[t] = c;
        c = getchar();
        t++;
    }
    user[t] = '\0';

    printf("Please Enter Your Password:\n");
    char c1 = getchar();
    t = 0;
    while(c1 == ' ' || c1 == '\t' || c1 == '\n')
        c1 = getchar();
    while(c1 != '\n')
    {
        pass[t] = c1;
        c1 = getchar();
        t++;
    }
    pass[t] = '\0';

    int res;
    char user2[50], pass2[50], temp[20];

    fseek(users, 0, SEEK_SET);

    res = fscanf(users, "%[^;];%[^;];%[^\n]\n", user2, pass2, temp) > 0;

    while (res)
    {
        if (strcmp(user, user2) == 0 && strcmp(pass, pass2) == 0)
        {
            strcpy(is_login->password, pass);
            strcpy(is_login->userName, user);
            strcpy(is_login->user, temp);
            fclose(users);
            return;
        }
        res = fscanf(users, "%[^;];%[^;];%[^\n]\n", user2, pass2, temp) > 0;

    }
    fclose(users);
    printf("The user is not found!\n");
}

void signup()
{
    FILE *users = fopen("users.txt", "a+");
    fseek(users, 0, SEEK_SET);
    char username[50];
    char pass[50];
    char user[20] = {'s','e','l','l','e','r', '\0'};

    printf("Please Enter Your Username:\n");

    char c = getchar();
    int i = 0;
    while(c == ' ' || c == '\t' || c == '\n')
        c = getchar();
    while(c != '\n')
    {
        username[i] = c;
        c = getchar();
        i++;
    }
    username[i] = '\0';

    printf("Please Enter Your Password:\n");
    char c1 = getchar();
    i = 0;
    while(c1 == ' ' || c1 == '\t' || c1 == '\n')
        c1 = getchar();
    while(c1 != '\n')
    {
        pass[i] = c1;
        c1 = getchar();
        i++;
    }
    pass[i] = '\0';

    char usernameTemp[50];
    char passTemp[50];
    char userTemp[20];

    int res = fscanf(users, "%[^;];%[^;];%[^\n]\n", usernameTemp, passTemp, userTemp);
    while(res>0)
    {
        if(strcmp(usernameTemp, username) == 0)
        {
            printf("There is an existing account with this username.\n");
            printf("Try to log in.\n");
            fclose(users);
            return;
        }
        res = fscanf(users, "%[^;];%[^;];%[^\n]\n", usernameTemp, passTemp, userTemp);

    }

    fprintf(users,"%s;%s;%s\n",username,pass,user);
    printf("You have successfully signed up.\n");
    fclose(users);
}


int sort0(const void* a, const void* b) {
    const Ads* ad1 = (const Ads*)a;
    const Ads* ad2 = (const Ads*)b;

    if (ad1->Area < ad2->Area) {
        return -1;
    } else if (ad1->Area > ad2->Area) {
        return 1;
    } else {
        return 0;
    }
}
int sort01(const void* a, const void* b) {
    const Ads* ad1 = (const Ads*)a;
    const Ads* ad2 = (const Ads*)b;
    if (ad1->Area > ad2->Area) {
        return -1;
    } else if (ad1->Area < ad2->Area) {
        return 1;
    } else {
        return 0;
    }
}
int sort1(const void* a, const void* b) {
    const Ads* ad1 = (const Ads*)a;
    const Ads* ad2 = (const Ads*)b;

    if (ad1->Price < ad2->Price) {
        return -1;
    } else if (ad1->Price > ad2->Price) {
        return 1;
    } else {
        return 0;
    }
}
int sort11(const void* a, const void* b) {
    const Ads* ad1 = (const Ads*)a;
    const Ads* ad2 = (const Ads*)b;

    if (ad1->Price > ad2->Price) {
        return -1;
    } else if (ad1->Price < ad2->Price) {
        return 1;
    } else {
        return 0;
    }
}
int sort2(const void* a, const void* b)
{
    const Ads* ad1 = (const Ads*)a;
    const Ads* ad2 = (const Ads*)b;

    if(abs(ad1->recommendedPrice - ad1->Price) < abs(ad2->recommendedPrice - ad2->Price))
        return -1;
    else if(abs(ad1->recommendedPrice - ad1->Price) > abs(ad2->recommendedPrice - ad2->Price))
        return 1;
    else
        return 0;
}
int sort21(const void* a, const void* b)
{
    const Ads* ad1 = (const Ads*)a;
    const Ads* ad2 = (const Ads*)b;

    if(abs(ad1->recommendedPrice - ad1->Price) > abs(ad2->recommendedPrice - ad2->Price))
        return -1;
    else if(abs(ad1->recommendedPrice - ad1->Price) < abs(ad2->recommendedPrice - ad2->Price))
        return 1;
    else
        return 0;
}


void Add_ad() {
    FILE *requested = fopen("requested.txt", "a+");

    Ads* ad = (Ads*)calloc(1, sizeof(Ads));

    printf("Please enter the title of the ad:\n");
    char c = getchar();
    while (c == ' ' || c == '\t' || c == '\n')
        c = getchar();

    int k = 0;
    while(c != '\n')
    {
        ad->Title[k] = c;
        c = getchar();
        k++;
    }
    ad->Title[k] = '\0';
    fprintf(requested, "%d;%s;", -1, ad->Title);

    printf("Please enter the area of the house:\n");
    scanf("%lld", &ad->Area);
    fprintf(requested, "%lld;", ad->Area);

    printf("Please enter the district of the house:\n");
    scanf("%d", &ad->District);
    fprintf(requested, "%d;", ad->District);

    long long int recom_price = recommendPrice(ad);
    if(recom_price == -1)
        printf("There is no suggested price for your ad!\n");
    else
        printf("Based on your house's properties, we estimate its price at $%lld.\n", recom_price);

    getchar();

    printf("Please enter your desired house price for the ad:\n");
    scanf("%lld", &ad->Price);
    fprintf(requested, "%lld;", ad->Price);

    getchar();

    printf("Please enter some description for your ad:\n");
    scanf("%[^\n]", ad->Description);
    fprintf(requested, "%s;", ad->Description);

    fprintf(requested, "%lld;", recom_price);

    ad->State = 0;
    fprintf(requested, "%d;", ad->State);

    fprintf(requested, "%s\n", is_login->userName);

    printf("Thank you for submitting your ad.\n");
    fclose(requested);

}

long long int recommendPrice(Ads *ad)
{
    /*FILE *ads = fopen("ads.txt", "r");
    fseek(ads, 0, SEEK_SET);

    long long int recom = 0;
    long long int count = 0;

    int id;
    char title[50];
    long long int price;
    long long int area;
    int district;
    char description[500];
    long long int recommendedprice;
    int state;
    char username[50];

    int res;

    res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                 description, &recommendedprice, &state, username) > 0;

    if(!res)
    {
        fclose(ads);
        return -1;
    }
    while(res)
    {
        if(id != -1) {
            long long int area_difference = abs(area - ad->Area);
            long long int district_difference = abs(area - ad->Area);
            recom += price/(area_difference+district_difference);
            count++;
        }
        res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                     description, &recommendedprice, &state, username) > 0;
    }

    fclose(ads);
    return recom/count;*/
    long int basePrice = 70000;  // A starting base price
    long int sizeFactor[] = {20000,19400, 18800,18200,17600,17000,16400,15800,15200,14600,14000,13400,12800,12200,11600,11000,10400,9800,9200,8600,8000,7400,6800,6200,6000};   // Price per square foot
    return basePrice + ad->Area * (sizeFactor[ad->District - 1] - 3000);

}

void print_personal_ads()
{
    FILE *ads = fopen("ads.txt", "r");
    FILE *requested = fopen("requested.txt", "r");

    int found = 0;
    int id;
    char title[50];
    long long int price;
    long long int area;
    int district;
    char description[500];
    long long int recommendedprice;
    int state;
    char username[50];

    fseek(ads, 0, SEEK_SET);
    int res;
    res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                 description, &recommendedprice, &state, username)> 0;
    while(res)
    {
        if(strcmp(username,is_login->userName) == 0)
        {
            found = 1;

            if(state == 1) {
                printf("This add in in Wall now:\n");
                printf("number: %d,Title: %s,Price: %lld,Area: %lld,District: %i\nDescription: %s\n", id, title, price,
                       area, district, description);
                printf("\n");
            }
            else if(state == -1){
                printf("We are unable to accept this ad:\n");
                printf("number: %d,Title: %s,Price: %lld,Area: %lld,District: %i\nDescription: %s\n",id, title, price, area, district, description);
                printf("\n");

            }
        }
        res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                     description, &recommendedprice, &state, username)> 0;
    }


    int res2 = 0, found2=0;
    int idt;
    char titlet[50];
    long long int pricet;
    long long int areat;
    int districtt;
    char descriptiont[500];
    long long int recommendedpricet;
    int statet;
    char usernamet[50];

    fseek(ads, 0, SEEK_SET);
    fseek(requested, 0, SEEK_SET);

    res2 = fscanf(requested, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                 description, &recommendedprice, &state, username)> 0;
    res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &idt, titlet, &areat, &districtt, &pricet ,
                 descriptiont, &recommendedpricet, &statet, usernamet)> 0;
    while(res2)
    {
        if(strcmp(username, is_login->userName) == 0)
        {
            while(res)
            {
                if(!strcmp(title,titlet) && area==areat && !strcmp(description,descriptiont))
                {
                    found2 = 1;
                    break;
                }
                res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &idt, titlet, &areat, &districtt, &pricet ,
                             descriptiont, &recommendedpricet, &statet, usernamet)> 0;
            }
            if(!found2) {
                found = 1;
                printf("This ad is not still accepted:\n");
                printf("number: %d,Title: %s,Price: %lld,Area: %lld,District: %i\nDescription: %s\n", id, title, price,
                       area, district, description);
                printf("\n");
            }
        }
        res2 = fscanf(requested, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                      description, &recommendedprice, &state, username) > 0;
        fseek(ads, 0, SEEK_SET);
        found2= 0;
    }
    if(!found)
    {
        printf("No ads available.\n");
        printf("\n");
    }

    fclose(ads);
    fclose(requested);
}

void printAd(int number)
{
    FILE *ads = fopen("ads.txt", "a+");

    int id;
    char title[50];
    long long int price;
    long long int area;
    int district;
    char description[500];
    long long int recommendedprice;
    int state;
    char username[50];

    fseek(ads, 0, SEEK_SET);
    int res;
    res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                 description, &recommendedprice, &state, username)> 0;


    while(res)
    {
        if(id == number && state == 1)
        {
            printf("\nTitle: %s\nPrice: %lld\nArea: %lld\nDistrict: %i\nDescription: %s\n", title, price, area, district, description);
            fclose(ads);
            return;
        }
        res = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                     description, &recommendedprice, &state, username) > 0;
    }
    printf("\n");
    printf("No matching ad found.\n");
    fclose(ads);
}

void requested_ads()
{
    FILE *ads = fopen("ads.txt", "a+");
    FILE *requested = fopen("requested.txt", "a+");
    FILE *record = fopen("record.txt", "a+");

    int option;
    int res, id;
    char title[50];
    long long int price;
    long long area;
    int district;
    char description[500];
    long long int recommendedprice;
    int state;
    char username[50];

    fseek(requested, 0, SEEK_SET);


    res = fscanf(requested, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                 description, &recommendedprice, &state, username) > 0;

    if(!res)
    {
        printf("There is no requested ad!\n");
        fclose(ads);
        fclose(requested);
        fclose(record);
        return;
    }

    while(res)
    {
        fseek(ads, 0, SEEK_SET);
        if(state == 0) {
            char titletemp[50], usernametemp[50];
            long long int areatemp, priceTemp,rectemp;
            int idtemp,districttemp,statetemp;
            char destemp[500];

            int res2 = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &idtemp, titletemp, &areatemp, &districttemp, &priceTemp, destemp,
            &rectemp, &statetemp, usernametemp) > 0;

            int repeat = 0;
            while (res2) {
                if(!(strcmp(titletemp,title)) && price==priceTemp && area == areatemp) {
                    repeat = 1;
                    break;
                }
                res2 = fscanf(ads, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &idtemp, titletemp,
                              &areatemp,&districttemp, &priceTemp, destemp,&rectemp, &statetemp, usernametemp) > 0;
            }
            if(!repeat) {
                printf("Number: %d,Title: %s,Price: %lld\n", id, title, price);
                printf("Open the ad(0) , accept (1), reject(2) , Exit(3), Next(4):");
                scanf("%d", &option);

                switch (option)
                {
                    case 0: {
                        int option2;
                        printf("Title: %s\nPrice: %lld\nArea: %lld\nDistrict: %i\nDescription: %s\n", title, price,
                               area,district, description);
                        printf("accept (1), reject(2)? , Exit(3):");
                        scanf("%d", &option2);
                        switch (option2) {
                            case 1:
                                fprintf(ads, "\n%d;%s;%lld;%d;%lld;%s;%lld;%i;%s",*(ad_count)+1,title, area, district, price, description, recommendedprice,1, username);
                                fprintf(record,"%d;%s;%s\n",*(ad_count)+1,username, is_login->userName);
                                *(ad_count) = *ad_count + 1;
                                break;
                            case 2:
                                fprintf(ads, "\n%d;%s;%lld;%d;%lld;%s;%lld;%i;%s",-1,title, area, district, price, description, recommendedprice,-1, username);
                                break;
                            case 3:
                                break;
                        }
                        break;
                    }

                    case 1:
                        fprintf(ads, "\n%d;%s;%lld;%d;%lld;%s;%lld;%i;%s",*(ad_count)+1,title, area, district, price, description, recommendedprice,1, username);
                        fprintf(record,"%d;%s;%s\n",*(ad_count)+1,username, is_login->userName);

                        *(ad_count) = *ad_count + 1;
                        break;
                    case 2:
                        fprintf(ads, "\n%d;%s;%lld;%d;%lld;%s;%lld;%i;%s",-1,title, area, district, price, description, recommendedprice,-1, username);
                        break;
                    case 3:
                        break;
                }
            }
        }
        if(option == 3)
            break;
        res = fscanf(requested, "%d;%[^;];%lld;%d;%lld;%[^;];%lld;%d;%[^\n]\n", &id, title, &area, &district, &price ,
                     description, &recommendedprice, &state, username)> 0;
    }
    fclose(ads);
    fclose(requested);
    fclose(record);

}

void printUsers()
{
    FILE *users = fopen("users.txt", "r");
    int page = 1, res, count = 0;
    char userName[50];
    char password[50];
    char user[20];

    fseek(users,0,SEEK_SET);
    printf("page %d:\n", page);
    //getchar();

    res = fscanf(users, "%[^;];%[^;];%[^\n]\n", userName, password, user) > 0;
    while (res) {

        printf("username: %s, ", userName);
        if(strstr(user,"agent") != NULL) {
            char temp[] = {'a', 'g', 'e', 'n', 't', '\0'};
            printf("user access: %s\n", temp);
            count++;
        }
        else if(strstr(user,"seller") != NULL)
        {
            char temp[] = {'s', 'e', 'l', 'l', 'e','r', '\0'};
            printf("user access: %s\n", temp);
            count++;
        }



        if (count == 10) {
            count = 0;
            int next = -1;
            printf("\n");
            printf("Enter 0 to change a users access.\n");
            printf("Enter 1 to go to the next page of users.\n");
            printf("Enter 2 to go back to the main menu.\n");
            scanf("%d", &next);
            getchar();
            while (1) {
                if (next == 1) {
                    page++;
                    printf("page %d:\n", page);
                    break;
                } else if (next == 0) {
                    printf("Enter the username of the person:");
                    char usetemp[50];
                    char c1 = getchar();
                    while(c1 == '\t' || c1== '\n' || c1 == ' ')
                        c1 = getchar();
                    int i = 0;
                    while(c1 != '\n') {
                        usetemp[i] = c1;
                        i++;
                        c1 = getchar();
                    }
                    usetemp[i]='\0';
                    printf("\n");

                    printf("Enter the access you'd like to grant:");
                    char access[20];
                    char c2 = getchar();
                    while(c2 == '\t' || c2 == '\n' || c2 == ' ')
                        c2 = getchar();
                    i = 0;
                    while(c2 != '\n') {
                        access[i] = c2;
                        i++;
                        c2 = getchar();
                    }
                    access[i]='\0';
                    printf("\n");
                    long int position = ftell(users);
                    change_access(usetemp, access);
                    fseek(users, position, SEEK_SET);


                } else
                    break;
                printf("\n");
                printf("Enter 0 to change a users access.\n");
                printf("Enter 1 to go to the next page of users\n");
                printf("Enter 2 to go back to the main menu\n");
                scanf("%d", &next);
                getchar();
            }
        }
        res = fscanf(users, "%[^;];%[^;];%[^\n]\n", userName, password, user) > 0;
    }
    if (count != 0) {
        while (1) {
            printf("\n");
            printf("Enter 0 to change a users access.\n");
            printf("Enter 1 to go back to the main menu\n");

            int next;
            scanf("%d", &next);
            if (next == 0) {
                printf("Enter the username of the person:");
                char usetemp[50];
                char c1 = getchar();
                while(c1 == '\t' || c1== '\n' || c1 == ' ')
                    c1 = getchar();
                int i = 0;
                while(c1 != '\n') {
                    usetemp[i] = c1;
                    i++;
                    c1 = getchar();
                }
                usetemp[i]='\0';

                printf("Enter the access you'd like to grant:\n");
                char access[20];
                char c2 = getchar();
                while(c2 == '\t' || c2 == '\n' || c2 == ' ')
                    c2 = getchar();
                i = 0;
                while(c2 != '\n') {
                    access[i] = c2;
                    i++;
                    c2 = getchar();
                }
                access[i]='\0';

                long int position = ftell(users);
                change_access(usetemp, access);
                fseek(users, position, SEEK_SET);

            } else
                break;
        }
    }
    fclose(users);

}
void change_access(char username[], char newAccess[])
{
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[26];
    while (fgets(line, sizeof(line), file) != NULL) {
        char user_nametemp[20];
        int i = 0;
        while(line[i] != ';')
        {
            user_nametemp[i] = line[i];
            i++;
        }
        user_nametemp[i]= '\0';
        if (strcmp(user_nametemp, username) == 0) {
            fseek(file, -strlen(line)-1, SEEK_CUR);

            char *rolePos = strstr(line, "seller");
            if(rolePos == NULL)
            {
                rolePos = strstr(line, "agent");
            }
            if (rolePos != NULL) {
                strncpy(rolePos, newAccess, strlen(newAccess));
            }

            fputs(line, file);

            fclose(file);
            printf("Successfully changed!\n");
            return;
        }
    }

    fclose(file);
    printf("Unsuccessful change!\n");


}
void request_promot()
{
    FILE *prom_requests = fopen("prom_requested.txt", "a+");

    fseek(prom_requests,0,SEEK_SET);


    char usernametemp[50];
    int res = fscanf(prom_requests, "%s", usernametemp) > 0;

    while(res)
    {
        if(strcmp(usernametemp, is_login->userName) == 0)
        {
            printf("You already requested for promotion!\n\n");
            fclose(prom_requests);
            return;
        }
        if(strstr(is_login->user,"agent") != NULL)
        {
            printf("You cannot be promoted beyond this level.\n\n");
            fclose(prom_requests);
            return;
        }
        res = fscanf(prom_requests, "%s", usernametemp) > 0;
    }
    fprintf(prom_requests, "%s\n", is_login->userName);
    printf("Your request has been successfully delivered!\n\n");
    fclose(prom_requests);

}

void see_promotion_requests()
{
    FILE *prom_requests = fopen("prom_requested.txt", "r");
    FILE *users = fopen("users.txt", "r");
    FILE *rejected_sellers = fopen("rejected_sellers.txt", "a+");

    int empty = 1;
    fseek(prom_requests,0, SEEK_SET);
    fseek(users,0, SEEK_SET);

    char username[50];
    char username_temp[50];
    char password_temp[50];
    char user_temp[50];
    int n;
    char newaccess[] = {'a','g','e','n','t', '\0'};

    int res = fscanf(prom_requests, "%[^\n]\n", username)>0;
    if(!res)
    {
        printf("No requests have been received yet.\n");
        fclose(prom_requests);
        fclose(users);
        fclose(rejected_sellers);
        return;
    }
    int res2 = fscanf(users, "%[^;];%[^;];%[^\n]\n", username_temp, password_temp, user_temp) > 0;

    int found;
    while(res){
        found = 0;
        while(res2)
        {
            if(!strcmp(username, username_temp) && strstr(user_temp, "agent") != NULL) {
                found = 1;
                break;
            }
            res2 = fscanf(users, "%[^;];%[^;];%[^\n]\n", username_temp, password_temp, user_temp) > 0;
        }
        if(!found)
        {
            char temp[50];
            fseek(rejected_sellers,0, SEEK_SET);
            int res3 = fscanf(rejected_sellers, "%[^\n]\n", temp)>0;
            while(res3)
            {
                if(!strcmp(temp, username))
                {
                    found = 1;
                    break;
                }
                res3 = fscanf(rejected_sellers, "%[^\n]\n", temp)>0;
            }
        }
        if(!found){
            empty = 0;
            printf("%s\n", username);
            printf("accept(0) , reject(1), Exit(2), Next(3)?\n");
            scanf("%d", &n);
            if(n == 0)
            {
                change_access(username, newaccess);
            }
            else if(n == 1)
            {
                fprintf(rejected_sellers, "%s\n", username);
                printf("done!\n");
            }
            else if(n == 2)
                break;
        }

        res = fscanf(prom_requests, "%[^\n]\n", username)>0;

        fseek(users,0, SEEK_SET);
        fseek(rejected_sellers,0, SEEK_SET);
        res2 = fscanf(users, "%[^;];%[^;];%[^\n]\n", username_temp, password_temp, user_temp) > 0;
    }
    if(empty)
    {
        printf("No requests have been received yet.\n");
    }

    fclose(prom_requests);
    fclose(users);
    fclose(rejected_sellers);

}

void see_ads_history()
{
    FILE *record = fopen("record.txt", "r");

    if(record == NULL) {
        printf("There is no ad to display!\n");
        fclose(record);
        return;
    }

    fseek(record, 0,SEEK_SET);
    int ad_id, count, page = 1;
    char seller[50];
    char agent[50];
    printf("page %d:\n", page);
    int res = fscanf(record, "%d;%[^;];%[^\n]\n", &ad_id, seller, agent) > 0;
    while(res)
    {
        printf("Number: %d, Seller: %s, Agent: %s\n", ad_id, seller, agent);
        count ++;

        if(count == 9){
            count = 0;
            int next;
            printf("\n");
            printf("Enter 0 to check an ad with specific information.\n");
            printf("Enter 1 to go to the next page of ads\n");
            printf("Enter 2 to go back to the main menu\n");
            scanf("%d", &next);
            while (1) {
                if (next == 1) {
                    page++;
                    printf("page %d:\n", page);
                    break;
                } else if (next == 0) {
                    printf("Enter the number of ad :");
                    int num;
                    scanf("%d", &num);
                    printAd(num);
                } else {
                    fclose(record);
                    return;
                }
                printf("\n");
                printf("Enter 0 to check an ad with specific information.\n");
                printf("Enter 1 to go to the next page of ads\n");
                printf("Enter 2 to go back to the main menu\n");
                scanf("%i", &next);
            }
        }
        res = fscanf(record, "%d;%[^;];%[^\n]\n", &ad_id, seller, agent) > 0;
    }
    if (count != 0) {
        while (1) {
            printf("\n");
            printf("Enter 0 to check an ad with specific information.\n");
            printf("Enter 1 to go back to the main menu\n");

            int next;
            scanf("%i", &next);
            if (next == 0) {
                printf("Enter the number of ad :");
                int num;
                scanf("%d", &num);
                printAd(num);
            } else {
                fclose(record);
                return;
            }
        }
    }
    fclose(record);

}
