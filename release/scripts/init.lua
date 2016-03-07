-- init.lua
-- Init.lua is the core script ran on execute. All Sokoban code and environment will be initialized in some form through this script
	local x = os.clock()
    print("Running setup script");
	
--initialize the main Sokoban script
	dofile("scripts/sokoban.lua")


   print(string.format("Total setup time: %.2f\n", os.clock() - x))
-- end