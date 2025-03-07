/* ----------------------------------------------------------------
 * yadkin.c
 * ========
 * 
 * Summary
 * =======
 * A command-line tool for quickly generating Android app templates or
 * libraries.
 *
 * LICENSE
 * -------
 * Copyright 2021-2025 Antonio R. Collins II (ramar@ramar.work)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.

 * ---------------------------------------------------------------- */
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include "zrender.h"
#include "ztable.h"

#if 0
#include "zjson.h"
#include <sqlite3.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "lua.h"
#endif

#define HELP(...) \
	fprintf( stderr, "%s", "yadkin: " ) && \
	fprintf( stderr, __VA_ARGS__ ) && \
	fprintf( stderr, "\n" )

//  TODO: This should be under share/, but it just depends on where the libs are.  Might want to put this in a config file.
#define ANDROID_TEMPLATE_DIR "resources/required/android"

#define OPTIONSMSG \
	"-c, --create <PATH>     Create an app at \\$PATH.\n" \
	"-i, --identifier <ARG>  Specify an company identifier (e.g. com.$ID).\n" \
	"-f, --file <ARG>        Specify a file defining the structure of the app.\n" \
	"-n, --name <ARG>        Specify a proper name for the app.\n" \
	"-g, --generate <ARG>    Generate an app template.\n" \
	"-v, --verbose           Be verbose.\n"


struct app {
	const char *appname;
	const char *propername;
	const char *identifier;	
};


struct file { 
	const char *filename;
	const mode_t mode;
};


struct symfile {
	const char *name, *spath, *dpath;
};


struct options {
	int create;
	char *createArg;
	int generate;
	char *appname;
	char *storename;
	int verbose;
	char *id;
	char *file;
	int androidBuild;
	int iosBuild;
}; 


const char *strings[] = {
	"appname"
,	"app_proper_name"
, "identifier"
,	"dependencies"
};


struct options opt = {
	.create = 0
,	.createArg = NULL 
,	.generate = 0 
,	.appname = "my_app" 
,	.storename = "My App" 
,	.verbose = 0 
,	.id = "example" //  TODO: Use config.h.in to fix this
,	.file = "share/example.lua"
, .androidBuild = 1
, .iosBuild = 1
};


struct file android_dirs[] = {
 	{ "app", 0755 }
, { "app/libs", 0755 }
, { "app/src", 0755 }
, { "app/src/androidTest", 0755 }
, { "app/src/main", 0755 }
, { "app/src/main/java", 0755 }
, { "app/src/main/java/com", 0755 }
, { "app/src/main/kotlin", 0755 }
, { "app/src/main/kotlin/com", 0755 }
, { "$app/src/main/java/com", 0755 }
, { "@app/src/main/java/com", 0755 }
, { "$app/src/main/kotlin/com", 0755 }
, { "@app/src/main/kotlin/com", 0755 }
#if 0
, { "Fapp/src/main/java/com/-/-/fragments", 0755 }
#endif
, { "app/src/main/res", 0755 }
, { "app/src/main/res/drawable", 0755 }
, { "app/src/main/res/drawable-v24", 0755 }
, { "app/src/main/res/font", 0755 }
, { "app/src/main/res/layout", 0755 }
, { "app/src/main/res/mipmap-anydpi-v26", 0755 }
, { "app/src/main/res/mipmap-hdpi", 0755 }
, { "app/src/main/res/mipmap-mdpi", 0755 }
, { "app/src/main/res/mipmap-xhdpi", 0755 }
, { "app/src/main/res/mipmap-xxhdpi", 0755 }
, { "app/src/main/res/mipmap-xxxhdpi", 0755 }
, { "app/src/main/res/values", 0755 }
//, { "app/src/main/res/values-night", 0755 }
, { "app/src/test", 0755 }
, { "app/src/test/java", 0755 }
, { "app/src/test/java/com", 0755 }
, { "$app/src/test/java/com", 0755 }
, { "@app/src/test/java/com", 0755 }
, { "app/src/test/kotlin", 0755 }
, { "app/src/test/kotlin/com", 0755 }
, { "$app/src/test/kotlin/com", 0755 }
, { "@app/src/test/kotlin/com", 0755 }
, { "gradle", 0755 }
, { "gradle/wrapper", 0755 }
,	{ NULL, -1 }
};


