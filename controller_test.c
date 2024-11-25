//
// Created by 박재영 on 2024. 11. 24..
//
#include "controller.h"

int main() {
    int **test_Map;
    int test_Arr[5][5] = {
        {0, 0, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 1, 0},
        {1, 1, 1, 1, 0}
    };
    int row = 5;
    int col = 5;

    test_Map = (int **) malloc(sizeof(int *) * row);
    for (int i = 0; i < row; ++i) {
        test_Map[i] = (int *) malloc(sizeof(int) * col);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            test_Map[i][j] = test_Arr[i][j];
        }
    }

    controller_Status start;
    start.rows = row;
    start.cols = col;
    start.row_Num = 2;
    start.col_Num = 1;
    start.direction = 'R';

    test_Controller(test_Map, &start);

    for (int i = 0; i < row; ++i) {
        free(test_Map[i]);
    }
    free(test_Map);
}

void test_Controller(int **map, controller_Status *status) {
    obstacle_Location obstacle_Location;
    bool dust_Existence;
    cleaner_Command cleaner_Command;
    cleaner_Command = set_Cleaner_Command(ON);
    test_Cleaner_Interface(map, status, cleaner_Command);
    bool is_Backward = false;

    while (1) {
        obstacle_Location = test_Determine_OL(map, status);
        dust_Existence = test_Determine_DE(map, status);

        if (!obstacle_Location.F && !is_Backward) {
            test_Move_Forward(map, status);
            if (dust_Existence) {
                cleaner_Command = set_Cleaner_Command(UP);
                test_Cleaner_Interface(map, status, cleaner_Command);
                sleep(1);
            } else {
                cleaner_Command = set_Cleaner_Command(ON);
                test_Cleaner_Interface(map, status, cleaner_Command);
            }
        } else if (!obstacle_Location.R) {
            test_Turn_Right(map, status);
            cleaner_Command = set_Cleaner_Command(OFF);
            test_Cleaner_Interface(map, status, cleaner_Command);
            sleep(1);
            is_Backward = false;
        } else if (!obstacle_Location.L) {
            test_Turn_Left(map, status);
            cleaner_Command = set_Cleaner_Command(OFF);
            test_Cleaner_Interface(map, status, cleaner_Command);
            sleep(1);
            is_Backward = false;
        } else {
            test_Stop(map, status);
            cleaner_Command = set_Cleaner_Command(OFF);
            test_Cleaner_Interface(map, status, cleaner_Command);
            sleep(1);
            test_Move_Backward(map, status);
            is_Backward = true;
        }
        printf("\n");
        sleep(1);
    }
}

obstacle_Location test_Determine_OL(int **map, controller_Status *status) {
    obstacle_Location obstacle_Location;

    obstacle_Location.F = test_FS_Interface(map, status);
    obstacle_Location.L = test_LS_Interface(map, status);
    obstacle_Location.R = test_RS_Interface(map, status);

    return obstacle_Location;
}

bool test_FS_Interface(int **map, controller_Status *status) {
    switch (status->direction) {
        case 'R':
            if (status->col_Num + 1 >= status->cols) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num][status->col_Num + 1] == 0) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;

        case 'L':
            if (status->col_Num - 1 < 0) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num][status->col_Num - 1] == 0) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;

        case 'T':
            if (status->row_Num - 1 < 0) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num - 1][status->col_Num] == 0) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;
        case 'B':
            if (status->row_Num + 1 >= status->rows) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num + 1][status->col_Num] == 0) {
                printf("Front Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;
    }
    return false;
}

bool test_LS_Interface(int **map, controller_Status *status) {
    switch (status->direction) {
        case 'R':
            if (status->row_Num - 1 < 0) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num - 1][status->col_Num] == 0) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;

        case 'L':
            if (status->row_Num + 1 >= status->rows) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num + 1][status->col_Num] == 0) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;

        case 'T':
            if (status->col_Num - 1 < 0) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num][status->col_Num - 1] == 0) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;
        case 'B':
            if (status->col_Num + 1 >= status->cols) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num][status->col_Num + 1] == 0) {
                printf("Left Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;
    }
    return false;
}

