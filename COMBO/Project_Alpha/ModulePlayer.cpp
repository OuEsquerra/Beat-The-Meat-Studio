#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayerII.h"
#include <stdio.h>
#include <iostream>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA


using namespace std;


ModulePlayer::ModulePlayer()
{
	graphicsP1 = NULL;
	currentP1_animation = NULL;



	score = 0;

	healthP1.x = 100;
	healthP1.y = 400;
	healthP1.w = 200;
	healthP1.h = 20;

	{ //BASIC MOVEMENTS ANIMATIONS

		//Idle animation (arcade sprite sheet)
		idleP1.PushBack({ 28, 27, 105, 100 });
		idleP1.PushBack({ 133, 27, 100, 100 });
		idleP1.PushBack({ 233, 27, 100, 100 });
		idleP1.speed = 0.08f;

		//Walk FORWARD Animation
		forwardP1.PushBack({ 699, 127, 97, 84 });
		forwardP1.PushBack({ 232, 127, 90, 84 });
		forwardP1.PushBack({ 322, 127, 100, 84 });
		forwardP1.PushBack({ 422, 127, 100, 84 });
		forwardP1.PushBack({ 522, 127, 88, 84 });
		forwardP1.PushBack({ 609, 127, 90, 84 });
		forwardP1.PushBack({ 132, 127, 100, 84 });
		forwardP1.PushBack({ 29, 127, 105, 84 });
		forwardP1.loop = true;
		forwardP1.speed = 0.1f;

		//Walk backwards animation
		backwardP1.PushBack({ 694, 211, 101, 101 });
		backwardP1.PushBack({ 609, 211, 85, 101 });
		backwardP1.PushBack({ 522, 211, 87, 101 });
		backwardP1.PushBack({ 232, 211, 91, 101 });
		backwardP1.PushBack({ 322, 211, 105, 101 });
		backwardP1.PushBack({ 427, 211, 95, 101 });
		backwardP1.PushBack({ 132, 211, 100, 101 });
		backwardP1.PushBack({ 29, 211, 104, 101 });
		backwardP1.loop = true;
		backwardP1.speed = 0.1f;

		//Crouch Animation
		crouchP1.PushBack({ 427, 323, 99, 94 });
		crouchP1.PushBack({ 526, 323, 89, 94 });
		crouchP1.PushBack({ 615, 323, 93, 94 });
		crouchP1.speed = 0.5f;
		crouchP1.loop = false;

		//Neutral Jump Animation
		NjumpP1.PushBack({ 28, 525, 97, 128 });
		NjumpP1.PushBack({ 125, 525, 85, 128 });
		NjumpP1.PushBack({ 210, 525, 83, 128 });
		NjumpP1.PushBack({ 293, 525, 86, 128 });
		NjumpP1.PushBack({ 210, 525, 83, 128 });
		NjumpP1.PushBack({ 125, 525, 85, 128 });
		NjumpP1.PushBack({ 28, 525, 97, 128 });
		NjumpP1.speed = 0.1f;
		NjumpP1.loop = false;

		//Forward Jump Animation
		FjumpP1.PushBack({ 28, 525, 97, 128 });
		FjumpP1.PushBack({ 125, 525, 85, 128 });
		FjumpP1.PushBack({ 210, 525, 83, 128 });
		FjumpP1.PushBack({ 293, 525, 86, 128 });
		FjumpP1.PushBack({ 379, 525, 90, 128 });
		FjumpP1.PushBack({ 469, 525, 98, 128 });
		FjumpP1.PushBack({ 567, 525, 119, 128 });
		FjumpP1.PushBack({ 686, 525, 96, 128 });
		FjumpP1.PushBack({ 379, 525, 90, 128 });
		FjumpP1.PushBack({ 293, 525, 86, 128 });
		FjumpP1.speed = 0.17f;
		FjumpP1.loop = false;

		//Backward Jump Animation
		BjumpP1.PushBack({ 28, 525, 97, 128 });
		BjumpP1.PushBack({ 125, 525, 85, 128 });
		BjumpP1.PushBack({ 210, 525, 83, 128 });
		BjumpP1.PushBack({ 293, 525, 86, 128 });
		BjumpP1.PushBack({ 210, 525, 83, 128 });
		BjumpP1.PushBack({ 125, 525, 85, 128 });
		BjumpP1.PushBack({ 28, 525, 97, 128 });
		BjumpP1.speed = 0.17f;
		BjumpP1.loop = false;

		//Standing Turn Animation
		SturnP1.PushBack({ 36, 418, 89, 105 });
		SturnP1.PushBack({ 125, 418, 103, 105 });
		SturnP1.PushBack({ 228, 418, 97, 105 });

		//Crouch Turn Animation
		CturnP1.PushBack({ 622, 451, 82, 71 });
		CturnP1.PushBack({ 516, 451, 106, 71 });
		CturnP1.PushBack({ 428, 451, 88, 71 });

		//Standing Block Animation
		SblockP1.PushBack({ 730, 2169, 100, 96 });
		SblockP1.PushBack({ 630, 2169, 100, 96 });
		
		//Crouch Block Animation
		CblockP1.PushBack({ 730, 2100, 100, 63 });
		CblockP1.PushBack({ 630, 2100, 100, 63 });

	    //Standing Damage 
		SdamageP1.PushBack({});

		//Standing Damage Low Attack
		SdamagelowP1.PushBack({});

		//Crouch Damage
		CdamageP1.PushBack({});

		//Electric Thunder Damage
		ETdamgeP1.PushBack({});

		//Recovery
		RecoveryP1.PushBack({});

	}

	{ //ATTACKS ANIMATIONS
		
	  //Standing LP
	  SLFP_P1.PushBack({28, 658, 104, 105});
	  SLFP_P1.PushBack({132, 658, 143, 105});
	  SLFP_P1.PushBack({275, 658, 123, 105});
	  SLFP_P1.speed = 0.2f;	
	  SLFP_P1.loop = false;

	  //Crouch LP
	  CLP_P1.PushBack({610, 709, 109, 56 });
	  CLP_P1.PushBack({727, 715, 154, 50 });
	  CLP_P1.PushBack({890, 713, 142, 52 });
	  CLP_P1.speed = 0.2f;
	  CLP_P1.loop = false;

	  //Jumping LP
	  JLP_P1.PushBack({});

	  //Standing MP
	  //Crouch MP
	  //Jump MP

	  //Standing HP
	  //Crouch HP
	  //Jump HP

	  //Electric Thunder 
	  Ethunder_P1.PushBack({});

	  //Rolling Attack
	  RollingP1.PushBack({});

	}


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	graphicsP1 = App->textures->Load("Sprites/BlankaP1.png"); // JA TE LA FOTO BONA
	currentstateP1 = idlestateP1;
	//Player 2 stest collider
	playerP1_collider = App->collision->AddCollider({ positionP1.x , positionP1.y - 100, 60, 93 }, COLLIDER_PLAYER, App->player);
	attackP1_collider = nullptr;
	return true;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphicsP1);
	return true;
}