struct file android_files[] = {
  { "$build.gradle", 0644 }
, { "$gradle.properties", 0644 }
, { "$gradlew", 0755 }
, { "$gradlew.bat", 0644 }
, { "settings.gradle", 0644 }
, { "$gradle/wrapper/gradle-wrapper.jar", 0644 }
, { "$gradle/wrapper/gradle-wrapper.properties", 0644 }
, { "app/build.gradle", 0644 }
, { "$app/proguard-rules.pro", 0644 }
, { "app/src/main/AndroidManifest.xml", 0644 }
, { "$app/src/main/res/drawable/ic_launcher_background.xml", 0644 }
, { "$app/src/main/res/drawable-v24/ic_launcher_foreground.xml", 0644 }
, { "$app/src/main/res/layout/activity_main.xml", 0644 }
, { "$app/src/main/res/mipmap-anydpi-v26/ic_launcher.xml", 0644 }
, { "$app/src/main/res/mipmap-anydpi-v26/ic_launcher_round.xml", 0644 }
, { "$app/src/main/res/mipmap-hdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-hdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-mdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-mdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-xhdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-xhdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-xxhdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-xxhdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-xxxhdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-xxxhdpi/ic_launcher_round.webp", 0644 }
	// ???
, { "$app/src/main/res/values/colors.xml", 0644 }
, { "app/src/main/res/values/strings.xml", 0644 }
, { "app/src/main/res/values/themes.xml", 0644 }
	// ???
	//, { "app/src/main/res/values-night/themes.xml", 0644 }
, { "@app/src/main/java/#/#/#/MainActivity.java", 0644 }
	//, { "@app/src/main/kotlin/#/#/#/MainActivity.kt", 0644 }
,	{ NULL, -1 }
};


struct symfile np_android[] = {
 	{ "Generic", "classes", "app/src/main/java/com" }
, { "Login", "classes", "app/src/main/java/com" }
,	{ NULL }
};



/// Read in the contents of a file
unsigned char *read_file ( const char *filename, int *len, char *err, int errlen ) {
	// Check for and load whatever file
	int fd, fstat, bytesRead, fileSize;
	unsigned char *buf = NULL;
	struct stat sb;
	memset( &sb, 0, sizeof( struct stat ) );

	// Check for the file 
	if ( ( fstat = stat( filename, &sb ) ) == -1 ) {
		// fprintf( stderr, "FILE STAT ERROR: %s\n", strerror( errno ) );
		snprintf( err, errlen, "Stat error on %s: %s\n", filename, strerror( errno ) );
		return NULL;	
	}

	// Check for the file 
	if ( ( fd = open( filename, O_RDONLY ) ) == -1 ) {
		snprintf( err, errlen, "File open error on %s: %s\n", filename, strerror( errno ) );
		return NULL;	
	}

	// Allocate a buffer
	fileSize = sb.st_size + 1;
	if ( !( buf = malloc( fileSize ) ) || !memset( buf, 0, fileSize ) ) {
		snprintf( err, errlen, "allocation error: %s, %s\n", filename, strerror( errno ) );
		close( fd );
		return NULL;	
	}

	// Read the entire file into memory, b/c we'll probably have space 
	if ( ( bytesRead = read( fd, buf, sb.st_size ) ) == -1 ) {
		snprintf( err, errlen, "read error: %s, %s\n", filename, strerror( errno ) );
		free( buf );
		close( fd );
		return NULL;	
	}

	// This should have happened before...
	if ( close( fd ) == -1 ) {
		snprintf( err, errlen, "Could not close file %s: %s\n", filename, strerror( errno ) );
		free( buf );
		return NULL;	
	}

	*len = sb.st_size;
	return buf;
}



/// Copy raw files :)
int raw_copy( const char *src, const char *dest, char *err, int esize, mode_t mode ) {
	// ...
	unsigned char *data = NULL;
	int dlen = 0, fd = 0, w = 0;

	// Read the file in
	if ( !( data = read_file( src, &dlen, err, esize ) ) ) {
		return 0;
	}
	
	// Open the destination
	if ( ( fd = open( dest, O_RDWR | O_CREAT, mode ) ) == -1 ) {
		snprintf( err, esize, "Failed to open %s: %s", dest, strerror( errno ) ); 
		return 0;
	}
	
	// Write it
	if ( ( w = write( fd, data, dlen ) ) == -1 || w < dlen ) {
		snprintf( err, esize, "Failed to write to %s: %s", dest, strerror( errno ) ); 
		return 0;
	}

	// Free the data and close the destination
	free( data ), close( fd );
	return 1;
}



