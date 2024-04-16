#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

SDL_Surface* Screen;
TTF_Font* font;
bool quit = false;

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		printf("SDL Succesfully initialized\n");
    Screen = SDL_SetVideoMode(240, 240,16, SDL_HWSURFACE );
		if(Screen)
		{
      printf("Succesfully Set %dx%dx16\n",240,240);
      SDL_ShowCursor(SDL_DISABLE);
			if (TTF_Init() == 0)
			{
        printf("Succesfully initialized TTF\n");
				font = TTF_OpenFont("./fs/font.ttf",50);
				if (font)
				{            
						printf("Succesfully Loaded fonts\n");
						TTF_SetFontStyle(font,TTF_STYLE_NORMAL);
						while (!quit)
						{
              SDL_Event event;
              while (SDL_PollEvent(&event)) { 
                if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN ))
                {
                  quit = true;
                }
              }
              SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format,0,0,0));
              FILE *fp;
              char temp[1024];
              
              fp = popen("printf \"(%d*0.1)-144.7\" $(i2cget -y -f 0 0x34 0x5E w|awk '{print \"0x\"substr($0,5,2)substr($0,4,1)}')|bc", "r");
              if (fp == NULL) {
                printf("Failed to run command\n" );
                quit = true;
              }
              
              if (fgets(temp, sizeof(temp), fp) != NULL)
              {
                SDL_Color color={255,255,255,255};
                SDL_Surface *TextSurface;
                if(!(TextSurface=TTF_RenderText_Solid(font,temp, color))) 
                {
                  printf("Failed to render text\n" );
                } 
                else 
                {
                  SDL_Rect rect;
                  rect.x = (240-TextSurface->w) / 2;
                  rect.y = (240-TextSurface->h) / 2;
                  rect.w = TextSurface->w;
                  rect.h = TextSurface->h;
                  SDL_BlitSurface(TextSurface,NULL,Screen,&rect);
                  //perhaps we can reuse it, but I assume not for simplicity.
                  SDL_FreeSurface(TextSurface);
                  SDL_Flip(Screen);
                }
              }
              
              pclose(fp);
              
              SDL_Delay(1000);
						}
						TTF_CloseFont(font);
						font=NULL;
				}
				else
				{
					printf("Failed to Load fonts\n");
				}
				TTF_Quit();
				}
			else
			{
				printf("Failed to initialize TTF\n");
			}
      SDL_FreeSurface(Screen);
      Screen=NULL;
		}
		else
		{
			printf("Failed to Set Videomode %dx%dx16\n",240, 240);
		}

		SDL_Quit();
	}
	else
	{
		printf("Couldn't initialise SDL!\n");
	}
	return 0;
}
