local moving = 0
local dir = "up"
local oldFace = 0
local face = 1

local this = nil
local transform = nil
local reload = 1



local function rotateCamera(face)
	if(face == 0)	
			local nt = Vec3.Create(0, 90, 00)
	then
end

local function turn(direction)
	--Front
	if (face == 0)
	then
		local rotate = Transform.GetOrientation(transform)
		if (direction == "up")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 180, 00)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "dn")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 180, 180)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "lf")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 180, 90)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "rt")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 180, 270)
			Transform.SetOrientation(transform, nt)
		end
	end
	--Right
	if (face == 1)
	then
		local rotate = Transform.GetOrientation(transform)
		if (direction == "up")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 90, 00)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "dn")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 90, 180)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "lf")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 90, 90)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "rt")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 90, 270)
			Transform.SetOrientation(transform, nt)
		end
	end
	--Back
	if (face == 2)
	then
		local rotate = Transform.GetOrientation(transform)
		if (direction == "up")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 0, 00)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "dn")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 0, 180)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "lf")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 0, 90)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "rt")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 0, 270)
			Transform.SetOrientation(transform, nt)
		end
	end
	
	--Left
	if (face == 3)
	then
		local rotate = Transform.GetOrientation(transform)
		if (direction == "up")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 270, 0)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "dn")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 270, 180)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "lf")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 270, 270)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "rt")
		then
			local nt = Vec3.Create(Vec3.x(rotate), 270, 90)
			Transform.SetOrientation(transform, nt)
		end
	end
	
	
	
	--Top
	if (face == 4)
	then
		local rotate = Transform.GetOrientation(transform)
		if (direction == "up")
		then
			local nt = Vec3.Create(90, Vec3.y(rotate), 0)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "dn")
		then
			local nt = Vec3.Create(90, Vec3.y(rotate), 180)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "lf")
		then
			local nt = Vec3.Create(90, Vec3.y(rotate), 90)
			Transform.SetOrientation(transform, nt)
		elseif (direction == "rt")
		then
			local nt = Vec3.Create(90, Vec3.y(rotate), 270)
			Transform.SetOrientation(transform, nt)
		end
	end
end

local function handleKeys(dir)
	if(dir == "w") 
	then 
		if(SOKOBAN.CanPlayerMove(0) == 1)
		then
			moving = 1
			dir = "up"
			turn(dir)	
			oldFace = face
			face = SOKOBAN.CurrentFace()
			movesMade = movesMade + 1
			rotateCamera(face)
		end

	elseif( dir == "a") 
	then
		if(SOKOBAN.CanPlayerMove(2) == 1)
		then
			moving = 1
			dir = "lf"
			turn(dir)
			oldFace = face
			face = SOKOBAN.CurrentFace()
			movesMade = movesMade + 1
			rotateCamera(face)
		end
	elseif(dir == "s") 
	then
		if(SOKOBAN.CanPlayerMove(1) == 1)
		then
			moving = 1
			dir = "dn"
			turn(dir)
			oldFace = face
			face = SOKOBAN.CurrentFace()
			movesMade = movesMade + 1
			rotateCamera(face)
		end
	elseif(dir == "d") 
	then
		if(SOKOBAN.CanPlayerMove(3) == 1)
		then
			moving = 1
			dir = "rt"
			turn(dir)
			oldFace = face
			face = SOKOBAN.CurrentFace()
			movesMade = movesMade + 1
			rotateCamera(face)
		end
	end
end

local function movePlayer(direction)
	local translate = Transform.GetPosition(transform)
	local z = Vec3.z(translate);
	local x = Vec3.x(translate);
	local y = Vec3.y(translate);
	
	if (direction == "up")
	then
		if (face == 0) then y = y-1 end
		if (face == 1) then y = y-1 end
		if (face == 2) then y = y-1 end
		if (face == 3) then y = y-1 end
		if (face == 4) then x = x+1 end
		if (face == 5) then x = x-1 end
	elseif (direction == "dn")
	then
		if (face == 0) then y = y+1 end
		if (face == 1) then y = y+1 end
		if (face == 2) then y = y+1 end
		if (face == 3) then y = y+1 end
		if (face == 4) then x = x-1 end
		if (face == 5) then x = x+1 end
	elseif (direction == "lf")
	then
		if (face == 0) then x = x-1 end
		if (face == 1) then z = z-1 end
		if (face == 2) then x = x+1 end
		if (face == 3) then z = z+1 end
		if (face == 4) then z = z-1 end
		if (face == 5) then z = z+1 end
	elseif (direction == "rt")
	then
		if (face == 0) then x = x+1 end
		if (face == 1) then z = z+1 end
		if (face == 2) then x = x-1 end
		if (face == 3) then z = z-1 end
		if (face == 4) then z = z+1 end
		if (face == 5) then z = z-1 end
	end
	
	if (oldFace ~= face)
	then
		if (oldFace == 0)
		then
			if(face == 3) then x = x-1 end
			if(face == 1) then x = x+1 end
			if(face == 4) then y = y+1 end
			if(face == 5) then y = y-1 end
		end
		if (oldFace == 1)
		then
			if(face == 0) then z = z-1 end
			if(face == 2) then z = z+1 end
			if(face == 4) then y = y+1 end
			if(face == 5) then y = y-1 end
		end
		if (oldFace == 2)
		then
			if(face == 1) then x = x+1 end
			if(face == 3) then x = x-1 end
			if(face == 4) then y = y+1 end
			if(face == 5) then y = y-1 end
		end
		if (oldFace == 3)
		then
			if(face == 2) then z = z+1 end
			if(face == 0) then z = z-1 end
			if(face == 4) then y = y+1 end
			if(face == 5) then y = y-1 end
		end
	end
	local nt = Vec3.Create(x, y, z)
	Transform.SetPosition(transform, nt)
end

function Update()
--If necessary check movement inputs
	if (reload == 1)
	then	
		this = Entity.Find("BLOCK1")
		transform = Entity.GetTransform( this )
		reload = 0
	end
	
	if (moving == 0) 
	then 
		handleKeys()
	elseif(moving == 32) 
	then 
		moving = 0 
	else 
		moving = moving + 1
		movePlayer(dir)
	end
end

function MOVE(direction)
	handleKeys(direction)
end

print ("Script: Loaded player controller")