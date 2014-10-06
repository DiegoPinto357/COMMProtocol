//---------------------------------------------------------------------------

#ifndef comm_protocol_defsH
#define comm_protocol_defsH

//---------------------------------------------------------------------------

//includes

//---------------------------------------------------------------------------

//sync word
#define CMD_SYNC1                             0x55
#define CMD_SYNC2                             0xAA

//control
#define CMD_NOP                               0x00
#define CMD_SET_ADDR                          0x01 //uint8_t addr
#define CMD_GET_INFO                          0x02 /////////////////////////////////////////////////////

#define CMD_DEV_DESC                          0x04 //char *description

#define CMD_PING                              0x06
#define CMD_ACK                               0x07
#define CMD_NACK                              0x08
#define CMD_TEXT                              0x09 //char *text

//debug - data capture
#define CMD_POLL_SCH                          0x0A //uint8_t cmd, uint16_t period
#define CMD_GET_DATA                          0x0B //uint8_t cmd
#define CMD_CAPTURE_DATA                      0x0C //uint8_t cmd, uint8_t trigger_cmd, int16_t trigger_value, uint8_t trigger_mode
#define CMD_DATA_BUFFER                       0x0D //uint8_t cmd

//raw controller data
#define CMD_X_AXIS                            0x20 //int16_t value
#define CMD_Y_AXIS                            0x21 //int16_t value
#define CMD_Z_AXIS                            0x22 //int16_t value
#define CMD_R_AXIS                            0x23 //int16_t value
#define CMD_U_AXIS                            0x24 //int16_t value
#define CMD_V_AXIS                            0x25 //int16_t value
#define CMD_DPAD                              0x26 //uint8_t value
#define CMD_BUTTONS                           0x27 //uint16_t value

//PID controller
#define CMD_PID_PERIOD                        0x60 //uint8_t pid_index, uint16 period
#define CMD_PID_PARAMETERS                    0x61 //uint8_t pid_index, float kp, float ki, float kd
#define CMD_PID_KP                            0x62 //uint8_t pid_index, float kp
#define CMD_PID_KI                            0x63 //uint8_t pid_index, float ki
#define CMD_PID_KD                            0x64 //uint8_t pid_index, float kd

//tank
#define CMD_TANK_MOTOR_R                      0x80 //int16_t value
#define CMD_TANK_MOTOR_L                      0x81 //int16_t value
#define CMD_TANK_ENCODER_R                    0x82 //int16_t value
#define CMD_TANK_ENCODER_L                    0x83 //int16_t value
#define CMD_TANK_CURRENT_R                    0x84 //int16_t value
#define CMD_TANK_CURRENT_L                    0x85 //int16_t value

//pan - tilt
#define CMD_PAN                               0x90 //int16_t value
#define CMD_TILT                              0x91 //int16_t value

//IMU
#define CMD_ACC_X                             0xA0 //int16_t value
#define CMD_ACC_Y                             0xA1 //int16_t value
#define CMD_ACC_Z                             0xA2 //int16_t value
#define CMD_GYRO_X                            0xA3 //int16_t value
#define CMD_GYRO_Y                            0xA4 //int16_t value
#define CMD_GYRO_Z                            0xA5 //int16_t value
#define CMD_YAW                               0xA6 //int16_t value
#define CMD_PITCH                             0xA7 //int16_t value
#define CMD_ROLL                              0xA8 //int16_t value
#define CMD_QUAT                              0xA9 //int16_t q0, int16_t q1, int16_t q2, int16_t q3

//---------------------------------------------------------------------------

//CMD_POLL
#define CMD_POLL_DEACTIVATE                   0x00

//CMD_DPAD
#define CMD_DPAD_UP                           0x01
#define CMD_DPAD_DOWN                         0x02
#define CMD_DPAD_RIGHT                        0x04
#define CMD_DPAD_LEFT                         0x08

//---------------------------------------------------------------------------