update_status ModulePlayer::PreUpdate() {
	
	time = SDL_GetTicks() / 20;
	
	

	
	//MOVE BACKWARD
	//inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
	//MOVE FORWARD
	//inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	//CROUCH
	//inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
	//JUMP
//	inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 
	// SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	/* inputplayerP1.right_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.up_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;*/
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN;
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_B][GAME_PAD_1] == KEY_DOWN;
     App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_1] == KEY_DOWN;
	 inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_LEFT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	 inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 inputplayerP1.U_active = App->input->keyboard[SDL_SCANCODE_U] == KEY_DOWN;
	 inputplayerP1.X_active = App->input->keyboard[SDL_SCANCODE_X] == KEY_DOWN;
	 inputplayerP1.C_active = App->input->keyboard[SDL_SCANCODE_C] == KEY_DOWN;
	 inputplayerP1.V_active = App->input->keyboard[SDL_SCANCODE_V] == KEY_DOWN;
	 inputplayerP1.Z_active = App->input->keyboard[SDL_SCANCODE_Z] == KEY_DOWN;
	 {

		 //COMBOS COMBINACIO

		  //Z,X,C,V

		 char InputCombo[5];
		 char ComboArray1[] = "zxcv";
		 bool combostart = 0;

		 

		// for (int p=0,c=0; p <= 4; ++p) {

		//	 if (InputCombo[p] == ComboArray[p]) {
		//		 LOG("COMPARED");
		//		 ++c;
		//	 }
		//	
		//			 
		//	 

		//	 if (c = 5) {
		//		// currentstateP1 = NjumpstateP1;
		//		 LOG("COMBO ACTIVE");
		//	 }
		//}

		 

		 /*bool comboactive1 = 0;
		 bool comboactive2 = 0;
		 bool comboactive3 = 0;
		 bool comboactive4 = 0;*/

		  //BASIC MOVEMENTS

		   //IDLE STATE
		 if (currentstateP1 == idlestateP1) {
			  
			 if (inputplayerP1.Z_active) {
				 combostart = 1;

				 InputCombo[0] = 'z';
			 }
			 if (inputplayerP1.X_active) {

				 InputCombo[1] = 'x';

			 }
			 if (inputplayerP1.C_active) {

				 InputCombo[2] = 'c';
			 }

			 if (inputplayerP1.V_active) {

				 InputCombo[2] = 'v';

			 }

			 if (strcmp(InputCombo, ComboArray1) == 0) {
				 if (combostart == 1) {
					 currentstateP1 = NjumpstateP1;
				 }
			 }
			
				 if (inputplayerP1.A_active) {
					 currentstateP1 = backwardstateP1;
					 blockP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x + 50 ,positionP1.y - 80 - App->render->camera.y * 2, 10, 30 }, COLLIDER_PLAYER_BLOCK, App->player);
					 LOG("IDLE TO BACK");
				 }
				 if (inputplayerP1.D_active) {
					 currentstateP1 = forwardstateP1;
					 LOG("IDLE TO forward");
				 }
				 if (inputplayerP1.S_active) {
					 currentstateP1 = crouchstateP1;
					 LOG("IDLE to CROUCH");
				 }
				 if (inputplayerP1.W_active) {
					 jumping = true;
					 currentstateP1 = NjumpstateP1;
					 jumpstart = time;
					 jumpTimer = 0;
					 LOG("IDLE to CROUCH");
				 }
				 if (inputplayerP1.U_active) {
					 currentstateP1 = standingfarLP;
					 LOG("IDLE to LP");
				 }
	     }
		
		 
			 if (currentstateP1 == backwardstateP1) {
				 if (!inputplayerP1.A_active) {
					 currentstateP1 = idlestateP1;
					 blockP1_collider->to_delete = true;
					 LOG("BACK to IDLE");
				 }
				 if (inputplayerP1.S_active) {
					 currentstateP1 = crouchstateP1;
					 blockP1_collider->to_delete = true;
					 LOG("BACK to CROUCH");
				 }
				 if (inputplayerP1.W_active) {
					 jumping = true;
					 currentstateP1 = BjumpstateP1;
					 jumpstart = time;
					 jumpTimer = 0;
					 LOG("IDLE to CROUCH");
				 }
				 if (inputplayerP1.U_active) {
					 currentstateP1 = standingfarLP;
					 LOG("BACK to LP");
				 }
			 }
			 //FORWARD STATE
			 if (currentstateP1 == forwardstateP1) {
				 if (!inputplayerP1.D_active) {
					 currentstateP1 = idlestateP1;
					 LOG("FOR to IDLE");
				 }
				 if (inputplayerP1.A_active) {
					 currentstateP1 = backwardstateP1;
					 blockP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x + 55, positionP1.y - 80 - App->render->camera.y * 2, 7, 30 }, COLLIDER_PLAYER_BLOCK, App->player);
					 LOG("FOR to BACK");
				 }

				 if (inputplayerP1.S_active) {
					 currentstateP1 = crouchstateP1;
					 LOG("FOR to CROUCH");
				 }
				 if (inputplayerP1.W_active) {
					 jumping = true;
					 currentstateP1 = FjumpstateP1;
					 jumpstart = time;
					 jumpTimer = 0;
					 LOG("FOR to CROUCH");
				 }
				 if (inputplayerP1.U_active) {
					 currentstateP1 = standingfarLP;
					 LOG("FOR to LP");
				 }
			 }
			 //COUCH STATE
			 if (currentstateP1 == crouchstateP1) {
				 if (!inputplayerP1.S_active) {
					 crouchP1.Reset();
					 currentstateP1 = idlestateP1;
					 LOG("CROUCH to IDLE");
				 }

				 if (inputplayerP1.U_active) {
					 currentstateP1 = crouchLP;
					 LOG("CROUCH to LP");
				 }
			 }
			 //JUMP STATE
			 if (jumping = true) {

				 if (positionP1.y >= groundLevel + 10) {
					 positionP1.y = groundLevel;
					 currentstateP1 = idlestateP1;
					 NjumpP1.Reset();
					 FjumpP1.Reset();
					 BjumpP1.Reset();
					 jumping = false;
					 jumpTimer = 0;

				 }

			 }



			 //ATTACKS
			 //STANDING FAR LP
			 if (currentstateP1 == standingfarLP) {
				 if (currentP1_animation->Finished() && !inputplayerP1.U_active) {
					 currentstateP1 = idlestateP1;
					 alreadyHit = false;
					 SLFP_P1.Reset();
					 LOG("LP to IDLE");
				 }
			 }
			 //CROUCH LP
			 if (currentstateP1 == crouchLP) {
				 if (currentP1_animation->Finished() && !inputplayerP1.U_active && inputplayerP1.S_active) {
					 currentstateP1 = crouchstateP1;
					 alreadyHit = false;
					 CLP_P1.Reset();
					 LOG("LP to CROUCH");
				 }
				 if (currentP1_animation->Finished() && !inputplayerP1.U_active && !inputplayerP1.S_active) {
					 currentstateP1 = idlestateP1;
					 alreadyHit = false;
					 CLP_P1.Reset();
					 LOG("LP to CROUCH");
				 }
			 }

			 return UPDATE_CONTINUE;
		 }
	 }

