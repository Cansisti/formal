getmetatable("").__index = function(str,i)
  if type(i) == 'number' then
    return string.sub(str,i,i)
  else
    return string[i]
  end
end

function get_prefix_table(pattern)
  local m = #pattern
  local pi = {}
  pi[1] = 0
  local k = 0
  for q = 2, m do
    while k > 0 and pattern[k+1] ~= pattern[q] do
      k = pi[k]
    end
    if pattern[k+1] == pattern[q] then
      k = k + 1
    end
    pi[q] = k
  end
  return pi
end

function kmp_match(text, pattern)
  local n = #text
  local m = #pattern
  local pi = get_prefix_table(pattern)
  local q = 0
  for i = 1, n do
    while q > 0 and pattern[q+1] ~= text[i] do
      q = pi[q]
    end
    if pattern[q+1] == text[i] then
      q = q + 1
    end
    if q == m then
      return i - m
    end
  end
end

x = kmp_match("1111101", "01")
print(x)