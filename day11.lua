local counts = {["5"] = 1, ["89749"] = 1, ["6061"] = 1, ["43"] = 1, ["867"] = 1, ["1965860"] = 1, ["0"] = 1, ["206250"] = 1}

for i = 1, 75 do
	local new_counts = {}
	for stone_value, count in counts do
		if stone_value == '0' then
			-- Rule 1
			if not new_counts['1'] then new_counts['1'] = 0 end
			new_counts['1'] += count
		elseif string.len(stone_value) % 2 == 0 then
			-- Rule 2
			local len = string.len(stone_value)
			local left = tostring(tonumber(string.sub(stone_value, 1, len/2)))
			local right = tostring(tonumber(string.sub(stone_value, len/2+1)))
			if not new_counts[left] then new_counts[left] = 0 end
			new_counts[left] += count
			if not new_counts[right] then new_counts[right] = 0 end
			new_counts[right] += count	
		else
			if not new_counts[tostring(2024 * tonumber(stone_value))] then new_counts[tostring(2024 * tonumber(stone_value))] = 0 end
			new_counts[tostring(2024 * tonumber(stone_value))] += count
		end
	end
	counts = new_counts
end

local total = 0
for _, c in counts do
	total += c
end

print(total)