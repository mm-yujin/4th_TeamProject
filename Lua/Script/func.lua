-- func.lua

Person = {}
function Person:new(name, age)
    local instance setmetatable({}, self)
    self.__index = self
    instance.name = name or 'chul-su'
    instance.age = age or 20

    return instance
end

function Person:hello()
    print(string.format('Hello, My name is %s. I am %d years old', self.name, self.age))
end

function Test()
    return Person:new('응애', 1)
end

function LuaAdd( num1, num2 )
    return num1 + num2, 10
end

function LuaSub( num1, num2)
    return num1 - num2
end


EVENT_SAMPLE = 1000
RegisterEvent("EventHandler")
function EventHandler(id, ...)
    if id == EVENT_SAMPLE then
        print("Sample Event!")
    end
end