/*-------------------------------------------------------------------------------------------------------------------
----                                                                                                            -----
----                               RIVER CROSSSING IMPLEMENTATION IN C - LANGUAGE                               -----
----                                                                                                            -----
----                        Authors : Aniruddh Nagar | Vivek Noel Soren | Akshay Apte                           -----
----                                                                                                            -----
--------------------------------------------------------------------------------------------------------------------*/

//===================================================== LIBRARIES ==================================================//
//==================================================================================================================//

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

//============================================ NODE STRUCTURE DEFINITION ===========================================//
//==================================================================================================================//

typedef struct _state {
	int key;
//	struct _state *parent;
//	struct _state *child;
	bool valid;
//	bool visited;
} STATE;

int hash_map[16];
int number_of_valid_path = 0;
int number_of_invalid_path = 0; 

//============================================ STATE INITIALIZATION FUNCTION =======================================//
//==================================================================================================================//

STATE *make_state(int value){

    STATE *state;
    state = (STATE *)malloc(sizeof(STATE));
    state->key = value;
//   state->parent = NULL;
//   state->child = NULL;
    state->valid = true;
//    state->visited = false;
    return state;
}

//================================================== FINAL CHECK FUNCTION ==========================================//
//==================================================================================================================//

bool isFinalSolution(STATE *state, int h){

    if (state->key == 15){
        return true;
    }
    else
        return false;
}

//=============================================== VALIDITY CHECK FUNCTION ==========================================//
//==================================================================================================================//

bool isValid(STATE *state){
    // 3, 6, 7, 8, 9, 12

    if(state->key == 3 || state->key == 6 || state->key == 7 || state->key == 8 || state->key == 9 || state->key == 12)  
        return false;
    else
        return true;
}

//================================================= REPEAT CHECK FUNCTION ==========================================//
//==================================================================================================================//

bool isRepeat(STATE *state, int h){

    int i;

    for(i=0; i<h; i++){
        if(hash_map[i] == state->key)
            return true;
    }
    
    return false;
}

//============================================= HASH MAP UPDATE FUNCTION  ==========================================//
//==================================================================================================================//

void hash_map_update(STATE *state, int h){

    hash_map[h] = state->key;
    // printf("\n hash_map_update!! \n");
    return;

}

//================================================= PRINT PATH FUNCTION ============================================//
//==================================================================================================================//
void convert(int dec, char *output) {
    output[4] = '\0';
    output[3] = (dec & 1) + '0';
    output[2] = ((dec >> 1) & 1) + '0';
    output[1] = ((dec >> 2) & 1) + '0';
    output[0] = ((dec >> 3) & 1) + '0';
}


void print_path(int h){

    int i,j;
    char binary[5];
    char arr[4] = {'F','W','G','C'};

    for(i=1; i<h; i++){
        convert(hash_map[i], binary);

        printf("\n  ");

        for(j=0; j<4; j++){

            if(binary[j] == '0')
                printf("%c",arr[j]);
            else
                printf("_");
        }
        printf(" | ");

        for(j=0; j<4; j++){

            if(binary[j] == '1')
                printf("%c",arr[j]);
            else
                printf("_");
        }

        printf("\n");
    }
       
}


//============================================= NEXT STATE GENERATION FUNCTION =====================================//
//==================================================================================================================//

void next_state_generation(STATE *state, int h){
    
    if(isFinalSolution(state, h) == true ){
        hash_map_update(state, h);        
        h += 1;
        number_of_valid_path += 1;
        printf("\n Successful Path (%d) ------ \n", number_of_valid_path);
        print_path(h);
        return;
    }

    if(isValid(state) == false ){
        state->valid = false;
        number_of_invalid_path += 1;
        // printf("\n Failed Path (%d) ------ \n", number_of_invalid_path);
        // hash_map_update(state, h);
        // h += 1;
        // print_path(h);
        // h -= 1;        
        return;
    }

    if( isRepeat(state, h) == true ){
        state->valid = false;
        number_of_invalid_path += 1;                
        // printf("\n Failed Path (%d) ------ \n", number_of_invalid_path);
        // hash_map_update(state, h);
        // h += 1;
        // print_path(h);
        // h -= 1;
        return;
    }

    state->valid = true;    

    hash_map_update(state, h);

    STATE *new_state1;
    new_state1 = make_state(12); 
    new_state1->key = (state->key) ^ (new_state1->key);
    h += 1;
    next_state_generation(new_state1, h);
    h -= 1;

    STATE *new_state2;
    new_state2 = make_state(8); 
    new_state2->key = (state->key) ^ (new_state2->key);
    h += 1;
    next_state_generation(new_state2, h);
    h -= 1;

    STATE *new_state3;
    new_state3 = make_state(10); 
    new_state3->key = (state->key) ^ (new_state3->key);
    h += 1;
    next_state_generation(new_state3, h);
    h -= 1;

    STATE *new_state4;
    new_state4 = make_state(9);
    new_state4->key = (state->key) ^ (new_state4->key);
    h += 1;
    next_state_generation(new_state4, h);
    h -= 1;

}


//=============================================== MAIN FUCTION DEFINATION ==========================================//
//==================================================================================================================//

void main(){


    int h = 1;
    
    STATE *state;

    for(int i=0; i<16 ; i++){
        hash_map[i] = -1;
    }

    printf("\n ======== Crossing Started ======= \n");

    state = make_state(0);

    next_state_generation(state, h);

    printf("\n Total Succes Path------ [%d]  \n", number_of_valid_path);

    printf("\n Total Failed Path------ [%d]  \n \n", number_of_invalid_path);


}





//======================================================= CODE END =================================================//
//==================================================================================================================//