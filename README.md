#                               cprint                               #

Improved print function that handles ANSI escapes even on Windows


##                               Usage                              ##

The function returned by this Lua module is compatible with the
default Lua `print` function and can serve as a replacement for it.

    print = require( "cprint" )
    print( "hello world" )

Additionally, the following ANSI color escape sequences are supported
on both Windows and POSIX platforms:

*   `"\027[30m"` to `"\027[37m"`, and `"\027[39m"`

    Those escape sequences set the foreground color to black, red,
    green, yellow, blue, magenta/purple, cyan/aqua, white, and the
    default foreground color, respectively.

*   `"\027[40m"` to `"\027[47m"`, and `"\027[49m"`

    Those escape sequences set the background color to black, red,
    green, yellow, blue, magenta/purple, cyan/aqua, white, and the
    default background color, respectively.

*   `"\027[0m"`, `"\027[1m"`, and `"\027[7m"`

    Those escape sequences represent normal mode, bright/highlighted
    mode, and inverted mode.

The escape sequences can be combined by separating the numbers with
`;`, e.g.:

    print( "\027[31;1mbright red\027[39;49;0m" )

If the standard output stream is not connected to a terminal/console,
or if the terminal is not recognized as compatible, the escape
sequences are stripped from the output.


##                              License                             ##

cprint is *copyrighted free software* distributed under the MIT
license (the same license as Lua 5.1). The full license text follows:

    cprint (c) 2013 Philipp Janda

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

The actual code implementing the `print` function is taken almost
verbatim from the [Lua][1] source code, which is

    Copyright (C) 1994-2013 Lua.org, PUC-Rio.

  [1]:  http://www.lua.org/