bool test_RS_Interface(int **map, controller_Status *status) {
    switch (status->direction) {
        case 'R':
            if (status->row_Num + 1 >= status->rows) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num + 1][status->col_Num] == 0) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;

        case 'L':
            if (status->row_Num - 1 < 0) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num - 1][status->col_Num] == 0) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;

        case 'T':
            if (status->col_Num + 1 >= status->cols) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num][status->col_Num + 1] == 0) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;
        case 'B':
            if (status->col_Num - 1 < 0) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else if (map[status->row_Num][status->col_Num - 1] == 0) {
                printf("Right Obstacle Detected!\n");
                return true;
            } else
                return false;
            break;
    }
    return false;
}

bool test_Determine_DE(int **map, controller_Status *status) {
    return test_DS_Interface(map, status);
}

bool test_DS_Interface(int **map, controller_Status *status) {
    if (map[status->row_Num][status->col_Num] >= 2) {
        printf("Dust Detected!\n");
        return true;
    } else
        return false;
}

void test_Move_Forward(int **map, controller_Status *status) {
    motor_Command motor_Command;
    motor_Command.F = true;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    test_Motor_Interface(map, status, motor_Command);
}

void test_Motor_Interface(int **map, controller_Status *status, motor_Command motor_Command) {
    switch (status->direction) {
        case 'R':
            if (motor_Command.F)
                status->col_Num += 1;
            else if (motor_Command.L)
                status->direction = 'T';
            else if (motor_Command.R)
                status->direction = 'B';
            else if (motor_Command.B)
                status->col_Num -= 1;
            break;

        case 'L':
            if (motor_Command.F)
                status->col_Num -= 1;
            else if (motor_Command.L)
                status->direction = 'B';
            else if (motor_Command.R)
                status->direction = 'T';
            else if (motor_Command.B)
                status->col_Num += 1;
            break;

        case 'T':
            if (motor_Command.F)
                status->row_Num -= 1;
            else if (motor_Command.L)
                status->direction = 'L';
            else if (motor_Command.R)
                status->direction = 'R';
            else if (motor_Command.B)
                status->row_Num += 1;
            break;

        case 'B':
            if (motor_Command.F)
                status->row_Num += 1;
            else if (motor_Command.L)
                status->direction = 'R';
            else if (motor_Command.R)
                status->direction = 'L';
            else if (motor_Command.B)
                status->row_Num -= 1;
            break;
    }

    if (motor_Command.F) {
        printf("Move Forward!\n");
        printf("(%d, %d)\n", status->row_Num, status->col_Num);
    } else if (motor_Command.B) {
        printf("Move Backward!\n");
        printf("(%d, %d)\n", status->row_Num, status->col_Num);
    } else if (motor_Command.L) {
        printf("Turn Left!\n");
    } else if (motor_Command.R) {
        printf("Turn Right!\n");
    } else {
        printf("Stop!\n");
    }
}

void test_Cleaner_Interface(int **map, controller_Status *status, cleaner_Command cleaner_Command) {
    if (cleaner_Command.on) {
        printf("Cleaner ON!\n");
        map[status->row_Num][status->col_Num] = 1;
    } else if (cleaner_Command.off) {
        printf("Cleaner OFF!\n");
    } else if (cleaner_Command.up) {
        printf("Cleaner UP!\n");
        map[status->row_Num][status->col_Num] = 1;
    }
}

void test_Turn_Right(int **map, controller_Status *status) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = true;
    motor_Command.B = false;

    test_Motor_Interface(map, status, motor_Command);
}

void test_Turn_Left(int **map, controller_Status *status) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = true;
    motor_Command.R = false;
    motor_Command.B = false;

    test_Motor_Interface(map, status, motor_Command);
}

void test_Stop(int **map, controller_Status *status) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    test_Motor_Interface(map, status, motor_Command);
}

void test_Move_Backward(int **map, controller_Status *status) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = true;

    test_Motor_Interface(map, status, motor_Command);
}

cleaner_Command set_Cleaner_Command(int set_num) {
    cleaner_Command cleaner_Command;

    if (set_num == ON) {
        cleaner_Command.on = true;
        cleaner_Command.off = false;
        cleaner_Command.up = false;
    } else if (set_num == OFF) {
        cleaner_Command.on = false;
        cleaner_Command.off = true;
        cleaner_Command.up = false;
    } else if (set_num == UP) {
        cleaner_Command.on = false;
        cleaner_Command.off = false;
        cleaner_Command.up = true;
    }

    return cleaner_Command;
}
