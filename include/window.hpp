#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
class Window
{
private:	
        // 私有成员：窗口模块内部使用，外部不可直接访问（封装性）
    SDL_Window* window = nullptr;    // 窗口指针
    SDL_Renderer* renderer = nullptr;// 渲染器指针
    TTF_Font* font = nullptr;        // 字体（绘制文字用）
    bool initSuccess = false;        // 初始化是否成功
    const int FONT_SIZE = 24;        // 字体大小（固定）
    const std::string FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";  // Linux系统字体路径

public :
    Window();
    ~Window();
    void clearWindow();  // 清空窗口（每次绘制前调用）
    void drawRect(int x, int y, int w, int h, SDL_Color color);  // 绘制矩形（墙、陷阱、按钮）
    void drawText(const std::string& text, SDL_Color color, int x, int y);  // 绘制文字（生命值、菜单）
    void Windowupdate();  // 刷新窗口（将绘制的内容显示到屏幕）

};

#endif 