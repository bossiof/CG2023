#include "game_main.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "project_setup.hpp"
#include <iostream>

// Handle control logic, be sure to dump needed values in the
// GameModel variables

#define SPEED_EFFECT_DAMPING 2.0f
#define ROTATION_EFFECT_DAMPING 8.0f

// Generic damp function
template <class T>
static inline T damp(T oldVal, T newVal, float lambda, float dt) {
	return
		(oldVal * (float)pow(M_E,-lambda * dt) ) +
		(newVal * (float)(1-pow(M_E, -lambda * dt)));
}

#define DAMP(T, val, lambda)\
	do{\
		static T val##Old = val;\
		val = damp<T>(val##Old, val, lambda, deltaT);\
		val##Old = val;\
	}while(0)

void GameMain::gameLogic(GameModel& game) {

	const float nearPlane = 0.1f;
	const float farPlane = 100.f;

	// Camera target height and distance
	const float camHeight = 0.26;
	const float camDist = 2.2;
	// Camera Pitch limits
	const float minPitch = glm::radians(-90.0f);
	const float maxPitch = glm::radians(90.0f);
	//camera roll limits
		const float minRoll = glm::radians(-90.0f);
	const float maxRoll = glm::radians(90.0f);
	//camera Yaw limits
	const float minYaw = glm::radians(-90.0f);
	const float maxYaw = glm::radians(90.0f);
	// Rotation and motion speed
	const float ROT_SPEED = glm::radians(120.0f);

	// Integration with the timers and the controllers
	// returns:
	// <float deltaT> the time passed since the last frame
	// <glm::vec3 m> the state of the motion axes of the controllers (-1 <= m.x, m.y, m.z <= 1)
	// <glm::vec3 r> the state of the rotation axes of the controllers (-1 <= r.x, r.y, r.z <= 1)
	// <bool fire> if the user has pressed a fire button (not required in this assginment)
	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;
	this->getSixAxis(deltaT, m, r, fire);
	
	game.time += deltaT;

	static float
		MOVE_SPEED = 2;
	static float fixed_FOVy = glm::radians(45.0f);

	static float
		FOVy = glm::radians(45.0f);

	if(fire) {
		MOVE_SPEED = 8;
		if(m.z > 0) {
			FOVy = glm::radians(100.0f);
			r.x *= 0.5; // You are going into the hyperspace, drift with care
			r.y *= 0.5;
		}
	} else {
		MOVE_SPEED = 2;
		FOVy = glm::radians(45.0f);
	}

	// Game Logic implementation
	// Current Player Position - statc variables make sure thattheri value remain unchanged in subsequent calls to the procedure
	static float CamYaw = 0.0f,
		CamPitch = 0.0f,
		CamRoll = 0.0f;

	CamYaw = -ROT_SPEED * deltaT * r.y;
	//CamYaw = glm::clamp(CamYaw,minYaw, maxYaw);
	CamPitch  = -ROT_SPEED * deltaT * r.x;
	//CamPitch = glm::clamp(CamPitch,minPitch, maxPitch);
	CamRoll   = ROT_SPEED * deltaT * r.z;
	//CamRoll = glm::clamp(CamRoll,minRoll, maxRoll);

	//quaternion making to avoid gimball lock on the starhip rotation
	game.character->rotation *=
		  glm::rotate(glm::quat(1,0,0,0), CamPitch, glm::vec3(1,0,0))
		* glm::rotate(glm::quat(1,0,0,0), CamYaw, glm::vec3(0,1,0))
		* glm::rotate(glm::quat(1,0,0,0), CamRoll, glm::vec3(0,0,1));

	glm::mat4 MQ = glm::mat4(game.character->rotation);

	glm::vec3 ux = glm::vec3(MQ * glm::vec4(1,0,0,1));
	glm::vec3 uy = glm::vec3(MQ * glm::vec4(0,1,0,1));
	glm::vec3 uz = glm::vec3(MQ * glm::vec4(0,0,-1,1));

	DAMP(float, MOVE_SPEED, SPEED_EFFECT_DAMPING);
	DAMP(float, FOVy, SPEED_EFFECT_DAMPING);

	//we calculate initial position 
	//we do not use the left and right translation on the starship
	game.character->position += MOVE_SPEED * m.y * uy * deltaT;
	game.character->position += MOVE_SPEED * m.z * uz * deltaT;

	float dist = glm::length(game.character->position);

	if(dist > 40) { game.character->position *= 40.0f / dist; } // Prevent from going outside the map

	glm::vec3 targetPosition = game.character->position;
	//the camera position is based on the target position with two rotations and a translation at a certain distance
	glm::vec3 cameraPosition = targetPosition+ camHeight*uy-camDist*uz;

	DAMP(glm::vec3, cameraPosition, ROTATION_EFFECT_DAMPING);

	game.camera->position = cameraPosition;

	//projection matrix
	glm::mat4 Mprj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	glm::mat4 fixed_Mprj = glm::perspective(fixed_FOVy, Ar, nearPlane, farPlane);

	//view matrix
	glm::mat4 Mv =glm::lookAt(cameraPosition, targetPosition, uy);
	Mprj[1][1] *= -1;
	fixed_Mprj[1][1] *= -1;

	game.ViewPrj =Mprj*Mv;
	game.fixed_ViewPrj =fixed_Mprj*Mv;
	//world matrix
	game.World =  glm::translate(glm::mat4(1.0), game.character->position) * MQ;
}