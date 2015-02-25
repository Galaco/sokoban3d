-- extended.lua
-- Initialize the main 3d state
	State.CreateSokoban("SOKOBAN")
	
--Set the states ambient light
	local dirLight = State.GetDirectionalLight("SOKOBAN")
	DirectionalLight.SetColor(dirLight, Vec3.Create(1, 1, 1))
	DirectionalLight.SetAmbience(dirLight, 1)
	DirectionalLight.SetDiffuse(dirLight, 0.2)

	State.RequestPriority("SOKOBAN")
	
	
	
-- Create the camera
	local camera = Camera.Create("extendedCamera")
	State.AddCamera(camera, "SOKOBAN")
	
	Mouse.Lock()
	--Camera.ToggleMouseControl(camera);
	Camera.AddSkybox(camera, "skyboxes/ambient_sky/clouds");
	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(0, 500, 0))
	Transform.SetOrientation(trans, Vec3.Create(80.11, 0, 0))
	Camera.SetTransform(camera, trans);
	
	local script = CScript.Create()
	Entity.AddComponent(camera, script, "LuaScript")
	CScript.AddScript(script, "objects/camera/controller.lua")
	
-- end