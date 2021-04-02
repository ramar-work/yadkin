#include <SDL.h>
#include <SDL_ttf.h>
#ifdef __ANDROID__
#include <android/log.h>
#endif
#include <sys/stat.h>

#define PROG "screentest"


//Push the SDL quit event...
#define EXIT() \
	return 1

#define fill_pixel(clr, opq) \
	(((clr>>16) & 0xFF)<<16) | (((clr>>8) & 0xFF)<<8) | ((clr>>0) & 0xFF)


#ifdef __ANDROID__
#define DPRINTF(fmt,...) \
	__android_log_print( ANDROID_LOG_DEBUG, PROG, fmt, __VA_ARGS__ );
#endif

#ifndef __ANDROID__
#define DPRINTF(...) \
	fprintf( stderr, __VA_ARGS__ )
#endif
	

//Define common assets globally 
const char image[] = "data/aeon-thumb.bmp"; 
const char fontname[] = "data/DejaVuSans.ttf";
//const char *ipath = SDL_AndroidGetInternalStoragePath();
//const char *epath = SDL_AndroidGetExternalStoragePath();


void fill_surface( SDL_Surface *sf, uint32_t color ) {
	for ( int i=0; i < sf->w * sf->h; i++ ) {
		*((int *)sf->pixels + i ) = fill_pixel( color, 0xff ); 
	}
}


int main ( int argc, char *argv[] ) {
	SDL_Window *w = NULL;
	SDL_Surface *ts, *img, *ws = NULL;
	SDL_Color fgcolor = { 0, 0, 0 };
	TTF_Font *font;
	SDL_RWops *io = NULL; 

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

	//Do this for both iOS and Android
	//Paint the window green....
	fill_surface( ws, 0x00ff00 );
	SDL_UpdateWindowSurface( w );

	//Open the image file
	if ( !( io = SDL_RWFromFile( image, "rb" ) ) ) {
		EXIT();	
	}

	//Read the image file	
	if ( !( img = SDL_LoadBMP_RW( io, 0 ) ) ) {
		EXIT();	
	}

	#if 0
	//Get size of window and image surfaces.
	//Create a rectangle that will center the image ( 
		find the center, calc back 1/2 of image for x & y, and write )
	#endif

	//Copy to the window surface (nowhere special, just the top left)	
	SDL_BlitSurface( img, NULL, ws, NULL );
	SDL_UpdateWindowSurface( w );
	SDL_FreeSurface( img );
	SDL_RWclose( io );

	//Delay, so we can at least see that the image is working
	SDL_Delay( 1000 );

//or is it #if defined(__MACOSX__ || __IPHONEOS__)?
#if defined( __MACOSX__ ) || defined( __IPHONEOS__ )
#endif

	//Turn on TTF library
	if ( TTF_Init() == -1 ) {
		fprintf( stderr, PROG ": TTF_Init() failed %s.\n", TTF_GetError() );
		EXIT();
	}

	//SDL TTF test
	if ( !( font = TTF_OpenFont( fontname, 32 ) ) ) {
		fprintf( stderr, PROG ": TTFOpenFont() failed %s.\n", TTF_GetError() );
		EXIT();
	}

	if ( !( ts = TTF_RenderText_Solid( font, "This is a test.", fgcolor ) ) ) {
		fprintf( stderr, PROG ": TTF_RenderText_Solid() failed %s.\n", TTF_GetError() );
		EXIT();	
	}

	SDL_BlitSurface( ts, NULL, ws, NULL );
	SDL_UpdateWindowSurface( w );
	SDL_FreeSurface( ts );
	SDL_Delay( 1000 );

	//Initialize controls and etc by loading stuff
	for ( int clri = 0, go = 1; go; ) {
		//SDL_TouchFingerEvent tf = {0};
		SDL_Delay( 100 ); // Don't just run with all your heart and soul...
		for ( SDL_Event e; SDL_PollEvent( &e ); ) {
			if ( e.type == SDL_QUIT )
				go = 0;	
			else if ( e.type == SDL_KEYDOWN )
				go = 0;	
			else if ( e.type == SDL_MOUSEBUTTONDOWN /*|| e.type == SDL_FINGERUP*/ ) {
				//Finally, let's track the clicks (and eventually touches)
				char *type, buf[512] = {0};
				int x = 0, y = 0, clrsl;
				int clr[3] = { 0xff0000, 0x0000ff, 0xff00ff };	

				//if ( e.type == SDL_MOUSEBUTTONDOWN ) 
					x = e.button.x, y = e.button.y;
				#if 0
				else {
					type = "finger", x = e.tfinger.x, y = e.tfinger.y;
				}
				#endif
		
				snprintf( buf, sizeof( buf ), "Event received at points (%d, %d)\n", x, y );	
				clrsl = clr[ ( clri > 2 ) ? clri = 0 : clri ];
				fill_surface( ws, clrsl );
			#if 1
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
