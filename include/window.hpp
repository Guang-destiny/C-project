#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/character.hpp"
#include "../include/map.hpp"

class Window
{
private:	
   
    SDL_Window* window = nullptr;    
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;        
    const int FONT_SIZE = 24;        
    const std::string FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";  

public :
    Window();
    ~Window();
    void clear();  
    void drawRect(int x, int y, int w, int h, SDL_Color color);  
    void drawText(const std::string& text, SDL_Color color, int x, int y);  
    void update();  
    void drawMenu();
    void drawGame1(map& myMap,character& myCharacter);
    void drawGame2(map& myMap,character& myCharacter);
    void drawEnd(bool victory);
    void drawButton(const std::string& text, int x, int y, int w, int h);
    void drawTextSize(const std::string& text, SDL_Color color, int x, int y, int fontSize);

};

#endif 