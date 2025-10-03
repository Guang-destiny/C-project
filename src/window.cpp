#include <iostream>
#include "../include/window.hpp"
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

    // 所有初始化成功
    initSuccess = true;
}


Window::~Window()
{

        // 释放顺序：先释放内部资源，再释放外部资源
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();





}


// 清空窗口（背景色：浅灰色）
void Window::clearWindow() {
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
    // 1. 文字转表面
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    if (textSurface == nullptr) {
        std::cerr << "文字表面创建失败：" << TTF_GetError() << std::endl;
        return;
    }

    // 2. 表面转纹理
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "文字纹理创建失败：" << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    // 3. 绘制文字
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // 4. 释放资源
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// 刷新窗口
void Window::Windowupdate() {
    SDL_RenderPresent(renderer);
}