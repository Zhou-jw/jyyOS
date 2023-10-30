function all_tests()
    local res = {}
    for _, x in ipairs(os.files("*.c")) do
        local item = {}
        local s = path.filename(x)
        table.insert(item, s:sub(1, #s - 2))       -- target
        table.insert(item, path.relative(x, "."))  -- source
        table.insert(res, item)
    end
    return res
end

for _, test in ipairs(all_tests()) do
    -- print(test[2], "\n")
    target(string.format("5_%s",test[1]))
        set_kind("binary")
        add_files(test[2])
end
-- print(all_tests())