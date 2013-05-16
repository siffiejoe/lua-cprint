
#line 1 "pr_ansi.rh"
/*
 * Compile (to pr_ansi.h):
 * $ ragel -C -G2 pr_ansi.rh
 * For graphviz output:
 * $ ragel -V -p pr_ansi.rh | dot -T png -o out.png
 */



#line 16 "pr_ansi.rh"



static int terminal_supported( char const* p ) {
  int res = 0;
  int cs = 0;

#line 21 "pr_ansi.h"
static const int term_support_start = 1;

static const int term_support_en_main = 1;


#line 27 "pr_ansi.h"
	{
	cs = term_support_start;
	}

#line 32 "pr_ansi.h"
	{
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 108: goto st2;
		case 114: goto st7;
		case 120: goto st10;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	p += 1;
case 2:
	if ( (*p) == 105 )
		goto st3;
	goto st0;
st3:
	p += 1;
case 3:
	if ( (*p) == 110 )
		goto st4;
	goto st0;
st4:
	p += 1;
case 4:
	if ( (*p) == 117 )
		goto st5;
	goto st0;
st5:
	p += 1;
case 5:
	if ( (*p) == 120 )
		goto st6;
	goto st0;
st6:
	p += 1;
case 6:
	if ( (*p) == 0 )
		goto tr8;
	goto st0;
tr8:
#line 15 "pr_ansi.rh"
	{ res = 1; {p++; cs = 14; goto _out;} }
	goto st14;
st14:
	p += 1;
case 14:
#line 83 "pr_ansi.h"
	goto st0;
st7:
	p += 1;
case 7:
	if ( (*p) == 120 )
		goto st8;
	goto st0;
st8:
	p += 1;
case 8:
	if ( (*p) == 118 )
		goto st9;
	goto st0;
st9:
	p += 1;
case 9:
	if ( (*p) == 116 )
		goto tr8;
	goto st0;
st10:
	p += 1;
case 10:
	if ( (*p) == 116 )
		goto st11;
	goto st0;
st11:
	p += 1;
case 11:
	if ( (*p) == 101 )
		goto st12;
	goto st0;
st12:
	p += 1;
case 12:
	if ( (*p) == 114 )
		goto st13;
	goto st0;
st13:
	p += 1;
case 13:
	if ( (*p) == 109 )
		goto tr8;
	goto st0;
	}

	_out: {}
	}

#line 27 "pr_ansi.rh"

  (void)term_support_en_main;
  return res;
}



#line 50 "pr_ansi.rh"


static void write_ansi( iprint_info* info, char const* p, size_t n ) {
  int cs = 0;
  char const* pe = p + n;
  char const* eof = pe;
  char const* prev = p;

#line 149 "pr_ansi.h"
static const int ansi_escape_start = 0;

static const int ansi_escape_en_main = 0;


#line 155 "pr_ansi.h"
	{
	cs = ansi_escape_start;
	}

#line 160 "pr_ansi.h"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr5:
#line 44 "pr_ansi.rh"
	{
    iprint_doansi( info, prev, p+1-prev );
    prev = p+1;
  }
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 177 "pr_ansi.h"
	if ( (*p) == 27 )
		goto tr1;
	goto st0;
tr1:
#line 39 "pr_ansi.rh"
	{
    if( p > prev )
      w( prev, p-prev );
    prev = p;
  }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 193 "pr_ansi.h"
	switch( (*p) ) {
		case 27: goto tr1;
		case 91: goto st2;
	}
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 27 )
		goto tr1;
	if ( (*p) < 51 ) {
		if ( 48 <= (*p) && (*p) <= 50 )
			goto st3;
	} else if ( (*p) > 52 ) {
		if ( 53 <= (*p) && (*p) <= 57 )
			goto st3;
	} else
		goto st4;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 27: goto tr1;
		case 59: goto st2;
		case 109: goto tr5;
	}
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 27: goto tr1;
		case 59: goto st2;
		case 109: goto tr5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st3;
	goto st0;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 0: 
	case 1: 
	case 2: 
	case 3: 
	case 4: 
#line 39 "pr_ansi.rh"
	{
    if( p > prev )
      w( prev, p-prev );
    prev = p;
  }
	break;
#line 259 "pr_ansi.h"
	}
	}

	}

#line 62 "pr_ansi.rh"

  (void)ansi_escape_en_main;
}

