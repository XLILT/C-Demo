#!/usr/bin/env lua

--[[====[
print(package.path)
print(package.cpath)

local socket = require("socket")
local host = "www.baidu.com"
local file = "/"
local sock = assert(socket.connect(host, 80))
sock:send("GET " ..file.. " HTTP/1.0\r\n\r\n")
repeat
    local chunk, status, partial = sock:receive(1024)
    print(chunk or partial)
until status ~= "closed"

sock:close()
]====]]

--[[====
local http = require("socket.http")
local response = http.request("http://www.yb.dz11.com/")
print(response)
]====]]

--print("hello lua print" , "string link")

--[[
a = 1
while a ~= 10 do
    io.write(a .. " ")
    a = a + 1
end
]]

--[[
a = 1
repeat
    print(a)
    a = a + 1
until a == 10
]]

--[[
for a = 1, 10, 1 do
    io.write(a .. " ")
end
]]

--[[
function f(par1, par2)
    return par1 + par2, par1 - par2
end

print(f(1, 1))
]]

--[[
linbc = {}
linbc.sex = "male"
linbc.age = 27

print(linbc, linbc.sex, linbc["age"])

for k, v in pairs(linbc) do
    print(k, v)
end

arr = {1, 2, 3}
table.insert(arr, linbc)
table.foreach(arr, function(k, v) print (k, v) end)
]]

function readFile()
    fname = "test.txt"
    BUFSIZE = 1024
    local f = assert(io.open(fname, 'r'))
    local str = f:read("*all")
    f:close()
    return str
end

function increase(x)
    return x + 1
end

--print(increase(1))
--print(readFile())
