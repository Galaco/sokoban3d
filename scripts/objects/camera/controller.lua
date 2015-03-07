local moving = 0
local dir = "up"
local loadCam = 0
local e = Camera.Find("extendedCamera")

local function handleKeys()
	if(Keyboard.KeyDown("r")) 
	then 
		local trans = Camera.GetTransform(e)
		Transform.SetPosition(trans, Vec3.Create(600, 0, -150))
		Transform.SetOrientation(trans, Vec3.Create(3.2, 4.75, 0))
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