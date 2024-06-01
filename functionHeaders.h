#include <stdio.h>
// Created by mahak on 1/21/2024.
//

#ifndef PROJECT_FUNCTIONHEADERS_H
#define PROJECT_FUNCTIONHEADERS_H

typedef struct Person{
    char userName[50];
    char password[50];
    char user[20]; // Seller   Agent  Admin
}Person;
typedef struct Ads{
    int ID;
    char Title[50];
    long long int Price;
    long long int Area;
    int District;
    char Description[500];
    long long int recommendedPrice;
    int State;// 1: accepted   0: Still Not accepted  -1: Passed
    char Username[50]; // the person who has created this ad
}Ads;

void login();
void signup();

int sort1(const void* a, const void* b);
int sort11(const void* a, const void* b);
int sort0(const void* a, const void* b);
int sort01(const void* a, const void* b);
int sort2(const void* a, const void* b);
int sort21(const void* a, const void* b);

void print(int filter);
long long int recommendPrice(Ads *ad);
void Add_ad();
void print_personal_ads();
void printAd(int number);
void requested_ads();
void printUsers();
void change_access(char username[], char newAccess[]);
void request_promot();
void see_promotion_requests();
void see_ads_history();



extern int *ad_count ;
extern Person *is_login;
#endif //PROJECT_FUNCTIONHEADERS_H
