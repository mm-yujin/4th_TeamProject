function Damage(strength, type)
	if type == 0 then
		return strength * 1.1
	elseif type == 1 then
		return strength * 0.8
	else
		return strength * 1.3
	end
end
