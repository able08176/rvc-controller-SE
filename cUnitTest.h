//
// Created by 박재영 on 2024. 11. 21..
//

#ifndef RVC_CONTROLLER_CONTROLLER_H
#define RVC_CONTROLLER_CONTROLLER_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"
#define ON 0
#define OFF 1
#define UP 2

// new dataTypes for RVC
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

// RVC functions (refactoring for cUnit)
void controller(bool is_Backward, obstacle_Location OL, bool DE);
obstacle_Location determine_OL(double fsi, double lsi, double rsi);
bool determine_DE(bool dsi);
bool FS_Interface(double sensor_input);
bool LS_Interface(double sensor_input);
bool RS_Interface(double sensor_input);
bool DS_Interface(double sensor_input);
const char* Cleaner_Interface(cleaner_Command cleaner_Command);
const char* Motor_Interface(motor_Command motor_Command);
motor_Command move_Forward(void);
motor_Command turn_Left(void);
motor_Command turn_Right(void);
motor_Command stop(void);
motor_Command move_Backward(void);
cleaner_Command set_Cleaner_Command(int set_num);

// suite_1 (6 TC) - about interfaces
void test_FS_Interface(void);
void test_LS_Interface(void);
void test_RS_Interface(void);
void test_DS_Interface(void);
void test_Cleaner_Interface(void);
void test_Motor_Interface(void);

// suite_2 (2 TC) - about determiners
void test_Determine_OL(void);
void test_Determine_DE(void);

// suite_3 (5 TC) - about motor operations
void test_Move_Forward(void);
void test_Turn_Left(void);
void test_Turn_Right(void);
void test_Stop(void);
void test_Move_Backward(void);

// suite_4 (1 TC) - about set_cleaner_command
void test_Set_Cleaner_Command(void);

// suite_5 (5 TC) - about controller
void test_Controller_MF(void);
void test_Controller_UP(void);
void test_Controller_TR(void);
void test_Controller_TL(void);
void test_Controller_SMB(void);

#endif //RVC_CONTROLLER_CONTROLLER_H