update_status ModulePlayer::Update() {
	
	switch (currentstateP1)
	{


	case idlestateP1:
		playerP1_collider->rect.h = 93;
		currentP1_animation = &idleP1;
		//LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP1:
		playerP1_collider->rect.h = 93;
		blockP1_collider->SetPos(positionP1.x + 55 - App->render->camera.x  *2, positionP1.y -80 - App->render->camera.y * 2);
		currentP1_animation = &backwardP1;
		positionP1.x -= speed;
		LOG("BACK ANIMATION ACTIVE");
		break;

	case forwardstateP1:
		
		currentP1_animation = &forwardP1;
		positionP1.x += speed;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP1:
		currentP1_animation = &crouchP1;
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - App->render->camera.x *2  , positionP1.y - 68 - App->render->camera.y * 2);
		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case NjumpstateP1:
		currentP1_animation = &NjumpP1;
		positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;

	case FjumpstateP1:
		currentP1_animation = &FjumpP1;
		positionP1.x += speed;
		positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" FORWARD JUMP ANIMATION ACTIVE");
		break;

	case BjumpstateP1:
		currentP1_animation = &BjumpP1;
		positionP1.x -= speed;
		positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" BACKWARD JUMP ANIMATION ACTIVE");
		break;

	case standingfarLP:
		currentP1_animation = &SLFP_P1;
		LOG("LP ANIMATION ACTIVE");
		break;

	case crouchLP:
		currentP1_animation = &CLP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	}

	if ( currentstateP1 != crouchstateP1) {
		playerP1_collider->SetPos(positionP1.x  - App->render->camera.x *2  , positionP1.y - 93 - App->render->camera.y * 2);
	}

	SDL_Rect r = currentP1_animation->GetCurrentFrame();
	//SHADOW
	shadowP1 = {796,27,100,20};
	
	if (jumping) {

		jumpTimer = time - jumpstart;

		playerP1_collider->SetPos(positionP1.x - App->render->camera.x * 2, positionP1.y - 68 - App->render->camera.y * 2);

	}


	if (playerP1_collider->rect.x < App->player2->playerP2_collider->rect.x ) {
		App->render->Blit(graphicsP1, positionP1.x - 10, groundLevel-15, &shadowP1, 1.0f, true,SDL_FLIP_NONE);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE);
	}
	else {
		App->render->Blit(graphicsP1, positionP1.x - 10, groundLevel -15, &shadowP1, 1.0f, true, SDL_FLIP_HORIZONTAL);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_HORIZONTAL);
	}

	if (positionP1.x <= (App->render->camera.x - 10))
	{
		positionP1.x = (App->render->camera.x - 10);
	}
	if (positionP1.x >= (App->render->camera.x) + SCREEN_WIDTH)
	{
		positionP1.x = (App->render->camera.x) +SCREEN_WIDTH;
	}






	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	/*if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_PLAYER2 && inputplayerP1.D_active) {

		speed = 0;
	}
	else
	{
		speed = 3;
	}*/

}