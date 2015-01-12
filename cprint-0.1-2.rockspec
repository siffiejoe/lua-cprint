package="cprint"
version="0.1-2"
source = {
  url = "git://github.com/siffiejoe/lua-cprint.git",
  tag = "v0.1",
}
description = {
  summary = "An improved print function",
  detailed = [[
    An improved print function that can handle simple
    ANSI color escape sequences.
  ]],
  homepage = "https://github.com/siffiejoe/lua-cprint/",
  license = "MIT"
}
dependencies = {
  "lua >= 5.1, < 5.4"
}
build = {
  type = "builtin",
  modules = {
    cprint = "cprint.c",
  }
}

