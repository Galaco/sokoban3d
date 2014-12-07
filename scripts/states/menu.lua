-- game.lua
-- Initialize the main game state, where the actual Sokoban gameplay will take place
	State.Create("mainmenu")
	
--Set the states ambient light
	local dirLight = State.GetDirectionalLight("mainmenu")
	DirectionalLight.SetColor(dirLight, Vec3.Create(1, 1, 1))
	DirectionalLight.SetAmbience(dirLight, 1)
	DirectionalLight.SetDiffuse(dirLight, 1)

	State.RequestPriority("mainmenu")
	
	
	
-- Create the camera
	local camera = Camera.Create("defaultCamera")
	Camera.AddSkybox(camera, "skyboxes/black");
	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(0, 800, 0))
	Transform.SetOrientation(trans, Vec3.Create(80.11, 0, 0))
	--Camera.ToggleMouseControl(camera);
	Camera.SetTransform(camera, trans)
	State.AddCamera(camera, "mainmenu")
-- end



-- Create the background
	local e = Entity.Create("bg")
	local t = Transform.Create()	
	
	--Transform.SetScale(t, Vec3.Create(2, 1, 2))
	--Entity.SetTransform(e,t)
	
	local g = CGraphics.Create()
	CGraphics.AddModel(g, "shapes/quad.obj")
	CGraphics.AddTexture(g, "vgui/menubg.jpg")
	CGraphics.SetRenderMode(g, "RENDER_2D")
	
	Entity.AddComponent(e, g, "Graphics")
	State.AddEntity(e, "mainmenu")
	
	
	
--buttons
  --Classic button	
	local e = Entity.Create("classic")	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(-0.2,0,-0.5))
	Transform.SetScale(trans, Vec3.Create(0.15, 0.035, 1))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddModel(g, "shapes/quad.obj")
	CGraphics.AddTexture(g, "vgui/sample_button.jpg")
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	CScript.AddScript(script, "objects/menu/classic.lua")
	Entity.AddComponent(e, script, "LuaScript")
	State.AddEntity(e, "mainmenu")
	
  --Extended button	
	local e = Entity.Create("extended")	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(-0.2,-0.1,-0.5))
	Transform.SetScale(trans, Vec3.Create(0.15, 0.035, 1))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddModel(g, "shapes/quad.obj")
	CGraphics.AddTexture(g, "vgui/sample_button.jpg")
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	--local script = CScript.Create()
	--Entity.AddComponent(e, script, "LuaScript")
	--CScript.AddScript(script, "objects/menu/extended.lua")
	State.AddEntity(e, "mainmenu")
	
  --Exit button	
	local e = Entity.Create("quit")	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(-0.2,-0.2,-0.5))
	Transform.SetScale(trans, Vec3.Create(0.15, 0.035, 1))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddModel(g, "shapes/quad.obj")
	CGraphics.AddTexture(g, "vgui/sample_button.jpg")
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/exit.lua")
	State.AddEntity(e, "mainmenu")
	
	
	Mouse.Show()
	Mouse.Unlock()