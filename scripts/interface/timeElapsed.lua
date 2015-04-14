--ui.lua

--Create Variables
local loaded = 0
local elapsed = 0
graphics = nil
	
function Update()
	if (loaded == 0)
	then
		graphics = Entity.GetComponent(Entity.Find("TIMETAKEN"), "Graphics")
		loaded = 1
	end
	
	local newTime = SOKOBAN.ElapsedTime()
	
	if (elapsed ~= newTime)
	then
		CGraphics.AddText(graphics, "Time Elapsed: " .. tostring(newTime), 8)
		elapsed = newTime
	end
end

print ("Script: Loaded movement logging")