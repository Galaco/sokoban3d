--Create the player object
    local e = Entity.Create("player")
	local trans = Transform.Create()	
	
	Transform.SetPosition(trans, Vec3.Create(2, 0, 0))	
	Transform.SetOrientation(trans, Vec3.Create(90, 0, 0))	
	Transform.SetScale(trans, Vec3.Create(1, 1, 1))	
	Entity.SetTransform(e,trans)
	
	local graphics = CGraphics.Create()
	CGraphics.AddModel(graphics, "player/boblampclean.md5mesh")
	Entity.AddComponent(e, graphics, "Graphics")
	
	
	--local animation = CAnimation.Create()
	--CAnimation.AddAnimation(animation, "player/boblampclean.md5anim")
	--Entity.AddComponent(e, animation, "Animation")
	
	local script = CScript.Create()
	Entity.AddComponent(e, script, "LuaScript")
	CScript.AddScript(script, "objects/player/controller.lua")

	State.AddEntity(e, "game")