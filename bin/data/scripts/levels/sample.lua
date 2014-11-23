 -- Create a sample ground
    local e = Entity.Create("1")
	local trans = Transform.Create()	
	
	Transform.SetPosition(trans, Vec3.Create(0, 0, 0))	
	Transform.SetOrientation(trans, Vec3.Create(0, 0, 0))	
	Transform.SetScale(trans, Vec3.Create(512, 1, 512))
	Entity.SetTransform(e,trans)
	
	local graphics = CGraphics.Create()
	CGraphics.AddModel(graphics, "data/resource/model/shapes/plane.obj")
	CGraphics.AddTexture(graphics, "data/resource/materials/ground/white.jpg")
	
	Entity.AddComponent(e, graphics, "Graphics")
	State.AddEntity(e, "game")