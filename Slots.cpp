#include <raylib.h>
#include <iostream>
#include <vector>
using namespace std;

class Button
{
    public:
    Rectangle rec;
    Texture2D texture;
    bool clicked;

    Button();
    bool IsClicked();
    
};

Button::Button()
    {
        ;
    }

bool Button::IsClicked()
    {
        if(GetMouseX()>=rec.x&&GetMouseX()<=rec.x+rec.width&&GetMouseY()>=rec.y&&GetMouseY()<=rec.y+rec.height
        &&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return true;
        return false;
    }


//Animation parameters
int frames = 0;
int animationFrame = 0;
bool StopAnimation = false, StopLever = true;
int AnimationRow=1;
int c1, c2, c3, c4, c5;
int leverFrame=0, flameFrame = 0;

//
Button Buttons[5];
Texture2D Lever;
Texture2D LeverAnimation[12];
Texture2D animation[15];
Texture2D Sprites[8];
Texture2D back;
Texture2D Flames[6];

//Game Logic parameters
string chanceArray[100];
string matrix[3][5];
bool leverPressed = false;
int leverPhase = 0;
int credit = 20;
int money = 3000, lastWin = 0, fakeMoney = 3000;
int tempMoney;
bool first = true;
vector<int> winners;
int lines = 0, linesNEW = 0;

bool LeverClicked()
{
    if(GetMouseX()>=650&&GetMouseX()<=800&&GetMouseY()>=170&&GetMouseY()<=650&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    return true;
    return false;
}

int GetMultiplier(string a, int b)
{
    if(a=="orange"||a=="cherry"||a=="banana")
    {
        if(b==3)return 5;
        if(b==4)return 10;
        if(b==5)return 100;
    }
    if(a=="grape"||a=="pomegranate")
    {
        if(b==3)return 10;
        if(b==4)return 20;
        if(b==5)return 200;
    }
    if(a=="strawberry")
    {
        if(b==3)return 10;
        if(b==4)return 40;
        if(b==5)return 400;
    }
    if(a=="diamond")
    {
        if(b==3)return 40;
        if(b==4)return 400;
        if(b==5)return 1000;
    }
    if(a=="treasure")
    {
        if(b==3)return 200;
        if(b==4)return 800;
        if(b==5)return 20000;
    }
    return 0;
}

void CheckOneLineNEW(string a, string b, string c, string d, string e, int A, int B, int C, int D, int E)
{
    string arr[5];
    arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d; arr[4] = e;

    //Check for treasure and replace it 
    for(int i=0;i<5;i++)
    {
        if(arr[i]=="treasure")
        {
            if(i>0)arr[i]=arr[i-1];
            else 
            {
                int j=i+1;
                while(arr[j]=="treasure")j++;

                string var = arr[j];
                j--;
                while(j>=i)
                {
                    arr[j] = var;
                    j--;
                }
            }
        }
    }

    if(arr[0]==arr[1]&&arr[1]==arr[2]&&arr[2]==arr[3]&&arr[3]==arr[4])
    {
        fakeMoney+=GetMultiplier(arr[0], 5)*credit;
        cout<<arr[0]<<' '<<arr[1]<<' '<<arr[2]<<' '<<arr[3]<<' '<<arr[4]<<' '<<"win: "<<
        GetMultiplier(arr[0], 5)*credit<<" multiplier: "<<GetMultiplier(arr[0], 5)<<" credit: "<<credit<<endl;
        winners.push_back(A);winners.push_back(B);winners.push_back(C);winners.push_back(D);winners.push_back(E);
        lines++;
    }
    else if(arr[0]==arr[1]&&arr[1]==arr[2]&&arr[2]==arr[3])
         {
             fakeMoney+=GetMultiplier(arr[0], 4)*credit;
             cout<<arr[0]<<' '<<arr[1]<<' '<<arr[2]<<' '<<arr[3]<<' '<<arr[4]<<' '<<"win: "<<
            GetMultiplier(arr[0], 4)*credit<<" multiplier: "<<GetMultiplier(arr[0], 4)<<" credit: "<<credit<<endl;
            winners.push_back(A);winners.push_back(B);winners.push_back(C);winners.push_back(D);
            lines++;
         }
         else if(arr[0]==arr[1]&&arr[1]==arr[2])
              {
                  fakeMoney+=GetMultiplier(arr[0], 3)*credit;
                  cout<<arr[0]<<' '<<arr[1]<<' '<<arr[2]<<' '<<arr[3]<<' '<<arr[4]<<' '<<"win: "<<
                GetMultiplier(arr[0], 3)*credit<<" multiplier: "<<GetMultiplier(arr[0], 3)<<" credit: "<<credit<<endl;
               winners.push_back(A);winners.push_back(B);winners.push_back(C);
                lines++;
              }
              
              
}

void CheckAllLinesNEW()
{
    CheckOneLineNEW(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3], matrix[0][4], 0, 1, 2, 3, 4); //1
    CheckOneLineNEW(matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3], matrix[1][4], 10, 11, 12, 13, 14); //2
    CheckOneLineNEW(matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3], matrix[2][4], 20, 21, 22, 23, 24); //3
    CheckOneLineNEW(matrix[0][0], matrix[1][1], matrix[2][2], matrix[1][3], matrix[0][4], 0, 11, 22, 13, 4); //4
    CheckOneLineNEW(matrix[2][0], matrix[1][1], matrix[0][2], matrix[1][3], matrix[2][4], 20, 11, 2, 13, 24); //5
    CheckOneLineNEW(matrix[0][0], matrix[0][1], matrix[1][2], matrix[2][3], matrix[2][4], 0, 1, 12, 23, 24); //6
    CheckOneLineNEW(matrix[2][0], matrix[2][1], matrix[1][2], matrix[0][3], matrix[0][4], 20, 21, 12, 3, 4); //7
    CheckOneLineNEW(matrix[1][0], matrix[2][1], matrix[2][2], matrix[2][3], matrix[1][4], 10, 21, 22, 23, 14); //8
    CheckOneLineNEW(matrix[1][0], matrix[0][1], matrix[0][2], matrix[0][3], matrix[1][4], 10, 1, 2, 3, 14); //9
    CheckOneLineNEW(matrix[0][0], matrix[1][1], matrix[1][2], matrix[1][3], matrix[0][4], 0, 11, 12, 13, 4); //10
    CheckOneLineNEW(matrix[2][0], matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][4], 20, 11, 12, 13, 24); //11
    CheckOneLineNEW(matrix[1][0], matrix[2][1], matrix[1][2], matrix[0][3], matrix[1][4], 10, 21, 12, 3, 14); //12
    CheckOneLineNEW(matrix[1][0], matrix[0][1], matrix[1][2], matrix[2][3], matrix[1][4], 10, 1, 12, 23, 14); //13
    CheckOneLineNEW(matrix[0][0], matrix[1][1], matrix[0][2], matrix[1][3], matrix[0][4], 0, 11, 2, 13, 4); //14
    CheckOneLineNEW(matrix[2][0], matrix[1][1], matrix[2][2], matrix[1][3], matrix[2][4], 20, 11, 22, 13, 24); //15
    CheckOneLineNEW(matrix[1][0], matrix[1][1], matrix[2][2], matrix[1][3], matrix[1][4], 10, 11, 22, 13, 14); //16
    CheckOneLineNEW(matrix[1][0], matrix[1][1], matrix[0][2], matrix[1][3], matrix[1][4], 10, 11, 2, 13, 14); //17
    CheckOneLineNEW(matrix[0][0], matrix[2][1], matrix[0][2], matrix[2][3], matrix[0][4], 0, 21, 2, 23, 4); //18
    CheckOneLineNEW(matrix[2][0], matrix[0][1], matrix[2][2], matrix[0][3], matrix[2][4], 20, 1, 22, 3, 24); //19
    CheckOneLineNEW(matrix[1][0], matrix[0][1], matrix[2][2], matrix[0][3], matrix[1][4], 10, 1, 22, 3, 4); //20
    
}


