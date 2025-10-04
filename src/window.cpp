#include <iostream>
#include "../include/window.hpp"
#include "../include/character.hpp"
#include "../include/map.hpp"
using namespace std;

Window::Window()
{

    // 1. 初始化SDL视频模块
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL初始化失败：" << SDL_GetError() << std::endl;
        return;
    }

    // 2. 初始化字体模块
    if (TTF_Init() != 0) {
        std::cerr << "字体模块初始化失败：" << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // 3. 创建窗口
    window = SDL_CreateWindow(
        "game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        std::cerr << "窗口创建失败：" << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // 4. 创建渲染器
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (renderer == nullptr) {
        std::cerr << "渲染器创建失败：" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // 5. 加载字体
    font = TTF_OpenFont(FONT_PATH.c_str(), FONT_SIZE);
    if (font == nullptr) {
        std::cerr << "字体加载失败：" << TTF_GetError() << std::endl;
        // 备选方案：如果系统字体找不到，尝试加载同目录的simhei.ttf
        font = TTF_OpenFont("simhei.ttf", FONT_SIZE);
        if (font == nullptr) {
            std::cerr << "备选字体加载失败：" << TTF_GetError() << std::endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            return;
        }
    }

}


Window::~Window()
{
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}


// 清空窗口（背景色：浅灰色）
void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);
}

// 绘制矩形
void Window::drawRect(int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}


// 绘制文字
void Window::drawText(const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* textSurf = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    if (!textSurf) {
        cerr << "文字创建失败：" << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);
    if (!textTex) {
        cerr << "文字纹理失败：" << SDL_GetError() << endl;
        SDL_FreeSurface(textSurf);
        return;
    }

    SDL_Rect textRect = {x, y, textSurf->w, textSurf->h};
    SDL_RenderCopy(renderer, textTex, nullptr, &textRect);

    SDL_FreeSurface(textSurf);
    SDL_DestroyTexture(textTex);
}
void Window::drawTextSize(const std::string& text, SDL_Color color, int x, int y, int fontSize) {
    // 1. 临时按指定字号加载字体（复用已有的字体路径）
    TTF_Font* tempFont = TTF_OpenFont(FONT_PATH.c_str(), fontSize);
    if (!tempFont) {
        // 若系统字体加载失败，尝试备选字体
        tempFont = TTF_OpenFont("simhei.ttf", fontSize);
        if (!tempFont) {
            cerr << "临时字体加载失败（字号" << fontSize << "）：" << TTF_GetError() << endl;
            return;
        }
    }

    // 2. 按临时字体生成文字（逻辑和原 drawText 一致）
    SDL_Surface* textSurf = TTF_RenderUTF8_Solid(tempFont, text.c_str(), color);
    if (!textSurf) {
        cerr << "文字创建失败：" << TTF_GetError() << endl;
        TTF_CloseFont(tempFont); // 释放临时字体
        return;
    }

    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);
    if (!textTex) {
        cerr << "文字纹理失败：" << SDL_GetError() << endl;
        SDL_FreeSurface(textSurf);
        TTF_CloseFont(tempFont); // 释放临时字体
        return;
    }

    // 3. 绘制文字
    SDL_Rect textRect = {x, y, textSurf->w, textSurf->h};
    SDL_RenderCopy(renderer, textTex, nullptr, &textRect);

    // 4. 释放资源（注意：必须关闭临时字体）
    SDL_FreeSurface(textSurf);
    SDL_DestroyTexture(textTex);
    TTF_CloseFont(tempFont);
}

// 刷新窗口
void Window::update() {
    SDL_RenderPresent(renderer);
}

void Window::drawMenu() {
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // 浅蓝色背景
    SDL_RenderClear(renderer);

    drawTextSize("select map", {0,0,200,255}, 240, 100,60);
    drawButton("map1", 300, 250, 200, 60);  // 复用按钮绘制逻辑
    drawButton("map2", 300, 350, 200, 60);

    update(); // 直接刷新
}

