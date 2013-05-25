#!/usr/bin/lua

local cprint = require( "cprint" )

cprint( "hello world!" )
cprint( "hello", "world!" )
cprint( "hello\027 world!" )
cprint( "hello\027[31 world!" )
cprint( "hello\027[31m world!" )
cprint( "hello\027[0m world!" )
cprint( "hello \027[31;44;1mworld\027[39;49;0m bla!" )

for i = 0, 7 do
  cprint( "\027[3"..i.."mwhoa!\027[1m highlighted!\027[0m" )
end

--[[
for i = 0, 7 do
  for j = 0, 7 do
    for _,m in ipairs{ 0, 1, 7 } do
      cprint( "Wait for it: \027[3"..j..";4"..i..";"..m..
              "mCOLOR\027[0m. cool, isn't it?" )
    end
  end
end
--]]


