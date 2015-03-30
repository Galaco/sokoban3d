-- extended.lua

--CREATE NECESSARY GLOBALS
movesMade = 0

-- Initialize the main 3d state
State.CreateSokoban("SOKOBAN", "scenes/sokoban.data")
	
State.RequestPriority("SOKOBAN")

local playerController = Entity.Create("PlayerController")
State.AddEntity(playerController, "SOKOBAN")
	
local script = CScript.Create()
Entity.AddComponent(playerController, script, "LuaScript")
CScript.AddScript(script, "objects/player/controller.lua")


dofile("scripts/interface/ui.lua")