#include "controller.h"

int main(void) {
    printf("Hello, World!\n");
    return 0;
}

void controller(void) {
    obstacle_Location obstacle_Location;
    bool dust_Existence;
    cleaner_Command cleaner_Command;
    cleaner_Command = set_Cleaner_Command(OFF);
    bool is_Backward = false;

    while (1) {
        obstacle_Location = determine_OL();
        dust_Existence = determine_DE();

        if (!obstacle_Location.F && !is_Backward) {
            move_Forward();
            if (dust_Existence) {
                cleaner_Command = set_Cleaner_Command(UP);
                Cleaner_Interface(cleaner_Command);
                sleep(4);
            } else {
                cleaner_Command = set_Cleaner_Command(ON);
                Cleaner_Interface(cleaner_Command);
            }
        } else if (!obstacle_Location.R) {
            turn_Right();
            cleaner_Command = set_Cleaner_Command(OFF);
            Cleaner_Interface(cleaner_Command);
            sleep(4);
            is_Backward = false;
        } else if (!obstacle_Location.L) {
            turn_Left();
            cleaner_Command = set_Cleaner_Command(OFF);
            Cleaner_Interface(cleaner_Command);
            sleep(4);
            is_Backward = false;
        } else {
            stop();
            cleaner_Command = set_Cleaner_Command(OFF);
            Cleaner_Interface(cleaner_Command);
            sleep(1);
            move_Backward();
            is_Backward = true;
        }
        sleep(1);
    }
}

obstacle_Location determine_OL(void) {
    obstacle_Location obstacle_Location;

    obstacle_Location.F = FS_Interface();
    obstacle_Location.L = LS_Interface();
    obstacle_Location.R = RS_Interface();

    return obstacle_Location;
}

bool determine_DE(void) {
    return DS_Interface();
}

bool FS_Interface(void) {
    double front_sensor_analog_input;
    printf("front sensor: ");
    scanf("%lf", front_sensor_analog_input);
    bool front_sensor_input = front_sensor_analog_input > 50 ? true : false;

    return front_sensor_input;
};

bool LS_Interface(void) {
    double left_sensor_analog_input;
    printf("left sensor: ");
    scanf("%lf", left_sensor_analog_input);
    bool left_sensor_input = left_sensor_analog_input > 50 ? true : false;

    return left_sensor_input;
};

bool RS_Interface(void) {
    double right_sensor_analog_input;
    printf("right sensor: ");
    scanf("%lf", right_sensor_analog_input);
    bool right_sensor_input = right_sensor_analog_input > 50 ? true : false;

    return right_sensor_input;
};

bool DS_Interface(void) {
    double dust_sensor_analog_input;
    printf("dust sensor: ");
    scanf("%lf", dust_sensor_analog_input);
    bool dust_sensor_input = dust_sensor_analog_input > 50 ? true : false;

    return dust_sensor_input;
};

void move_Forward(void) {
    motor_Command motor_Command;
    motor_Command.F = true;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);
}

void turn_Left(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = true;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);
}

void turn_Right(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = true;
    motor_Command.B = false;

    Motor_Interface(motor_Command);
}

void stop(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);
}

void move_Backward(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = true;

    Motor_Interface(motor_Command);
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
