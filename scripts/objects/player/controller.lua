local moving = 0
local dir = "up"

local this = nil
local transform = nil
local reload = 1

local function turn(direction)
	local rotate = Transform.GetOrientation(transform)
	if (direction == "up")
	then
		local z = Vec3.z(rotate);
		local x = Vec3.x(rotate);
		local y = 180;
		local nt = Vec3.Create(x, y, z)
		Transform.SetOrientation(transform, nt)
	elseif (direction == "dn")
	then
		local z = Vec3.z(rotate);
		local x = Vec3.x(rotate);
		local y = 0;
		local nt = Vec3.Create(x, y, z)
		Transform.SetOrientation(transform, nt)
	elseif (direction == "lf")
	then
		local z = Vec3.z(rotate);
		local x = Vec3.x(rotate);
		local y = 270;
		local nt = Vec3.Create(x, y, z)
		Transform.SetOrientation(transform, nt)
	elseif (direction == "rt")
	then
		local z = Vec3.z(rotate);
		local x = Vec3.x(rotate);
		local y = 90;
		local nt = Vec3.Create(x, y, z)
		Transform.SetOrientation(transform, nt)
	end
end

local function handleKeys()
	if(Keyboard.KeyDown("w")) 
	then 
		moving = 1
		dir = "up"
		turn(dir)

	elseif(Keyboard.KeyDown("a")) 
	then
		moving = 1
		dir = "lf"
		turn(dir)

	elseif(Keyboard.KeyDown("s")) 
	then
		moving = 1
		dir = "dn"
		turn(dir)
		
	elseif(Keyboard.KeyDown("d")) 
	then
		moving = 1
		dir = "rt"
		turn(dir)

	end
end

local function movePlayer(direction)
	local translate = Transform.GetPosition(transform)
	if (direction == "up")
	then
		local z = Vec3.z(translate)-1;
		local x = Vec3.x(translate);
		local y = Vec3.y(translate);
		local nt = Vec3.Create(x, y, z)
		Transform.SetPosition(transform, nt)
	elseif (direction == "dn")
	then
		local z = Vec3.z(translate)+1;
		local x = Vec3.x(translate);
		local y = Vec3.y(translate);
		local nt = Vec3.Create(x, y, z)
		Transform.SetPosition(transform, nt)
	elseif (direction == "lf")
	then
		local z = Vec3.z(translate);
		local x = Vec3.x(translate)-1;
		local y = Vec3.y(translate);
		local nt = Vec3.Create(x, y, z)
		Transform.SetPosition(transform, nt)
	elseif (direction == "rt")
	then
		local z = Vec3.z(translate);
		local x = Vec3.x(translate)+1;
		local y = Vec3.y(translate);
		local nt = Vec3.Create(x, y, z)
		Transform.SetPosition(transform, nt)
	end
end


function Update()
	--If necessary check movement inputs
	
	if (reload == 1)
	then	
		this = Entity.Find("PLAYER")
		transform = Entity.GetTransform( this )
		reload = 0
	end
	if (moving == 0) 
	then 
		handleKeys()
	elseif(moving == 31) 
	then 
		moving = 0 
	else 
		moving = moving + 1
		movePlayer(dir)
	end
end

print ("Script: Loaded player controller")