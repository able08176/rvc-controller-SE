//
// Created by 박재영 on 2024. 11. 21..
//

#ifndef RVC_CONTROLLER_CONTROLLER_H
#define RVC_CONTROLLER_CONTROLLER_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
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

// RVC functions
void controller(bool is_Backward, obstacle_Location OL, bool DE);
obstacle_Location determine_OL(void);
bool determine_DE(void);
bool FS_Interface(void);
bool LS_Interface(void);
bool RS_Interface(void);
bool DS_Interface(void);
void Cleaner_Interface(cleaner_Command cleaner_Command);
void Motor_Interface(motor_Command motor_Command);
motor_Command move_Forward(void);
motor_Command turn_Left(void);
motor_Command turn_Right(void);
motor_Command stop(void);
motor_Command move_Backward(void);
cleaner_Command set_Cleaner_Command(int);

#endif //RVC_CONTROLLER_CONTROLLER_H
