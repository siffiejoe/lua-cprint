#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"

#ifndef CPRINT_STREAM
#  define CPRINT_STREAM stdout
#endif

#define w( s, n ) (fwrite( (s), sizeof( char ), (n), CPRINT_STREAM ))
#define tab()     (putc( '\t', CPRINT_STREAM ))
#define nl()      (putc( '\n', CPRINT_STREAM ), fflush( CPRINT_STREAM ))


/* Try to figure out if we are a posix or windows environment */
#if defined( _WIN32 ) || defined( _WIN64 ) || defined( __WIN32__ ) || \
    defined( __TOS_WIN__ ) || defined( __WINDOWS__ )

  /* windows */
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <io.h>

  static int color_mapping[] = {
    0,  /* black */
    4,  /* red */
    2,  /* green */
    6,  /* yellow */
    1,  /* blue */
    5,  /* magenta/purple */
    3,  /* cyan/aqua */
    7,  /* white */
    0, 0 /* unused */
  };

  typedef struct {
    int enabled;
    HANDLE hConsole;
    int last_fg;
    int last_bg;
    int last_md;
  } cprint_info;

  static void cprint_init( cprint_info* info ) {
    info->last_fg = 7;
    info->last_bg = 0;
    info->last_md = 0;
    info->enabled = _isatty( _fileno( CPRINT_STREAM ) );
    info->hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    if( info->hConsole == INVALID_HANDLE_VALUE )
      info->enabled = 0;
  }

  static void cprint_doansi( cprint_info* info,
                             char const* esc, size_t n ) {
    if( info->enabled ) {
      char const* p = esc;
      int high, inverse;
      p += 2; /* skip ESC and [ */
      while( *p != 'm' ) {
        if( *p == '3' && '0' <= p[1] && p[1] <= '9' ) {
          int fg = p[1] - '0';
          if( fg > 7 )
            fg = 7; /* default foreground */
          info->last_fg = color_mapping[ fg ];
          p += 2;
        } else if( *p == '4' && '0' <= p[1] && p[1] <= '9' ) {
          int bg = p[1] - '0';
          if( bg > 7 )
            bg = 0; /* default background */
          info->last_bg = color_mapping[ bg ];
          p += 2;
        } else if( *p != ';' ) {
          switch( *p ) {
            case '0':
              if( p == esc+2 ) {
                info->last_fg = 7;
                info->last_bg = 0;
              }
              info->last_md = 0;
              break;
            case '1':
              info->last_md = 1;
              break;
            case '7':
              info->last_md = 7;
              break;
            default:
              info->last_md = 0;
              break;
          }
          p += 1;
        } else
          p += 1;
      }
      high = info->last_md == 1;
      inverse = info->last_md == 7;
      SetConsoleTextAttribute( info->hConsole,
                               info->last_fg*(1+inverse*15)+high*8 +
                               info->last_bg*(1+(!inverse)*15) );
    }
  }

#elif defined( unix ) || defined( __unix ) || defined( __unix__ ) || \
    defined( __TOS_AIX__ ) || defined( _SYSTYPE_BSD )

  /* some form of unix */
  #include <unistd.h>
  #include <stdlib.h>

  typedef struct {
    int enabled;
  } cprint_info;

  /* defined in pr_ansi.h */
  static int terminal_supported( char const* term );

  static void cprint_init( cprint_info* info ) {
    char const* term = getenv( "TERM" );
    info->enabled = term != NULL && terminal_supported( term ) &&
                    isatty( STDOUT_FILENO );
  }

  static void cprint_doansi( cprint_info* info,
                             char const* esc, size_t n ) {
    if( info->enabled )
      w( esc, n );
  }

#else

  /* unknown/unsupported OS */
  typedef struct {
    int dummy;
  } cprint_info;

  static void cprint_init( cprint_info* info ) {
    info->dummy = 0;
  }

  static void cprint_doansi( cprint_info* info,
                             char const* esc, size_t n ) {
    (void)info;
    (void)esc;
    (void)n;
  }

#endif


#include "pr_ansi.h"

static int cprint( lua_State* L ) {
  cprint_info* info = lua_touserdata( L, lua_upvalueindex( 1 ) );
  int top = lua_gettop( L );
  int i = 0;
  lua_getglobal( L, "tostring" );
  for( i = 1; i <= top; ++i ) {
    size_t n = 0;
    char const* s = NULL;
    lua_pushvalue( L, -1 );
    lua_pushvalue( L, i );
    lua_call( L, 1, 1 );
    s = lua_tolstring( L, -1, &n );
    if( s == NULL )
      return luaL_error( L, LUA_QL("tostring")
                            " must return a string to "
                            LUA_QL("print") );
    if( i > 1 )
      tab();
    write_ansi( info, s, n );
    lua_pop( L, 1 );
  }
  nl();
  return 0;
}


#ifndef CPRINT_API
#  define CPRINT_API
#endif

CPRINT_API int luaopen_cprint( lua_State* L ) {
  cprint_info* info = lua_newuserdata( L, sizeof( cprint_info ) );
  cprint_init( info );
  lua_pushcclosure( L, cprint, 1 );
  return 1;
}

