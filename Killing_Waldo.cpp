#include "raylib.h"
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int width = 1000;
int height = 1000;

int num_of_pedestrians = 5;
int frames_until_change_waldo = 0;

vector<float> ped_dx;
vector<float> ped_dy;
vector<int> frames_until_change_peds;

float waldo_dx = 0;
float waldo_dy = 0;

void random_vel(float &dx, float &dy, int speed = 2){
  float angle = GetRandomValue(0,360)*PI/180.0f;
  dx = cos(angle)*speed;
  dy = sin(angle)*speed;
}

void init(int n){

  ped_dx.resize(n);
  ped_dy.resize(n);
  frames_until_change_peds.resize(n);
  
for(int i = 0; i < n; i++){
  if(ped_dx[i] == 0 && ped_dy[i] == 0){
    random_vel(ped_dx[i],ped_dy[i],1 + GetRandomValue(1,4));
  }

  if(frames_until_change_peds[i] <= 0){
    frames_until_change_peds[i] = GetRandomValue(30,120);
  }
 }
 
}

struct Randomize{
  float waldo_x;
  float waldo_y;

  vector<float> ped_x;
  vector<float> ped_y;

  Randomize(int n = 0){
    waldo_x = GetRandomValue(0,width);
    waldo_y = GetRandomValue(0,height);

    ped_x.resize(n);
    ped_y.resize(n);
    
  for(int i = 0; i < n; i++){
    ped_x[i] = (float)GetRandomValue(0,width);
    ped_y[i] = (float)GetRandomValue(0,height); 
  }
  }

void update_size(int n){
  int old = (int)ped_x.size();
  if(n <= old){
    return;
  }
  ped_x.resize(n);
  ped_y.resize(n);

  for(int i = old; i < n; i++){
    ped_x[i] = (float)GetRandomValue(0,width);
    ped_y[i] = (float)GetRandomValue(0,height); 
  }
}
};

void init_peds(int n){
  ped_dx.resize(n);
  ped_dy.resize(n);
  frames_until_change_peds.resize(n);

  for(int i = 0; i < n; i++){
    if(ped_dx[i] == 0 && ped_dy[i] == 0){
      ped_dx[i] = (float)GetRandomValue(-2,2);
      ped_dy[i] = (float)GetRandomValue(-2,2);
    }

    if(frames_until_change_peds[i] <= 0){
      frames_until_change_peds[i] = GetRandomValue(30,120);
    }
  }
}

void update_players(Randomize &pos, int waldo_w, int waldo_h, int ped_w, int ped_h){
  
  if(frames_until_change_waldo <= 0){
    int roll = GetRandomValue(1,4);

    if(waldo_dx >= 10){
      waldo_dx = 0;
    }

    if(waldo_dy >= 10){
      waldo_dy = 0;
    }
    
    if(roll == 1){
    waldo_dx += 2;
    waldo_dy += 2;
    }

    else if(roll == 2){
    waldo_dx -= 2;
    waldo_dy += 2;
    }

    else if(roll == 3){
    waldo_dx += 2;
    waldo_dy -= 2;
    }

    else if(roll == 4){
    waldo_dx -= 2;
    waldo_dy -= 2;
    }
    }
    
    frames_until_change_waldo = GetRandomValue(30,60);

  pos.waldo_x += waldo_dx;
  pos.waldo_y += waldo_dy;

  if(pos.waldo_x <= 0 || pos.waldo_x > width - waldo_w){
    waldo_dx *= -1;
  }

  if(pos.waldo_y <= 0 || pos.waldo_y > height - waldo_h){
    waldo_dy *= -1;
  }

  frames_until_change_waldo--;

  for(int i = 0; i < num_of_pedestrians; i++){
    if(ped_dx[i] >= 10){
      ped_dx[i] = 0;
    }

    if(ped_dy[i] >= 10){
      ped_dy[i] = 0;
    }
    
    if(frames_until_change_peds[i] <= 0){
      random_vel(ped_dx[i],ped_dy[i],1 + GetRandomValue(0,4));
      frames_until_change_peds[i] = GetRandomValue(30,180);
    }
      pos.ped_x[i] += ped_dx[i];
      pos.ped_y[i] += ped_dy[i];

      if(pos.ped_x[i] <= 0){
	pos.ped_x[i] = 0;
	ped_dx[i] *= -1;
  }

      if(pos.ped_x[i] > width - ped_w){
	pos.ped_x[i] = width - ped_w;
	ped_dx[i] *= -1;
      }
      
    if(pos.ped_y[i] <= 0){
	pos.ped_y[i] = 0;
	ped_dy[i] *= -1;
  }

      if(pos.ped_y[i] > height - ped_h){
	pos.ped_y[i] = height - ped_h;
	ped_dy[i] *= -1;
      }
      
      frames_until_change_peds[i]--;
      }
}