/// Loads a file (src), and writes it to destination with replacements
int render_file ( const char *src, const char *dest, void *zd, char *err, int esize, mode_t mode ) {
	// TODO: This is awfully wordy... there's a better way...
	int fd, size = 0, written = 0, dlen = 0;
	unsigned char *content = NULL, *dd = NULL;

	// Read in the contents
	if ( !( content = read_file( src, &size, err, esize ) ) ) {
		// HELP( "Failed to read file - %s: %s", src, err );
		return 0;
	} 

	// Open a file
	if ( ( fd = open( dest, O_RDWR | O_CREAT, mode ) ) == -1 ) {
		snprintf( err, esize, "Failed to open file - %s: %s", dest, strerror( errno ) );
		return 0;
	}

	// Do the zrender dance
	zRender *zr = zrender_init();
	zrender_set_default_dialect( zr );
	zrender_set_boundaries( zr, "[[", "]]" );
	zrender_set_fetchdata( zr, zd );

	// Actually do the render...
	if ( !( dd = zrender_render( zr, content, size, &dlen ) ) ) {
		snprintf( err, esize, "Failed to finish render!\n" );
		return 0;
	}

	// Write contents
	if ( ( written = write( fd, dd, dlen ) ) == -1 || written != dlen ) {
		snprintf( err, esize, "Failed to write to file - %s: %s", dest, strerror( errno ) );
		return 0;
	}

	// Close the file
	close(fd);
	
	// And free the content
	free( content ), free( dd );

	// Free the zrender object too
	zrender_free( zr );
	return 1;
}



