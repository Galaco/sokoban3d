--ui.lua

--Create Variables
local savedMovesMade = 0
local loaded = 0
graphics = nil
	
function Update()
	if (loaded == 0)
	then
		graphics = Entity.GetComponent(Entity.Find("MOVESTAKEN"), "Graphics")
		loaded = 1
	end
	
	if (savedMovesMade ~= movesMade)
	then	
		CGraphics.AddText(graphics, "Moves Taken: " .. tostring(movesMade), 8)	
		savedMovesMade = movesMade
	end
end

print ("Script: Loaded movement logging script")