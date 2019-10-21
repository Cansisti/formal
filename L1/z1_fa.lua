getmetatable("").__index = function(str,i)
  if type(i) == 'number' then
    return string.sub(str,i,i)
  else
    return string[i]
  end
end

function get_transition_table(pattern, alphabet)
  local m = #pattern
  local d = {}
  for q = 0, m do
    d[q] = {}
    for a in alphabet:gmatch(".") do
      local k = math.min(m + 1, q + 2)
      repeat
        k = k - 1
      until (pattern:sub(1,k) == pattern:sub(1,q)..a) or (k == 0)
      d[q][a] = k
    end
  end
  return d
end

function fa_match(text, delta, m)
  local n = #text
  local q = 0
  for i = 1, n do
    q = delta[q][text[i]]
    if q == m then
      return i - m
    end
  end
  return -1
end

function fa_helper(text, pattern, alphabet)
  return fa_match(text, get_transition_table(pattern, alphabet), #pattern)
end

function fa_match_all(text, pattern, alphabet)
  local results = {}
  local p = 1
  while true do
    local f = fa_helper(text:sub(p), pattern, alphabet)
    if f >= 0 then
      table.insert(results, p+f-1)
      p = p + f + #pattern
    else
      break
    end
  end
  return results
end

x = fa_match_all("αβαβγβαβαβαβαβγ", "αβ", "αβγδ")
for k, v in pairs(x) do print(v) end
