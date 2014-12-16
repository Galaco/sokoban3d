function Update()
	if Keyboard.KeyDown("e")
	then 
		State.Deprioritise("mainmenu")
		dofile("scripts/states/extended.lua")
	end
end