void CheckOneLine(string a, string b, string c, string d, string e)
{
    string arr[5];
    arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d; arr[4] = e;

    //Check for treasure and replace it 
    for(int i=0;i<5;i++)
    {
        if(arr[i]=="treasure")
        {
            if(i>0)arr[i]=arr[i-1];
            else 
            {
                int j=i+1;
                while(arr[j]=="treasure")j++;

                string var = arr[j];
                j--;
                while(j>=i)
                {
                    arr[j] = var;
                    j--;
                }
            }
        }
    }

    if(arr[0]==arr[1]&&arr[1]==arr[2]&&arr[2]==arr[3]&&arr[3]==arr[4])
    {
        fakeMoney+=GetMultiplier(arr[0], 5)*credit;
        cout<<arr[0]<<' '<<arr[1]<<' '<<arr[2]<<' '<<arr[3]<<' '<<arr[4]<<' '<<"win: "<<
        GetMultiplier(arr[0], 5)*credit<<" multiplier: "<<GetMultiplier(arr[0], 5)<<" credit: "<<credit<<endl;
    }
    else if(arr[0]==arr[1]&&arr[1]==arr[2]&&arr[2]==arr[3])
         {
             fakeMoney+=GetMultiplier(arr[0], 4)*credit;
             cout<<arr[0]<<' '<<arr[1]<<' '<<arr[2]<<' '<<arr[3]<<' '<<arr[4]<<' '<<"win: "<<
            GetMultiplier(arr[0], 4)*credit<<" multiplier: "<<GetMultiplier(arr[0], 4)<<" credit: "<<credit<<endl;
         }
         else if(arr[0]==arr[1]&&arr[1]==arr[2])
              {
                  fakeMoney+=GetMultiplier(arr[0], 3)*credit;
                  cout<<arr[0]<<' '<<arr[1]<<' '<<arr[2]<<' '<<arr[3]<<' '<<arr[4]<<' '<<"win: "<<
                GetMultiplier(arr[0], 3)*credit<<" multiplier: "<<GetMultiplier(arr[0], 3)<<" credit: "<<credit<<endl;
              }
              
              
}

