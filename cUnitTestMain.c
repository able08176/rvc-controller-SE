#include "cUnitTest.h"

int main(void) {
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", NULL, NULL);

	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	// add the tests to the suite1
	if ((NULL == CU_add_test(pSuite, "test of FS_Interface", test_FS_Interface)) ||
		(NULL == CU_add_test(pSuite, "test of LS_Interface", test_LS_Interface)) ||
		(NULL == CU_add_test(pSuite, "test of RS_Interface", test_RS_Interface)) ||
		(NULL == CU_add_test(pSuite, "test of DS_Interface", test_DS_Interface)) ||
		(NULL == CU_add_test(pSuite, "test of Cleaner_Interface", test_Cleaner_Interface)) ||
		(NULL == CU_add_test(pSuite, "test of Motor_Interface", test_Motor_Interface)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	// add the tests to the suite2
	pSuite = CU_add_suite("Suite_2", NULL, NULL);
                                                         
	if ((NULL == CU_add_test(pSuite, "test of determine_OL", test_Determine_OL)) ||
                (NULL == CU_add_test(pSuite, "test of determine_DE", test_Determine_DE)))
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

	// add the tests to the suite3 
	pSuite = CU_add_suite("Suite_3", NULL, NULL);

	if ((NULL == CU_add_test(pSuite, "test of Move_Forward", test_Move_Forward)) ||
		(NULL == CU_add_test(pSuite, "test of Turn_Left", test_Turn_Left)) ||
		(NULL == CU_add_test(pSuite, "test of Turn_Right", test_Turn_Right)) ||
		(NULL == CU_add_test(pSuite, "test of Stop", test_Stop)) ||
		(NULL == CU_add_test(pSuite, "test of Move_Backward", test_Move_Backward)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	
	}

	// add the tests to the suite4 
	pSuite = CU_add_suite("Suite_4", NULL, NULL);	

	if ((NULL == CU_add_test(pSuite, "test of Set_Cleaner_Command", test_Set_Cleaner_Command)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}	
	
	// add the tests to the suite5 	
	pSuite = CU_add_suite("Suite_5", NULL, NULL);

	if ((NULL == CU_add_test(pSuite, "test of controller_Move_Forward", test_Controller_MF)) ||
		(NULL == CU_add_test(pSuite, "test of controller_Power_Up", test_Controller_UP)) ||
 		(NULL == CU_add_test(pSuite, "test of controller_Turn_Right", test_Controller_TR)) ||
		(NULL == CU_add_test(pSuite, "test of controller_Turn_Left", test_Controller_TL)) ||
		(NULL == CU_add_test(pSuite, "test of controller_Stop_and_Move_Backward", test_Controller_SMB)) ||
		(NULL == CU_add_test(pSuite, "test of controller_Move_Backward_and_Turn_Right", test_Controller_MBTR)) ||
		(NULL == CU_add_test(pSuite, "test of controller_Move_Backward_and_Turn_Left", test_Controller_MBTL)) ||
		(NULL == CU_add_test(pSuite, "test of controller_Keep_Move_Backward", test_Controller_MBMB)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

const char* controller(bool is_Backward, obstacle_Location OL, bool DE) {
    obstacle_Location obstacle_Location;
    const char *result;
    bool dust_Existence;

    obstacle_Location = OL;
    dust_Existence = DE;

    if (!obstacle_Location.F && !is_Backward) {
        if (dust_Existence) {
		result = "{1, 0, 0, 0}, {0, 0, 1}"; 
	} else {
		result = "{1, 0, 0, 0}, {1, 0, 0}";
        }
    } else if (!obstacle_Location.R) {
	result = "{0, 0, 1, 0}, {0, 1, 0}"; 
    } else if (!obstacle_Location.L) {
	result = "{0, 1, 0, 0}, {0, 1, 0}";
    } else {
	result = "{0, 0, 0, 0}, {0, 1, 0}, {0, 0, 0, 1}";
    }

    return result;
}
                
obstacle_Location determine_OL(double fsi, double lsi, double rsi) {
    obstacle_Location obstacle_Location;

    obstacle_Location.F = FS_Interface(fsi);
    obstacle_Location.L = LS_Interface(lsi);
    obstacle_Location.R = RS_Interface(rsi);

    return obstacle_Location;
}

bool determine_DE(bool dsi) {
    return dsi;
}

bool FS_Interface(double sensor_input) {
    double front_sensor_analog_input = sensor_input;
    bool front_sensor_input = front_sensor_analog_input > 50 ? true : false;

    return front_sensor_input;
}

bool LS_Interface(double sensor_input) {
    double left_sensor_analog_input = sensor_input;
    bool left_sensor_input = left_sensor_analog_input > 50 ? true : false;

    return left_sensor_input;
}

bool RS_Interface(double sensor_input) {
    double right_sensor_analog_input = sensor_input;
    bool right_sensor_input = right_sensor_analog_input > 50 ? true : false;

    return right_sensor_input;
}

bool DS_Interface(double sensor_input) {
    double dust_sensor_analog_input = sensor_input;
    bool dust_sensor_input = dust_sensor_analog_input > 50 ? true : false;

    return dust_sensor_input;
}

motor_Command move_Forward(void) {
    motor_Command motor_Command;
    motor_Command.F = true;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command turn_Left(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = true;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command turn_Right(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = true;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command stop(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command move_Backward(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = true;

    Motor_Interface(motor_Command);
    
    return motor_Command;
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

const char *Cleaner_Interface(cleaner_Command cleaner_Command) {
    const char *result;

    if (cleaner_Command.on)
    	result = "ON";
    else if (cleaner_Command.off)
        result = "OFF";
    else
	result = "UP";

    return result;
}

const char *Motor_Interface(motor_Command motor_Command) {
    const char *result;

    if (motor_Command.F) 
        result = "Move Forward";
    else if (motor_Command.L)
	result = "Turn Left";
    else if (motor_Command.R)
	result = "Turn Right";
    else if (motor_Command.B)
	result = "Move Backward";
    else
	result = "Stop";

    return result;
}

// suite 1
void test_FS_Interface(void) {
    CU_ASSERT(false == FS_Interface(-12));
    CU_ASSERT(false == FS_Interface(0));
    CU_ASSERT(false == FS_Interface(40));
    CU_ASSERT(false == FS_Interface(50));
    CU_ASSERT(true == FS_Interface(70));
    CU_ASSERT(true == FS_Interface(100));
    CU_ASSERT(true == FS_Interface(1557));
}
void test_LS_Interface(void) {
    CU_ASSERT(false == LS_Interface(-12));
    CU_ASSERT(false == LS_Interface(0));
    CU_ASSERT(false == LS_Interface(40));
    CU_ASSERT(false == LS_Interface(50));
    CU_ASSERT(true == LS_Interface(70));   
    CU_ASSERT(true == LS_Interface(100));
    CU_ASSERT(true == LS_Interface(1557));
}
void test_RS_Interface(void) {
    CU_ASSERT(false == RS_Interface(-12));
    CU_ASSERT(false == RS_Interface(0));
    CU_ASSERT(false == RS_Interface(40));
    CU_ASSERT(false == RS_Interface(50));
    CU_ASSERT(true == RS_Interface(70));
    CU_ASSERT(true == RS_Interface(100));
    CU_ASSERT(true == RS_Interface(1557));
}
void test_DS_Interface(void) {
    CU_ASSERT(false == DS_Interface(-12));
    CU_ASSERT(false == DS_Interface(0));
    CU_ASSERT(false == DS_Interface(40));
    CU_ASSERT(false == DS_Interface(50));
    CU_ASSERT(true == DS_Interface(70));
    CU_ASSERT(true == DS_Interface(100));
    CU_ASSERT(true == DS_Interface(1557));
}
void test_Cleaner_Interface(void) {
    cleaner_Command cc;
    cc.on = true;
    cc.off = false;
    cc.up = false;
    CU_ASSERT_STRING_EQUAL(Cleaner_Interface(cc), "ON");

    cc.on = false;
    cc.off = true;
    cc.up = false;
    CU_ASSERT_STRING_EQUAL(Cleaner_Interface(cc), "OFF");

    cc.on = false;
    cc.off = false;
    cc.up = true;
    CU_ASSERT_STRING_EQUAL(Cleaner_Interface(cc), "UP");
}
void test_Motor_Interface(void) {
    motor_Command mc;
    mc.F = true;
    mc.L = false;
    mc.R = false;
    mc.B = false;
    CU_ASSERT_STRING_EQUAL(Motor_Interface(mc), "Move Forward");

    mc.F = false;
    mc.L = true;
    mc.R = false;
    mc.B = false;
    CU_ASSERT_STRING_EQUAL(Motor_Interface(mc), "Turn Left");

    mc.F = false;
    mc.L = false;
    mc.R = true;
    mc.B = false;
    CU_ASSERT_STRING_EQUAL(Motor_Interface(mc), "Turn Right");

    mc.F = false;
    mc.L = false;
    mc.R = false;
    mc.B = true;
    CU_ASSERT_STRING_EQUAL(Motor_Interface(mc), "Move Backward");

    mc.F = false;
    mc.L = false;
    mc.R = false;
    mc.B = false;
    CU_ASSERT_STRING_EQUAL(Motor_Interface(mc), "Stop");

    mc.F = true;
    mc.L = true;
    mc.R = false;
    mc.B = false;
    CU_ASSERT_STRING_EQUAL(Motor_Interface(mc), "Turn Left");	
}

// suite 2
void test_Determine_OL(void) {
    CU_ASSERT(true == ((determine_OL(67, 12, 33).F == true) 
		&& (determine_OL(67, 12, 33).L == false) 
		&& (determine_OL(67, 12, 33).R == false)));
}
void test_Determine_DE(void) {
    CU_ASSERT(determine_DE(true) == true);
    CU_ASSERT(determine_DE(false) == false);
}

// suite 3
void test_Move_Forward(void) {
	CU_ASSERT(true == ((move_Forward().F == true)
		    && (move_Forward().L == false)
		    && (move_Forward().R == false)
	            && (move_Forward().B == false)));
}
void test_Turn_Left(void) {
	CU_ASSERT(true == ((turn_Left().F == false)
		    && (turn_Left().L == true)
		    && (turn_Left().R == false)
	            && (turn_Left().B == false)));
}
void test_Turn_Right(void) {
	CU_ASSERT(true == ((turn_Right().F == false)
		    && (turn_Right().L == false)
		    && (turn_Right().R == true)
	            && (turn_Right().B == false)));
}
void test_Stop(void) {
	CU_ASSERT(true == ((stop().F == false)
		    && (stop().L == false)
		    && (stop().R == false)
	            && (stop().B == false)));
}
void test_Move_Backward(void) {
	CU_ASSERT(true == ((move_Backward().F == false)
		    && (move_Backward().L == false)
		    && (move_Backward().R == false)
	            && (move_Backward().B == true)));
}

// suite 4
void test_Set_Cleaner_Command(void) {
	CU_ASSERT(true == ((set_Cleaner_Command(0).on == true)
		    && (set_Cleaner_Command(0).off == false)
 		    && (set_Cleaner_Command(0).up == false)));
	CU_ASSERT(true == ((set_Cleaner_Command(1).on == false)
                    && (set_Cleaner_Command(1).off == true)
                    && (set_Cleaner_Command(1).up == false)));
	CU_ASSERT(true == ((set_Cleaner_Command(2).on == false)
                    && (set_Cleaner_Command(2).off == false)
                    && (set_Cleaner_Command(2).up == true)));
}

// suite 5
void test_Controller_MF(void) {
	obstacle_Location OL;

	OL.F = false;
	OL.L = false;
	OL.R = false;
	CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{1, 0, 0, 0}, {1, 0, 0}");

	OL.F = false;
        OL.L = true;
        OL.R = false;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{1, 0, 0, 0}, {1, 0, 0}");

	OL.F = false;
        OL.L = false;
        OL.R = true;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{1, 0, 0, 0}, {1, 0, 0}");

	OL.F = false;
        OL.L = true;
        OL.R = true;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{1, 0, 0, 0}, {1, 0, 0}");
}
void test_Controller_UP(void) {
        obstacle_Location OL;

        OL.F = false;
        OL.L = false;
        OL.R = false;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, true), "{1, 0, 0, 0}, {0, 0, 1}");
}
void test_Controller_TR(void) {
        obstacle_Location OL;

        OL.F = true;
        OL.L = false;
        OL.R = false;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{0, 0, 1, 0}, {0, 1, 0}");

	OL.F = true;
        OL.L = true;
        OL.R = false;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{0, 0, 1, 0}, {0, 1, 0}");
}
void test_Controller_TL(void) {
        obstacle_Location OL;

        OL.F = true;
        OL.L = false;
        OL.R = true;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{0, 1, 0, 0}, {0, 1, 0}");
}
void test_Controller_SMB(void) {
        obstacle_Location OL;

        OL.F = true;
        OL.L = true;
        OL.R = true;
        CU_ASSERT_STRING_EQUAL(controller(false, OL, false), "{0, 0, 0, 0}, {0, 1, 0}, {0, 0, 0, 1}");
}
void test_Controller_MBTR(void) {
	obstacle_Location OL;

        OL.F = false;
        OL.L = true;
        OL.R = false;
        CU_ASSERT_STRING_EQUAL(controller(true, OL, false), "{0, 0, 1, 0}, {0, 1, 0}");

        OL.F = false;
        OL.L = false;
        OL.R = false;
        CU_ASSERT_STRING_EQUAL(controller(true, OL, false), "{0, 0, 1, 0}, {0, 1, 0}");
}
void test_Controller_MBTL(void) {
        obstacle_Location OL;

        OL.F = false;
        OL.L = false;
        OL.R = true;
        CU_ASSERT_STRING_EQUAL(controller(true, OL, false), "{0, 1, 0, 0}, {0, 1, 0}");
}
void test_Controller_MBMB(void) {
        obstacle_Location OL;

        OL.F = true;
        OL.L = true;
        OL.R = true;
        CU_ASSERT_STRING_EQUAL(controller(true, OL, false), "{0, 0, 0, 1}, {0, 1, 0}");
}
