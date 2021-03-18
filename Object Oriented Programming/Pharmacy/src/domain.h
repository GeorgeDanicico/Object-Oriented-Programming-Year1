#pragma once

typedef struct {
    char* name;
    int concentration;
    int quantity;
    int price;
}Medicine;

Medicine* createMedicine(char* name, int concentration, int quantity, int price);
void destroyMedicine(Medicine* medicine);
char* getName(Medicine* medicine);
int getConcentration(Medicine* medicine);
int getQuantity(Medicine* medicine);
int getPrice(Medicine* medicine);
void setPrice(Medicine* medicine, int new_price);
void setQuantity(Medicine* medicine, int quantity);