void CheckAllLines()
{
    CheckOneLine(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3], matrix[0][4]); //1
    CheckOneLine(matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3], matrix[1][4]); //2
    CheckOneLine(matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3], matrix[2][4]); //3
    CheckOneLine(matrix[0][0], matrix[1][1], matrix[2][2], matrix[1][3], matrix[0][4]); //4
    CheckOneLine(matrix[2][0], matrix[1][1], matrix[0][2], matrix[1][3], matrix[2][4]); //5
    CheckOneLine(matrix[0][0], matrix[0][1], matrix[1][2], matrix[2][3], matrix[2][4]); //6
    CheckOneLine(matrix[2][0], matrix[2][1], matrix[1][2], matrix[0][3], matrix[0][4]); //7
    CheckOneLine(matrix[1][0], matrix[2][1], matrix[2][2], matrix[2][3], matrix[1][4]); //8
    CheckOneLine(matrix[1][0], matrix[0][1], matrix[0][2], matrix[0][3], matrix[1][4]); //9
    CheckOneLine(matrix[0][0], matrix[1][1], matrix[1][2], matrix[1][3], matrix[0][4]); //10
    CheckOneLine(matrix[2][0], matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][4]); //11
    CheckOneLine(matrix[1][0], matrix[2][1], matrix[1][2], matrix[0][3], matrix[1][4]); //12
    CheckOneLine(matrix[1][0], matrix[0][1], matrix[1][2], matrix[2][3], matrix[1][4]); //13
    CheckOneLine(matrix[0][0], matrix[1][1], matrix[0][2], matrix[1][3], matrix[0][4]); //14
    CheckOneLine(matrix[2][0], matrix[1][1], matrix[2][2], matrix[1][3], matrix[2][4]); //15
    CheckOneLine(matrix[1][0], matrix[1][1], matrix[2][2], matrix[1][3], matrix[1][4]); //16
    CheckOneLine(matrix[1][0], matrix[1][1], matrix[0][2], matrix[1][3], matrix[1][4]); //17
    CheckOneLine(matrix[0][0], matrix[2][1], matrix[0][2], matrix[2][3], matrix[0][4]); //18
    CheckOneLine(matrix[2][0], matrix[0][1], matrix[2][2], matrix[0][3], matrix[2][4]); //19
    CheckOneLine(matrix[1][0], matrix[0][1], matrix[2][2], matrix[0][3], matrix[1][4]); //20
    
}

int SpriteValue(string sprite)
{
    if(sprite=="cherry")return 0;
    if(sprite=="orange")return 1;
    if(sprite=="banana")return 2;
    if(sprite=="grape")return 3;
    if(sprite=="pomegranate")return 4;
    if(sprite=="diamond")return 5;
    if(sprite=="treasure")return 6;
    if(sprite=="strawberry")return 7;
    return -1;
}