const char CMD_DESCRIPTION[256][16]=
                                    {"NOP",              //0x00 CMD_NOP
                                     "Set Address",      //0x01 CMD_SET_ADDR
                                     "Get Info",         //0x02 CMD_GET_INFO
                                     "\0",               //0x03
                                     "Dev Description",  //0x04 CMD_DEV_DESC
                                     "\0",               //0x05
                                     "Ping",             //0x06 CMD_PING
                                     "Acknowledge",      //0x07 CMD_ACK
                                     "Not Acknowledge",  //0x08 CMD_NACK
                                     "Text",             //0x09 CMD_TEXT
                                     "Poll Schedule",    //0x0A CMD_POLL_SCH
                                     "Get Data",         //0x0B CMD_GET_DATA
                                     "Capture Data",     //0x0C CMD_CAPTURE_DATA
                                     "Data Buffer",      //0x0D CMD_DATA_BUFFER
                                     "\0",               //0x0E
                                     "\0",               //0x0F
                                     "\0",               //0x10
                                     "\0",               //0x11
                                     "\0",               //0x12
                                     "\0",               //0x13
                                     "\0",               //0x14
                                     "\0",               //0x15
                                     "\0",               //0x16
                                     "\0",               //0x17
                                     "\0",               //0x18
                                     "\0",               //0x19
                                     "\0",               //0x1A
                                     "\0",               //0x1B
                                     "\0",               //0x1C
                                     "\0",               //0x1D
                                     "\0",               //0x1E
                                     "\0",               //0x1F
                                     "Control X Axis",   //0x20 CMD_X_AXIS
                                     "Control Y Axis",   //0x21 CMD_Y_AXIS 
                                     "Control Z Axis",   //0x22 CMD_Z_AXIS 
                                     "Control R Axis",   //0x23 CMD_R_AXIS 
                                     "Control U Axis",   //0x24 CMD_U_AXIS 
                                     "Control V Axis",   //0x25 CMD_V_AXIS 
                                     "Control D Pad",    //0x26 CMD_DPAD
                                     "Control Buttons",  //0x27 CMD_BUTTONS
                                     "\0",               //0x28
                                     "\0",               //0x29
                                     "\0",               //0x2A
                                     "\0",               //0x2B
                                     "\0",               //0x2C
                                     "\0",               //0x2D
                                     "\0",               //0x2E
                                     "\0",               //0x2F
                                     "\0",               //0x30
                                     "\0",               //0x31
                                     "\0",               //0x32
                                     "\0",               //0x33
                                     "\0",               //0x34
                                     "\0",               //0x35
                                     "\0",               //0x36
                                     "\0",               //0x37
                                     "\0",               //0x38
                                     "\0",               //0x39
                                     "\0",               //0x3A
                                     "\0",               //0x3B
                                     "\0",               //0x3C
                                     "\0",               //0x3D
                                     "\0",               //0x3E
                                     "\0",               //0x3F
                                     "\0",               //0x40
                                     "\0",               //0x41
                                     "\0",               //0x42
                                     "\0",               //0x43
                                     "\0",               //0x44
                                     "\0",               //0x45
                                     "\0",               //0x46
                                     "\0",               //0x47
                                     "\0",               //0x48
                                     "\0",               //0x49
                                     "\0",               //0x4A
                                     "\0",               //0x4B
                                     "\0",               //0x4C
                                     "\0",               //0x4D
                                     "\0",               //0x4E
                                     "\0",               //0x4F
                                     "\0",               //0x50
                                     "\0",               //0x51
                                     "\0",               //0x52
                                     "\0",               //0x53
                                     "\0",               //0x54
                                     "Sync 1",           //0x55 CMD_SYNC1
                                     "\0",               //0x56
                                     "\0",               //0x57
                                     "\0",               //0x58
                                     "\0",               //0x59
                                     "\0",               //0x5A
                                     "\0",               //0x5B
                                     "\0",               //0x5C
                                     "\0",               //0x5D
                                     "\0",               //0x5E
                                     "\0",               //0x5F
                                     "PID Period",       //0x60 CMD_PID_PERIOD
                                     "PID Parameters",   //0x61 CMD_PID_PARAMETERS
                                     "PID Kp",           //0x62 CMD_PID_KP
                                     "PID Ki",           //0x63 CMD_PID_KI
                                     "PID Kd",           //0x64 CMD_PID_KD
                                     "\0",               //0x65
                                     "\0",               //0x66
                                     "\0",               //0x67
                                     "\0",               //0x68
                                     "\0",               //0x69
                                     "\0",               //0x6A
                                     "\0",               //0x6B
                                     "\0",               //0x6C
                                     "\0",               //0x6D
                                     "\0",               //0x6E
                                     "\0",               //0x6F
                                     "\0",               //0x70
                                     "\0",               //0x71
                                     "\0",               //0x72
                                     "\0",               //0x73
                                     "\0",               //0x74
                                     "\0",               //0x75
                                     "\0",               //0x76
                                     "\0",               //0x77
                                     "\0",               //0x78
                                     "\0",               //0x79
                                     "\0",               //0x7A
                                     "\0",               //0x7B
                                     "\0",               //0x7C
                                     "\0",               //0x7D
                                     "\0",               //0x7E
                                     "\0",               //0x7F
                                     "Tank R Motor",     //0x80 CMD_TANK_MR
                                     "Tank L Motor",     //0x81 CMD_TANK_ML
                                     "Tank R Encoder",   //0x82 CMD_TANK_SPEED_R
                                     "Tank L Encoder",   //0x83 CMD_TANK_SPEED_L
                                     "Tank R Current",   //0x84 CMD_TANK_CURRENT_R
                                     "Tank L Current",   //0x85 CMD_TANK_CURRENT_L
                                     "\0",               //0x86
                                     "\0",               //0x87
                                     "\0",               //0x88
                                     "\0",               //0x89
                                     "\0",               //0x8A
                                     "\0",               //0x8B
                                     "\0",               //0x8C
                                     "\0",               //0x8D
                                     "\0",               //0x8E
                                     "\0",               //0x8F
                                     "Pan",              //0x90 CMD_PAN
                                     "Tilt",             //0x91 CMD_TILT
                                     "\0",               //0x92
                                     "\0",               //0x93
                                     "\0",               //0x94
                                     "\0",               //0x95
                                     "\0",               //0x96
                                     "\0",               //0x97
                                     "\0",               //0x98
                                     "\0",               //0x99
                                     "\0",               //0x9A
                                     "\0",               //0x9B
                                     "\0",               //0x9C
                                     "\0",               //0x9D
                                     "\0",               //0x9E
                                     "\0",               //0x9F
                                     "Acc X Axis",       //0xA0 CMD_ACC_X
                                     "Acc Y Axis",       //0xA1 CMD_ACC_Y
                                     "Acc Z Axis",       //0xA2 CMD_ACC_Z
                                     "Gyro X Axis",      //0xA3 CMD_GYRO_X
                                     "Gyro Y Axis",      //0xA4 CMD_GYRO_Y
                                     "Gyro Z Axis",      //0xA5 CMD_GYRO_Z
                                     "IMU Yaw",          //0xA6 CMD_YAW
                                     "IMU Pitch",        //0xA7 CMD_PITCH
                                     "IMU Roll",         //0xA8 CMD_ROLL
                                     "IMU Quaternion",   //0xA9 CMD_QUAT
                                     "Sync 2",           //0xAA CMD_SYNC2
                                     "\0",               //0xAB
                                     "\0",               //0xAC
                                     "\0",               //0xAD
                                     "\0",               //0xAE
                                     "\0",               //0xAF
                                     "\0",               //0xB0
                                     "\0",               //0xB1
                                     "\0",               //0xB2
                                     "\0",               //0xB3
                                     "\0",               //0xB4
                                     "\0",               //0xB5
                                     "\0",               //0xB6
                                     "\0",               //0xB7
                                     "\0",               //0xB8
                                     "\0",               //0xB9
                                     "\0",               //0xBA
                                     "\0",               //0xBB
                                     "\0",               //0xBC
                                     "\0",               //0xBD
                                     "\0",               //0xBE
                                     "\0",               //0xBF
                                     "\0",               //0xC0
                                     "\0",               //0xC1
                                     "\0",               //0xC2
                                     "\0",               //0xC3
                                     "\0",               //0xC4
                                     "\0",               //0xC5
                                     "\0",               //0xC6
                                     "\0",               //0xC7
                                     "\0",               //0xC8
                                     "\0",               //0xC9
                                     "\0",               //0xCA
                                     "\0",               //0xCB
                                     "\0",               //0xCC
                                     "\0",               //0xCD
                                     "\0",               //0xCE
                                     "\0",               //0xCF
                                     "\0",               //0xD0
                                     "\0",               //0xD1
                                     "\0",               //0xD2
                                     "\0",               //0xD3
                                     "\0",               //0xD4
                                     "\0",               //0xD5
                                     "\0",               //0xD6
                                     "\0",               //0xD7
                                     "\0",               //0xD8
                                     "\0",               //0xD9
                                     "\0",               //0xDA
                                     "\0",               //0xDB
                                     "\0",               //0xDC
                                     "\0",               //0xDD
                                     "\0",               //0xDE
                                     "\0",               //0xDF
                                     "\0",               //0xE0
                                     "\0",               //0xE1
                                     "\0",               //0xE2
                                     "\0",               //0xE3
                                     "\0",               //0xE4
                                     "\0",               //0xE5
                                     "\0",               //0xE6
                                     "\0",               //0xE7
                                     "\0",               //0xE8
                                     "\0",               //0xE9
                                     "\0",               //0xEA
                                     "\0",               //0xEB
                                     "\0",               //0xEC
                                     "\0",               //0xED
                                     "\0",               //0xEE
                                     "\0",               //0xEF
                                     "\0",               //0xF0
                                     "\0",               //0xF1
                                     "\0",               //0xF2
                                     "\0",               //0xF3
                                     "\0",               //0xF4
                                     "\0",               //0xF5
                                     "\0",               //0xF6
                                     "\0",               //0xF7
                                     "\0",               //0xF8
                                     "\0",               //0xF9
                                     "\0",               //0xFA
                                     "\0",               //0xFB
                                     "\0",               //0xFC
                                     "\0",               //0xFD
                                     "\0",               //0xFE
                                     "\0"};              //0xFF

//---------------------------------------------------------------------------                                          
#endif
