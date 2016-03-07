function Update()	
	if Keyboard.KeyDown("E")
	then
		State.Deprioritise("mainmenu")
		dofile("scripts/states/extended.lua")
	end
end