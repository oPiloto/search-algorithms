local math = require("math")
local socket = require("socket")

local function seq_search(vector, key)
    for i, value in ipairs(vector) do
        if value == key then
            return i
        end
    end
    return nil
end

local function binary_search(vector, key)
    local start = 0
    local end_table = #vector

    while start <= end_table do
        local middle = (start + end_table) // 2

        if vector[middle] == key then
            return middle
        elseif vector[middle] < key then
            start = middle + 1
        else
            end_table = middle - 1
        end
    end

    return nil
end

local function def_search(key, vector, algorithm)
    print(string.format("Looking for %d...", key))

    local start = socket.gettime()
    local index = algorithm(vector, key)
    if index then
        print(string.format("Number: %d found at position: %d", key, index))
    else
        print("Number not found.")
    end
    local duration = (socket.gettime() - start) * 1000
    print(string.format("Duration of execution: %.3f microseconds or %.3f ms\n", duration * 1000, duration))
    return duration * 1000
end

local list = { 10000, 100000, 1000000, 10000000, 100000000 }

local results_seq = {}
local results_bin = {}
local sort_time = {}

for i = 1, #list do
    results_seq[i] = {}
    results_bin[i] = {}
end

for n, num in ipairs(list) do
    local vector = {}
    for _ = 1, num do
        table.insert(vector, math.random(1, num))
    end

    -- Sequential
    print("Sequential Search:")
    for i = 1, 5 do
        print(string.format("Sequencial search number %d with %d values:", i, num))
        local key = math.random(1, num)

        table.insert(results_seq[n], def_search(key, vector, seq_search))
    end

    -- Time taken to sort the vector
    print("Sorting the vector for binary search...")
    local start = socket.gettime()
    table.sort(vector)
    local duration = (socket.gettime() - start) * 1000
    print(string.format("Duration of execution: %.3f microseconds or %.3f ms\n", duration * 1000, duration))
    table.insert(sort_time, duration)

    -- Binary
    print("Binary Search:")
    for i = 1, 5 do
        print(string.format("Binary search number %d with %d values:", i, num))
        local key = math.random(1, num)

        table.insert(results_bin[n], def_search(key, vector, binary_search))
    end
end

print("\n\nEnd of execution\nSequential search time:")
for i, num in ipairs(list) do
    io.write(string.format("\nList %s:", num))
    local add = 0
    for _, ele in ipairs(results_seq[i]) do
        io.write(string.format(" %.0fmicros", ele))
        add = add + ele
    end
    io.write(string.format(" | Average time: %.0fmicros", add / #list))
end

print("\n\nBinary search time:")
for i, num in ipairs(list) do
    io.write(string.format("\nList %s:", num))
    local add = 0
    for _, ele in ipairs(results_bin[i]) do
        io.write(string.format(" %.0fmicros", ele))
        add = add + ele
    end
    io.write(string.format(" | Time taken to sort the vector: %.0fms", sort_time[i]))
    io.write(string.format(" | Average time: %.0fmicros", add / #list))
end
print("\n")
