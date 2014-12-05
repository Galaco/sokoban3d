function Update()
	if Mouse.Pressed("left")
	then 
		State.Deprioritise("mainmenu")
		dofile("scripts/states/game.lua")
		print("ran script game.lua")
	
		dofile("scripts/levels/main.lua")
		print("ran script main.lua")
	end
end