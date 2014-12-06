function Update()
	if Mouse.Pressed("left")
	then 
		State.Deprioritise("mainmenu")
		dofile("scripts/states/game.lua")
	
		dofile("scripts/levels/main.lua")
	end
end