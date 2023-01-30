#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        glm::mat3 modelMatrixBullet;
        glm::mat3 modelMatrixScore1;
        glm::mat3 modelMatrixScore2;
        glm::mat3 modelMatrixWings;
        

        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
       
        float tx = 0;
        float ty = 0;
        float tx2 = 0;
        float ty2 = 0;
        float tx3 = 600;
        float ty3 = 250;
        float  rotate = 3.14/6;
        float scale = 1;
        float panta= 1;
        float realSpeed=0;
        float distancePerFrame = 0;
        float SpeedControl = 10;
       

        int cont = 0;
        int direction = 1;
        int colisionX = 1;
        int colisionY = 1;
        float speed = 10000;
        float SIN = 1;
        float COS = 1;
        

        bool OVER_RIGHT = false; // BECAUSE OF VARIABILE deltaTimeSecond, causing 2 frames to be out of screen !!!!!!!!!!!!!!!!!!!
        bool OVER_LEFT = false; // BECAUSE OF VARIABILE deltaTimeSecond, causing 2 frames to be out of screen !!!!!!!!!!!!!!!!!!!

        bool ROUND_END = true;
        bool ANIMATION_FALL = false;
        bool ANIMATION_ESCAPE = false;

        float hit_x = -9999;
        float hit_y = -9999;
        float timer = 0;

        int SCORE = 0;
        int BULLETS = 3;
        int LIVES = 3;
        float escape = 0;
        float procent;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
