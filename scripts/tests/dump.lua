function dump(lib, name, s)
	s = s or ''
	if name then
		print(s..name..':')
	end
	for key, value in pairs(lib) do
		if type(value) == 'table' then
			dump(value, key, s..'\t')
		else
			print(s..'\t'..key..': '..tostring(value))
		end
	end
end
