/* COP 3502C Assignment 3  
   This program is written by: Juan de Lapuerta */

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #define MAX_N 10             
   #define MAX_NAME_LEN 20 
   char names[MAX_N][MAX_NAME_LEN];  
   int has_snacks[MAX_N];           
   int restrictions[MAX_N][MAX_N]; 
   int used[MAX_N];                 
   int n, p;                         
   int valid_arrangements = 0;        
   // see if a seating arrangement is valid
   int is_valid(int seating[]) {
       // see if seating restrictions and snack accessibility
       for (int i = 0; i < n - 1; i++) {
           if (restrictions[seating[i]][seating[i + 1]]) {
               return 0;  
           }
       }
       
       // see if everyone has access to snacks
       for (int i = 0; i < n; i++) {
           if (!has_snacks[seating[i]] &&  (i == 0 || !has_snacks[seating[i - 1]]) && (i == n - 1 || !has_snacks[seating[i + 1]])) {
               return 0;  
           }
       }
       
       return 1;  
   }
   
   //generate all possible seat permutations
   void permute(int seating[], int index) {
       // base case
       if (index == n) {
           if (is_valid(seating)) {  
               valid_arrangements++; 
           }
           return;
       }
       
       // placing each person in the current position
       for (int i = 0; i < n; i++) {
           if (!used[i]) {  
               used[i] = 1;       
               seating[index] = i;   
               permute(seating, index + 1); // recursive
               used[i] = 0;    
           }
       }
   }
   
   int main() {
       scanf("%d %d", &n, &p);
       
       // read names and snack
       for (int i = 0; i < n; i++) {
           char name[MAX_NAME_LEN];
           int snack;
           scanf("%s %d", name, &snack);
           strcpy(names[i], name);  
           has_snacks[i] = snack;  
       }
       
       // initialize
       for (int i = 0; i < MAX_N; i++) {
           for (int j = 0; j < MAX_N; j++) {
                restrictions[i][j] = 0;
           }
       }
       
       // read seating restrictions 
       for (int i = 0; i < p; i++) {
           char name1[MAX_NAME_LEN], name2[MAX_NAME_LEN];
           scanf("%s %s", name1, name2); 
           int idx1 = -1, idx2 = -1;
           
           // find indices 
           for (int j = 0; j < n; j++) {
               if (strcmp(names[j], name1) == 0) idx1 = j;
               if (strcmp(names[j], name2) == 0) idx2 = j;
           }
           
           restrictions[idx1][idx2] = 1;
           restrictions[idx2][idx1] = 1;
       }
       
       // initialize used array
       for (int i = 0; i < MAX_N; i++) {
           used[i] = 0;
       }
       
       int seating[MAX_N];  
       permute(seating, 0);
       printf("%d\n", valid_arrangements);
       
       return 0;
   }
   
