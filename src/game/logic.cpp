#include "game_main.hpp"

void GameMain::gameLogic(GameModel& game) {
// The procedure must implement the game logic  to move the character in third person.
	// Input:
	// <Assignment07 *A> Pointer to the current assignment code. Required to read the input from the user
	// <float Ar> Aspect ratio of the current window (for the Projection Matrix)
	// Output:
	// <glm::mat4 &ViewPrj> the view-projection matrix of the camera
	// <glm::mat4 &World> the world matrix of the object
	// Parameters
	// Camera FOV-y, Near Plane and Far Plane
	const float FOVy = glm::radians(45.0f);
	const float nearPlane = 0.1f;
	const float farPlane = 100.f;
	
	// Player starting point
	const glm::vec3 StartingPosition = glm::vec3(-41.50, 0.0, -19.5);
	
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
	const float MOVE_SPEED = 2.0f;

   	if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

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

	// Game Logic implementation
	// Current Player Position - statc variables make sure thattheri value remain unchanged in subsequent calls to the procedure
	game.character->position = StartingPosition;
	static float CamYaw = 0.0f,
	CamPitch = 0.0f,
	CamRoll = 0.0f;

	CamYaw = CamYaw - ROT_SPEED * deltaT * r.y;
	//CamYaw = glm::clamp(CamYaw,minYaw, maxYaw);
	CamPitch  = CamPitch  - ROT_SPEED * deltaT * r.x;
	//CamPitch = glm::clamp(CamPitch,minPitch, maxPitch);
	CamRoll   = CamRoll   - ROT_SPEED * deltaT * r.z;
	//CamRoll = glm::clamp(CamRoll,minRoll, maxRoll);

	//quaternion making to avoid gimball lock on the starhip rotation
	game.character->rotation = glm::quat(glm::vec3(0, CamYaw, 0)) *
		glm::quat(glm::vec3(-CamPitch, 0, 0)) *
		glm::quat(glm::vec3(0, 0, CamRoll));
	glm::mat4 MQ = glm::mat4(game.character->rotation);

	glm::vec3 ux = glm::vec3(MQ*glm::vec4(1,0,0,1));
	glm::vec3 uy = glm::vec3(MQ*glm::vec4(0,1,0,1));
	glm::vec3 uz = glm::vec3(MQ*glm::vec4(0,0,-1,1));


	//we calculate initial position 
	//we do not use the left and right translation on the starship
	game.character->position += MOVE_SPEED * m.y * uy * deltaT;
	game.character->position += MOVE_SPEED * m.z *uz* deltaT;

	glm::vec3 targetPosition = game.character->position;
	//the camera position is based on the target position with two rotations and a translation at a certain distance
	glm::vec3 cameraPosition = targetPosition+ camHeight*uy-camDist*uz;

	glm::vec3 euler = glm::eulerAngles(game.character->rotation);
	// To be done in the assignment
	glm::mat4 camera_shift= glm::mat4(1);
	//projection matrix
	glm::mat4 Mprj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	//view matrix
	glm::mat4 Mv =glm::lookAt(cameraPosition, targetPosition, uy);
	Mprj[1][1] *= -1;
	game.ViewPrj = Mprj*Mv;
	//world matrix
	game.World = glm::translate(glm::mat4(1.0), game.character->position) * MQ;
}