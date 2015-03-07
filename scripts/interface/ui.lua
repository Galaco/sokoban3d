--ui.lua

--Create Variables
movesMade = 0
currentLevel = 1




--Current Level
	local e = Entity.Create("CURRENTLEVEL")	
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.95,0.9,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "Current level: " .. tostring(currentLevel), 10)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	State.AddEntity(e, "SOKOBAN")

--Create Moves count object
	local e = Entity.Create("MOVESTAKEN")	
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.95,0.72,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "Moves Taken: " .. tostring(movesMade), 8)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	State.AddEntity(e, "SOKOBAN")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "interface/currentMoves.lua")
	
--Time taken
	local e = Entity.Create("TIMETAKEN")	
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.95,0.8,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "Time Elapsed: ", 8)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	State.AddEntity(e, "SOKOBAN")