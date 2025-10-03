#include <iostream>
#include "../include/map.hpp"
#include "../include/character.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/window.hpp"
using namespace std;


enum class GameState{
    Menu,Game
};

int main() {

    int a=0;
	map myMap;
	character myCharacter;
    Window window;
    
    bool is_running = true;  // 控制循环的开关（true=继续运行，false=退出）
    SDL_Event event;         // 存储SDL事件（如鼠标点击、窗口关闭）
    cout<<"人物坐标为("<<myCharacter.getpts_x()<<","<<myCharacter.getpts_y()<<endl;

    myMap.MapUpdate(myCharacter.getpts_x(),myCharacter.getpts_y());
    while (is_running) 
    {
        
        // 遍历所有待处理的事件（如“点击窗口关闭按钮”会产生SDL_QUIT事件）
        while (SDL_PollEvent(&event)) 
        {
            // 判断事件类型：如果是“窗口关闭”事件
            if (event.type == SDL_QUIT) 
            {
                is_running = false;  // 设为false，退出循环
                std::cout << "收到窗口关闭指令，准备退出..." << std::endl;
            }
       
            if (event.type == SDL_KEYDOWN) 
            {   // 有按键被按下
                // event.key.keysym.sym 表示具体哪个键
                switch (event.key.keysym.sym) 
                {
                    case SDLK_w:  // W键
                        cout << "W键被按下" << endl;
                        myCharacter.setPosition('w');
                        
                        break;
                    case SDLK_s:  // S键
                        cout << "S键被按下" << endl;
                        myCharacter.setPosition('s');
                        break;
                    case SDLK_a:  // A键
                        cout << "A键被按下" << endl;
                        myCharacter.setPosition('a');
                        break;
                    case SDLK_d:  // D键
                        cout << "D键被按下" << endl;
                        myCharacter.setPosition('d');
                        break;
                    case SDLK_ESCAPE:  // ESC键
                        cout << "ESC键被按下（可用于暂停游戏）" << endl;
                        break;
                }
            } 
        }
        
        window.clearWindow();

        // ② 遍历二维数组，逐个绘制格子
        for (int row = 0; row < 10; row++) 
        {  // 遍历行
            for (int col = 0; col < 15; col++) 
            {  // 遍历列
                // 计算当前格子在屏幕上的位置
                SDL_Rect grid_rect = {
                    col * 40+10,  // X坐标 = 列索引 * 格子大小
                    row * 50+10,  // Y坐标 = 行索引 * 格子大小
                    40,        // 宽度 = 格子大小
                    50         // 高度 = 格子大小
                };

                // 根据数组元素值设置颜色
                
                switch (myMap.getPin(row,  col)) 
                {
                    case 0:  // 空地 → 白色
                        
                        window.drawRect(col * 40+10, row * 50+10, 40, 50, {255,255,255,255});

                        break;
                    case 1:  // 墙壁 → 灰色
                        window.drawRect(col * 40+10, row * 50+10, 40, 50, {100,100,100,255});

                        break;
                    case 2:  
                        window.drawRect(col * 40+10, row * 50+10, 40, 50, {255,0,255,255});

                        break;
                }

             
            }
        }
        a++;

        if(a>=200)
        {
            cout<<"人物坐标为("<<myCharacter.getpts_x()<<","<<myCharacter.getpts_y()<<endl;
            cout<<myMap.getPin(myCharacter.getpts_x(), myCharacter.getpts_y())<<endl;
            a=0;
        }
        myMap.MapUpdate(myCharacter.getpts_x(),myCharacter.getpts_y());
        window.Windowupdate();
        SDL_Delay(10);
    }
    

    cout << "资源已释放，程序正常退出！" << std::endl;


	return 0;
	
}
