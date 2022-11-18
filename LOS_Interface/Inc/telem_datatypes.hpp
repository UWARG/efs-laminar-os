#ifndef INC_TELEM_DATATYPES_HPP_
#define INC_TELEM_DATATYPES_HPP_

//TODO: Determine max number of waypoints
constexpr uint8_t MAX_WAYPOINTS = 10;
constexpr uint8_t NUM_MOTOR_OUTPUTS = 12;
constexpr uint8_t NUM_BATTERY_VOLTAGES = 13;
constexpr uint8_t NUM_CONTROLLER_VALUES = 16;
constexpr uint8_t NUM_AXES = 6;

typedef struct {
	double longitude;
	double latitude;
	double altitude;
  uint8_t waypointID;
} Waypoint_t;

typedef struct {
  uint8_t numWaypoints;
	Waypoint_t waypoints[MAX_WAYPOINTS];
} Waypoint_Message_t;

typedef struct {
  double P;
  double I;
  double D;
} PID_t;

typedef struct {
  uint8_t controller;
  uint8_t axis;
  PID_t PID;
} PID_Message_t;

typedef struct {
  bool arm;
} Arm_Message_t;

typedef struct {
  bool recievedWaypoints;
  Waypoint_Message_t waypointMessage;

  bool receivedPID;
  PID_Message_t PIDMessage;

  bool receivedArm;
  Arm_Message_t armMessage;
} Data_From_Ground_t;


typedef struct {
    uint8_t motorOutputs[NUM_MOTOR_OUTPUTS];

	double latitude;
	double longitude;
	double altitude;
	double climbRate;
	double track;
	double heading;
	double airSpeed;
	double groundSpeed;
	double roll;
	double pitch;
	double yaw;
	double rollRate;
	double pitchRate;
	double yawRate;

  //First value is overall voltage
  //3V-5V is mapped to range 0-200
  uint8_t batteryVoltages[NUM_BATTERY_VOLTAGES];

  uint8_t controllerValues[NUM_CONTROLLER_VALUES];
} Ground_Station_Message_t;

typedef struct {
    uint8_t numControllers;
    PID_t PID[NUM_AXES];
} PID_response_t;

typedef struct {
  bool sendGroundStation;
  Ground_Station_Message_t groundStationMessage;

  bool sendPIDResponse;
  PID_response_t PIDResponse;
} Data_To_Ground_t;

#endif /* INC_TELEM_DATATYPES_HPP_ */