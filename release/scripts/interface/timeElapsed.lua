--timeElapsed.lua

--Create Variables
local loaded = 0
local elapsed = 0
graphics = nil
entity = nil
	
function Update()
	if (loaded == 0)
	then
		entity = Entity.Find("TIMETAKEN")
		graphics = Entity.GetComponent(entity, "Graphics")
		loaded = 1
	end
	
	local newTime = SOKOBAN.ElapsedTime()
	
	if (elapsed ~= newTime)
	then
		CGraphics.AddText(graphics, "Time Elapsed: " .. tostring(newTime) .. "s", 8)
		elapsed = newTime
	end
end

print ("Script: Loaded movement logging")