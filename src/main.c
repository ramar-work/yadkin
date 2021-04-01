#include <SDL.h>
//#include <SDL/SDL_ttf.h>

#define PROG "screentest"

#define fill_pixel(clr, opq) \
	(((clr>>16) & 0xFF)<<16) | (((clr>>8) & 0xFF)<<8) | ((clr>>0) & 0xFF)


void fill_surface( SDL_Surface *sf, uint32_t color ) {
	for ( int i=0; i < sf->w * sf->h; i++ ) {
		//int *pix = ((int*)sf->pixels) + i;
		//*pix = fillPix(sc, 0xff); 
		*((int *)sf->pixels + i ) = fill_pixel( color, 0xff ); 
	}
}


int main ( int argc, char *argv[] ) {
	SDL_Window *w = NULL;
	SDL_Surface *ws = NULL;

	//Play WAV data with this 
	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 ) {
		fprintf( stderr, PROG ": SDL Init Error %s.\n", SDL_GetError() );
		return 1;
	}

	//Create a window?
	uint32_t flags = SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_MOUSE_CAPTURE;
	if ( !( w = SDL_CreateWindow( PROG, 0, 0, 500, 700, flags ) ) ) {
		fprintf( stderr, PROG ": SDL_CreateWindow failed %s.\n", SDL_GetError() );
		return 1;
	}

	//Create a window
	if ( !( ws = SDL_GetWindowSurface( w ) ) ) {
		fprintf( stderr, PROG ": SDL_LoadBMP failed %s.\n", SDL_GetError() );
		return 1;
	}

	//Paint the window green....
	fill_surface( ws, 0x00ff00 );
	//SDL_UpdateRect( ws );	
	//SDL_BlitSurface( rand_surf, pos_rect, ws, ws_part );
	SDL_UpdateWindowSurface( w );

#if 0
	//Turn on TTF library
	if ( TTF_Init() == -1 ) {
		fprintf( stderr, PROG ": TTF_Init() failed %s.\n", TTF_GetError() );
		return 1;
	}

	//SDL TTF test
	TTF_Font *font;
	font = TTF_OpenFont( "data/DejaVuSans.ttf", 16 );	

	if ( !font ) {
		fprintf( stderr, PROG ": TTFOpenFont() failed %s.\n", TTF_GetError() );
		return 1;
	}

	//
	SDL_Surface *ts;
	SDL_Color fgcolor = { 0, 0, 0 };
	ts = TTF_RenderText_Solid( font, "This is a test.", fgcolor );
	if ( !ts ) {
		fprintf( stderr, PROG ": TTF_RenderText_Solid() failed %s.\n", TTF_GetError() );
		return 1;
	}

	SDL_BlitSurface( ts, NULL, ws, NULL );
	SDL_UpdateWindowSurface( w );
	SDL_FreeSurface( ts );
#endif

	//Initialize controls and etc by loading stuff
	for ( int clri = 0, go = 1; go; ) {
		//SDL_TouchFingerEvent tf = {0};
		SDL_Delay( 100 ); // Don't just run with all your heart and soul...
		for ( SDL_Event e; SDL_PollEvent( &e ); ) {
			if ( e.type == SDL_QUIT )
				go = 0;	
			else if ( e.type == SDL_KEYDOWN )
				go = 0;	
			else if ( e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_FINGERDOWN ) {
				//Finally, let's track the clicks (and eventually touches)
				char *type, buf[512] = {0};
				int x = 0, y = 0, clrsl;
				int clr[3] = { 0xff0000, 0x0000ff, 0xff00ff };	

				if ( e.type == SDL_MOUSEBUTTONDOWN ) 
					type = "mouse", x = e.button.x, y = e.button.y;
				else {
					type = "finger", x = e.tfinger.x, y = e.tfinger.y;
				}
		
			#if 0
				snprintf( buf, sizeof( buf ), 
					"%s event received at points (%d, %d)\n", type, x, y );	
			#endif
				clrsl = clr[ ( clri > 2 ) ? clri = 0 : clri ];
				fill_surface( ws, clrsl );

			#if 0				
				if ( !( ts = TTF_RenderText_Solid( font, buf, fgcolor ) ) ) {
					fprintf( stderr, PROG ": TTF_RenderText_Solid() failed %s.\n", TTF_GetError() );
					return 1;
				}

				SDL_BlitSurface( ts, NULL, ws, NULL );
				SDL_UpdateWindowSurface( w );
				SDL_FreeSurface( ts );
			#endif
				SDL_UpdateWindowSurface( w );
				clri++;
			}
		}
	}

	//Destroy everything
	SDL_DestroyWindow( w );
	SDL_Quit();
	return 0;
}
