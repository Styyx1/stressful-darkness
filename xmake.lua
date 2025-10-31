-- set minimum xmake version
set_xmakever("2.8.2")

-- includes
includes("lib/commonlibsse")
includes("extern/styyx-utils/xmake.lua")

-- set project
set_project("stressful-darkness")
set_version("2.0.0")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_warnings("allextra")

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- set policies
--set_policy("build.optimization.lto", true)
set_policy("package.requires_lock", true)

-- set options
set_config("skyrim_ae", true)
set_config("commonlib_toml", true)

-- extra files
add_extrafiles("release/**.toml")

-- targets
target("stressful-darkness")
    -- add dependencies to target
    add_deps("commonlibsse")
    add_deps("styyx-util")
    -- add commonlibsse plugin
    add_rules("commonlibsse.plugin", {
        name = "stressful-darkness",
        author = "styyx",
        description = "darkness causes stress"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")
    add_extrafiles("contrib/**.toml", {public = true})

after_build(function(target)
    local copy = function(env, ext)
        for _, env in pairs(env:split(";")) do
            if os.exists(env) then
                local plugins = path.join(env, ext, "SKSE/Plugins")
                os.mkdir(plugins)
                os.trycp(target:targetfile(), plugins)
                os.trycp(target:symbolfile(), plugins)
                os.trycp("$(projectdir)/release/**.toml", plugins)
            end
        end
    end
    if os.getenv("XSE_TES5_MODS_PATH") then
        copy(os.getenv("XSE_TES5_MODS_PATH"), target:name())
    elseif os.getenv("XSE_TES5_GAME_PATH") then
        copy(os.getenv("XSE_TES5_GAME_PATH"), "Data")
    end
end)