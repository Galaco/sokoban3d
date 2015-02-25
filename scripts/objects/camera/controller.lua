local moving = 0
local dir = "up"

local e = Camera.Find("extendedCamera")


local function moveCamera(direction)
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
	if(Keyboard.KeyDown("i")) 
	then 
		moveCamera("up")

	elseif(Keyboard.KeyDown("j")) 
	then
		moveCamera("lf")

	elseif(Keyboard.KeyDown("k")) 
	then
		moveCamera("dn")
		
	elseif(Keyboard.KeyDown("l")) 
	then
		moveCamera("rt")

	end
end


function Update()
	handleKeys()
end