void DrawMatrixRow(int num) //Risuva kolonite na matricata
{
    switch(num)
    {
        case 0:
        {
            DrawTexture(Sprites[SpriteValue(matrix[0][0])], 5, 170, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[1][0])], 5, 295, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[2][0])], 5, 420, WHITE);
            break;
        }
        case 1:
        {
            DrawTexture(Sprites[SpriteValue(matrix[0][1])], 135, 170, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[1][1])], 135, 295, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[2][1])], 135, 420, WHITE);
            break;
        }
        case 2:
        {
            DrawTexture(Sprites[SpriteValue(matrix[0][2])], 265, 170, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[1][2])], 265, 295, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[2][2])], 265, 420, WHITE);
            break;
        }
        case 3:
        {
            DrawTexture(Sprites[SpriteValue(matrix[0][3])], 395, 170, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[1][3])], 395, 295, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[2][3])], 395, 420, WHITE);
            break;
        }
        case 4:
        {
            DrawTexture(Sprites[SpriteValue(matrix[0][4])], 525, 170, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[1][4])], 525, 295, WHITE);
            DrawTexture(Sprites[SpriteValue(matrix[2][4])], 525, 420, WHITE);
            break;
        }
        
    }
}

int AddAnimationFrame(int x)
{
    int ans;
    ans = animationFrame+x;
    if(ans>14)ans-=14;
    return ans;
}

void PlayAnimation()
{
       
        if(frames==60)frames=0;
        
        //Poleta na mashinata        
        if(animationFrame==14)animationFrame=0;
        else animationFrame++;
        
        DrawRectangle(0, 170 ,645 ,390 , WHITE);
        if(AnimationRow>5)
        for(int i=0;i<winners.size();i++)
        DrawRectangle((winners[i]%10)*130, (winners[i]/10)*130+170, 130 , 130, GREEN);

            if(first)
        {
            for(int i=0;i<3;i++)
            for(int j=0;j<5;j++)
            matrix[i][j] = "diamond";
            first = false;
        }
          else{  
            if(AnimationRow<2)c1 = AddAnimationFrame(2);
            if(AnimationRow<3)c2 = AddAnimationFrame(8);
            if(AnimationRow<4)c3 = AddAnimationFrame(4);
            if(AnimationRow<5)c4 = AddAnimationFrame(10);
            if(AnimationRow<6)c5 = AddAnimationFrame(6);

            if(AnimationRow<2)DrawTexture(animation[c1], 5, 170, WHITE);
            if(AnimationRow<3)DrawTexture(animation[c2], 135, 170, WHITE);
            if(AnimationRow<4)DrawTexture(animation[c3], 265, 170, WHITE);
            if(AnimationRow<5)DrawTexture(animation[c4], 395, 170, WHITE);
            if(AnimationRow<6)DrawTexture(animation[c5], 525, 170, WHITE);

            if(AnimationRow>1)DrawMatrixRow(0);
            if(AnimationRow>2)DrawMatrixRow(1);
            if(AnimationRow>3)DrawMatrixRow(2);
            if(AnimationRow>4)DrawMatrixRow(3);
            if(AnimationRow>5)
            {
            
                linesNEW = lines;
            DrawMatrixRow(4); 
            leverPressed = false; leverPhase=0; 
            if(fakeMoney - money!=0)
                {
                lastWin = fakeMoney - money;
               
                }
            money=fakeMoney;
    
            }
            
            if(frames%25==0)AnimationRow++;
            if(frames%2==0&&!StopLever)leverFrame++;
            if(leverFrame==12){leverFrame = 0;StopLever = true;}
          }
           
        //Butoni sus sumi
        int x = 27, y = 575;
        for(int i =0;i<5;i++)
        {
            DrawTexture(Buttons[i].texture,x, y, WHITE);
            if(Buttons[i].clicked)DrawRectangleLinesEx(Buttons[i].rec, 5, DARKGREEN);
            x+= 130;
        }

        DrawTexture(LeverAnimation[leverFrame], 650, 240, WHITE);
        DrawTexture(back, 0, 165, WHITE);

        DrawText(TextFormat("Money: %d", money), 15, 20, 30, BLACK);
        DrawText(TextFormat("Last Win: %d", lastWin), 15, 130, 30, BLACK);
        if(linesNEW>0)DrawText(TextFormat("Lines: %d", linesNEW), 415, 130, 30, BLACK);
}

