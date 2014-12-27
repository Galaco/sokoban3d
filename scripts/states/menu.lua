-- game.lua
-- Initialize the main game state, where the actual Sokoban gameplay will take place

	State.new("mainmenu")
	
--Set the states ambient light
	local dirLight = State.GetDirectionalLight("mainmenu")
	dirLight:SetColor(Vec3.new(1, 1, 1))
	dirLight:SetAmbience(1)
	dirLight:SetDiffuse(1)

	State.RequestPriority("mainmenu")
	
	
	
-- Create the camera
	local camera = Camera.new("defaultCamera")
	local trans = Transform.new()
	trans:SetPosition(Vec3.new(0, 800, 0))
	trans:SetOrientation(Vec3.new(80.11, 0, 0))
	camera:SetTransform(trans)
	State.AddCamera(camera, "mainmenu")
-- end



-- Create the background
	local e = Entity.new("bg")
	
	local g = CGraphics.new()
	g:AddModel("shapes/quad.obj")
	g:AddMaterial("vgui/menubg.mat")
	g:SetRenderMode("RENDER_2D")
	
	e:AddComponent(g, "Graphics")
	State.AddEntity(e, "mainmenu")
	
	--[[
-- Create the title	
	local e = Entity.new("title")	
	local trans = Transform.new()
	trans:SetPosition(Vec3.new(-0.4,0.15,-0.5))
	e:SetTransform(trans)	
	local g = CGraphics.new()
	g:SetRenderMode("RENDER_2D")	
	g:AddText("3D|SOKOBAN", 14)
	e:AddComponent(g, "Graphics")
	State.AddEntity(e, "mainmenu")
	
	
--buttons
  --Classic button	
	local e = Entity.new("classic")	
	State.AddEntity(e, "mainmenu")
	local trans = Transform.new()
	Transform.SetPosition(trans, Vec3.new(-0.35,0,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.new()
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	CGraphics.AddText(g, "Play Classic", 6)
	Entity.AddComponent(e, g, "Graphics")
	--e:AddComponent(g, "Graphics")
	local script = CScript.new()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/classic.lua")
	
	local col = CCollision.new()
	Entity.AddComponent(e, col, "Collision")
	CCollision.BuildCollisionMesh(col)
	
	local sel = CSelectable.new()
	Entity.AddComponent(e, sel, "Selectable")
	
  --Extended button	
	local e = Entity.new("extended")	
	local trans = Transform.new()
	Transform.SetPosition(trans, Vec3.new(-0.35,-0.1,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.new()
	CGraphics.AddText(g, "Play Extended", 6)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.new()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/extended.lua")
	State.AddEntity(e, "mainmenu")
	
  --Options button
	local e = Entity.new("options")	
	local trans = Transform.new()
	Transform.SetPosition(trans, Vec3.new(-0.35,-0.2,-0.5))
	Entity.SetTransform(e,trans)
	local g = CGraphics.new()
	CGraphics.AddText(g, "Options", 6)
	CGraphics.SetRenderMode(g, "RENDER_2D")
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.new()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/options.lua")
	State.AddEntity(e, "mainmenu")
	
  --Exit button	
	local e = Entity.new("quit")
	local trans = Transform.new()
	Transform.SetPosition(trans, Vec3.new(-0.35,-0.3,-0.5))
	Entity.SetTransform(e,trans)	
	local g = CGraphics.new()
	CGraphics.AddText(g, "Quit", 6)
	CGraphics.SetRenderMode(g, "RENDER_2D")	
	Entity.AddComponent(e, g, "Graphics")
	local script = CScript.new()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/menu/exit.lua")
	State.AddEntity(e, "mainmenu")
	
	
	Mouse.Show()
	Mouse.Unlock()]]--