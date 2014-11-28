-- game.lua
-- Initialize the main game state, where the actual Sokoban gameplay will take place
	State.Create("game")
	
--Set the states ambient light
	local dirLight = State.GetDirectionalLight("game")
	DirectionalLight.SetColor(dirLight, Vec3.Create(0.9, 0.9, 0.9))
	DirectionalLight.SetAmbience(dirLight, 1)
	DirectionalLight.SetDiffuse(dirLight, 1)

	State.RequestPriority("game")
	
	
	
-- Create the camera
	local camera = Camera.Create("defaultCamera")
	Camera.AddSkybox(camera, "skyboxes/black");
	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(0, 800, 0))
	Transform.SetOrientation(trans, Vec3.Create(80.11, 0, 0))
	--Camera.ToggleMouseControl(camera);
	Camera.SetTransform(camera, trans);
	State.AddCamera(camera, "game")
-- end