void GenerateMatrix()       //Generates new matrix
{
    int i, j;
    for(i=0;i<3;i++)
    for(j=0;j<5;j++)
    {
        matrix[i][j] = chanceArray[GetRandomValue(0, 99)];
    }
}

void Input()
{
    frames++;
    
    //Check for clicked multiplier button
    for(int i=0;i<5;i++)
    {
        if(Buttons[i].IsClicked())
        {
            for(int j=0;j<5;j++)
            Buttons[j].clicked = false;
            Buttons[i].clicked = true;\
            if(i==0)credit = 20;
            if(i==1)credit = 40;
            if(i==2)credit = 100;
            if(i==3)credit = 200;
            if(i==4)credit = 400;
        }
    }

    if((IsKeyPressed(KEY_SPACE)||LeverClicked())&&!leverPressed&&money!=0&&money>=credit)
    {
        winners.clear();
        lines = 0;
        leverPhase++;
        
       
            leverPressed = true;
            money-=credit;
            fakeMoney-=credit;
            tempMoney=money;
            if(GetRandomValue(1, 10)<9)
                {
                   do
                   {
                      fakeMoney = money;
                      GenerateMatrix();
                      CheckAllLines();  
                   }
                   while(fakeMoney!=money);   
                }
            else {
                    GenerateMatrix();
                    CheckAllLinesNEW();
                 }
            
        AnimationRow = 1;
        
        if(StopLever) StopLever = false;
    }
}

void Output()
{
    
    BeginDrawing();   
    ClearBackground(PINK);
    PlayAnimation();
    EndDrawing();

}


int main()
{
    InitWindow(800, 650, "Beta 0.3");
    SetTargetFPS(60);
   
    back = LoadTexture("sprites/back.png");
    for(int i=0;i<15;i++)
    {
        animation[i] = LoadTexture(TextFormat("anime/%d.png", i+1));
    }

    Sprites[0] = LoadTexture("sprites/cherry.png");
    Sprites[1] = LoadTexture("sprites/orange.png");
    Sprites[2] = LoadTexture("sprites/banana.png");
    Sprites[3] = LoadTexture("sprites/grape.png");
    Sprites[4] = LoadTexture("sprites/pomegranate.png");
    Sprites[5] = LoadTexture("sprites/diamond.png");
    Sprites[6] = LoadTexture("sprites/treasure.png");
    Sprites[7] = LoadTexture("sprites/strawberry.png");

    //Initialise Buttons
    int x = 27, y = 575;
    for(int i =0;i<5;i++)
    {
       Buttons[i].rec.x = x;
       Buttons[i].rec.y = y;
       Buttons[i].rec.width = 80;
       Buttons[i].rec.height = 50;
       x+= 130;
       Buttons[i].clicked = false;
    }
    Buttons[0].clicked = true;

    Buttons[0].texture = LoadTexture("sprites/20.png");
    Buttons[1].texture = LoadTexture("sprites/40.png");
    Buttons[2].texture = LoadTexture("sprites/100.png");
    Buttons[3].texture = LoadTexture("sprites/200.png");
    Buttons[4].texture = LoadTexture("sprites/400.png");

    Lever = LoadTexture("sprites/lever.png");
    for(int i=0;i<12;i++)
    LeverAnimation[i] = LoadTexture(TextFormat("anime/lever%d.png", i+4));

    
    //Declare ChanceArray
    for(int i=0;i<100;i++)
    {
        if(i>=0&&i<20)chanceArray[i] = "cherry";       //20% //17
        if(i>=20&&i<40)chanceArray[i] = "orange";      //20% //17
        if(i>=40&&i<60)chanceArray[i] = "banana";      //20% //17
        if(i>=60&&i<72)chanceArray[i] = "grape";       //12% //17
        if(i>=72&&i<84)chanceArray[i] = "pomegranate"; //12% //17
        if(i>=84&&i<92)chanceArray[i] = "strawberry";  //8%  //8
        if(i>=92&&i<97)chanceArray[i] = "diamond";     //5%  //5
        if(i>=97&&i<=99)chanceArray[i] = "treasure";   //3%  //2

    }

    while(!WindowShouldClose())
        {
            Input();
            Output();
        }
        CloseWindow();

}
