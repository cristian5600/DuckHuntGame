#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    cx =500;
    cy = 500;
    
    float squareSide = 264;
    glm::vec3 corner = glm::vec3( 0,0 , 0);

    Mesh* circle = object2D::CreateCircle("circle", glm::vec3(160, 160, 0), 37,300, glm::vec3(0.41, 0, 0));
    AddMeshToList(circle);
    Mesh* body = object2D::CreateDuckBody("body", glm::vec3(0,0,0), 50, glm::vec3(0.2, 0.34, 0.3434), true);
    AddMeshToList(body);
    Mesh* wings = object2D::CreateDuckWings("wings", glm::vec3(0, 0, 0), 70, glm::vec3(0.41, 0, 0), true);
    AddMeshToList(wings);
    Mesh* beak = object2D::CreateDuckBeak("beak", glm::vec3(0, 0, 0), 70, glm::vec3(0.41, 0.34, 0.4), true);
    AddMeshToList(beak);
    Mesh* bullet = object2D::CreateSquare("bullet", glm::vec3(0, 0, 0), 50,25, glm::vec3(0.77, 0.34, 0.1), true);
    AddMeshToList(bullet);
    Mesh* life = object2D::CreateCircle("life", glm::vec3(25, 25 , 0), 25, 50, glm::vec3(0.11, 0.71, 0.4));
    AddMeshToList(life);

    Mesh* score_outline = object2D::CreateSquare("score_outline", glm::vec3(0, 0, 0), 54,328, glm::vec3(0.77, 0.34, 0.1), false);
    AddMeshToList(score_outline);
    Mesh* score_fill = object2D::CreateSquare("score_fill", glm::vec3(0, 0, 0), 50, 325, glm::vec3(0.1, 0.34, 0.70), true);
    AddMeshToList(score_fill);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    timer += deltaTimeSeconds;
    realSpeed = float(distancePerFrame / deltaTimeSeconds);
    // cout << timer << endl;
    
    /// BULLETS AND LIVES 

    



    if (ROUND_END == true) { // initialization of next round, (and first round)
        //happens when round is over, and another duck has to appear
        //or when round is lost.
        if (SCORE == 10) {
            SpeedControl = 10;
            SCORE = 0;
            LIVES = 3;
        }
        if (LIVES == 0) {
            SpeedControl = 10;
            SCORE = 0;
            LIVES = 3;
        }
       

        OVER_RIGHT = false;
        OVER_LEFT = false;
        BULLETS = 3;
        rotate = float(float(rand() % 314) / 100);
        while(rotate<0.5 || rotate >2.7 || (rotate<AI_MATH_PI/2+0.3 && rotate > AI_MATH_PI/2 - 0.3))
            rotate = float(float(rand() % 314) / 100);
        tx = (rand() % 1280);
        ty = 100;
        panta = abs(tan(rotate));
      

        colisionY = 1;
        if (rotate > float(AI_MATH_PI / 2))
            colisionX = -1;
        else colisionX = 1;
        ROUND_END = false;
        //cout << tx << endl;
        cout << endl << "ROUND END LOOP" << endl;
        SpeedControl += 3;

    }
    if ((hit_x > (tx - 100)) && (hit_x < tx + 100) && (hit_y < ty + 100) && (hit_y > ty - 100) 
        && ANIMATION_ESCAPE != true && ANIMATION_FALL != true) {
        cout << endl << "  HIT !! !! !1  ";
        hit_x = -9999;
        hit_y = -9999;
        ANIMATION_FALL = true;
        BULLETS--;
        SCORE++;
        cout << "SCORE = " << SCORE << endl;

    }
    else if(!((hit_x > (tx - 100)) && (hit_x < tx + 100) && (hit_y < ty + 100) && (hit_y > ty - 100))
        && (hit_x > 0) && (hit_y >0) && ANIMATION_FALL != true && ANIMATION_ESCAPE != true) {

        BULLETS--;
        hit_x = -9999;
        hit_y = -9999;       
        if (BULLETS == 0) {
            ANIMATION_ESCAPE = true;
            LIVES--;
           // BULLETS = 3;
        }
    }
    else {
        hit_x = -9999;
        hit_y = -9999;
    }


    if (ROUND_END == false && ANIMATION_FALL == false && ANIMATION_ESCAPE == false) { // ACTIVE SECTION
        speed = SpeedControl*abs(1/(float(sqrt(1 + panta * panta)* deltaTimeSeconds))); //to have constant speed, independent of start angle
        scale += deltaTimeSeconds * 2.9 * direction;

        if (scale < 0.6) {
            direction = 1;
        }
        if (scale > 1.2) {
            direction = -1;
        }

        distancePerFrame = sqrt(float( deltaTimeSeconds * speed  * deltaTimeSeconds * speed)
            + float(panta *  deltaTimeSeconds * speed * panta *  deltaTimeSeconds * speed));
        tx += colisionX * deltaTimeSeconds * speed; // positive when going RIGHT
        ty += panta*colisionY * deltaTimeSeconds * speed; // positive when going UP
        // speed *= float(1.001);
        // rotate = AI_MATH_PI / 4;//AI_MATH_PI/2;
        if (ty > 720) {
            rotate = -abs(rotate);

            colisionY = -1;


        }
        else if (ty <= 0) { // different cases when colliding with OY going up or down;
            rotate = abs(rotate);
            colisionY = +1;
        }
        if (tx >= 1280) {
            if (OVER_RIGHT == false) {
                if (colisionY < 0)  // different cases when colliding with OY going up or down;
                    rotate = rotate - abs(2 * (3.14 / 2 - abs(rotate)));
                else
                    rotate = rotate + abs(2 * (3.14 / 2 - abs(rotate)));
            }
            colisionX = -1;

            OVER_RIGHT = true;
            OVER_LEFT = false;
        }
        else if (tx <= 0) {
            if (OVER_LEFT == false) {
                if (colisionY > 0)
                    rotate = rotate - abs(2 * (3.14 / 2 - abs(rotate)));
                else
                    rotate = rotate + abs(2 * (3.14 / 2 - abs(rotate)));
            }
            colisionX = +1;
            OVER_RIGHT = false;
            OVER_LEFT = true;
        }
        if (abs(rotate) >= 3.14) {
            rotate = 3.14 - (abs(rotate) - 3.14);
        }
        // cout << " Angle= "<<rotate * 180 / 3.14 << "  ||  TX = " << tx << " || TY = " << ty << "  || speed = " << speed << endl;
        
        modelMatrix = glm::mat3(1);
        modelMatrixWings = glm::mat3(1);

        modelMatrixWings *= transform2D::Translate(tx, ty);
        modelMatrix *= transform2D::Translate(tx, ty);

        modelMatrixWings *= transform2D::Scale(scale, scale);
        modelMatrixWings *= transform2D::Rotate(rotate - AI_MATH_PI / 4);
        modelMatrix *= transform2D::Rotate(rotate - AI_MATH_PI / 4);

        // (3*70,3*70) este pozitia varfului ciocului fata de (0,0) , deci lungimea ratei
        modelMatrix *= transform2D::Translate(-1.5 * 70, -1.5 * 70);
        modelMatrixWings *= transform2D::Translate(-1.5 * 70, -1.5 * 70);
        //cout << endl << " BASIC LOOP" << endl;
    }
    if (ANIMATION_FALL == true ){
        ty += -deltaTimeSeconds*300;

        scale += deltaTimeSeconds * 2.4 * direction;
        if (scale < 0.6) {
            direction = 1;
        }
        if (scale > 1.2) {
            direction = -1;
        }

        rotate = -3.14/2;
        distancePerFrame = sqrt(0+ float(deltaTimeSeconds * 300 * deltaTimeSeconds * 300));
        //cout << " Angle= " << rotate * 180 / 3.14 << "  ||  TX = " << tx << " || TY = " << ty << "  || speed = " << speed << endl;
        if (ty <= 0) {
            ANIMATION_FALL = false;
            ROUND_END = true;
            return;
        }

        modelMatrix = glm::mat3(1);
        modelMatrixWings = glm::mat3(1);

        modelMatrixWings *= transform2D::Translate(tx, ty);
        modelMatrix *= transform2D::Translate(tx, ty);

        modelMatrixWings *= transform2D::Scale(scale, scale);
        modelMatrixWings *= transform2D::Rotate(rotate - AI_MATH_PI / 4);
        modelMatrix *= transform2D::Rotate(rotate - AI_MATH_PI / 4);

        // (3*70,3*70) este pozitia varfului ciocului fata de (0,0) , deci lungimea ratei
        modelMatrix *= transform2D::Translate(-1.5 * 70, -1.5 * 70);
        modelMatrixWings *= transform2D::Translate(-1.5 * 70, -1.5 * 70);
        // cout << endl << " ANIMATION LOOP" << endl;
   }
    if (ANIMATION_ESCAPE == true) {
        ty +=  +deltaTimeSeconds * 500;
        rotate = 3.14 / 2;
        
        scale += deltaTimeSeconds * 2.4 * direction;

        if (scale < 0.6) {
            direction = 1;
        }
        if (scale > 1.2) {
            direction = -1;
        }

        distancePerFrame = sqrt(0 + float(deltaTimeSeconds * 300 * deltaTimeSeconds * 300));
        //cout << " Angle= " << rotate * 180 / 3.14 << "  ||  TX = " << tx << " || TY = " << ty << "  || speed = " << speed << endl;
        if (ty >= 720) {
            ANIMATION_ESCAPE = false;
            ROUND_END = true;
            BULLETS = 3;
            return;
        }

        modelMatrix = glm::mat3(1);
        modelMatrixWings = glm::mat3(1);

        modelMatrixWings *= transform2D::Translate(tx, ty);
        modelMatrix *= transform2D::Translate(tx, ty);

        modelMatrixWings *= transform2D::Scale(scale, scale);
        modelMatrixWings *= transform2D::Rotate(rotate - AI_MATH_PI / 4);
        modelMatrix *= transform2D::Rotate(rotate - AI_MATH_PI / 4);

        // (3*70,3*70) este pozitia varfului ciocului fata de (0,0) , deci lungimea ratei
        modelMatrix *= transform2D::Translate(-1.5 * 70, -1.5 * 70);
        modelMatrixWings *= transform2D::Translate(-1.5 * 70, -1.5 * 70);
        // cout << endl << " ANIMATION LOOP" << endl;
    }
    //IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
   // cout << " Angle= " << rotate * 180 / 3.14 << "  ||  TX = " << tx << " || TY = " << ty << "  || speed = " << realSpeed <<" Pixels/sec"<< endl;
    //modelMatrixWings *= transform2D::Translate(300, 300);

    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["wings"], shaders["VertexColor"], modelMatrixWings);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);


    for (int i = 0; i < BULLETS; i++) {
        modelMatrixBullet = glm::mat3(1);
        modelMatrixBullet *= transform2D::Translate(1100 + 50 * i, 650);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrixBullet);
    }
    for (int j = 0; j < LIVES; j++) {
        modelMatrixBullet = glm::mat3(1);
        modelMatrixBullet *= transform2D::Translate(900 + 55 * j, 650);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixBullet);
    }
    for (int k = 0; k < LIVES; k++) {
       // modelMatrixBullet = glm::mat3(1);
       // modelMatrixBullet *= transform2D::Translate(800 + 55 * j, 650);
       // RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixBullet);
    }
    procent = float(float(SCORE % 11) / 10);
    modelMatrixScore1 = glm::mat3(1);
    modelMatrixScore1 *= transform2D::Translate(900, 550);
    modelMatrixScore1 *= transform2D::Scale(procent, 1);

    modelMatrixScore2 = glm::mat3(1);
   
    modelMatrixScore2 *= transform2D::Translate(899, 548);
    RenderMesh2D(meshes["score_fill"], shaders["VertexColor"], modelMatrixScore1);
    RenderMesh2D(meshes["score_outline"], shaders["VertexColor"], modelMatrixScore2);




    


  
}







void Tema1::FrameEnd()
{
    // DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

    hit_x = 1280 * float(float(mouseX)/ float(window->GetResolution().x));
    hit_y = 720 - 720 * float(float(mouseY) / float(window->GetResolution().y));
    cout << endl << " hit_x = " << hit_x << " || hit_y= " << hit_y;
    cout<< "[ (" << tx - 100 << " , " << tx+100 << " ) , ( "<<ty-100<<" , "<<ty+100<<") ]";
    cout << endl << BULLETS << "  bullets || ";
    cout << "real speed = " << realSpeed<< " Pixels/sec";
    // BULLETS--;
    //cout << mouseX << " " << mouseY << " " << window->GetResolution().x << " X " << window->GetResolution().y;
    //cout<< "  " << hit_x << endl;



    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