int main(){
  
  InitWindow(width,height,"Killing Waldo");
  InitAudioDevice();

  Sound shoot = LoadSound("Gun_shot.mp3");
  Sound hit = LoadSound("hit.mp3");
  
  SetTargetFPS(60);

  Image crosshair = LoadImage("Crosshair.png");
  Texture2D Crosshair = LoadTextureFromImage(crosshair);
  UnloadImage(crosshair);

  Image pedestrian = LoadImage("Pedestrian.png");
  Texture2D Pedestrian = LoadTextureFromImage(pedestrian);
  UnloadImage(pedestrian);

  Image waldo = LoadImage("Waldo.png");
  Texture2D Waldo = LoadTextureFromImage(waldo);
  UnloadImage(waldo);

  int hits = 0;
  int casualties = 0;
  int shots = 0;
  
  int waldo_w = Waldo.width;
  int waldo_h = Waldo.height;
  int ped_h = Pedestrian.height;
  int ped_w = Pedestrian.width;
  
  Randomize pos(num_of_pedestrians);

  init_peds(num_of_pedestrians);
  random_vel(waldo_dx, waldo_dy, 2);
  
  while(!WindowShouldClose()){
    update_players(pos,waldo_w,waldo_h,ped_w,ped_h);
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("Hits: %i", hits), 20, 0, 25, RED);
    DrawText(TextFormat("Shots: %i", shots), 450, 0, 25, RED);
    DrawText(TextFormat("Casualties: %i", casualties), 800, 0, 25, RED);
			
    Rectangle crosshair = {0.0f,0.0f,(float)Crosshair.width,(float)Crosshair.height};
    Rectangle crosshair_scaled = {GetMousePosition().x,GetMousePosition().y,(float)Crosshair.width,(float)Crosshair.height};
    Vector2 point = {(float)Crosshair.width/2.0,(float)Crosshair.height/2.0};
    DrawTexturePro(Crosshair, crosshair,crosshair_scaled,point, 0.0f, WHITE);
    
    DrawTexture(Waldo, pos.waldo_x, pos.waldo_y,WHITE);

    for(int i = 0; i < num_of_pedestrians; i++){
      DrawTexture(Pedestrian,pos.ped_x[i],pos.ped_y[i],WHITE);
    }
    
    EndDrawing();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      shots++;
      PlaySound(shoot);
      Vector2 mouse_pos;
      mouse_pos = GetMousePosition();

      if(mouse_pos.x >= pos.waldo_x && mouse_pos.x <= pos.waldo_x + waldo_w && mouse_pos.y >= pos.waldo_y && mouse_pos.y <= pos.waldo_y + waldo_h){
	hits++;
	PlaySound(hit);
	int old_size = num_of_pedestrians;
	num_of_pedestrians += 5;
	init(num_of_pedestrians);
	pos.update_size(num_of_pedestrians);
	ped_dx.resize(num_of_pedestrians);
	ped_dy.resize(num_of_pedestrians);
	frames_until_change_peds.resize(num_of_pedestrians);

	pos.waldo_x = GetRandomValue(0,width);
	pos.waldo_y = GetRandomValue(0,height);
	
	for(int i = old_size; i < num_of_pedestrians; i++){
	  random_vel(ped_dx[i], ped_dy[i], 1 + GetRandomValue(1,4));
	  frames_until_change_peds[i] = GetRandomValue(30,120);
	}
      }

      for(int i = 0; i < num_of_pedestrians; i++){
      if(mouse_pos.x >= pos.ped_x[i] && mouse_pos.x <= pos.ped_x[i] + ped_w && mouse_pos.y >= pos.ped_y[i] && mouse_pos.y <= pos.ped_y[i] + ped_h){
	casualties++;
	PlaySound(hit);
	int old_size = num_of_pedestrians;
	num_of_pedestrians += 2;
	init(num_of_pedestrians);
	pos.update_size(num_of_pedestrians);
	ped_dx.resize(num_of_pedestrians);
	ped_dy.resize(num_of_pedestrians);
	frames_until_change_peds.resize(num_of_pedestrians);

	for(int i = old_size; i < num_of_pedestrians; i++){
	  random_vel(ped_dx[i], ped_dy[i], 1 + GetRandomValue(1,4));
	  frames_until_change_peds[i] = GetRandomValue(30,120);
	}
      }
    }
    }
  }

  CloseWindow();
  return 0;
}
