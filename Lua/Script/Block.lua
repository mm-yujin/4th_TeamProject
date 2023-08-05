function Block(block, dex, level)
	return math.min((block * (dex -15) / (level * 2)), 0.75)
end