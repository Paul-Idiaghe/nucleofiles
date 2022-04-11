#include "linearActuatorControl.h"

LinearActuatorControl::LinearActuatorControl() : _controlMode(D7), _runMode(D8), 
    _linAct1(D9), _linAct2(D10), _linAct3(D11), _linAct4(D12), 
    _actBtn1(D3), _actBtn2(D4), _actBtn3(D5), _actBtn4(D6) {
        
    for (int i = 0; i < 4; i++) {
        _idlePositions[i] = 0;
        _actPositions[i] = 0;
        _manualPositionsDown[i] = 0;
        _manualPositionsUp[i] = 1;
    }

    _linAct1.period_ms(20);
    _linAct2.period_ms(20);
    _linAct3.period_ms(20);
    _linAct4.period_ms(20);
}

void LinearActuatorControl::refresh() {
    if (!_controlMode) {
        _linAct1.pulsewidth_us(!_actBtn1 ? (1000*(1+_manualPositionsDown[0])) : (1000*(1+_manualPositionsUp[0])));
        _linAct2.pulsewidth_us(!_actBtn2 ? (1000*(1+_manualPositionsDown[1])) : (1000*(1+_manualPositionsUp[1])));
        _linAct3.pulsewidth_us(!_actBtn3 ? (1000*(1+_manualPositionsDown[2])) : (1000*(1+_manualPositionsUp[2])));
        _linAct4.pulsewidth_us(!_actBtn4 ? (1000*(1+_manualPositionsDown[3])) : (1000*(1+_manualPositionsUp[3])));
        
    } else {
        if (_runMode) { 
            //update PWM to sequence positions
            _linAct1.pulsewidth_us(1000*(1+_actPositions[0]));
            _linAct2.pulsewidth_us(1000*(1+_actPositions[1]));
            _linAct3.pulsewidth_us(1000*(1+_actPositions[2]));
            _linAct4.pulsewidth_us(1000*(1+_actPositions[3]));
        } else {
            //change to idle positions
            _linAct1.pulsewidth_us(1000*(1+_idlePositions[0]));
            _linAct2.pulsewidth_us(1000*(1+_idlePositions[1]));
            _linAct3.pulsewidth_us(1000*(1+_idlePositions[2]));
            _linAct4.pulsewidth_us(1000*(1+_idlePositions[3]));
        }
    }
}

void LinearActuatorControl::setIdlePositions(float pos1, float pos2, float pos3, float pos4) {
    _idlePositions[0] = pos1;
    _idlePositions[1] = pos2;
    _idlePositions[2] = pos3;
    _idlePositions[3] = pos4;
}

void LinearActuatorControl::setManualPositionsDown(float pos1, float pos2, float pos3, float pos4) {
    _manualPositionsDown[0] = pos1;
    _manualPositionsDown[1] = pos2;
    _manualPositionsDown[2] = pos3;
    _manualPositionsDown[3] = pos4;
}

void LinearActuatorControl::setManualPositionsUp(float pos1, float pos2, float pos3, float pos4) {
    _manualPositionsUp[0] = pos1;
    _manualPositionsUp[1] = pos2;
    _manualPositionsUp[2] = pos3;
    _manualPositionsUp[3] = pos4;
}

void LinearActuatorControl::move(float pos1, float pos2, float pos3, float pos4) {
    _actPositions[0] = pos1;
    _actPositions[1] = pos2;
    _actPositions[2] = pos3;
    _actPositions[3] = pos4;
    refresh();
}

bool LinearActuatorControl::inUserSequence() {
    if (_controlMode && _runMode) {
        return true;
    } 
    return false;
}

float _convertToPulseWidth_us(float input) {
    return 1000*(1+input);   
}