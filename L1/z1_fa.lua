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
    q = delta[q][text:sub(i, i)]
    if q == m then
      return i-m
    end
  end
  return -1
end

x = fa_match("1111101", get_transition_table("01", "01"), 2)
print(x)