-- game.lua
-- Initialize the main game state, where the actual Sokoban gameplay will take place
	State.Create("mainmenu")
	
--Set the states ambient light
	local dirLight = State.GetDirectionalLight("mainmenu")
	print(dirLight)
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
	CGraphics.AddText(g, "3D|SOKOBAN", 14)
	Entity.AddComponent(e, g, "Graphics")
	State.AddEntity(e, "mainmenu")
	
	
--buttons
  --Classic button	
	local e = Entity.Create("classic")	
	State.AddEntity(e, "mainmenu")
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.35,0,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	CGraphics.AddText(g, "Play Classic", 6)
	Entity.AddComponent(e, g, "Graphics")
	--e:AddComponent(g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/classic.lua")
	
	local col = CCollision.Create()
	Entity.AddComponent(e, col, "Collision")
	CCollision.BuildCollisionMesh(col)
	
	local sel = CSelectable.Create()
	Entity.AddComponent(e, sel, "Selectable")
	
  --Extended button	
	local e = Entity.Create("extended")	
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.35,-0.1,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "Play Extended", 6)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/extended.lua")
	State.AddEntity(e, "mainmenu")
	
  --Options button
	local e = Entity.Create("options")	
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.35,-0.2,-0.5))
	Entity.SetTransform(e,trans)
	local g = CGraphics.Create()
	CGraphics.AddText(g, "Options", 6)
	CGraphics.SetRenderMode(g, "RENDER_2D")
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/options.lua")
	State.AddEntity(e, "mainmenu")
	
  --Exit button	
	local e = Entity.Create("quit")
	local trans = Transform.Create()
	Transform.SetPosition(trans, Vec3.Create(-0.35,-0.3,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.Create()
	CGraphics.AddText(g, "Quit", 6)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/exit.lua")
	State.AddEntity(e, "mainmenu")
	
	
	Mouse.Show()
	Mouse.Unlock()