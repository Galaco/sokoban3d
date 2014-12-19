function Update()
	if Mouse.Pressed("right")
	then 
		State.Deprioritise("mainmenu")
		dofile("scripts/states/game.lua")
	
		dofile("scripts/levels/main.lua")
	end
end