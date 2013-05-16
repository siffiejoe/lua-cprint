#!/usr/bin/lua

local iprint = require( "iprint" )

iprint( "hello world!" )
iprint( "hello", "world!" )
iprint( "hello\027 world!" )
iprint( "hello\027[31 world!" )
iprint( "hello\027[31m world!" )
iprint( "hello\027[0m world!" )
iprint( "hello \027[31;44;1mworld\027[39;49;0m bla!" )

for i = 0, 7 do
  iprint( "\027[3"..i.."mwhoa!\027[1m highlighted!\027[0m" )
end

--[[
for i = 0, 7 do
  for j = 0, 7 do
    for _,m in ipairs{ 0, 1, 7 } do
      iprint( "Wait for it: \027[3"..j..";4"..i..";"..m..
              "mCOLOR\027[0m. cool, isn't it?" )
    end
  end
end
--]]


