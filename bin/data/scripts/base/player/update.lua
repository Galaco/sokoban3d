function Update()
	if(Keyboard.KeyDown("w")) 
	then 
		local e = Entity.Find("player")
		local transform = Entity.GetTransform( e )
		local translate = Transform.GetPosition(transform)
		local x = Vec3.x(translate);
		local y = Vec3.y(translate);
		local z = Vec3.z(translate)-1;
		local nt = Vec3.Create(x, y, z)
		
		Transform.SetPosition(transform, nt)
	elseif(Keyboard.KeyDown("a")) 
	then
		local e = Entity.Find("player")
		local transform = Entity.GetTransform( e )
		local translate = Transform.GetPosition(transform)
		local x = Vec3.x(translate)-1;
		local y = Vec3.y(translate);
		local z = Vec3.z(translate);
		local nt = Vec3.Create(x, y, z)
		
		Transform.SetPosition(transform, nt)
	elseif(Keyboard.KeyDown("s")) 
	then
		local e = Entity.Find("player")
		local transform = Entity.GetTransform( e )
		local translate = Transform.GetPosition(transform)
		local x = Vec3.x(translate);
		local y = Vec3.y(translate);
		local z = Vec3.z(translate)+1;
		local nt = Vec3.Create(x, y, z)
		
		Transform.SetPosition(transform, nt)
	elseif(Keyboard.KeyDown("d")) 
	then
		local e = Entity.Find("player")
		local transform = Entity.GetTransform( e )
		local translate = Transform.GetPosition(transform)
		local x = Vec3.x(translate)+1;
		local y = Vec3.y(translate);
		local z = Vec3.z(translate);
		local nt = Vec3.Create(x, y, z)
		
		Transform.SetPosition(transform, nt)
	end
end