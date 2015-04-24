-- game.lua
-- Initialize the main game state, where the actual Sokoban gameplay will take place
	State.Create("mainmenu", "")
	
	
--Set the states ambient light
	local dirLight = State.GetDirectionalLight("mainmenu")
	--dirLight:setColor(Vec3.Create(1, 1, 1))
	DirectionalLight.SetColor(dirLight, Vec3.Create(1, 1, 1))
	DirectionalLight.SetAmbience(dirLight, 1)
	DirectionalLight.SetDiffuse(dirLight, 1)

	State.RequestPriority("mainmenu")
	
-- Create the camera
	local camera = Camera.Create("defaultCamera")
	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(0, 800, 0))
	Transform.SetOrientation(trans, Vec3.Create(80.11, 0, 0))
	Camera.SetTransform(camera, trans)
	State.AddCamera(camera, "mainmenu")
-- end



-- Create the background
	local e = Entity.Create("bg")	
	local trans = Transform.Create()
	Transform.SetOrientation(trans, Vec3.Create(180,0,0))
	Entity.SetTransform(e,trans)
	
	local g = CGraphics.Create()
	CGraphics.AddModel(g, "shapes/quad.obj")
	CGraphics.AddMaterial(g, "vgui/menubg.mat")
	CGraphics.SetRenderMode(g, "RENDER_2D")
	
	Entity.AddComponent(e, g, "Graphics")
	State.AddEntity(e, "mainmenu")
	
-- Create the title	
	local e = Entity.Create("title")	
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.4,0.15,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	CGraphics.AddText(g, "3D|SOKOBAN", 18)
	Entity.AddComponent(e, g, "Graphics")
	State.AddEntity(e, "mainmenu")
	
  --Extended button	
	local e = Entity.Create("extended")	
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.39,0,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "[E]-Play", 10)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/extended.lua")
	State.AddEntity(e, "mainmenu")
	
  --Exit button	
	local e = Entity.Create("quit")
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.39,-0.15,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "[Q]-Quit", 10)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/exit.lua")
	State.AddEntity(e, "mainmenu")
	
	
	Mouse.Hide()
	Mouse.Unlock()
	
	
--Info bottom corner
	local e = Entity.Create("credits")
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(0.58,-0.95,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "Joshua Martin-2015", 5)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/exit.lua")
	State.AddEntity(e, "mainmenu")