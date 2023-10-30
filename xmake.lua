set_project("jyyOS")

add_includedirs("include")
add_cflags("-O")
-- local subdir = {}
-- for _, dir in ipairs(os.dirs("$(scriptdir)/*")) do
--     if(os.isdir(dir) and dir:sub(1,1)~=".") then
--         table.insert(subdir, dir)
--     end
-- end
-- print(subdir)
includes("*/xmake.lua")