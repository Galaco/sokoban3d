function Update()
	if Mouse.Pressed("left")
	then 
		dofile("scripts/states/game.lua")
		dofile("scripts/levels/main.lua")
	end
end