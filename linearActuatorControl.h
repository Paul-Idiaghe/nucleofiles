#ifndef LINEAR_ACTUATOR_CONTROL_H
#define LINEAR_ACTUATOR_CONTROL_H

#include "mbed.h"

class LinearActuatorControl {
    private:
        DigitalIn _controlMode;
        DigitalIn _runMode;
        
        PwmOut _linAct1;
        PwmOut _linAct2;
        PwmOut _linAct3;
        PwmOut _linAct4;

        DigitalIn _actBtn1;
        DigitalIn _actBtn2;
        DigitalIn _actBtn3;
        DigitalIn _actBtn4;

        float _idlePositions[4];        //stores values of idle positions, deafult all 0, user defined with setIdlePositions
        float _actPositions[4];         //stores current positions of the actuators, updated by move()
        float _manualPositionsDown[4];  //positions of actuators when switch is down
        float _manualPositionsUp[4];    //positions of actuators when switch is up
        
        float _convertToPulseWidth_us(float);   //takes in value from 0 to 1 for actuator extention percentage, and converts this to the appropriate pulse width in us
    public:
        LinearActuatorControl();

        //user function to command actuators to move, takes any float value from 0 to 1 for the percent extension of the actuator (0.45 = 45% extended)
        //changes _actPositions array
        void move(float pos1, float pos2, float pos3, float pos4);

        //similar to move, but sets the idle positions for the actuators
        void setIdlePositions(float pos1, float pos2, float pos3, float pos4);
        void setManualPositionsDown(float pos1, float pos2, float pos3, float pos4);
        void setManualPositionsUp(float pos1, float pos2, float pos3, float pos4);

        //used to check the state of the machine, will return true if in auto+run mode
        bool inUserSequence();

        void refresh();     //should be called refresh or update?
};

#endif