void Window::drawGame1(map& myMap,character& myCharacter)
{


        clear();
        SDL_Color color;
        // ② 遍历二维数组，逐个绘制格子
        for (int row = 0; row < myMap.getrow(); row++) 
        {  // 遍历行
            for (int col = 0; col < myMap.getcol(); col++) 
            {  // 遍历列
                switch (myMap.getPTs1(row,  col)) 
                {
                    case 0:  
                        color={255,255,255,255};
                        break;
                    case 1:  
                        color={100,100,100,255};

                        break;
                    case 2:  
                        color={150,100,200,255};

                        break;
                    case 3:
                        color={100,255,100,255};
                }
                drawRect(col * 40 , row * 40, 40, 40, color);
            }
        }

        //游戏注释
        string hpText = "HP :  " + to_string(myCharacter.getHP()); 
        drawText(hpText, {255, 0, 0, 255}, 650, 50);


        

        drawRect(612, 155, 30, 30, {255,0,0,255});
        drawText(":character", {255, 0, 0, 255}, 652, 150);
        drawRect(607 , 200, 40, 40, {255,255,255,255});
        drawText(":road", {255, 0, 0, 255}, 652, 200);
        drawRect(607 , 250, 40, 40, {100,100,100,255});
        drawText(":barrier", {255, 0, 0, 255}, 652, 250);
        drawRect(607 , 300, 40, 40, {150,100,200,255});
        drawText(":danger", {255, 0, 0, 255}, 652, 300);
        drawRect(607 , 350, 40, 40, {100,255,100,255});
        drawText(":exit", {255, 0, 0, 255}, 652, 350);
         
        drawButton("play again", 620, 480, 150, 80);




        
        

        myCharacter.setHP(myMap.getPTs1(myCharacter.getpts_x(), myCharacter.getpts_y()));
        myMap.setPTs1(myCharacter.getpts_x(), myCharacter.getpts_y(), 0);
        drawRect(myCharacter.getpts_y()*40+5, myCharacter.getpts_x()*40+5, 30, 30, {255,0,0,255});
        update();
}
void Window::drawGame2(map& myMap,character& myCharacter)
{

        clear();
        SDL_Color color;
        // ② 遍历二维数组，逐个绘制格子
        for (int row = 0; row < myMap.getrow(); row++) 
        {  // 遍历行
            for (int col = 0; col < myMap.getcol(); col++) 
            {  // 遍历列
                switch (myMap.getPTs2(row,  col)) 
                {
                    case 0:  
                        color={255,255,255,255};
                        break;
                    case 1:  
                        color={100,100,100,255};

                        break;
                    case 2:  
                        color={150,100,200,255};

                        break;
                    case 3:
                        color={100,255,100,255};
                }
                drawRect(col * 40 , row * 40, 40, 40, color);
            }
        }
            
        
    
        //游戏注释
        string hpText = "HP :  " + to_string(myCharacter.getHP()); 
        drawText(hpText, {255, 0, 0, 255}, 650, 50);


        

        drawRect(612, 155, 30, 30, {255,0,0,255});
        drawText(":character", {255, 0, 0, 255}, 652, 150);
        drawRect(607 , 200, 40, 40, {255,255,255,255});
        drawText(":road", {255, 0, 0, 255}, 652, 200);
        drawRect(607 , 250, 40, 40, {100,100,100,255});
        drawText(":barrier", {255, 0, 0, 255}, 652, 250);
        drawRect(607 , 300, 40, 40, {150,100,200,255});
        drawText(":danger", {255, 0, 0, 255}, 652, 300);
        drawRect(607 , 350, 40, 40, {100,255,100,255});
        drawText(":exit", {255, 0, 0, 255}, 652, 350);
         
        drawButton("play again", 620, 480, 150, 80);




        
        

        myCharacter.setHP(myMap.getPTs2(myCharacter.getpts_x(), myCharacter.getpts_y()));
        myMap.setPTs2(myCharacter.getpts_x(), myCharacter.getpts_y(), 0);
        drawRect(myCharacter.getpts_y()*40+5, myCharacter.getpts_x()*40+5, 30, 30, {255,0,0,255});
        update();
}
void Window::drawEnd(bool victory)
{
    clear();
    if(victory)drawTextSize("Victory", {255,0,0,255}, 280, 180,60);
    else drawTextSize("Game Over", {255,255,255,255}, 230, 180,60);
    drawButton("play again", 300, 350, 200, 60);
    update();

}
void Window::drawButton(const std::string& text, int x, int y, int w, int h) {
    // 绘制按钮背景
    SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255); // 天蓝色
    SDL_Rect btnRect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &btnRect);

    // 绘制按钮文字
    SDL_Surface* textSurf = TTF_RenderUTF8_Solid(font, text.c_str(), {0,0,0,255});
    if (!textSurf) return;

    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);
    SDL_Rect textRect = {
        x + (w - textSurf->w)/2,
        y + (h - textSurf->h)/2,
        textSurf->w,
        textSurf->h
    };
    SDL_RenderCopy(renderer, textTex, nullptr, &textRect);

    // 释放临时资源
    SDL_FreeSurface(textSurf);
    SDL_DestroyTexture(textTex);
}
