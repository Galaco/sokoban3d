--Create the player object

function constructWall(x, z)
    local e = Entity.Create("wall")
	local trans = Transform.Create()	
	
	Transform.SetPosition(trans, Vec3.Create(32*x, 16, -(32*z)))		
	Transform.SetScale(trans, Vec3.Create(32, 32, 32))	
	Entity.SetTransform(e,trans)
	
	local graphics = CGraphics.Create()
	CGraphics.AddModel(graphics, "wall/wall.obj")
	CGraphics.AddTexture(graphics, "wall/wall.jpg")
	Entity.AddComponent(e, graphics, "Graphics")

	State.AddEntity(e, "game")
end