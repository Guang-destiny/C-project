#include <iostream>
#include "../include/map.hpp"
#include "../include/character.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/window.hpp"
using namespace std;



enum class GameState{
    Menu,Game1,Game2,End
};


int main() {
    int a=0;
	map myMap,mapRST;
	character myCharacter;
    Window window;

    //使用状态机，设置初始状态
    GameState currestate=GameState::Menu;

    bool is_running = true;  
    SDL_Event event;         

    //判断是否胜利
    bool victory=false;

   
    while (is_running) 
    {
        switch(currestate)
        {
            case GameState::Menu:
                window.drawMenu();
                while(SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT) 
                    {
                        is_running = false;  
                        cout << "收到窗口关闭指令，准备退出..." << endl;
                    }
                    //状态变换，移动至下一状态
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
                    {
                        if((event.button.x >= 300) && (event.button.x <= 300 + 200) && (event.button.y >= 250) && (event.button.y <= 250 + 60))
                            currestate=GameState::Game1;
                        else if((event.button.x >= 300) && (event.button.x <= 300 + 200) && (event.button.y >= 350) && (event.button.y <= 350 + 60))
                            currestate=GameState::Game2;
                    }
                }
                break;
            case GameState::Game1:
                window.drawGame1(myMap,myCharacter);
                while (SDL_PollEvent(&event)) 
                {
                    if (event.type == SDL_QUIT) 
                    {
                        is_running = false; 
                        cout << "收到窗口关闭指令，准备退出..." << std::endl;
                    }
                
                    if (event.type == SDL_KEYDOWN) 
                    {   
                        switch (event.key.keysym.sym) 
                        {
                            case SDLK_w:  // W键
                                myCharacter.setPTs1('w');
                                break;
                            case SDLK_s:  // S键
                                myCharacter.setPTs1('s');
                                break;
                            case SDLK_a:  // A键
                                myCharacter.setPTs1('a');
                                break;
                            case SDLK_d:  // D键
                                myCharacter.setPTs1('d');
                                break;
                            case SDLK_ESCAPE:  // ESC键
                                cout << "ESC键被按下" << endl;
                                break;
                        }
                    } 
                    //返回主菜单
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
                    {
                        if((event.button.x >= 620) && (event.button.x <= 620 + 150) && (event.button.y >= 480) && (event.button.y <= 480 + 80));
                        {    
                            currestate=GameState::Menu;
                            myMap=mapRST;
                            myCharacter.RST();
                        }
                    }
                } 
                //胜利结算
                if(myMap.getPTs1(myCharacter.getpts_x(), myCharacter.getpts_y())==3)
                {
                    currestate=GameState::End;
                    victory=true;
                }
                //失败结算
                else if(myCharacter.getHP()<=0)
                {
                    currestate=GameState::End;
                    victory=false;
                }
                break;


            case GameState::Game2:
                window.drawGame2(myMap,myCharacter);
                while (SDL_PollEvent(&event)) 
                {
                    
                    if (event.type == SDL_QUIT) 
                    {
                        is_running = false;  
                        cout << "收到窗口关闭指令，准备退出..." << std::endl;
                    }
                
                    if (event.type == SDL_KEYDOWN) 
                    {   // 有按键被按下
                        
                        switch (event.key.keysym.sym) 
                        {
                            case SDLK_w:  // W键
                                myCharacter.setPTs2('w');
                                break;
                            case SDLK_s:  // S键
                                myCharacter.setPTs2('s');
                                break;
                            case SDLK_a:  // A键
                                myCharacter.setPTs2('a');
                                break;
                            case SDLK_d:  // D键
                                myCharacter.setPTs2('d');
                                break;
                            case SDLK_ESCAPE:  // ESC键
                                cout << "ESC键被按下" << endl;
                                break;
                        }
                    } 
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
                    {
                

                        if((event.button.x >= 620) && (event.button.x <= 620 + 150) && (event.button.y >= 480) && (event.button.y <= 480 + 80));
                        {    
                            currestate=GameState::Menu;
                            myMap=mapRST;
                            myCharacter.RST();
                        }
                    }
                } 
                if(myMap.getPTs2(myCharacter.getpts_x(), myCharacter.getpts_y())==3)
                {
                    currestate=GameState::End;
                    victory=true;
                }
                else if(myCharacter.getHP()<=0)
                {
                    currestate=GameState::End;
                    victory=false;
                }
                
                break;
            case GameState::End:
                window.drawEnd(victory);
                while(SDL_PollEvent(&event))
                {
                    
                    if (event.type == SDL_QUIT) 
                    {
                        is_running = false;  
                        cout << "收到窗口关闭指令，准备退出..." << endl;
                    }
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
                    {
                        //重置地图人物状态
                        if((event.button.x >= 300) && (event.button.x <= 300 + 200) && (event.button.y >= 350) && (event.button.y <= 350 + 60))
                        {    
                            currestate=GameState::Menu;
                            myMap=mapRST;
                            myCharacter.RST();
                        }
                    }
                }
            break;
        }
        window.update();
        SDL_Delay(10);
    }
	return 0;
	
}
