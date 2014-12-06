local moving = 0
local dir = "up"



local function moveCamera(direction)
	local e = Camera.Find("classicCamera")
	if (direction == "up")
	then
		Camera.GoUp(e)
	elseif (direction == "dn")
	then
		Camera.GoDown(e)
	elseif (direction == "lf")
	then
		Camera.GoLeft(e)
	elseif (direction == "rt")
	then
		Camera.GoRight(e)
	end
end

local function handleKeys()
	if(Keyboard.KeyDown("up")) 
	then 
		moveCamera("up")

	elseif(Keyboard.KeyDown("left")) 
	then
		moveCamera("lf")

	elseif(Keyboard.KeyDown("down")) 
	then
		moveCamera("dn")
		
	elseif(Keyboard.KeyDown("right")) 
	then
		moveCamera("rt")

	end
end


function Update()
print("moshi")
	handleKeys()
end