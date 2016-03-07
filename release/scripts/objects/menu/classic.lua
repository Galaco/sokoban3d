function Update()
	if Keyboard.KeyDown("C")
	then
		State.Deprioritise("mainmenu")
		dofile("scripts/states/game.lua")
		
		dofile("scripts/levels/main.lua")
	end
end