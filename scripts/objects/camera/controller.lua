local moving = 0
local dir = "up"
local loadCam = 0
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
	if(Keyboard.KeyDown("w")) 
	then 
		moveCamera("up")

	elseif(Keyboard.KeyDown("a")) 
	then
		moveCamera("lf")

	elseif(Keyboard.KeyDown("s")) 
	then
		moveCamera("dn")
		
	elseif(Keyboard.KeyDown("d")) 
	then
		moveCamera("rt")

	end
end


function Update()
	if (loadCam == 0)
	then
		e = Camera.Find("extendedCamera")
		loadCam = 1
	end
	handleKeys()
end