/// Randomly generate a string of text
char * rand_gen ( int len ) {
	const char randchar[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	char * buf = malloc ( len + 1 );
	struct timespec n = { 0 };
	
	// ....
	clock_gettime( CLOCK_REALTIME, &n );
	memset( buf, 0, len );
	srand( n.tv_nsec );

	for ( int i = 0; i < len; i++ ) {
		buf[ i ] = randchar[ rand() % 36 ];
	}

	return buf;
}



int main ( int argc, char *argv[] ) {
	
	char err[ 2048 ] = { 0 };
	// const char *file = "example.lua";
	// lua_State *L = NULL;
	zTable *zt = NULL;

	if ( argc < 2 ) {
		HELP( "No arguments specified.\n" OPTIONSMSG );
		return 1;	
	}

	for ( char **av = ++argv; *av; av++ ) {
		if ( !strcmp( *av, "-c" ) || !strcmp( *av, "--create" ) ) {
			opt.create = 1; 
			av++;

			if ( !( opt.createArg = *av ) ) {
				HELP( "No argument specified for --create." );
				return 1;	
			}	

			// Set the appname from the path
			opt.appname = basename( opt.createArg );
		}
		else if ( !strcmp( *av, "-i" ) || !strcmp( *av, "--identifier" ) ) {
			av++;
			if ( !( opt.id = *av ) ) {
				HELP( "No argument specified for --identifier." );
				return 1;	
			}	
		}
		else if ( !strcmp( *av, "-f" ) || !strcmp( *av, "--file" ) ) {
			av++;
			if ( !( opt.file = *av ) ) {
				HELP( "No argument specified for --file." );
				return 1;	
			}	
		}
		else if ( !strcmp( *av, "-n" ) || !strcmp( *av, "--name" ) ) {
			av++;
			if ( !( opt.appname = *av ) ) {
				HELP( "No argument specified for --name." );
				return 1;	
			}	
		}
		else if ( !strcmp( *av, "-s" ) || !strcmp( *av, "--store-name" ) ) {
			av++;
			if ( !( opt.storename = *av ) ) {
				HELP( "No argument specified for --store-name." );
				return 1;	
			}	
		}
		else if ( !strcmp( *av, "--android-only" ) ) {
			opt.iosBuild = 0;
		}
		else if ( !strcmp( *av, "--ios-only" ) ) {
			opt.androidBuild = 0;
		}
		else if ( !strcmp( *av, "-v" ) || !strcmp( *av, "--verbose" ) ) {
			opt.verbose = 1;
		}
	#if 0
		else if ( !strcmp( *av, "-g" ) || !strcmp( *av, "--generate" ) ) {
			opt.generate = 1;
			av++;
			if ( !( opt.file = *av ) ) {
				HELP( "No argument specified for --generate." );
				return 1;	
			}	
		}
	#endif
		else {
			HELP( "Unknown/unsupported flag: %s.", *av );
			return 1;	
		}
	}

	// Depending on what's used to create the app, we probably
	// should also create the files for the backend too...
	#if 0	
	if ( opt.generate ) {
		// Just generate a blank file with keys that we'll most likely need
		zTable *zt = NULL;
		const char *src = "share/example.lua";
		unsigned char *data = NULL;
		char dest[ PATH_MAX ] = { 0 }, *content = NULL;
		int dsize = 0, clen = 0, written = 0, fd = 0;

		// Set an appname by default
		if ( !opt.appname ) {
			opt.appname = basename( opt.file );
		}

		if ( !( zt = lt_make( 128 ) ) ) {
			HELP( "Could not generate new table." );
			return 1;
		}

		lt_addtextkey( zt, "identifier" );
		lt_addtextvalue( zt, opt.id );
		lt_finalize( zt );
		lt_addtextkey( zt, "app_name" );
		lt_addtextvalue( zt, opt.appname );
		lt_finalize( zt );
		lt_addtextkey( zt, "app_proper_name" );
		lt_addtextvalue( zt, opt.appname );
		lt_finalize( zt );
		lt_lock( zt );


		// Do find & replace and write the new file to the RIGHT location
		snprintf( dest, PATH_MAX - 1, "%s.lua", opt.file );  
	#if 0
		if ( !render_file( src, dest, zt, err, sizeof( err ) ) ) {
			HELP( "Couldn't write file '%s': %s\n", dest, err );
			return 0;
		}
	#else
		// Read in the contents
		if ( !( data = read_file( src, &dsize, err, sizeof( err ) ) ) ) {
			// HELP( "Failed to read file - %s: %s", src, err );
			return 0;
		} 

		// Open a file
		if ( ( fd = open( dest, O_RDWR | O_CREAT, 0755 ) ) == -1 ) {
			snprintf( err, sizeof( err ), "Failed to open file - %s: %s", dest, strerror( errno ) );
			return 0;
		}

		// Do the zrender dance
		zRender *zr = zrender_init();
		zrender_set_default_dialect( zr );
		zrender_set_boundaries( zr, "<<", ">>" );
		zrender_set_fetchdata( zr, zt );

		// Actually do the render...
		if ( !( content = (char *)zrender_render( zr, data, dsize, &clen ) ) ) {
			snprintf( err, sizeof( err ), "Failed to finish render!\n" );
			return 0;
		}

		// Write contents
		if ( ( written = write( fd, content, clen ) ) == -1 || written != clen ) {
			snprintf( err, sizeof( err ), "Failed to write to file - %s: %s", dest, strerror( errno ) );
			return 0;
		}

		// Close
		close( fd );
	#endif  

		// Do a zrender dance...
		lt_free( zt ), free( zt );
	}
	#endif
	
	// Trigger Android builds
	if ( opt.create && opt.androidBuild ) {
		char src_dir[ PATH_MAX ], layout_dir[ PATH_MAX ], fragments_dir[ PATH_MAX ];
		char activity_dir[ PATH_MAX ];
		int id = 0;

		if ( opt.verbose ) {
			fprintf( stderr, "Creating app: %s at %s\n", opt.appname, opt.createArg );
		}

		if ( !strlen( opt.appname ) ) {
			HELP( "No appname specified..." );
			return 1;
		}

    if ( !strlen( opt.id ) ) {
			HELP( "No namespace identifier specified..." );
			return 1;
		}

    if ( !strlen( opt.storename ) ) {
			HELP( "No store/proper name specified..." );
			return 1;
		}

		// Define a file just for testing...
		if ( !( zt = lt_make( 1024 ) ) ) {
			HELP( "ztable creation failed: %s.", lt_strerror ( zt ) );
			return 0;
		}

    //  Add the identifier
    lt_addtextkey( zt, "identifier" );
    lt_addtextvalue( zt, opt.id );
    lt_finalize( zt );

    //  Add app name
    lt_addtextkey( zt, "app_name" );
    lt_addtextvalue( zt, opt.appname );
    lt_finalize( zt );

    //  Add the proper name
    lt_addtextkey( zt, "app_proper_name" );
    lt_addtextvalue( zt, opt.storename );
    lt_finalize( zt );

    // "Lock" the table (which simply creates a hash table of all values stored)
		if ( !lt_lock( zt ) ) {
			HELP( "Failed to lock zTable." );
			return 0;
		}

#if 0
lt_dump( zt );
lt_free( zt );
exit(0);

		// Try to load a Lua file. and do some stuff
		if ( !lua_exec_file( L, opt.file, err, sizeof( err ) ) ) {
			HELP( "Lua execution failure: %s.", err );
			return 0;
		}
		
		// Then convert it to table
		if ( !lua_to_ztable( L, 1, zt ) ) {
			HELP( "Failed to convert Lua to C structure." );
			return 0;
		}
#endif 


	#if 1
		// Create the host directory
		if ( mkdir( opt.createArg, 0755 ) == -1 ) {
			HELP( "Failed to create source directory: %s.", strerror( errno ) );
			return 1;
		}

		// Create all the directories
		for ( struct file *dir = android_dirs; dir->filename != NULL; ++dir ) {

			const char fb[ PATH_MAX ];
			memset( (void *)fb, 0, PATH_MAX );

			if ( *dir->filename == '$' )
				snprintf( (char *)fb, PATH_MAX - 1, "%s/%s/%s", opt.createArg, dir->filename + 1, opt.id );
			else if ( *dir->filename == '@' )
				snprintf( (char *)fb, PATH_MAX - 1, "%s/%s/%s/%s", opt.createArg, dir->filename + 1, opt.id, opt.appname );
			else if ( *dir->filename == 'F' )
				snprintf( (char *)fb, PATH_MAX - 1, "%s/%s/%s/%s/fragments", opt.createArg, dir->filename + 1, opt.id, opt.appname );
			else {
				snprintf( (char *)fb, PATH_MAX - 1, "%s/%s", opt.createArg, dir->filename );
			}

			// TODO: Proper clean up should be done in case there are failures.
			if ( mkdir( fb, dir->mode ) == -1 ) {
				HELP( "Failed to create directory: %s; %s.", fb, strerror( errno ) );
				return 1;
			}

		}

		// Copy all the files to the right places for now...
		for ( struct file *file = android_files; file->filename; ++file ) {

			const char template_dir[] = ANDROID_TEMPLATE_DIR;
			const char src[ PATH_MAX ], dest[ PATH_MAX ];
			memset( (void *)src, 0, PATH_MAX ), memset( (void *)dest, 0, PATH_MAX );

			// The $ sign with files means do a raw copy...
			if ( *file->filename == '$' ) {
				snprintf( (char *)src, PATH_MAX - 1, "%s/%s", template_dir, file->filename + 1 );	
				snprintf( (char *)dest, PATH_MAX - 1, "%s/%s", opt.createArg, file->filename + 1 );

        if ( opt.verbose ) fprintf( stderr, "Copying source file to %s\n", dest );

				if ( !raw_copy( src, dest, err, sizeof( err ), file->mode ) ) {
					HELP( "Error writing file: %s", err );
					return 1;
				}
			}
			//  The @ sign denotes a render to a "variable" location (like /path/to/${opt.id}/file)
			else if ( *file->filename == '@' ) {
				snprintf( (char *)src, PATH_MAX - 1, "%s/%s", template_dir, file->filename + 1 );	
				snprintf( (char *)dest, PATH_MAX - 1, "%s/", opt.createArg );
				int times = 0;
				for ( char *f = (char *)file->filename + 1, *d = (char *)dest + strlen( opt.createArg ) + 1; *f; f++ ) {
					if ( *f != '#' )
						*d = *f, d++;
					else {
						if ( times == 0 )
							memcpy( d, "com", 3 ), d += 3, times++;
						else if ( times == 1 )
							memcpy( d, opt.id, strlen( opt.id ) ), d += strlen( opt.id ), times++;
						else if ( times == 2 ) {
							memcpy( d, opt.appname, strlen( opt.appname ) ), d += strlen( opt.appname ), times++;
						}
					}
				}
	      if ( opt.verbose ) fprintf( stderr, "Generating file %s\n", dest );
				if ( !render_file( src, dest, zt, err, sizeof( err ), file->mode ) ) {
					HELP( "Error writing file: %s", err );
					return 1;
				}
			}
			else {
				snprintf( (char *)src, PATH_MAX - 1, "%s/%s", template_dir, file->filename );	
				snprintf( (char *)dest, PATH_MAX - 1, "%s/%s", opt.createArg, file->filename );

	      if ( opt.verbose ) fprintf( stderr, "Generating file %s\n", dest );
				if ( !render_file( src, dest, zt, err, sizeof( err ), file->mode ) ) {
					HELP( "Error writing file: %s", err );
					return 1;
				}
			}
		}

    //  This is the only one we're doing manually, simply because I don't have a rule for it above
    
	#endif

	#if 0
		// Create all the activities files...
		if ( ( id = lt_geti( zt, "activities" ) ) > -1 ) {
			// Copy all the activities into their own table 
			zTable *tt = lt_copy_by_index( zt, id );
			const char *tdir = "share", **keys = lt_get_keys( tt ); // , 0, 0, 1 );

			if ( keys ) {	
				// Copy each table (denoted by key) from the activities table
				// and generate a class file render
				for ( const char **k = keys; k && *k; k++ ) {
					// Make buffers
					char key[ 1024 ] = {0}, tkey[ 1024 ] = {0};
					char src[ PATH_MAX ] = {0}, dest[ PATH_MAX ] = {0};
					zTable *ii = NULL; 

					// Generate the key for finding the inner table
					snprintf( key, sizeof( key ), "%s.%s", "activities", *k );

					// Copy a table
					if ( ( ii = lt_copy_by_key( tt, key ) ) ) {
						// Need to add more than a few keys for this to work...
						char *template = NULL, *rs = rand_gen( 32 );
						struct symfile *cc = NULL;
						int index = 0;
						lt_addtextkey( ii, "identifier" ), lt_addtextvalue( ii, opt.id ), lt_finalize( ii );
						lt_addtextkey( ii, "app_name" ), lt_addtextvalue( ii, opt.appname ), lt_finalize( ii );
						lt_addtextkey( ii, "class_name" ), lt_addtextvalue( ii, *k ), lt_finalize( ii );
						lt_addtextkey( ii, "eid" ), lt_addtextvalue( ii, rs ), lt_finalize( ii ), free( rs );
						lt_lock( ii );
						lt_kfdump( ii, 2 );

						// Stop and let the user know that they need this...
						if ( ( index = lt_geti( ii, "layout" ) ) == -1 ) {
							HELP( "Key 'layout' not in activity '%s'", *k );
							return 1;
						}
						
						// TODO: Consider listing all the files in the directory
						// Build a buffer for finding the template
						snprintf( tkey, sizeof( tkey ), "%s.template", *k );

						// Get the template (if one is specified), if not use a generic
						template = lt_text( ii, tkey ) ? lt_text( ii, tkey ) : "generic";
						for ( struct symfile *t = np_android; t->name; t++ ) {
							if ( !strcasecmp( t->name, template ) ) {
								cc = t;
								break;	
							}
						}

						// Create the full source file name
						snprintf( src, PATH_MAX - 1, "%s/%s/%s.java", tdir, cc->spath, cc->name );
						snprintf( dest, PATH_MAX - 1, "%s/%s/%s/%s/%s.java", opt.createArg, cc->dpath, opt.id, opt.appname, *k );
						// fprintf( stderr, "S: %s, D: %s\n", src, dest );

						// Do find & replace and write the new file to the RIGHT location
						if ( !render_file( src, dest, ii, err, sizeof( err ) ) ) {
							HELP( "Couldn't write file '%s': %s\n", dest, err );
							return 0;
						}

						// You can descend and create each of the layouts / fragments that are related here...
						lt_free( ii ), free( ii );
					}
				}
				lt_free_keys( keys );	
			}

			// Loop through each key, if template exists; find, replace and copy
			lt_free( tt ), free( tt );
		}
	#endif
		
		// Generate layouts 
		// Same here
		
		// Generate fragments 
		// and here
		
		// Start generating the layouts 
		memset( layout_dir, 0, PATH_MAX );
		// snprintf( layout_dir, ... );
		
		// Copy assets, fonts, etc
		
		// Finally, generate the AndroidManifest.xml file
		
		// And a Makefile...
		
		// Free the table made from the file
		lt_free( zt ), free( zt );
	}

	return 0;
}




