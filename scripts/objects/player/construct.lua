--Create the player object
	local script = CScript.Create()
    local e = Entity.Create("player")
	local trans = Transform.Create()	
	
	Transform.SetPosition(trans, Vec3.Create(2, 0, 0))	
	Transform.SetOrientation(trans, Vec3.Create(90, 0, 0))	
	Transform.SetScale(trans, Vec3.Create(1, 1, 1))	
	Entity.SetTransform(e,trans)
	
	local graphics = CGraphics.Create()
	CGraphics.AddModel(graphics, "player/boblampclean.md5mesh")
	Entity.AddComponent(e, graphics, "Graphics")
	
	
	local animation = CAnimation.Create()
	CAnimation.AddAnimation(animation, "player/boblampclean.md5anim")
	Entity.AddComponent(e, animation, "Animation")

	State.AddEntity(e, "game")