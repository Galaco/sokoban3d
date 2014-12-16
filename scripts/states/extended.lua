-- extended.lua
-- Initialize the main 3d state
	State.Create("extended")
	
--Set the states ambient light
	local dirLight = State.GetDirectionalLight("extended")
	DirectionalLight.SetColor(dirLight, Vec3.Create(1, 1, 1))
	DirectionalLight.SetAmbience(dirLight, 1)
	DirectionalLight.SetDiffuse(dirLight, 1)

	State.RequestPriority("extended")
	
	
	
-- Create the camera
	local camera = Camera.Create("extendedCamera")
	
	local trans = Transform.Create();
	Transform.SetPosition(trans, Vec3.Create(0, 500, 0))
	Transform.SetOrientation(trans, Vec3.Create(80.11, 0, 0))
	Camera.SetTransform(camera, trans);
	
	--Camera.ToggleMouseControl(camera);
	Camera.AddSkybox(camera, "skyboxes/ambient_sky/clouds");
	
	--local script = CScript.Create()
	--Entity.AddComponent(camera, script, "LuaScript")
	--CScript.AddScript(script, "objects/camera/controller.lua")
	
	State.AddCamera(camera, "extended")
-- end