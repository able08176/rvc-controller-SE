//
// Created by Admin on 2024-11-25.
//

#ifndef CONTROLLER_TEST_H
#define CONTROLLER_TEST_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ON 0
#define OFF 1
#define UP 2

typedef struct _Obstacle_Location {
    bool F;
    bool L;
    bool R;
} obstacle_Location;

typedef struct _Cleaner_Command {
    bool on;
    bool off;
    bool up;
} cleaner_Command;

typedef struct _Motor_Command {
    bool F;
    bool L;
    bool R;
    bool B;
} motor_Command;

typedef struct _Controller_Status {
    int rows;
    int cols;
    int row_Num;
    int col_Num;
    char direction;
} controller_Status;

void test_Controller(int **, controller_Status *);

void test_Move_Forward(int **, controller_Status *);

void test_Motor_Interface(int **, controller_Status *, motor_Command);

obstacle_Location test_Determine_OL(int **, controller_Status *);

bool test_FS_Interface(int **, controller_Status *);

bool test_LS_Interface(int **, controller_Status *);

bool test_RS_Interface(int **, controller_Status *);

bool test_Determine_DE(int **, controller_Status *);

bool test_DS_Interface(int **, controller_Status *);

void test_Cleaner_Interface(int **, controller_Status *, cleaner_Command);

void test_Turn_Right(int **, controller_Status *);

void test_Turn_Left(int **, controller_Status *);

void test_Stop(int **, controller_Status *);

void test_Move_Backward(int **, controller_Status *);

cleaner_Command set_Cleaner_Command(int);

#endif //CONTROLLER_TEST_H
