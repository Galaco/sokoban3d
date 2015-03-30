m_runningTime = 0
loaded = 0
transform = nil

function Update()
	print("ho")
	if (loaded == 0)
	then
		transform = Entity.GetTransform(Entity.Find("splash"))
		loaded = 1
	end
	m_runningTime = m_runningTime + 1/60;
	if (m_runningTime < 2) 
	then
		if(m_runningTime > 1)
		then
			print("hello")
			--splash.GetTransform()->getOrientation().y += (90* 1/60);
		end
	end

	if (m_runningTime >= 4)
	then
		State.Deprioritise("Splash")
	end
end